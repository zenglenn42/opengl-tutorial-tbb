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
# Plus, many of the required frameworks live under:
#
# /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks
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
TAR   = tar
UNZIP = unzip

# Build and install dependencies out of tree.

# Directory where src zips reside.
dep_ZIP_DIR = $(top_DIR)/../dependencies-srczip
# Install directory for built deps.
dep_INSTALL_DIR = $(top_DIR)/../$(PROJECT)-dependencies
# Build area for deps.
dep_BUILD_DIR   = $(top_DIR)/../$(PROJECT)-build-dependencies

#---------------
# glew-2.1.0.zip
#
# https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip/download
# OpenGL extension wranger.  Cross-platform open-source extension loading library.
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
#
# https://github.com/g-truc/glm/archive/0.9.8.5.zip
# OpenGL-friendly mathematics library.
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
#
# https://www.libsdl.org/release/SDL2-2.0.7.zip
# Portable windowing/media layer for graphics apps, etc.
#----------------
sdl2_VERSION = 2.0.7
sdl2_SRC_ZIP = $(dep_ZIP_DIR)/SDL2-$(sdl2_VERSION).zip
sdl2_SRC_DIR = $(dep_BUILD_DIR)/SDL2-$(sdl2_VERSION)
sdl2_PREFIX  = $(dep_INSTALL_DIR)
sdl2_BLD_DIR = $(sdl2_SRC_DIR)/build
sdl2_Build   = $(sdl2_BLD_DIR)/cmake_install.cmake
sdl2_Install = $(sdl2_PREFIX)/include/SDL2/SDL.h
sdl2_config_PATH = $(sdl2_PREFIX)/bin

#-----------------------
# debugbreak-7ee9b29.zip
#
# https://github.com/scottt/debugbreak
# Break to the debugger at runtime.
#-----------------------
debugbreak_VERSION = 7ee9b29
debugbreak_SRC_ZIP = $(dep_ZIP_DIR)/debugbreak-$(debugbreak_VERSION).zip
debugbreak_SRC_DIR = $(dep_BUILD_DIR)/debugbreak-master
debugbreak_PREFIX  = $(dep_INSTALL_DIR)
debugbreak_BLD_DIR = $(debugbreak_SRC_DIR)
debugbreak_Build   = $(debugbreak_BLD_DIR)/debugbreak.h
debugbreak_IDIR    = $(debugbreak_PREFIX)/include/debugbreak
debugbreak_Install = $(debugbreak_IDIR)/debugbreak.h

#-----------------------
# stb-e6afb9c.zip
#
# https://github.com/nothings/stb
# Includes primitives for loading texture images.
#-----------------------
stb_VERSION = e6afb9c
stb_SRC_ZIP = $(dep_ZIP_DIR)/stb-$(stb_VERSION).zip
stb_SRC_DIR = $(dep_BUILD_DIR)/stb-master
stb_PREFIX  = $(dep_INSTALL_DIR)
stb_BLD_DIR = $(stb_SRC_DIR)
stb_Build   = $(stb_BLD_DIR)/stb.h
stb_IDIR    = $(stb_PREFIX)/include/stb
# Specify headers to install from BLD_DIR.
stb_Headers = stb.h stb_image.h
stb_Install = $(patsubst %, $(stb_IDIR)/%, $(stb_Headers))

#-----------------------
# freetype-2.9.tar.gz
#
# https://download.savannah.gnu.org/releases/freetype/
# Includes library for rendering fonts.
# License: https://www.freetype.org/license.html FTL (BSD-style)
#-----------------------
ft_VERSION = 2.9
ft_SRC_GZ = $(dep_ZIP_DIR)/freetype-$(ft_VERSION).tar.gz
ft_SRC_DIR = $(dep_BUILD_DIR)/freetype-$(ft_VERSION)
ft_PREFIX  = $(dep_INSTALL_DIR)
ft_BLD_DIR = $(ft_SRC_DIR)/build
ft_Build   = $(ft_BLD_DIR)/Makefile
#ft_Build  = $(ft_BLD_DIR)/cmake_install.cmake
ft_Install = $(ft_PREFIX)/include/freetype2/freetype/freetype.h

#-----------------------
# SDL2_ttf-2.0.14.zip
#
# https://www.libsdl.org/projects/SDL_ttf/release
# TrueType support for SDL2.
#-----------------------
sdl2ttf_VERSION = 2.0.14
sdl2ttf_SRC_ZIP = $(dep_ZIP_DIR)/SDL2_ttf-$(sdl2ttf_VERSION).zip
sdl2ttf_SRC_DIR = $(dep_BUILD_DIR)/SDL2_ttf-$(sdl2ttf_VERSION)
sdl2ttf_PREFIX  = $(dep_INSTALL_DIR)
sdl2ttf_BLD_DIR = $(sdl2ttf_SRC_DIR)/build
sdl2ttf_Build   = $(sdl2ttf_BLD_DIR)/Makefile
sdl2ttf_Install = $(sdl2ttf_PREFIX)/lib/libSDL2_ttf.a

