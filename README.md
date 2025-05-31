# Snake Game Project

This project is a **work in progress** aimed at building out core game engine modules while leveraging the capabilities of **raylib** for rendering, window management, and input handling. The ultimate goal is to create a modular, extensible game engine that powers the game "Snake" and act as the foundation for other future games.

---

## Features (So Far)

- **Core Modules**:
    - Provides essential interfaces such as `IGameState` and `IStateMachine` to manage game states and transitions in a modular way.
- **Rendering**:
    - Utilizes **raylib** for rendering 2D graphics and managing window operations.
- **Input Handling**:
    - Supports an input abstraction framework through `InputManager`, utilizing raylib's input backend.
- **Game-Specific Implementation**:
    - Includes game-specific UI components such as `MainMenuUI` and the game state logic built on top of the `IGameState` core module.
- **Decoupled Design**:
    - Cleanly separates engine functionality (`Core`) from game-specific implementations (`Game` namespace).

---

## Current Structure

The project is divided into several modules, highlighting its modular design:

1. **Core Module**:
    - Contains reusable interfaces and abstractions for managing game logic.
    - Interfaces include `IGameState` (for states) and `IStateMachine` (for managing state transitions).

2. **Platform Module**:
    - Handles platform-related functionality such as input, windowing, and configuration of the game environment.
    - **raylib** is integrated here as the foundational library for rendering and input.

3. **Game Module**:
    - Implements game-specific functionality such as:
        - Gameplay State handling with `GameplayStateMachine`
        - `Snake` and `Apple` Entities that make up the core gameplay functionality

4. **Raylib Module**:
    - Adapts raylib functionality into classes and abstractions used throughout the project.

4. **Engine Module**:
    - Holds the Application class and initial setup related functionality
     
4. **Renderer-2D Module**:
    - Contains 2D Render Components that handle drawing
    - Acts as an abstraction layer
---

## Prerequisites

To build and run the project, you need the following installed on your system:

- **C++ Compiler**:
    - GCC/Clang on Linux
    - Apple Clang on macOS
    - MSVC on Windows
- **CMake** (minimum version 3.20):
    - For build configuration.
- **raylib** (latest version):
    - The project currently leverages raylib for rendering, windowing, and input handling. Ensure that raylib is both installed and accessible for the build process.

---

## How to Build and Run

### Step 1: Clone the Repository

```bash
bash git clone https://github.com/DeanWilsonDev/snake/tree/game-with-engine-architecture && cd snake
```

### Step 2: Build the Project
1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
2. Configure the build with CMake:
   ```bash
   cmake ..
   ```
3. Build the project:
   ```bash
   cmake --build .
   ```

### Step 3: Run the Project
Once built, you can run the generated executable (e.g., `Snake`) from the `build` directory:


---

## Work in Progress

This project is still under active development. Some key areas currently in progress include:

1. **Input System Integration**:
    - Consolidating all input functionality under `InputManager` to ensure abstraction from raylib's input methods.

2. **State Management**:
    - Expanding game-specific logic for transitioning between `GameState` implementations (e.g., from `MainMenuState` to `GameplayState`).

3. **UI Improvements**:
    - Enhancing interaction layers with better rendering abstraction.

4. **Core Features**:
    - Building out reusable components and patterns for other future games.

---

## Future Goals

- Modular support for multiple rendering and input backends beyond raylib.
- Creation of a complete "Snake" playable game.
- Abstracted and reusable UI framework built on top of the core engine.
- Potential support for other games leveraging the same engine foundation.

---

## Acknowledgements

This project heavily relies on **raylib**, a simple and easy-to-use library designed for games and multimedia programming. We appreciate the incredible work from the raylib team and the surrounding community.

For more information about raylib, visit: [https://www.raylib.com](https://www.raylib.com)

---

## Contributing

This project is a foundational portfolio item. Contributions will not be accepted. Thank you.

---

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute the project as per the license terms.