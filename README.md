# AGH RPG Game

AGH RPG Game is a simple 2D retro-inspired RPG created using C++ and the SFML library. The game showcases a tile-based map and basic player movement mechanics.

## Features
- **Tilemap Rendering**: The game uses a grid-based tilemap system, allowing for easy creation and customization of game levels.
- **Basic Player Movement**: Players can move within the boundaries of the map using the keyboard.
- **SFML Integration**: The game leverages SFML for rendering, handling input, and managing game assets.

## Installation and Compilation

### Prerequisites
- **SFML**: Ensure you have SFML installed. You can install it using your package manager or from [SFML's official site](https://www.sfml-dev.org/).
- **C++ Compiler**: You need a C++ compiler like `g++`.

### Compilation
A ZSH script `run.zsh` is provided for compiling and running the game.

1. Open a terminal and navigate to the project's root directory.
2. Run the script with the following command:

    ```bash
    ./run.zsh
    ```

### Manual Compilation
You can also compile the game manually using:

```bash
g++ -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

Then, run the game using:

```bash
./main
```

## Controls
- **Arrow Keys**: Move the player character up, down, left, or right.

## Directory Structure
```
├── main.cpp          # Main game logic
├── run.zsh           # Compilation and execution script
├── textures/         # Game assets (tileset and player textures)
├── fonts/            # Fonts for future text rendering
└── .vscode/          # VSCode configuration files
```

## Future Features (Planned)
- Add more game levels and enemies.
- Implement additional player actions and an inventory system.
- Introduce combat mechanics and health points.

---

Feel free to contribute by submitting pull requests or suggesting improvements!
