#include <math.h>
#include <OpenGL/gl.h>

void circleFan(GLdouble base, GLint slices) {
    GLfloat x, y, angle;    // Storage for coordinates and angles
    int toggleColor = 0;    // Used to flag alternating colors

    // Enforce algorithmic requirement for even number of slices.

    GLint evenSlices = slices;
    if (evenSlices % 2 != 0) {
        evenSlices = 2 * (slices / 2);
        evenSlices = (evenSlices > 0) ? evenSlices : 2;
    }

    // Loop around in clockwise direction, specifying evenly-spaced
    // radial points as the vertices of the triangle fan.
    
    GLfloat angleStep = (2.0 * M_PI) / (GLfloat)evenSlices;

    angle = 0.0f;
    for (GLint i = 0; i <= evenSlices; ++i) {

        // Calculate x and y position of the next vertex.

        x = (base / 2.0f) * sin(angle);
        y = (base / 2.0f) * cos(angle);

        // Alternate color between green and blue.

        if ((toggleColor % 2) == 0)
             glColor3f(0.2f, 0.6f, 0.3f);
        else
             glColor3f(0.2f, 0.3f, 0.6f);

        // Toggle fill color.

        toggleColor++;

        // Specify the next vertext for the triangle fan

        glVertex3f(x, y, 0.0f);

        angle += angleStep;
    }
}

void gSolidCone(GLdouble base, GLdouble height, GLint slices) {

    glPushMatrix();
    glFrontFace(GL_CW);

    // cone top

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, height);  // pinnacle
        circleFan(base, slices);
    glEnd();

    // cone bottom

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);
        circleFan(base, slices);
    glEnd();

    glPopMatrix();
}
