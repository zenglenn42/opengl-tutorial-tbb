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
# Once the dependencies are built, you should be able to switch
# to building from within Xcode.
#
# TODO: A cmake front-end to this would be more portable than 
#       this custom makefile and hard-coded Xcode project file.
#
# Also, for my own amazement, I'm documenting where stuff lands
# when building within Xcode in a dev work-flow:
#
# /Users/<user>/Library/Developer/Xcode/DerivedData/opengl-tutorial-tbb-<mangled-name>/Build/Products/Debug
#
# which feels like a distant and exotic land.
#
# Tested on OSX 10.13
#
# Copyright (☯) 2018 Glenn Streiff
#-----------------------------------------------------------------
.SUFFIXES:

PROJECT = opengl-tutorial-tbb
top_DIR = $(PWD)

# Tools isolation

CMAKE = cmake

# Build and install dependencies out of tree.

# Directory where src zips reside.
dep_ZIP_DIR = $(top_DIR)/../dependencies-srczip
# Install directory for built deps.
dep_INSTALL_DIR = $(top_DIR)/../$(PROJECT)-dependencies
# Build area for deps.
dep_BUILD_DIR   = $(top_DIR)/../$(PROJECT)-build-dependencies

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

#-----------------------
# debugbreak-7ee9b29.zip
#-----------------------
debugbreak_VERSION = 7ee9b29
debugbreak_SRC_ZIP = $(dep_ZIP_DIR)/debugbreak-$(debugbreak_VERSION).zip
debugbreak_SRC_DIR = $(dep_BUILD_DIR)/debugbreak-master
debugbreak_PREFIX  = $(dep_INSTALL_DIR)
debugbreak_BLD_DIR = $(debugbreak_SRC_DIR)
debugbreak_Build   = $(debugbreak_BLD_DIR)/debugbreak.h
debugbreak_IDIR    = $(debugbreak_PREFIX)/include/debugbreak
debugbreak_Install = $(debugbreak_IDIR)/debugbreak.h

default_target: $(dep_BUILD_DIR) $(glew_Build) $(glm_Build) $(sdl2_Build) $(debugbreak_Build)

.PHONY: glew glm sdl2
glew: $(dep_BUILD_DIR) $(glew_Build) $(dep_INSTALL_DIR) $(glew_Install)
glm: $(dep_BUILD_DIR) $(glm_Build) $(dep_INSTALL_DIR) $(glm_Install)
sdl2: $(dep_BUILD_DIR) $(sdl2_Build) $(dep_INSTALL_DIR) $(sdl2_Install)
debugbreak: $(dep_BUILD_DIR) $(debugbreak_Build) $(dep_INSTALL_DIR) $(debugbreak_Install)

$(dep_BUILD_DIR) $(dep_INSTALL_DIR) $(debugbreak_IDIR):
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

debugbreak_Unpack = $(debugbreak_SRC_DIR)/GNUmakefile
$(debugbreak_Unpack): $(debugbreak_SRC_ZIP)
	cd $(dep_BUILD_DIR) && unzip $(unzip_FLAGS) $(debugbreak_SRC_ZIP)

$(glew_Build): $(glew_Unpack)
	cd $(glew_SRC_DIR) && $(MAKE) GLEW_PREFIX=$(glew_PREFIX) GLEW_DEST=$(glew_DEST)

$(glm_Build): $(glm_Unpack)
	mkdir -p $(glm_BLD_DIR) && cd $(glm_BLD_DIR) && $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(glm_PREFIX) ..

$(sdl2_Build): $(sdl2_Unpack)
	mkdir -p $(sdl2_BLD_DIR) && cd $(sdl2_BLD_DIR) && $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(sdl2_PREFIX) ..
	cd $(sdl2_BLD_DIR) && $(MAKE)

$(debugbreak_Build): $(debugbreak_Unpack)
	cd $(debugbreak_SRC_DIR) && $(MAKE)

install: $(dep_INSTALL_DIR) $(glew_Install) $(glm_Install) $(sdl2_Install) $(debugbreak_Install)

$(glew_Install):
	cd $(glew_SRC_DIR) && $(MAKE) install GLEW_PREFIX=$(glew_PREFIX) GLEW_DEST=$(glew_DEST)

$(glm_Install):
	cd $(glm_SRC_DIR)/build && $(MAKE) install

$(sdl2_Install):
	cd $(sdl2_SRC_DIR)/build && $(MAKE) install

$(debugbreak_Install): | $(debugbreak_IDIR)
	cp $(debugbreak_Build) $(debugbreak_IDIR)

.PHONY: clean
clean:
	rm -rf $(dep_BUILD_DIR)

.PHONY: distclean
distclean:
	rm -rf $(dep_BUILD_DIR)
	rm -rf $(dep_INSTALL_DIR)
