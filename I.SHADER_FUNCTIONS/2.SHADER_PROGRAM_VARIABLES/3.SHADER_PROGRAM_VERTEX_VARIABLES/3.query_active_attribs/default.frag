precision mediump float;
varying vec3 vColor;
void main() {
    gl_FragColor = vec4(vColor, 1.0);
};



/*
precision mediump float;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;GLfloat time = 0.0f;
    vec3 color = vec3(0.);
    color = vec3(st.x,st.y,abs(sin(u_time)));

    gl_FragColor = vec4(color,1.0f);
};
*/
