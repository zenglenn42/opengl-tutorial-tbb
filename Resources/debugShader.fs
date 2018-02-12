#version 120

void main() {
    // Want to use vertex-shader influenced color?
    
    gl_FragColor = gl_Color;
    
    
    
    // Want to override upstream vertex-shader color?
    // Hard-code it here ...
    
    //gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); // green
}
