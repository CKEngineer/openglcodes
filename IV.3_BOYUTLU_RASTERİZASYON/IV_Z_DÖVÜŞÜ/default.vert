attribute vec3 aPos;
attribute vec3 aColor;
attribute vec2 aTex;

varying vec2 vTexCoord;
varying vec3 vColor;
uniform float scale;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model_x;
uniform mat4 model_y;
uniform mat4 view;
uniform mat4 proj;

void main()
{   gl_Position = proj*view*model_y*model_x*vec4(aPos, 1.0);
	vColor = aColor;
	vTexCoord = aTex;
}
