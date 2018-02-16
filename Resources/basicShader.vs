#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
    //gl_Position = vec4(position, 1.0);
    
    gl_Position = transform * vec4(position, 1.0); // last param affects xlation
    texCoord0 = texCoord;
    
    vec4 normalTransform = transform * vec4(normal, 0.0); // 0.0 means light is invariant of translation
    normal0 = (normalTransform).xyz;
}
