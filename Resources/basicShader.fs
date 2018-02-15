#version 120

varying vec2 texCoord0;

uniform sampler2D diffuse;

void main()
{
    // gl_FragColor = texture2D(diffuse, vec2(0.3, 0.8));
    gl_FragColor = texture2D(diffuse, texCoord0);
}