#-----------------------
# sdl2-widgets-b8acdda.zip
#
# https://github.com/zenglenn42/sdl2-widgets
# http://members.chello.nl/w.boeke/SDL-widgets/SDL2-widgets-2.1.tar.gz
# Widgets for SDL2-based apps.
# Circa ~SDL2-widgets-2.1.tar.gz with a few macOS porting changes
#-----------------------
sdl2widgets_VERSION = b8acdda
sdl2widgets_SRC_ZIP = $(dep_ZIP_DIR)/sdl2-widgets-$(sdl2widgets_VERSION).zip
sdl2widgets_SRC_DIR = $(dep_BUILD_DIR)/sdl2-widgets-master
sdl2widgets_PREFIX  = $(dep_INSTALL_DIR)
sdl2widgets_BLD_DIR = $(sdl2widgets_SRC_DIR)
sdl2widgets_Build   = $(sdl2widgets_BLD_DIR)/sdl-widgets.a
sdl2widgets_IDIR    = $(sdl2widgets_PREFIX)/include/sdl2widgets
sdl2widgets_Headers = $(patsubst %, $(sdl2widgets_IDIR)/%, sdl-widgets.h) 
sdl2widgets_Install = $(sdl2widgets_PREFIX)/lib/sdl-widgets.a $(sdl2widgets_Headers)

default_target: $(dep_BUILD_DIR) $(glew_Build) $(glm_Build) $(sdl2_Build) $(debugbreak_Build) $(stb_Build) $(ft_Build) $(sdl2ttf_Build) $(sdl2widgets_Build)

.PHONY: glew glm sdl2 debugbreak stb ft sdl2ttf sdl2widgets
glew: $(dep_BUILD_DIR) $(glew_Build) $(dep_INSTALL_DIR) $(glew_Install)
glm: $(dep_BUILD_DIR) $(glm_Build) $(dep_INSTALL_DIR) $(glm_Install)
sdl2: $(dep_BUILD_DIR) $(sdl2_Build) $(dep_INSTALL_DIR) $(sdl2_Install)
debugbreak: $(dep_BUILD_DIR) $(debugbreak_Build) $(dep_INSTALL_DIR) $(debugbreak_Install)
stb: $(dep_BUILD_DIR) $(stb_Build) $(dep_INSTALL_DIR) $(stb_Install)
ft: $(dep_BUILD_DIR) $(ft_Build) $(dep_INSTALL_DIR) $(ft_Install)
sdl2ttf: $(dep_BUILD_DIR) $(sdl2ttf_Build) $(dep_INSTALL_DIR) $(sdl2ttf_Install)
sdl2widgets: $(dep_BUILD_DIR) $(sdl2widgets_Build) $(dep_INSTALL_DIR) $(sdl2widgets_Install) 

$(dep_BUILD_DIR) $(dep_INSTALL_DIR) $(debugbreak_IDIR) $(stb_IDIR) $(sdl2widgets_IDIR):
	mkdir -p $@

unzip_CURRENT_TIME = -DD
unzip_FLAGS = $(unzip_CURRENT_TIME)

glew_Unpack = $(glew_SRC_DIR)/Makefile
$(glew_Unpack): $(glew_SRC_ZIP)
	cd $(dep_BUILD_DIR) && $(UNZIP) $(unzip_FLAGS) $(glew_SRC_ZIP)

glm_Unpack = $(glm_SRC_DIR)/CMakeLists.txt
$(glm_Unpack): $(glm_SRC_ZIP)
	cd $(dep_BUILD_DIR) && $(UNZIP) $(unzip_FLAGS) $(glm_SRC_ZIP)

sdl2_Unpack = $(sdl2_SRC_DIR)/CMakeLists.txt
$(sdl2_Unpack): $(sdl2_SRC_ZIP)
	cd $(dep_BUILD_DIR) && $(UNZIP) $(unzip_FLAGS) $(sdl2_SRC_ZIP)

debugbreak_Unpack = $(debugbreak_SRC_DIR)/GNUmakefile
$(debugbreak_Unpack): $(debugbreak_SRC_ZIP)
	cd $(dep_BUILD_DIR) && $(UNZIP) $(unzip_FLAGS) $(debugbreak_SRC_ZIP)

stb_Unpack = $(stb_SRC_DIR)/README.md
$(stb_Unpack): $(stb_SRC_ZIP)
	cd $(dep_BUILD_DIR) && $(UNZIP) $(unzip_FLAGS) $(stb_SRC_ZIP)

ft_Unpack = $(ft_SRC_DIR)/configure
untar_FLAGS = -zxvmf
$(ft_Unpack): $(ft_SRC_GZ)
	cd $(dep_BUILD_DIR) && $(TAR) $(untar_FLAGS) $(ft_SRC_GZ)

