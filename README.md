# Sonolus Debugger / Simulator (sdb)

> [!WARNING]  
>
> **This project is Work In Progress(WIP)**

> [!NOTE]
>
> **Check pass on engines written by Sonolus.h.**
>
> <span style="color: red">**Check failed on engines written by Sonolus.py.**</span>

> [!IMPORTANT]
>
> **Only play, watch and tutorial mode was implemented, and there still exists some functions are not implemented.**

## Dependencies

```bash
sudo apt install libgl-dev libglfw3-dev libx11-dev libjsoncpp-dev zlib1g-dev libpng-dev libglew-dev libreadline-dev -y
```

## Generate Headers from Runtime

> [!WARNING]  
>
> **Only use these programs when Sonolus updates their runtime-metadata.**
>
> **Currently sdb has already generated headers from runtime-metadata for Sonolus v1.1.4**

Download runtime-metadata from <https://github.com/Sonolus/runtime-metadata>.

Compile programs:

```bash
g++ function_generator.cpp -o a.out -ljsoncpp -O3
g++ blocks/block_generator.cpp -o blocks/a.out -ljsoncpp -O3
```

Generate headers:

```bash
./a.out ./Function.json ./functions
./blocks/a.out ./blocks/PlayBlock.json ./blocks/Play.h Play 
./blocks/a.out ./blocks/WatchBlock.json ./blocks/Watch.h Watch 
./blocks/a.out ./blocks/TutorialBlock.json ./blocks/Tutorial.h Tutorial 
```

## Main Application

Compile application:

```bash
g++ main.cpp -omain -ljsoncpp -lz -lpng -lGL -lglfw -lGLEW -lreadline -O3
```

Usage:

```bash
Usage: ./main [--help] [--version]
              --mode <play|watch|tutorial>
              [[--config config.json]|[--input-directory data]]
              [--key-mapping key.json]
              [--width 1920] [--height 1080]
              [--engine-data EngineData] [--engine-configuration engine.json]
              [--level-data LevelData]
              [--skin-data SkinData] [--skin-texture SkinTexture]
              [--particle-data ParticleData]
              [--particle-texture ParticleTexture]
              [--disable-command] [--disable-gui] [--use-x11]

This is Sonolus debugger/simulator (sdb)

Optional arguments:
  -h, --help                          shows help message and exits 
  -v, --version                       prints version information and exits 
  -m, --mode <play|watch|tutorial>    select mode for Sonolus simulator. [required]
  -c, --config config.json            specify the configuration file. 
  -i, --input-directory data          specify the working directory. 
  -k, --key-mapping key.json          specify the key mapping file. 
  --width                             specify the width of the window [nargs=0..1] [default: 1920]
  --height                            specify the height of the window [nargs=0..1] [default: 1080]
  --engine-data EngineData            specify the engine data file. 
  --engine-configuration engine.json  specify the engine configuration file. 
  --level-data LevelData              specify the level data file. 
  --skin-data SkinData                specify the skin data file. 
  --skin-texture SkinTexture          specify the skin texture file. 
  --particle-data ParticleData        specify the particle data file. 
  --particle-texture ParticleTexture  specify the particle texture file. 
  --disable-command                   disable interactive command line. 
  --disable-gui                       disable GUI. 
  --use-x11                           use X11 to render window.
```

config.json(Take phigros engine as an example):

```json
{
    "window": {
        "width": 1920,
        "height": 1080
    },
    "engine": {
        "play": "data/Phigros/EnginePlayData",
        "watch": "data/Phigros/EngineWatchData",
        "tutorial": "data/Phigros/EngineTutorialData",
        "config": "data/Phigros/config.json" // Generated from config-app
    },
    "level": {
        "data": "data/Phigros/LevelData"
    },
    "skin": {
        "data": "data/Phigros/SkinData",
        "texture": "data/Phigros/SkinTexture"
    },
    "particle": {
        "data": "data/Phigros/ParticleData",
        "texture": "data/Phigros/ParticleTexture"
    }
}
```

Interactive command line:

```
Work in progress...
```

GUI:

![Main App Preview](preview/main.png)

# config-app

See [config-app](./config-app/README.md)