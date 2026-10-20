# ctrboot

Source for the Nintendo 3DS boot ROMs, boot9 and boot11, rebuilt with the original compiler to the original code.

| | ROM | Runs on | Matching |
|---|---|---|---|
| `boot9` | boot9 | ARM9 | 486 / 589 |
| `boot11` | boot11 | ARM11 | 212 / 287 |

The function counts come from a first static analysis and will move as function boundaries are fixed.

No ROM is included, nor anything from one: the keys and the rest of the data come from your own dumps when you build. See [BUILDING.md](BUILDING.md).

## License

CC0 1.0. It covers what the contributors wrote; the ROMs themselves are Nintendo's and are not included.
