precision mediump float;
varying vec3 vTexCoord;
uniform samplerCube tex0;

void main()
{
	gl_FragColor = textureCube(tex0,vTexCoord);
}
