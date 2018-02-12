# opengl-tutorial-tbb

Following along in this opengl tutorial: https://www.youtube.com/playlist?list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh

I like this series because it:

	* addresses basic opengl concepts
	* shows how to abstract opengl programming with c++ classes
	* employs a portable and modern windowing sdk (SDL2) to wrapper our opengl renderings
	* discusses the programmable GPU pipeline

# Build dependencies from source

I've included some Xcode project files in my repo, but they assume the following dependencies have been installed under

	../dependencies/include
	../dependencies/lib

To accomplish this, I downloaded the following src zip files:

	* SDL2-2.0.7.zip
	* glew-2.1.0.zip
	* glm-0.9.8.5.zip
	* [debugbreak-7ee9b29.zip](https://github.com/scottt/debugbreak)

and staged them under:

	../dependencies-srczip

then built and installed them to ../dependencies with:

	make
	make install

With that out of the way, I can now build from within the Xcode IDE for a better dev workflow.  There's probably a more unified way to do all this, but I'm trying not to get too snarled up in build generality.

Strangely, my first attempt at running the wafer-thin example code that just brings up an empty SDL window failed with a borderless window (with no title or sizing decorations).  I speculate this was a dynamic link library search path issue which probably could be resolved by tweaking the embedded rpath of the executable through Xcode's Build Settings: Linking/Runpath Search Paths or tweaking with the dynamic library search path at the shell level.  I opted for just going with static linking by removing the dynamically linked libraries out of the dependencies directory and rebuilding from within Xcode.
