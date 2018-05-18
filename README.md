# Game of Life for Nintendo Switch (using libnx)

## Quick start w/ Docker

```bash
# Clean if needed
docker run -ti --rm -v ${PWD}:/src yuzu-emu/switch-dev-env make clean

# Make
docker run -ti --rm -v ${PWD}:/src yuzu-emu/switch-dev-env make
```

Output file will be `gol/gol.nso`

## How to play

- `L`: Pause game
- `R`: Resume game
- `A`: Randomize cells
- `+`: Quit game

- Press touch screen to revive cells.