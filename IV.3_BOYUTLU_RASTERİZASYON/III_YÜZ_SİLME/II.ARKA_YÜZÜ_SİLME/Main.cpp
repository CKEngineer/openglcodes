#include<iostream>
#include<math.h>

#include"Texture.h"
#include"VBO.h"
#include"EBO.h"
#include"shaderClass.h"
#include "Camera.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define SCR_WIDTH  512
#define SCR_HEIGHT  512
#define CHECK_GL_ERROR CatchErrorAndPrint(__FUNCTION__, __FILE__, __LINE__)


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

float length = 1.0f;
GLfloat vertices[] =
{ //     COORDINATES     			/     COLORS      /          TexCoord  //
-length/2,  -length/2,  length/2,     1.0f, 0.0f, 0.0f,        0.0f, 1.0f,// Front Left Bottom
-length/2,   length/2,  length/2,     0.0f, 1.0f, 0.0f,        0.0f, 0.0f,// Front Right Bottom
 length/2,   length/2,  length/2,     0.0f, 0.0f, 1.0f,        1.0f, 0.0f,// Front Right Top
 length/2,  -length/2,  length/2,     1.0f, 1.0f, 0.0f,        1.0f, 1.0f,// Front Left Top

-length/2,  -length/2,   -length/2,      0.0f,1.0f,1.0f,			0.0f, 1.0f,// Back Left Bottom
-length/2,   length/2,   -length/2,      1.0f,0.0f,1.0f,			0.0f, 0.0f,// Back Right Bottom
 length/2,   length/2,   -length/2,      0.7f,0.2f,0.4f,			1.0f, 0.0f,// Back Right Top
 length/2,  -length/2,   -length/2,      1.0f,1.0f,1.0f,			1.0f, 1.0f//  Back Left Top
};

/*Tex Coordların konumlanması önemli victorun ki stbye uyarlamak için texkoordlar ters konumlanmış*/
// Indices for vertices order



GLuint indices[] = {
// Ön yüz
0,3,2,
2,1,0,
//Arka Yüz
7,4,5,
5,6,7,
//Sağ Yüz
3,7,6,
6,2,3,
//Sol Yüz
4,0,1,
1,5,4,
//Üst Yüz
1,2,6,
6,5,1,
//Alt Yüz
4,7,3,
3,0,4
};


int main()
{

    glfwInit();
	// Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

	// Tell GLFW what version of OpenGL we are using 
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	// Tell GLFW we are using the CORE profile

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D_CUBE_CULLED_BACK_FACE", NULL, NULL);
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
	CHECK_GL_ERROR;
	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	CHECK_GL_ERROR;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	CHECK_GL_ERROR;

	EBO EBO1(indices, sizeof(indices));
	CHECK_GL_ERROR;

	VBO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	CHECK_GL_ERROR;

	VBO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	CHECK_GL_ERROR;

	VBO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    CHECK_GL_ERROR;

    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();
	EBO1.Unbind();
    CHECK_GL_ERROR;

	
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	while (!glfwWindowShouldClose(window))
	{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    shaderProgram.Activate();
	// Handles camera inputs
	camera.Inputs(window);
	// Updates and exports the camera matrix to the Vertex Shader
	camera.Matrix(90.0f, 0.1f, 100.0f, shaderProgram);
	VBO1.Bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, indices);

	if(glGetError() != GL_NO_ERROR){
		CHECK_GL_ERROR;
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