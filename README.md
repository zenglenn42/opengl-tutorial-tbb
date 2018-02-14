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

	* SDL2-2.0.7.zip  http://www.libsdl.org/release/SDL2-2.0.7.zip
	* glew-2.1.0.zip  https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip/download
	* glm-0.9.8.5.zip https://github.com/g-truc/glm/archive/0.9.8.5.zip
	* debugbreak-7ee9b29.zip https://github.com/scottt/debugbreak

and staged them under:

	../dependencies-srczip

then built and installed them to ../dependencies with:

	make
	make install

With that out of the way, I can now build from within the Xcode IDE for a better dev workflow.  There's probably a more unified way to do all this, but I'm trying not to get too snarled up in build generality.

Strangely, my first attempt at running the wafer-thin example code that just brings up an empty SDL window failed with a borderless window (with no title or sizing decorations).  I speculate this was a dynamic link library search path issue which probably could be resolved by tweaking the embedded rpath of the executable through Xcode's Build Settings: Linking/Runpath Search Paths or tweaking with the dynamic library search path at the shell level.  I opt for just going with static linking by removing the dynamically linked libraries out of the dependencies directory and rebuilding from within Xcode.

# Getting [Tutorial 3.5](https://www.youtube.com/watch?v=0jML5fMBDGg) to build and render is a Thing

Lightness and dark, a metaphor for life and opengl programming.  You type the code in perfectly and are rewarded with an empty rendering window.  It's a dark alley and you're not sure how to proceed.

I double check the code, start reading the comment section of the youtube video, and look for general strategies for OpenGL debugging, then sleep on it so my subconcious can churn away on the mystery.

Cutting to the chase, I discover two issues:

	* mesh.cpp Mesh::Mesh constructor fails in glGenVertexArrays() with EXC_BAD_ACCESS
	* main.cpp main() vertices specified in clockwise order were getting culled by uplevel display.cpp from github.

I fix the first issue in display.cpp by enabling glewExperimental:

![alt tag](img/tutorial-3.5-rtbreak.png)

```
display.cpp
    ...
    Display::Display(...)

    //
    // NB: Avoid "Thread 1: EXC_BAD_ACCESS (code=1, address=0x0)"
    // https://stackoverflow.com/questions/13558073/program-crash-on-glgenvertexarrays-call
    //
>>> glewExperimental = GL_TRUE;
    
    GLenum res = glewInit();
    ...
```

I fix the second issue by reording the verties in counter-clockwise order so they are interpreted as front-facing:

```
main.cpp

    int main(...)
    ...
    Vertex vertices[] =
    {
        // NB: Vertices specified in counter-clockwise order are
        //     interpreted as front-facing by convention.
        //
        // This is important to know if your code culls back-facing vertices
        // and you mistakenly specify them in clockwise order ...
        // and now are wondering why your rendering window is blank. :-/

        Vertex(glm::vec3(-0.5, -0.5, 0.0)),
>>>     Vertex(glm::vec3( 0.5, -0.5, 0.0)),
>>>     Vertex(glm::vec3( 0.0,  0.5, 0.0))
    };
```

In the process, I pick up some debug strategies that should serve me nicely going forward:

* Leverage Yan Cherno's [GLCall() wrapper](https://github.com/zenglenn42/opengl-tutorial-tbb/blob/master/opengl-tutorial-tbb/gldebug.h) that breaks to the debugger when glError complains.

* Use Scott Tsai's [debug_break()](https://github.com/scottt/debugbreak) function to extend GLCall to gcc, clang, and msvc compilers.

