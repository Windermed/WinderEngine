# WinderEngine

A lightweight C++ game engine base built using SFML 3.1

## Structure

WinderEngine is split into two parts:

- **engine/** - the core engine. which is built as a static library
- **source/** - the source folder that the game built on top of WinderEngine uses. to make things easier, I've included a base game project to start from.

## Engine System

- **Object** - this is a base class for everything that's in the world
- **Character** - a base for anything that moves and has a sprite
- **Player** - a base player class that has 8 directional inputs.
- **GameSprite** - a sprite class with opacity, scale, flip and pulse helpers.
- **GameText** - this is a text class with centering, flashing, and now a per-character rainbow effect.
- **SoundManager** a singleton audio manager responsible for loading sound buffers, managing a sound pool for overlapping audio, and controlling playback volume.
- **Engine** - the core of the game. contains window management, input, etc.

## Using WinderEngine

### As a standalone project
Clone and run `build.bat` to start up the Engine and access the base project included.

### As a submodule in your own project
```bash
git submodule add https://github.com/Windermed/WinderEngine.git engine
```
Then just reference it in your own `CmakeLists.txt`:
```cmake
add_subdirectory(engine)
target_link_libraries(YourGame PRIVATE WinderEngine)
target_include_directories(YourGame PRIVATE engine/source)
```

# Compiling The Project
> **Note:** First build will download and compile SFML 3.1 alongside
> its dependencies which can be a minimum of (~2GB). Subsequent builds are significantly faster.

## Build Instructions

### Requirements
* Cmake 3.28+
* Visual Studio 2022 (for Windows) or GCC/Clang with C++17 Support.

### Windows
Start by running `build.bat` and open `build/BaseGame.sln` using Visual Studio 2022.

### Mac/Linux
```bash
# give the build script permission to execute
chmod +x build.sh

# now run the build script
./build.sh
```

## Credits
If you use or reference this project please provide credit. that's all I ask.

## License
MIT License. see the LICENSE file for more info.