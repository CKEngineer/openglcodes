#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<GLFW/glfw3.h>
#include<GLES2/gl2.h>
#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLenum slot_holder;
	GLint texparameters[4]; //Since there are 4 symbolic parameters for this function
	Texture(const GLvoid *bytes,GLsizei width,GLsizei height,GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    Texture(
		const GLvoid *positive_x,
		const GLvoid *negative_x,

		const GLvoid *positive_y,
		const GLvoid *negative_y,

		const GLvoid *positive_z,
		const GLvoid *negative_z,
		GLsizei width,GLsizei height,GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
    //Queries Texture
	void QueryTexture();
    //Updates Texture
	void UpdateTexture(const GLvoid *bytes,GLint xoffset,GLint yoffset,GLsizei width_of_update,GLsizei height_of_update,GLenum texType,GLenum format, GLenum pixelType);
};
#endif