# Developer guide
This document's purpose is to provide a high-level understanding of how Brickout works. Programmers wishing to get involved should review our [contribution](./md/CONTRIBUTING.md) guidelines as well as have a decent understanding of C++ and build tools. Having some knowledge of SOCs, such as the [ESP32-WROVER](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/get-started-wrover-kit.html) would also be very helpful. 
Brickout is a cross-platform a block-breaking game developed by [Modus Create](https://moduscreate.com) and its sole purpose is to demonstrate how to use [creative engine](https://github.com/moduscreateorg/creative-engine). Brickout runs on the [ODROID GO](https://www.hardkernel.com/shop/odroid-go/), macOS and Linux.


*Note* We've standardized on ESP-IDF version 3.2:
https://github.com/espressif/esp-idf/releases/tag/v3.2
https://docs.espressif.com/projects/esp-idf/en/v3.2/


## How to Play
Brickout is a simple game where you have to outsmart your AI opponent and land the ball behind his paddle. 

![brickout-gameplay.gif](./img/brickout-gameplay.gif)

The following is a list of dependencies for each platform.

### Dependencies (All platforms)
[Brickout](https://github.com/moduscreateorg/brickout), this game.\
[Creative Engine](https://github.com/ModusCreateOrg/creative-engine) is the game engine developed by Modus Create. It implements LibXMP, SDL2, ESP-IDF (Audio, Video and Input drivers).\
[LibXMP](http://xmp.sourceforge.net/) is a fantastic cross-platform library for playing music using the [Xtended Module (XM)](https://en.wikipedia.org/wiki/XM_(file_format)) format and also has additional functionality to play sound effects.\
[Rcomp](https://github.com/ModusCreateOrg/creative-engine/blob/master/tools/rcomp.cpp) is a CLI tool that takes any binary resources and packages  (graphic, audio, etc.) them into a binary blob to be included in the game executable and is part of [Creative Engine](https://github.com/ModusCreateOrg/creative-engine).

#### macOS, Linux
[SDL2](https://www.libsdl.org/download-2) is a cross-platform low-level media layer framework. Creative Engine generates audio data with LibXMP and feeds it into the SDL2 audio run loop and does similar to present visuals in the application window as well as poll for keyboard input to allow for game play.

#### ODROID GO
[Espressif IoT development Framework (ESP IDF)](https://github.com/espressif/esp-idf) is a low level framework for accessing capabilities of the ESP32-WOVER SOC.


## Getting started
Let's get setup for desktop and device development. To do so, we'll need to ensure that we have the right libraries and tools installed.

We're going to get setup in three phases:
1. Clone Brickout and Creative Engine
2. Install supporting desktop libraries and tools
3. Install ESP IDF toolchain (this is only needed if you want to program an ODROID GO)

## Clone Brickout and Creative Engine
The first thing we need to is create a folder that will contain Brickout and Creative engine. When we're done, the folder struction will look similar to the following.

    projects/
       |-brickout-game/
            |-creative-engine/      # Source Creative Engine
            |-brickout/                # Source for Brickout
                |-creative-engine/  # Symbolic Link to ../creative-engine/

Let's clone the Brickout and Creative Engine repos:

    # Would be within ~/projects or similar
    mkdir brickout-game/     
    cd brickout-game/
    git clone git@github.com:ModusCreateOrg/brickout.git
    git clone git@github.com:ModusCreateOrg/creative-engine.git
    ln -s creative-engine/ brickout/creative-engine               # Create Symbolic Link
   
## Install dependencies

### macOS
- [ ] Install [XCode](https://developer.apple.com/xcode/) CLI tools
    
```
xcode-select --install
``` 
  
- [ ] Install [Homebrew](https://brew.sh)

```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`
```
- [ ] Install final dependencies via HomeBrew
```    
# Run this command from brickout/
brew install
```
- [ ] Build and run Brickout
```    
# Run these commands command from brickout/
make rcomp resources    # Build necessary tooling & resources binary
mkdir build             # Create build directory
cd build                   
cmake ..                # Execute Cmake and prepare for build
make -j 4               # Four threads. Change to whatever you wish for faster compilation
open brickout.app       # Run Brickout
```

### Linux (Debian based)
- [ ] Install dependencies
```
sudo apt-get install libsdl2-dev libsdl2-image-dev cmake g++ -y
```
- [ ] Build Brickout
```    
# Run this command from brickout/
make resources       # Generates src/Resources.bin binary file to be included in our program
mkdir build          # Create build directory
cd build                       
cmake ..             # Execute Cmake and prepare for build
make -j 4            # Four threads. Change to whatever you wish for faster compilation
./brickout
```
### Raspberry Pi
Brickout is tested on Raspbian Stretch (9.6) on the Raspberry Pi 2B+ and 3B+. You will need about 2GB of space in /tmp and about 2GB of space in /home to build this.

The game will run very slowly without enabling the OpenGL desktop driver. You can enable it by running `sudo raspbi-config` and choosing _Advanced Options / GL Driver / GL (Full KMS)_. The game will run very slowly without enabling the OpenGL desktop driver. You can enable it by running `sudo raspbi-config` and choosing _Advanced Options / GL Driver / GL (Full KMS)_. See this site for complete instructions:  [https://eltechs.com/how-to-enable-opengl-on-raspberry-pi/](https://eltechs.com/how-to-enable-opengl-on-raspberry-pi/).



## ODROID GO/ESP32
- [ ] Follow the [setup-toolchain](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/#setup-toolchain) instructions for the ESP IDF. Be sure to follow them thorougly! 
- [ ] Stage the appropriate SDK config file
```
# Linux ONLY
cp sdkconfig.linux sdkconfig
# macOS ONLY
cp sdkconfig.mac sdkconfig
```
- [ ] Build and run Brickout 
```
# From within brickout/
# *IF* you are prompted by the build system to say yes or no to any configura†ion changes, 
# choose the default (press ENTER).
make rcomp resources    # Build necessary tooling & resources binary
make -j 4 flash         # Assuming you have four CPU cores to compile

# *IF* you are prompted by the build system to say yes or no to any configura†ion changes, 
# choose the default (press ENTER).
```

## Additional information
We highly recommend using the [CLion IDE](https://www.jetbrains.com/clion/) to develop the project and run the builds.


## Git Workflow
Read about [GitHub workflow](https://github.com/ModusCreateOrg/creative-engine) at the creative-engine repo.

The gist is that we fork the main repos and work in our private forks.  We push to our forks.  We create Pull Requests against the main repos.

The only way code makes it into master in the main repo is if we merge a PR.
