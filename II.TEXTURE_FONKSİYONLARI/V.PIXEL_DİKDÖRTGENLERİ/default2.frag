// Outputs colors in RGBA
precision mediump float;
// Inputs the texture coordinates from the Vertex Shader
varying vec2 vTexCoord;
varying vec3 vColor;
// Gets the Texture Unit from the main function
uniform sampler2D tex1;

void main()
{
	gl_FragColor = texture2D(tex1, vTexCoord);
   //gl_FragColor = vec4(vColor,1.0f);
}
/*#version 330 core
out vec4 FragColor;
void main()
{
   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
}*/