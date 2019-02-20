# ESP-IDF Makefile for game project
PROJECT_NAME=Brickout

BRICKOUT_SRC_PATH=${PROJECT_PATH}/src
ifndef CREATIVE_ENGINE_PATH
CREATIVE_ENGINE_PATH=$(abspath ${PROJECT_PATH}/../creative-engine)
export CREATIVE_ENGINE_PATH
endif

BRICKOUT_STATES+=$(BRICKOUT_SRC_PATH)/SplashState
BRICKOUT_STATES+=$(BRICKOUT_SRC_PATH)/TitleState
BRICKOUT_STATES=$(BRICKOUT_SRC_PATH)/GameState


EXTRA_COMPONENT_DIRS=${CREATIVE_ENGINE_PATH} ${PROJECT_PATH}/src $(BRICKOUT_STATES)

include $(IDF_PATH)/make/project.mk

# Temporary until RCOMP is folded into the music/sfx workflow
gen_sound_headers: gen_music_headers gen_sfx_headers FORCE

gen_music_headers:
	echo "Generating music headers"
	cd resources/music && ./gen_header.sh

gen_sfx_headers:
	echo "Generating sound effects headers"
	cd resources/sound_effects && ./gen_header.sh

release: FORCE
	./scripts/build.sh && cp ./build/genus.tgz ~/Downloads/

rcomp: FORCE
	echo "Building rcomp"
	echo ${EXTRA_COMPONENT_DIRS}
	cd ${CREATIVE_ENGINE_PATH}/tools && make

resources: rcomp FORCE
	echo "Compiling resources"
	cd src && ${CREATIVE_ENGINE_PATH}/tools/rcomp Resources.r

reset: FORCE
	echo "Resetting high score table (and options)"
	 rm -f cmake-build-debug/genus.app/Contents/MacOS/*.store

FORCE:


