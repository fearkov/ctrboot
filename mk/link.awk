# Splits a program into the pieces armlink places: the functions that have
# source, and the gaps between them, whose bytes come from your image.
#
#   awk -v out=scatter -f mk/link.awk <program>.layout <program>.functions
#
# out=scatter    the scatter file: a load region per part of the layout
# out=gaps       one line per gap: address, offset in the image, size
# out=symdefs    every function as FUN_<address>, so that code can call any of
#                them, with source or not, as extern "C" FUN_<address>
# out=placement  with the linker's map as a third file: the functions that did
#                not land at their address
# out=where      with the output of cmp -l as a third file: where the first
#                differences are
#
# armlink starts an execution region only at a multiple of 4, so a region
# starts at every piece that starts at one. A Thumb function at 2 past a
# multiple of 4 joins the region before it: gaps are cut at multiples of 4 so
# that a region holds at most a gap first, then functions, then a gap last.
# The functions between are placed in armlink's default order, by name, which
# is also the order armcc writes them in.

function hex(s,    n, c) {
    n = 0
    s = toupper(s)
    for (c = 1; c <= length(s); c++)
        n = n * 16 + index("0123456789ABCDEF", substr(s, c, 1)) - 1
    return n
}

# printf's %X is not safe above 2^31 in every awk
function tohex(n,    s, c, digit) {
    s = ""
    for (c = 0; c < 8; c++) {
        digit = n % 16
        s = substr("0123456789ABCDEF", digit + 1, 1) s
        n = (n - digit) / 16
    }
    return s
}

function add(kind, from, bytes, symbol) {
    pieces++
    kind_[pieces] = kind
    at_[pieces] = from
    bytes_[pieces] = bytes
    name_[pieces] = symbol
}

# a gap, cut at the multiples of 4 next to its ends
function add_gap(from, to,    a, b) {
    a = from % 4 ? from + 4 - from % 4 : from
    if (a > to)
        a = to
    b = to - to % 4
    if (b < a)
        b = a
    if (a > from)
        add("gap", from, a - from)
    if (b > a)
        add("gap", a, b - a)
    if (to > b)
        add("gap", b, to - b)
}

function selector(piece) {
    return kind_[piece] == "gap" ? "gap." tohex(at_[piece]) : "i." name_[piece]
}

FNR == 1 { file++ }
/^#/ || NF == 0 { next }
file == 1 { part[++parts] = $1; base[parts] = hex($2); offset[parts] = hex($3); size[parts] = hex($4); next }
file == 2 { address[++functions] = hex($1); length_[functions] = $2; state[functions] = $3; name[functions] = $4; next }
file == 3 && out == "where" { differing[++differences] = $1; next }
file == 3 && out == "placement" && $(NF - 1) ~ /^i\./ { placed[substr($(NF - 1), 3)] = toupper(substr($1, 3)); next }

END {
    if (out == "symdefs") {
        print "#<SYMDEFS># ctrboot: every function as FUN_<address>"
        for (i = 1; i <= functions; i++)
            printf "0x%s %s FUN_%s\n", tohex(address[i]), state[i] == "thumb" ? "T" : "A", tohex(address[i])
        exit
    }
    if (out == "placement") {
        wrong = 0
        for (i = 1; i <= functions; i++)
            if (name[i] !~ /^FUN_/ && placed[name[i]] != tohex(address[i])) {
                printf "  %s is at 0x%s, the list says 0x%s\n", name[i], placed[name[i]], tohex(address[i])
                wrong++
            }
        exit wrong ? 1 : 0
    }
    if (out == "where") {
        for (d = 1; d <= differences && d <= 8; d++) {
            at = differing[d] - 1
            for (r = 1; r < parts && !(offset[r] <= at && at < offset[r] + size[r]); r++)
                ;
            va = base[r] + at - offset[r]
            inside = ""
            for (i = 1; i <= functions; i++)
                if (address[i] <= va && va < address[i] + length_[i])
                    inside = sprintf(", %s+0x%X", name[i], va - address[i])
            printf "  0x%s%s\n", tohex(va), inside
        }
        if (differences > 8)
            printf "  and %d more bytes\n", differences - 8
        exit
    }
    for (r = 1; r <= parts; r++) {
        start = base[r]
        end = base[r] + size[r]
        pieces = 0
        at = start
        for (i = 1; i <= functions; i++) {
            if (name[i] ~ /^FUN_/ || address[i] < start || address[i] >= end)
                continue
            if (address[i] > at)
                add_gap(at, address[i])
            add("function", address[i], length_[i], name[i])
            at = address[i] + length_[i]
        }
        if (at < end)
            add_gap(at, end)
        if (out == "gaps") {
            for (p = 1; p <= pieces; p++)
                if (kind_[p] == "gap")
                    printf "%s %d %d\n", tohex(at_[p]), offset[r] + at_[p] - start, bytes_[p]
            continue
        }
        printf "LR_%s 0x%s {\n", part[r], tohex(start)
        for (p = 1; p <= pieces; p = q) {
            for (q = p + 1; q <= pieces && at_[q] % 4; q++)
                ;
            printf "  %s 0x%s FIXED {\n", p == 1 ? part[r] : "E_" tohex(at_[p]), tohex(at_[p])
            for (k = p; k < q; k++) {
                order = ""
                if (q - p > 1 && kind_[k] == "gap")
                    order = k == p ? ", +FIRST" : ", +LAST"
                printf "    * (%s%s)\n", selector(k), order
            }
            print "  }"
        }
        print "}"
    }
    # anything the sources define that is not in the list goes here, outside the image
    if (out == "scatter")
        print "LR_unplaced 0x40000000 {\n  unplaced +0 { .ANY (+RO, +RW, +ZI) }\n}"
}
