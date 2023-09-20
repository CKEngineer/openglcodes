#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>


int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL ES 2.0 İlk Üçgen Örneği", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    float length = 0.7f;

    GLfloat vertices[] = {
        0.0f,  length,
       -length, -length,
        length, -length,
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


   /*SHADER PROGRAMININ YARATILDIĞI KISIM*/
    const char* vertexShaderCode =
        "attribute vec2 aPosition;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "}";

    const char* fragmentShaderCode =
        "precision mediump float;\n"
        "void main() {\n"
        "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindAttribLocation(shaderProgram,13,"aPosition"); // aPosition attribute değerine 0 değeri atandı
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glVertexAttribPointer(13, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(13);




    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDetachShader(shaderProgram,fragmentShader);
    glDetachShader(shaderProgram,vertexShader);
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexBuffer);

    glfwTerminate();
    return 0;
}
