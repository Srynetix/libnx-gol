# Game of Life for Nintendo Switch (using libnx)

## Build for Switch w/ Docker

```bash
# Clean if needed
docker run -ti --rm -v ${PWD}:/src yuzu-emu/switch-dev-env make -f Makefile.switch clean

# Make
docker run -ti --rm -v ${PWD}:/src yuzu-emu/switch-dev-env make -f Makefile.switch
```

Output file will be `gol.nso`

## Build for Linux (using SDL2)

```bash
# Clean if needed
make -f Makefile.pc clean

# Make
make -f Makefile.pc
```

Output file will be `gol`

## How to play

- `L`: Pause game
- `R`: Resume game
- `A`: Randomize cells
- `X`: Clear screen
- `Y`: Speed up x5
- `+`: Quit game

- Press touch screen to revive cells.
