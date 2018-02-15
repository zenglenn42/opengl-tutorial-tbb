#version 120

attribute vec3 position;
attribute vec2 texCoordIn;

varying vec2 texCoord;

void main()
{
    gl_Position = vec4(position, 1.0);
    texCoord = texCoordIn;
}
