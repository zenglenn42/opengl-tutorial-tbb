#include <math.h>

const GLfloat GL_PI = M_PI;

GLint slicesPerSemiCircle = 12;     // Specifying slices this way ensures and
                                    // even number for the entire circle, an
					// algorithmic requirement.

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 75.0f);  // pinnacle
        makeCircularTriangleFan(slicesPerSemiCircle);
    glEnd();

    // cone bottom
    //
    // NB: The "front" of this polygon is actually facing
    //     into the interior of the cone.  So you would have
    //     to specify glPolygonMode(GL_BACK, GL_FILL) to
    //     make the bottom appear solid.

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f);
        makeCircularTriangleFan(slicesPerSemiCircle);
    glEnd();



//-----------------------------------------------------------------------------
// Construct a clockwise circular triangle fan.  
//
// Assumes the initial vertext has already been added to the model 
// before calling this function.
//
// Base of cone assumed to lie in xy-plane (at z = 0, by default)
// with tip along the positive z-axis prior to calling this function.
//-----------------------------------------------------------------------------
void makeCircularTriangleFan(GLint slicesPerSemiCircle, GLfloat z = 0.0f) {
    GLfloat x, y, angle;    // Storage for coordinates and angles
#if 0
    int toggleColor = 0;    // Used to flag alternating colors
#endif

    // Loop around in clockwise direction, specifying 
    // evenly-spaced radial points as the vertices of the triangle fan

    GLfloat angleStep = GL_PI / (GLfloat)slicesPerSemiCircle;
    
    angle = 0.0f;
    for (GLint i = 0; i <= 2 * slicesPerSemiCircle; ++i) {

        // Calculate x and y position of the next vertex
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);

#if 0
        // Alternate color between green and blue
        if ((toggleColor % 2) == 0)
             glColor3f(0.2f, 0.6f, 0.3f);
        else
             glColor3f(0.2f, 0.3f, 0.6f);

        // Increment to toggle fill color for next triangle
        toggleColor++;
#endif

        // Specify the next vertext for the triangle fan
        glVertex3f(x, y, z);

        angle += angleStep;
    }    
} // makeCircularTriangleFan

