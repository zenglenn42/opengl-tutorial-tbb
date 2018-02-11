#-----------------------------------------------------------------
# makefile
#
# This makefile builds the 3rd party dependencies required for
# thebennybox modern-opengl tutorial found here:
#
#    https://www.youtube.com/watch?v=ftiKrP3gW3k
#
# usage
#
#    make            # builds src zips into build-dependencies
#    make install    # install deps to dependencies/{include, lib}
#
# update dep_ZIP_DIR = path/to/src_zips as needed
#
# Tested on OSX 10.13
#
# Copyright (☯) 2018 Glenn Streiff
#-----------------------------------------------------------------
.SUFFIXES:

top_DIR = $(PWD)

# Tools isolation

CMAKE = cmake

# Directory where src zips reside.
dep_ZIP_DIR = $(top_DIR)/../dependencies-srczip
dep_INSTALL_DIR = $(top_DIR)/dependencies
dep_BUILD_DIR   = $(top_DIR)/build-dependencies

#---------------
# glew-2.1.0.zip
#---------------
glew_VERSION = 2.1.0
glew_SRC_ZIP = $(dep_ZIP_DIR)/glew-$(glew_VERSION).zip
glew_SRC_DIR = $(dep_BUILD_DIR)/glew-$(glew_VERSION)
glew_PREFIX  = $(dep_INSTALL_DIR)
glew_DEST    = $(dep_INSTALL_DIR)
glew_Build   = $(glew_SRC_DIR)/include/GL/glew.h
glew_Install = $(glew_PREFIX)/include/GL/glew.h

#----------------
# glm-0.9.8.5.zip
#----------------
glm_VERSION = 0.9.8.5
glm_SRC_ZIP = $(dep_ZIP_DIR)/glm-$(glm_VERSION).zip
glm_SRC_DIR = $(dep_BUILD_DIR)/glm
glm_PREFIX  = $(dep_INSTALL_DIR)
glm_BLD_DIR = $(glm_SRC_DIR)/build
glm_Build   = $(glm_BLD_DIR)/cmake_install.cmake
glm_Install = $(glm_PREFIX)/include/glm/glm.hpp

#----------------
# SDL2-2.0.7.zip
#----------------
sdl2_VERSION = 2.0.7
sdl2_SRC_ZIP = $(dep_ZIP_DIR)/SDL2-$(sdl2_VERSION).zip
sdl2_SRC_DIR = $(dep_BUILD_DIR)/SDL2-$(sdl2_VERSION)
sdl2_PREFIX  = $(dep_INSTALL_DIR)
sdl2_BLD_DIR = $(sdl2_SRC_DIR)/build
sdl2_Build   = $(sdl2_BLD_DIR)/cmake_install.cmake
sdl2_Install = $(sdl2_PREFIX)/include/SDL2/SDL.h

default_target: $(dep_BUILD_DIR) $(glew_Build) $(glm_Build) $(sdl2_Build)

.PHONY: glew glm sdl2
glew: $(dep_BUILD_DIR) $(glew_Build) $(dep_INSTALL_DIR) $(glew_Install)
glm: $(dep_BUILD_DIR) $(glm_Build) $(dep_INSTALL_DIR) $(glm_Install)
sdl2: $(dep_BUILD_DIR) $(sdl2_Build) $(dep_INSTALL_DIR) $(sdl2_Install)

$(dep_BUILD_DIR) $(dep_INSTALL_DIR):
	mkdir -p $@

unzip_CURRENT_TIME = -DD
unzip_FLAGS = $(unzip_CURRENT_TIME)

glew_Unpack = $(glew_SRC_DIR)/Makefile
$(glew_Unpack): $(glew_SRC_ZIP)
	cd $(dep_BUILD_DIR) && unzip $(unzip_FLAGS) $(glew_SRC_ZIP)

glm_Unpack = $(glm_SRC_DIR)/CMakeLists.txt
$(glm_Unpack): $(glm_SRC_ZIP)
	cd $(dep_BUILD_DIR) && unzip $(unzip_FLAGS) $(glm_SRC_ZIP)

sdl2_Unpack = $(sdl2_SRC_DIR)/CMakeLists.txt
$(sdl2_Unpack): $(sdl2_SRC_ZIP)
	cd $(dep_BUILD_DIR) && unzip $(unzip_FLAGS) $(sdl2_SRC_ZIP)

$(glew_Build): $(glew_Unpack)
	cd $(glew_SRC_DIR) && $(MAKE) GLEW_PREFIX=$(glew_PREFIX) GLEW_DEST=$(glew_DEST)

$(glm_Build): $(glm_Unpack)
	mkdir -p $(glm_BLD_DIR) && cd $(glm_BLD_DIR) && $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(glm_PREFIX) ..

$(sdl2_Build): $(sdl2_Unpack)
	mkdir -p $(sdl2_BLD_DIR) && cd $(sdl2_BLD_DIR) && $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(sdl2_PREFIX) ..
	cd $(sdl2_BLD_DIR) && $(MAKE)

install: $(dep_INSTALL_DIR) $(glew_Install) $(glm_Install) $(sdl2_Install)

$(glew_Install):
	cd $(glew_SRC_DIR) && $(MAKE) install GLEW_PREFIX=$(glew_PREFIX) GLEW_DEST=$(glew_DEST)

$(glm_Install):
	cd $(glm_SRC_DIR)/build && $(MAKE) install

$(sdl2_Install):
	cd $(sdl2_SRC_DIR)/build && $(MAKE) install

.PHONY: clean
clean:
	rm -rf $(dep_BUILD_DIR)

.PHONY: distclean
distclean:
	rm -rf $(dep_BUILD_DIR)
	rm -rf $(dep_INSTALL_DIR)
