// Outputs colors in RGBA
precision mediump float;
// Inputs the texture coordinates from the Vertex Shader
varying vec2 vTexCoord;
varying vec3 vColor;
// Gets the Texture Unit from the main function
uniform int tex_switch;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
   vec4 texColor1 = texture2D(tex0,vTexCoord);
   vec4 texColor2 = texture2D(tex1,vTexCoord);
   vec4 texColor3 = texture2D(tex2,vTexCoord);
   
   if(tex_switch == 1){
      gl_FragColor = vec4(vColor,1.0);
   }
   else if(tex_switch == 2){
      gl_FragColor = texColor1;
   }
   else if(tex_switch == 3){
      gl_FragColor = texColor2;
   }
   else if(tex_switch == 4){
      gl_FragColor = texColor3;
   }
   else if(tex_switch == 5){
      gl_FragColor = vec4(texColor1.r,texColor2.g,texColor3.b,1.0);
   }
}
	
   //gl_FragColor = vec4(vColor,1.0f);

