attribute vec3 aPos;
attribute vec3 aColor;
attribute vec2 aTex;

varying vec2 vTexCoord;
varying vec3 vColor;
uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	vColor = aColor;
	vTexCoord = aTex;
}
