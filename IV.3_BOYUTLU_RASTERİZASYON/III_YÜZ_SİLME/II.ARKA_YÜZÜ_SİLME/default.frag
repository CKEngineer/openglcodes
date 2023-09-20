precision mediump float;
varying vec2 vTexCoord;
varying vec3 vColor;
uniform sampler2D tex0;

void main()
{
	gl_FragColor = vec4(vColor,1.0f);
}
