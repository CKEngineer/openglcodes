#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
#define SCR_WIDTH 1200
#define SCR_HEIGHT 720

/*Pencere küçültülüp büyütüldüğünde içindeki yapıda buna adapte olacaktır (Basic seviye)*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // Diğer gerekli adaptasyon işlemleri burada yapılabilir.
}

int main() {
    /*Pencerenin oluşturulması*/
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL ES 2.0 Texture Örneği", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /*Dikdörtgenin köşeleri pencerinin üst ve alt köşelerinde birer tane var*/
    GLfloat vertices[] = {
        -0.7f, -0.7f,   // Sol alt köşe
         0.7f, -0.7f,   // Sağ alt köşe
         0.7f,  0.7f,   // Sağ üst köşe
        -0.7f,  0.7f    // Sol üst köşe
    };

    GLuint indices[] = {
        0, 1, 2,   // İlk üçgen
        0, 2, 3    // İkinci üçgen
    };

    GLfloat texCoord[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint texCoordBuffer;
    glGenBuffers(1, &texCoordBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

    const char* vertexShaderCode =
        "attribute vec2 aPosition;\n"
        "attribute vec2 aTexCoord;\n"
        "varying vec2 vTexCoord;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPosition, 0.0, 1.0);\n"
        "    vTexCoord = aTexCoord;\n"
        "}";

    const char* fragmentShaderCode =
        "precision mediump float;\n"
        "varying vec2 vTexCoord;\n"
        "uniform sampler2D uTexture;\n"
        "void main() {\n"
        "    gl_FragColor = texture2D(uTexture, vTexCoord);\n"
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
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint aPosition = glGetAttribLocation(shaderProgram, "aPosition");
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(aPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(aPosition);

    GLint aTexCoord = glGetAttribLocation(shaderProgram, "aTexCoord");
    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glVertexAttribPointer(aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(aTexCoord);


unsigned char r_with_no_alpha[] = {
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,  
    255,0,0,
    255,0,0,
    255,0,0,
    255,0,0,

};

unsigned char r_with_alpha[] = {
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,

    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,

    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,

    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,

    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,

    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,

    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,

    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
    255,0,0,128,
};

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture2);
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, 8,8, 0, GL_RGB, GL_UNSIGNED_BYTE, r_with_no_alpha);
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE1); // uniform değer gönderiyoruz tekstür olarak bu değeri gönderiyoruz
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, 8,8, 0, GL_RGBA, GL_UNSIGNED_BYTE, r_with_alpha);
    glGenerateMipmap(GL_TEXTURE_2D);


    GLint uTexture = glGetUniformLocation(shaderProgram, "uTexture");
    

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Ekran beyaza boyanır

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /*GL_RGBA ile yapılmış olan alpha değerleninin hesaplanmasını sağlar*/
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        glViewport(0,0,SCR_WIDTH/2,SCR_HEIGHT);
        glUniform1i(uTexture, 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glViewport(SCR_WIDTH/2,0,SCR_WIDTH/2,SCR_HEIGHT);
        glUniform1i(uTexture, 1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(1, &texture);
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &texCoordBuffer);
    glDeleteBuffers(1, &elementBuffer);

    glfwTerminate();
    return 0;
}
