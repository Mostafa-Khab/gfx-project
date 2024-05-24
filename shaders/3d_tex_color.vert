#version 110
uniform mat4 MVP;
attribute vec4 vCol;
attribute vec3 vPos;
attribute vec2 vTex;
varying vec4 color;
varying vec2 texCoord;
void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    color = vCol;
    texCoord = vTex;
}
