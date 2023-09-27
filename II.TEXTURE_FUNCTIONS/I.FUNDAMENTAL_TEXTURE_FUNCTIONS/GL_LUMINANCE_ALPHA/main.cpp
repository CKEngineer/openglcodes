#include <GLFW/glfw3.h>
#include <GLES2/gl2.h>
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
    GLFWwindow* window = glfwCreateWindow(512, 512, "OpenGL ES 2.0 Texture Örneği", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /*Dikdörtgenin köşeleri pencerinin üst ve alt köşelerinde birer tane var*/
    GLfloat vertices[] = {
        -1.0f, -1.0f,   // Sol alt köşe
         1.0f, -1.0f,   // Sağ alt köşe
         1.0f,  1.0f,   // Sağ üst köşe
        -1.0f,  1.0f    // Sol üst köşe
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

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    /*Texture oluşturmak için farklı yollar var*/
    /*1.YOL kütüphane stb_image.h başlık dosyasının kullanılması*/


   /*2. YOL Raw data kullanılarak (resmin convert edilmiş hali) kullanılması*/
    unsigned char pixel_textures[] = {
      0,255,0
   };
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, 1,1, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel_textures);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLint uTexture = glGetUniformLocation(shaderProgram, "uTexture");
    glUniform1i(uTexture, 0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//Ekran beyaza boyanır
    //glViewport(0, 0, 1024, 1024);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
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
