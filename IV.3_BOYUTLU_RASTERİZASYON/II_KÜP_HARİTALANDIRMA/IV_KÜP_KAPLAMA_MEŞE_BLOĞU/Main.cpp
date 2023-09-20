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



float length = 0.8f;
GLfloat vertices[] =
{ //     COORDINATES     			    TexCoord  //
	//   Coordinates 
	-length, -length,  length,       				//        7--------6
	 length, -length,  length,       				//       /|       /|
	 length, -length, -length,       				//      4--------5 |
	-length, -length, -length,       				//      | |      | |
	-length,  length,  length,       				//      | 3------|-2
	 length,  length,  length,       				//      |/       |/
	 length,  length, -length,       				//      0--------1
	-length,  length, -length
};


GLuint indices[] = {
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
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

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D_OAK_LOG", NULL, NULL);
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
	Shader shaderProgram("vertex.glsl", "fragment.glsl");
	CHECK_GL_ERROR;
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	CHECK_GL_ERROR;
	EBO EBO1(indices, sizeof(indices));
	CHECK_GL_ERROR;
	VBO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	CHECK_GL_ERROR;

    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();
	EBO1.Unbind();
    CHECK_GL_ERROR;

	
	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
    unsigned char ust_yuz[]={95,74,43,76,61,38,95,74,43,116,90,54,95,74,43,76,61,38,95,74,43,95,74,43,116,90,54,76,61,38,95,74,43,95,74,43,76,61,38,95,74,43,95,74,43,95,74,43,76,61,38,184,148,95,184,148,95,184,148,95,184,148,95,175,143,85,184,148,95,175,143,85,194,157,98,175,143,85,175,143,85,184,148,95,184,148,95,184,148,95,184,148,95,76,61,38,95,74,43,184,148,95,126,98,55,126,98,55,150,116,65,150,116,65,159,132,77,150,116,65,159,132,77,159,132,77,159,132,77,159,132,77,150,116,65,150,116,65,194,157,98,95,74,43,95,74,43,184,148,95,126,98,55,194,157,98,194,157,98,184,148,95,184,148,95,184,148,95,184,148,95,175,143,85,184,148,95,184,148,95,184,148,95,150,116,65,184,148,95,95,74,43,95,74,43,175,143,85,150,116,65,184,148,95,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,184,148,95,159,132,77,175,143,85,95,74,43,76,61,38,184,148,95,159,132,77,184,148,95,175,143,85,150,116,65,150,116,65,159,132,77,159,132,77,150,116,65,150,116,65,175,143,85,184,148,95,150,116,65,175,143,85,76,61,38,95,74,43,175,143,85,150,116,65,175,143,85,175,143,85,126,98,55,175,143,85,175,143,85,175,143,85,175,143,85,150,116,65,175,143,85,175,143,85,150,116,65,184,148,95,95,74,43,95,74,43,175,143,85,159,132,77,184,148,95,175,143,85,150,116,65,175,143,85,159,132,77,159,132,77,175,143,85,159,132,77,175,143,85,184,148,95,159,132,77,175,143,85,95,74,43,95,74,43,175,143,85,159,132,77,184,148,95,175,143,85,150,116,65,175,143,85,159,132,77,150,116,65,175,143,85,150,116,65,175,143,85,184,148,95,150,116,65,175,143,85,95,74,43,76,61,38,175,143,85,159,132,77,184,148,95,175,143,85,150,116,65,175,143,85,175,143,85,175,143,85,175,143,85,159,132,77,175,143,85,175,143,85,150,116,65,175,143,85,76,61,38,95,74,43,175,143,85,150,116,65,184,148,95,175,143,85,150,116,65,150,116,65,126,98,55,150,116,65,159,132,77,159,132,77,175,143,85,184,148,95,159,132,77,175,143,85,95,74,43,95,74,43,175,143,85,159,132,77,184,148,95,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,175,143,85,184,148,95,150,116,65,175,143,85,95,74,43,76,61,38,184,148,95,159,132,77,184,148,95,184,148,95,175,143,85,184,148,95,184,148,95,184,148,95,184,148,95,184,148,95,194,157,98,184,148,95,150,116,65,175,143,85,76,61,38,95,74,43,184,148,95,159,132,77,150,116,65,159,132,77,150,116,65,150,116,65,150,116,65,150,116,65,150,116,65,150,116,65,150,116,65,150,116,65,150,116,65,184,148,95,95,74,43,95,74,43,184,148,95,184,148,95,184,148,95,175,143,85,175,143,85,184,148,95,175,143,85,175,143,85,194,157,98,175,143,85,175,143,85,184,148,95,184,148,95,184,148,95,95,74,43,95,74,43,76,61,38,95,74,43,95,74,43,95,74,43,76,61,38,95,74,43,95,74,43,116,90,54,76,61,38,95,74,43,95,74,43,76,61,38,116,90,54,95,74,43,95,74,43,};
    unsigned char yan_yuz[]={116,90,54,76,61,38,145,113,66,116,90,54,116,90,54,56,43,24,145,113,66,116,90,54,116,90,54,56,43,24,116,90,54,145,113,66,76,61,38,145,113,66,116,90,54,95,74,43,116,90,54,76,61,38,152,120,73,95,74,43,116,90,54,56,43,24,152,120,73,95,74,43,116,90,54,56,43,24,116,90,54,145,113,66,76,61,38,116,90,54,116,90,54,95,74,43,116,90,54,56,43,24,95,74,43,95,74,43,116,90,54,56,43,24,152,120,73,95,74,43,116,90,54,76,61,38,116,90,54,76,61,38,76,61,38,116,90,54,116,90,54,95,74,43,145,113,66,56,43,24,116,90,54,95,74,43,116,90,54,76,61,38,116,90,54,95,74,43,116,90,54,95,74,43,116,90,54,56,43,24,76,61,38,116,90,54,145,113,66,95,74,43,145,113,66,76,61,38,116,90,54,95,74,43,116,90,54,56,43,24,116,90,54,95,74,43,152,120,73,95,74,43,116,90,54,95,74,43,116,90,54,76,61,38,145,113,66,116,90,54,145,113,66,116,90,54,76,61,38,116,90,54,145,113,66,76,61,38,116,90,54,76,61,38,152,120,73,95,74,43,145,113,66,76,61,38,116,90,54,76,61,38,145,113,66,116,90,54,95,74,43,116,90,54,76,61,38,116,90,54,145,113,66,95,74,43,95,74,43,116,90,54,145,113,66,116,90,54,145,113,66,116,90,54,116,90,54,76,61,38,145,113,66,116,90,54,95,74,43,116,90,54,56,43,24,116,90,54,145,113,66,116,90,54,95,74,43,145,113,66,116,90,54,116,90,54,145,113,66,95,74,43,116,90,54,95,74,43,145,113,66,116,90,54,116,90,54,76,61,38,56,43,24,152,120,73,116,90,54,116,90,54,95,74,43,145,113,66,116,90,54,95,74,43,145,113,66,95,74,43,145,113,66,95,74,43,145,113,66,116,90,54,116,90,54,116,90,54,76,61,38,152,120,73,116,90,54,116,90,54,95,74,43,116,90,54,116,90,54,95,74,43,145,113,66,76,61,38,145,113,66,116,90,54,56,43,24,116,90,54,116,90,54,116,90,54,116,90,54,145,113,66,116,90,54,95,74,43,116,90,54,56,43,24,116,90,54,95,74,43,116,90,54,76,61,38,145,113,66,116,90,54,56,43,24,116,90,54,116,90,54,76,61,38,116,90,54,145,113,66,116,90,54,95,74,43,116,90,54,56,43,24,152,120,73,116,90,54,116,90,54,56,43,24,152,120,73,116,90,54,76,61,38,116,90,54,152,120,73,76,61,38,116,90,54,116,90,54,145,113,66,95,74,43,145,113,66,56,43,24,152,120,73,95,74,43,116,90,54,56,43,24,116,90,54,116,90,54,95,74,43,116,90,54,152,120,73,116,90,54,76,61,38,116,90,54,145,113,66,116,90,54,116,90,54,76,61,38,145,113,66,95,74,43,116,90,54,76,61,38,116,90,54,116,90,54,116,90,54,116,90,54,145,113,66,116,90,54,76,61,38,145,113,66,116,90,54,116,90,54,145,113,66,56,43,24,116,90,54,76,61,38,116,90,54,76,61,38,76,61,38,145,113,66,116,90,54,116,90,54,145,113,66,116,90,54,76,61,38,145,113,66,76,61,38,116,90,54,145,113,66,76,61,38,116,90,54,76,61,38,116,90,54,116,90,54,76,61,38,145,113,66,116,90,54,95,74,43,};
    
    	// Creates the cubemap texture object

	unsigned int cubemapTexture;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);//pixel store i unpack alignment
	glGenTextures(1, &cubemapTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
// Pozitif X yüzeyine büyük ana texture'ı yükle
glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X ,0,   0,0,16,16,GL_RGB,GL_UNSIGNED_BYTE,yan_yuz);

// Negatif X yüzeyine büyük ana texture'ı yükle
glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0,   0, 0, 16, 16, GL_RGB, GL_UNSIGNED_BYTE, yan_yuz);

// Pozitif Y yüzeyine büyük ana texture'ı yükle
glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0,   0, 0, 16, 16, GL_RGB, GL_UNSIGNED_BYTE, ust_yuz);

// Negatif Y yüzeyine büyük ana texture'ı yükle
glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0,   0, 0, 16, 16, GL_RGB, GL_UNSIGNED_BYTE, ust_yuz);

// Pozitif Z yüzeyine büyük ana texture'ı yükle
glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0,   0, 0, 16, 16, GL_RGB, GL_UNSIGNED_BYTE, yan_yuz);

// Negatif Z yüzeyine büyük ana texture'ı yükle
glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0,   0, 0, 16, 16, GL_RGB, GL_UNSIGNED_BYTE, yan_yuz);

	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shaderProgram.ID, "tex0");
	// Shader needs to be activated before changing the value of a uniform
	shaderProgram.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, 0);

	CHECK_GL_ERROR;
	
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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