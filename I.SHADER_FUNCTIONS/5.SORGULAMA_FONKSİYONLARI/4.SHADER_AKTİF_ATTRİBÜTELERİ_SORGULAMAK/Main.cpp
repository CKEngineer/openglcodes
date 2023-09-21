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
GLfloat vertices[] = {
        //Coordinates of triangle vertex
        0.0f,  0.6f, /*Üst Köşe*/1.0f,0.0f,0.0f,//RED
       -0.6f, -0.6f,/*Sol Alt Köşe*/0.0f,1.0f,0.0f,//GREEN
        0.6f, -0.6f,/*Lower Rigth Vertex*/0.0f,0.0f,1.0f//BLUE
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
    //aPosition Shader Programında glBindAttribLocation ile bağlandı
	VBO1.LinkAttrib(VBO1,0,2,GL_FLOAT,5 * sizeof(float), (void*)0); //GL_FALSE 5(arrayin 1 satırının uzunluğu kadr) * sizeof(float) // Ve nereden başladığı (void *)
	//aColor Shader Programında glBindAttribLocation ile bağlandı
	VBO1.LinkAttrib(VBO1,1,3,GL_FLOAT,5 * sizeof(float), (void*)(2 * sizeof(float)) );
    CHECK_GL_ERROR;


    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();
	EBO1.Unbind();

    shaderProgram.QueryActiveAttribs();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
    
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    shaderProgram.Activate();
    glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, indices);
	if(glGetError() != GL_NO_ERROR){
        break;
	}
    
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