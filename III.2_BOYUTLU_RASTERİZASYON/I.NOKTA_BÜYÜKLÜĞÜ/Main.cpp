#include<iostream>
#include<math.h>

#include<GLFW/glfw3.h>
#include"VBO.h"
#include"EBO.h"
#include"shaderClass.h"

#define SCR_WIDTH  512
#define SCR_HEIGHT  512
#define CHECK_GL_ERROR CatchErrorAndPrint(__FUNCTION__, __FILE__, __LINE__)


void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // Diğer gerekli adaptasyon işlemleri burada yapılabilir.
}

void CatchErrorAndPrint(const char* function, const char* file, int line) {
    GLenum error = glGetError();
    while (error != GL_NO_ERROR) {
        const char* errorStr;
        switch (error) {
            case GL_INVALID_ENUM: errorStr = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE: errorStr = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: errorStr = "GL_INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY: errorStr = "GL_OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            default: errorStr = "Unknown Error"; break;
        }
        std::cout << "OpenGL error in function '" << function << "' (" << file << ":" << line << "): " << errorStr << std::endl;
        error = glGetError();
    }
}

// Vertices coordinates
GLfloat vertices[] =
{
	-0.7f, -0.7f, /*Alt sol noktası */ 0.0f,0.0f,1.0f,//MAVİ
	0.7f, -0.7f, /* Alt sağ noktası */1.0f, 1.0f, 0.0f,//SARI
	0.0f, 0.0f, /* Orijin noktası */ 0.0f,0.0f,0.0f,//SİYAH
	0.7f, 0.7f, /* Üst sağ noktası */ 0.0f,1.0f,0.0f,//YEŞİL
	-0.7f, 0.7f, /* Üst sol noktası */ 1.0f,0.0f,0.0f//KIRMIZI
};


int main()
{
	// Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

	// Tell GLFW what version of OpenGL we are using 
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	// Tell GLFW we are using the CORE profile

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Colorful changing Triangle", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	CHECK_GL_ERROR;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	CHECK_GL_ERROR;
	VBO1.LinkAttrib(VBO1,0,2,GL_FLOAT,5 * sizeof(float), (void*)0); //POZİSYON
	VBO1.LinkAttrib(VBO1,1,3,GL_FLOAT,   5 * sizeof(float), (void*)(2 * sizeof(float)) );//RENK
    CHECK_GL_ERROR;

	GLfloat point_size_float = glGetUniformLocation(shaderProgram.ID,"uPositionSize");
	

    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    shaderProgram.Activate();
    glUniform1f(point_size_float,50.0f);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
    glDrawArrays(GL_POINTS,0,5);
	CHECK_GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwSwapInterval(1);
    glfwSwapBuffers(window);
    glfwPollEvents();
	}



	// Delete all the objects we've created
	VBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}