* Craft debug [vertex](https://github.com/zenglenn42/opengl-tutorial-tbb/blob/master/Resources/debugShader.vs) and [fragment](https://github.com/zenglenn42/opengl-tutorial-tbb/blob/master/Resources/debugShader.fs) shaders that allow easy overrides for incoming and outgoing variables.

Even after deploying [theCherno's debug fu](https://www.youtube.com/watch?v=FBbPWSOQ0-w&index=10&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2) and wrangling community suggestions, I still have a blank window after a full day of effort.  In the morning, I realize I don't know if the issue is on the CPU or GPU side.  Is there a problem with the mesh vertices getting sent down?  Backlevel driver weirdness on macOS?  Are the shaders even *firing*?  I mean, I *think* they're firing.  I don't see any compile or link errors along that path.  But how could I test that?  With some stripped down shaders, I can hardcode the fragment color and should see a new color to my blank window ... yeah, that works.  So I shift focus to the CPU side, dropping the mesh vertices array from the tutorial code and just wedging in my own legacy mesh triangle using the classic [immediate-mode](https://stackoverflow.com/questions/6733934/what-does-immediate-mode-mean-in-opengl) idiom:

```
glBegin(GL_TRIANGES);
   // Heads-up: Notice the clockwise ordering?
   //
   //           This will be interpreted as the 
   //           back face of the triangle by default
   //           by OpenGL. :-/
   glVertex3f(-0.5f, -0.5f, 0.0f); 
   glVertex3f(0.0f, 0.5f, 0.0f); 
   glVertex3f(0.5f, -0.5f, 0.0f);
glEnd();
```

This is facilitated in the debug [vertex shader](https://github.com/zenglenn42/opengl-tutorial-tbb/blob/master/Resources/debugShader.vs#L11) by calling ftransform:

```
gl_Position = ftransform();
```

Still, no joy.

I punt on GL_TRIANGLES and opt for GL_LINES and /finally/ get something on the screen.  

But even that is a bit rough for dumb reasons ... me forgetting that you need pairs of vertices to draw one line segment as opposed to a mistaken connect-the-dots assumption about how that works.  Oddly, that also gets me looking into controlling line color at the shader level.  That leads to discussions of gl_FrontColor and gl_BackColor within the GLSL shader language and backs me into the crucial realization that front-facing meshes are specified with vertices in *counter-clockwise* order and in the tutorial they're specified in *clockwise* order (which is probably anti-pattern).

If I had just recreated the live display.cpp code from the youtube tutorial, the vertex ordering would not be an issue since there is no vertex culling in *that* code. But I kinda mix and match live code with stuff I pull from the uplevel [github repo](https://github.com/BennyQBD/ModernOpenGLTutorial/blob/master/display.cpp#L29).  In the repo code, culling of GL_BACK vertices is enabled, killing off the clockwise-ordered mesh of vertices in the live code of main().  Once I realize that, I revert back to my dummied-up GL_TRIANGLES and relize I've made the same mistake of specifying them in clockwise order.  Once I move them to counter-clockwise, I'm rewarded with a green triangle courtesy my debug shaders:

![alt tag](img/tutorial-3.5-gldebug.png)

Now I backout of my debug paths entirely and use my cleaned-up version of the live code from the tutorial video and the coveted red triangle now appears:

![alt tag](img/tutorial-3.5-red.png)

the product of nice c++ abstraction, gpu-efficient [retained-mode](https://stackoverflow.com/questions/6733934/what-does-immediate-mode-mean-in-opengl) programmable pipeline, and a modern windowing sdk (SDL2).

Some clouds lift. [Light now plays with shadow](http://glslsandbox.com/e#44945.0), gracing my keyboard and spirits.

# Okay, but how do I make all this work with my models?

... especially since my previous OpenGL work relied upon the GLUT layer I'm trying to deprecate for modeling primitives like glutSolidCone.

I'm tempted to take a diversion through a few threads so I can render a 3D cone in retained mode instead of a humble triangle.

Specifically,

[immediate-to-retained-mode](https://stackoverflow.com/questions/6733934/what-does-immediate-mode-mean-in-opengl)

[display-list-to-vbo](https://stackoverflow.com/questions/26189645/opengl-convert-from-displaylist-to-use-vbo)

[retained-mode-history-lesson](https://stackoverflow.com/questions/21652546/what-is-the-role-of-glbindvertexarrays-vs-glbindbuffer-and-what-is-their-relatio)

[computing-cone-surface-normals](https://stackoverflow.com/questions/19245363/opengl-glut-surface-normals-of-cone)

seem nutrient dense for my purposes.  Hmmm, that looks like a bit of work. Not sure if I'm ready for all that kodified-kale just yet, but that's in the back of my mind as I reach for the Téo Gelato and press play on the next tutorial.

Huh, maybe I can use [gluCylinder](http://pyopengl.sourceforge.net/documentation/manual-3.0/gluCylinder.html) with top radius = 0 to make my cone. (Dang, doesn't look like GLU is available on mobile since it is not implemented with OpenGL ES.)

# Programmatic model of a cone

Went ahead and cleaned up a programmatic model of a cone based upon triangle fans.  It's still immediate mode, but gets me closer to something that will load up into a vertex buffer object.

![alt tag](img/cone-topview.png)

This is a view from the top, so it appears as a circle in two dimensions.
