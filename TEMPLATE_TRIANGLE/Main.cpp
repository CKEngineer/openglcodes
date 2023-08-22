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
	-0.7f, -0.7f, /*Lower left corner */ 1.0f,0.0f,0.0f,
	0.7f, -0.7f, /* Lower right corner */0.0f, 1.0f, 0.0f,
	0.0f, 0.7f, /* Upper corner */ 0.0f,0.0f,1.0f,
};

GLuint indices[] =
{
	0, 1, 2, // Lower left triangle
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Template Triangle", NULL, NULL);
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

	EBO EBO1(indices, sizeof(indices));
	CHECK_GL_ERROR;

    GLint aPosition = glGetAttribLocation(shaderProgram.ID, "aPosition");
	VBO1.LinkAttrib(VBO1,aPosition,2,GL_FLOAT,5 * sizeof(float), (void*)0); //GL_FALSE 5(arrayin 1 satırının uzunluğu kadr) * sizeof(float) // Ve nereden başladığı (void *)
	GLint aColor = glGetAttribLocation(shaderProgram.ID, "aColor");
	VBO1.LinkAttrib(VBO1,aColor,3,GL_FLOAT,   5 * sizeof(float), (void*)(2 * sizeof(float)) );
    CHECK_GL_ERROR;


    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();
	EBO1.Unbind();


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
    
    
    glClearColor(0.07f, 0.13f, 0.17f, 0.8f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    shaderProgram.Activate();
    glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices);
	CHECK_GL_ERROR;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	
    glfwSwapBuffers(window);
    glfwPollEvents();
	}



	// Delete all the objects we've created
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}