sdl2ttf_Unpack = $(sdl2ttf_SRC_DIR)/configure
$(sdl2ttf_Unpack): $(sdl2ttf_SRC_ZIP)
	cd $(dep_BUILD_DIR) && $(UNZIP) $(unzip_FLAGS) $(sdl2ttf_SRC_ZIP)

sdl2widgets_Unpack = $(sdl2widgets_SRC_DIR)/configure
$(sdl2widgets_Unpack): $(sdl2widgets_SRC_ZIP)
	cd $(dep_BUILD_DIR) && $(UNZIP) $(unzip_FLAGS) $(sdl2widgets_SRC_ZIP)

$(glew_Build): $(glew_Unpack)
	cd $(glew_SRC_DIR) && $(MAKE) GLEW_PREFIX=$(glew_PREFIX) GLEW_DEST=$(glew_DEST)

$(glm_Build): $(glm_Unpack)
	mkdir -p $(glm_BLD_DIR) && cd $(glm_BLD_DIR) && $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(glm_PREFIX) ..

$(sdl2_Build): $(sdl2_Unpack)
	mkdir -p $(sdl2_BLD_DIR) && cd $(sdl2_BLD_DIR) && $(CMAKE) -DCMAKE_INSTALL_PREFIX=$(sdl2_PREFIX) ..
	cd $(sdl2_BLD_DIR) && $(MAKE)

$(debugbreak_Build): $(debugbreak_Unpack)
	cd $(debugbreak_SRC_DIR) && $(MAKE)

$(stb_Build): $(stb_Unpack)
	@echo "Nothing to build for stb :-)"

$(ft_Build): $(ft_Unpack)
	mkdir -p $(ft_BLD_DIR) && cd $(ft_BLD_DIR) && $(ft_SRC_DIR)/configure --prefix=$(ft_PREFIX)
	cd $(ft_BLD_DIR) && $(MAKE)

sdl2_FRAMEWORKS=-Wl,-framework,CoreAudio,-framework,AudioToolbox,-framework,CoreFoundation,-framework,CoreGraphics,-framework,CoreVideo,-framework,ForceFeedback,-framework,IOKit,-framework,Carbon,-framework,AppKit
$(sdl2ttf_Build): $(sdl2ttf_Unpack) $(sdl2_Install) $(ft_Install)
	mkdir -p $(sdl2ttf_BLD_DIR) && cd $(sdl2ttf_BLD_DIR) && LDFLAGS=$(sdl2_FRAMEWORKS) LIBS=-liconv $(sdl2ttf_SRC_DIR)/configure --with-freetype-prefix=$(ft_PREFIX) --with-sdl-prefix=$(sdl2_PREFIX) --prefix=$(sdl2ttf_PREFIX)
	cd $(sdl2ttf_BLD_DIR) && $(MAKE)

$(sdl2widgets_Build): $(sdl2widgets_Unpack) $(sdl2ttf_Install)
	mkdir -p $(sdl2widgets_BLD_DIR) && cd $(sdl2widgets_BLD_DIR) && PATH=$(PATH):$(sdl2_config_PATH) ./configure
	export PATH=$(PATH):$(sdl2_config_PATH) && cd $(sdl2widgets_BLD_DIR) && $(MAKE) LDFLAGS_OPTS="$(sdl2_FRAMEWORKS)"

install: $(dep_INSTALL_DIR) $(glew_Install) $(glm_Install) $(sdl2_Install) $(debugbreak_Install) $(stb_Install) $(ft_Install) $(sdl2ttf_Install) $(sdl2widgets_Install)

$(glew_Install):
	cd $(glew_SRC_DIR) && $(MAKE) install GLEW_PREFIX=$(glew_PREFIX) GLEW_DEST=$(glew_DEST)

$(glm_Install):
	cd $(glm_SRC_DIR)/build && $(MAKE) install

$(sdl2_Install):
	cd $(sdl2_SRC_DIR)/build && $(MAKE) install

$(debugbreak_Install): | $(debugbreak_IDIR)
	cp $(debugbreak_Build) $(debugbreak_IDIR)

$(stb_Install): | $(stb_IDIR)
	cd $(stb_BLD_DIR) && cp $(@F) $@

$(ft_Install):
	cd $(ft_SRC_DIR)/build && $(MAKE) install

$(sdl2ttf_Install):
	cd $(sdl2ttf_SRC_DIR)/build && $(MAKE) install

$(sdl2widgets_Install): | $(sdl2widgets_IDIR)
	cd $(sdl2widgets_SRC_DIR) && cp $(@F) $@

.PHONY: clean
clean:
	rm -rf $(dep_BUILD_DIR)

.PHONY: distclean
distclean:
	rm -rf $(dep_BUILD_DIR)
	rm -rf $(dep_INSTALL_DIR)
