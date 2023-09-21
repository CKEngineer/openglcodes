attribute vec2 aPosition;
attribute vec3 aColor;
varying vec3 vColor;

void main() {
    gl_Position = vec4(aPosition,0.0f,1.0f);
    vColor = aColor;
};
