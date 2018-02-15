#version 120

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
    //gl_Position = vec4(position, 1.0);
    
    gl_Position = transform * vec4(position, 1.0); // last param affects xlation
    texCoord0 = texCoord;
}
