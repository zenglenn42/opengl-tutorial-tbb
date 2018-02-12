#version 120

void main(void) {
    
    // Simulate what the fixed pipeline does to the vertex position.

    // Allows fixed-pipeline calls to generate your mesh:
    //    glBegin(GL_LINES); glVertex3f(-0.5f, -0.5f, 0.0);glVertex3f(0.5, -0.5f, 0.0) ;glEnd();
    // with sane rendering through your debug shader.

    gl_Position = ftransform();

    
    
    // Allow glColor*() calls to drive inputs to the vs/fs pathway.
    gl_FrontColor = gl_Color;
    
    // Override incoming color from the cpu side of the code.
    //gl_FrontColor = vec4(1.0, 1.0, 0.0, 1.0);   // hardcode to some debug color
}
