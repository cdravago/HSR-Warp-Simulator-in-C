# HSR Warp Simulator

A small, terminal-based warp simulator written in C and inspired by the warp system in *Honkai: Star Rail*. This project was created as part of my first-year Computer Engineering coursework and serves as a practical exercise in structs, enums, functions, input handling, and probability-based simulation.

> This is an unofficial fan project. It is not affiliated with or endorsed by HoYoverse.

## Features

- Check the current Stellar Jade balance and pity counters.
- Deposit Stellar Jades for simulated pulls.
- Perform single pulls or ten-pulls.
- Simulate 3-star, 4-star, and 5-star results.
- Apply a 1% base 5-star chance with soft pity beginning at pull 75.
- Guarantee a 5-star by pull 90 and a 4-star by pull 10.
- Use a small cross-platform delay abstraction for Windows and POSIX-like systems.
- Reject invalid menu input without terminating the program.

## Pull Costs and Pity

| Action | Cost | Result behavior |
| --- | ---: | --- |
| Single pull | 160 Stellar Jades | Simulates one result |
| Ten-pull | 1,600 Stellar Jades | Simulates ten consecutive results |
| 5-star pity | - | Soft pity starts at pull 75; hard pity occurs at pull 90 |
| 4-star pity | - | A 4-star or higher is guaranteed within ten pulls |

The simulator is intended for experimentation and entertainment. Its probabilities and mechanics are an approximation implemented for this project, not a representation of live-game rates.

## Requirements

- A C compiler such as GCC or Clang
- A terminal or command prompt

## Build and Run

From the project directory, compile the program with:

```bash
gcc warpSim.c -o warpSim
```

Run it on macOS or Linux with:

```bash
./warpSim
```

On Windows with MinGW, run:

```powershell
gcc warpSim.c -o warpSim.exe
.\warpSim.exe
```

## Menu

When the program starts, choose from:

1. Check Stellar Jades
2. Deposit Jades
3. Warp once
4. Warp ten times
5. Exit

## Project Files

- `warpSim.c` - Current C implementation of the simulator.
- `warpSim_changes.txt` - Earlier implementation snapshot retained as project history.
- `warpSim.exe` - Windows executable included in the repository.

## Learning Goals

This project focuses on practicing:

- Structs for player state
- Enums for pull results
- Modular function design
- Random number generation
- Pity-counter state management
- Basic console input validation
