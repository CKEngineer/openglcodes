attribute vec3 aPos;

varying vec3 vTexCoord;
uniform float scale;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model_x;
uniform mat4 model_y;
uniform mat4 model_z;
uniform mat4 view;
uniform mat4 proj;

void main()
{   
	gl_Position = proj*view*model_z*model_y*model_x*vec4(aPos,1.0);
	vTexCoord =  vec3(aPos.x, aPos.y, aPos.z);
}
