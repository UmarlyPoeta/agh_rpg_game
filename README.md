# AGH RPG Game

## Project Description
AGH RPG Game is a role-playing game set in the AGH campus, where the player explores the environment, battles opponents, and makes decisions that influence the storyline. The game is written in C++ and uses the SFML library for graphics and interaction handling.

## Requirements
To run the project, you need:
- A compiler supporting C++17 (e.g., g++ or clang++)
- **SFML 2.5+** (Simple and Fast Multimedia Library)
- **CMake** for build management

## Installation
### 1. Installing SFML
#### Ubuntu / Debian
```sh
sudo apt update
sudo apt install libsfml-dev
```
#### Arch Linux
```sh
sudo pacman -S sfml
```
#### Windows
Download and install SFML from the [official website](https://www.sfml-dev.org/download.php).

### 2. Cloning the repository
```sh
git clone https://github.com/username/agh_rpg_game.git
cd agh_rpg_game
```

### 3. Building and Running
```sh
mkdir build
cd build
cmake ..
make
./agh_rpg_game
```

## Project Structure
```
agh_rpg_game/
├── assets/       # Graphic files (characters, maps, UI)
├── include/      # C++ header files
├── src/          # Class implementations
├── CMakeLists.txt # CMake configuration file
├── README.md      # Project documentation
```

## Game Mechanics
- The player explores the AGH map and interacts with NPCs
- Battles follow a turn-based combat system
- Enemies represent different characters related to student life
- The player can win or lose depending on their choices

## Authors
- **Patryk Kozłowski**
- **Kamil Kobusz**
- **Mikołaj Kołodziejczyk**

## License
This project is available under the MIT License.

