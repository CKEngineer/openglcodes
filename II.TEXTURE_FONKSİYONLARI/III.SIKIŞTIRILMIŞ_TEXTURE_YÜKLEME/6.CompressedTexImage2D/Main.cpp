#include<iostream>
#include<math.h>

#include"Texture.h"
#include"VBO.h"
#include"EBO.h"
#include"shaderClass.h"
#include "dds_loader.h"

#define SCR_WIDTH  640
#define SCR_HEIGHT 960
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

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,        0.0f, 1.0f,   // Sol alt köşe// Lower left corner
-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,        0.0f, 0.0f, // Sol üst köşe // Upper left corner
 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,        1.0f, 0.0f,   // Sağ üst köşe// Upper right corner
 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,        1.0f, 1.0f // Sağ alt köşe // Lower right corner
/*Tex Coordların konumlanması önemli victorun ki stbye uyarlamak için texkoordlar ters konumlanmış*/
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TEMPLATE_TEXTURE", NULL, NULL);
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

    GLint aPos = glGetAttribLocation(shaderProgram.ID,"aPos");
	CHECK_GL_ERROR;
	VBO1.LinkAttrib(VBO1, aPos, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	CHECK_GL_ERROR;

	GLint aColor = glGetAttribLocation(shaderProgram.ID,"aColor");
	VBO1.LinkAttrib(VBO1, aColor, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	CHECK_GL_ERROR;

    GLint aTex = glGetAttribLocation(shaderProgram.ID,"aTex");
	CHECK_GL_ERROR;
	VBO1.LinkAttrib(VBO1, aTex, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    CHECK_GL_ERROR;

    // Unbind the buffer and shader program after setting up attributes
    VBO1.Unbind();
	EBO1.Unbind();
    CHECK_GL_ERROR;

	/*Compressed Texture işlemleri başlıyor !*/
    
    /*Öncelikle bu cihazda compressed texture format tipleri destekleniyor mu ona bakıyoruz*/
	if(GL_NUM_COMPRESSED_TEXTURE_FORMATS > 0){
		printf("Tebrikler compresed texture format destekleniyor\n");
	}

    GLint numFormats;
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numFormats);

    GLint* formats = new GLint[numFormats];
    glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, formats);

    std::cout << "Supported Compressed Texture Formats:" << std::endl;
    for (int i = 0; i < numFormats; ++i) {
        std::cout << "Format #" << i << ": " << std::hex << formats[i] << std::dec << std::endl;
    }

	unsigned char pixels[] = {
    255,0,0
	};


    GLuint ID;
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	DDS_TEXTURE* sample_texture = new DDS_TEXTURE();
	bool do_flip = false;
	load_dds_from_file("pexels-travis-rupert-1032650.dds", &sample_texture, do_flip);
	glCompressedTexImage2D(GL_TEXTURE_2D, 0, sample_texture->format, sample_texture->width, sample_texture->height, 0, sample_texture->sz, sample_texture->pixels);
    delete (sample_texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Assigns the image to the OpenGL Texture object
	
	// Generates MipMaps
	

	// Deletes the image data as it is already in the OpenGL Texture object

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified

	CHECK_GL_ERROR;
	CHECK_GL_ERROR;
    
	
	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.Activate();
	glUniform1f(glGetUniformLocation(shaderProgram.ID, "scale"), 1.0f);
	VBO1.Bind();
    glBindBuffer(GL_ARRAY_BUFFER, VBO1.ID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

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