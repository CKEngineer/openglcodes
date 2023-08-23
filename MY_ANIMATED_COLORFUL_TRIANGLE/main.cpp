#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
#include <stdio.h>


int main() {
    if (!glfwInit()) {
        return -1;
    }
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ES 2.0 My First Triangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 

    GLfloat vertices[] = {
        //Coordinates of triangle vertex
        0.0f,  0.6f, /*Upper Vertex*/1.0f,0.0f,0.0f,//RED
       -0.6f, -0.6f,/*Lower Left Vertex*/0.0f,1.0f,0.0f,//GREEN
        0.6f, -0.6f,/*Lower Rigth Vertex*/0.0f,0.0f,1.0f//BLUE
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vertexShaderCode =
        "attribute vec2 aPosition;\n"
        "attribute vec3 aColor;\n"
        "varying vec3 vColor;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "    vColor = aColor;\n"
        "}";

    const char* fragmentShaderCode =
        "precision mediump float;\n"
        "uniform vec2 u_resolution;\n"
        "uniform float u_time;\n"
        "void main() {\n"
        "vec2 st = gl_FragCoord.xy/u_resolution.xy;\n"
        "st.x *= u_resolution.x/u_resolution.y;\n"
        "vec3 color = vec3(0.);\n"
        "color = vec3(st.x,st.y,abs(sin(u_time)));\n"
        "gl_FragColor = vec4(color,1.0);\n"
        "};";
   
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    /*Solution 1
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    GLint aPosition = glGetAttribLocation(shaderProgram, "aPosition");
    glVertexAttribPointer(aPosition, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(aPosition);
    GLint aColor= glGetAttribLocation(shaderProgram, "aColor");
    glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(aColor);
    */

    /*Solution 2*/
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindAttribLocation(shaderProgram,0,"aPosition");
    glBindAttribLocation(shaderProgram,1,"aColor");
    glLinkProgram(shaderProgram);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    /*In thıs code CPU and GPU will communicate through uniform variables*/
    GLfloat time = 0.0f;
    GLfloat time_float = glGetUniformLocation(shaderProgram,"u_time");
    GLfloat resoulution_float = glGetUniformLocation(shaderProgram,"u_resolution");

    

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        glUniform2f(resoulution_float,800,600);
        glUniform1f(time_float,time);
        time = time + 0.01f;
        if(time > 2*3.14){
           time = 0.0f;
        }
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vertexBuffer);

    glfwTerminate();
    return 0;
}
