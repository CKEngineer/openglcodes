#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<GLES2/gl2.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
	
	//Compile checking
	void compileErrors(unsigned int graphic_object);

	void QueryActiveAttribs();

	void QueryUniformVariables();

	void QueryShaders();

	void QueryShaderPrecision(GLenum precision_format);

	void QueryVertexAttrib(GLuint attrib_index);
	
	void RetriveUniformi(const GLchar *name,GLint *params);

	void RetriveUniformf(const GLchar *name,GLfloat *params);

	void SetUniform1i(GLint v0,const GLchar *uniname);

	void SetUniform2i(GLint v0,GLint v1,const GLchar *uniname);

	void SetUniform3i(GLint v0,GLint v1,GLint v2,const GLchar *uniname);

	void SetUniform4i(GLint v0,GLint v1,GLint v2,GLint v3,const GLchar *uniname);

	void SetUniform1f(GLfloat v0,const GLchar *uniname);

	void SetUniform2f(GLfloat v0,GLfloat v1,const GLchar *uniname);

	void SetUniform3f(GLfloat v0,GLfloat v1,GLfloat v2,const GLchar *uniname);

	void SetUniform4f(GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3,const GLchar *uniname);

	void SetMat2x2(const GLfloat *matrix,GLboolean isTranspose,const GLchar *matName);

	void SetMat3x3(const GLfloat *matrix,GLboolean isTranspose,const GLchar *matName);

	void SetMat4x4(const GLfloat *matrix,GLboolean isTranspose,const GLchar *matName);
};
#endif
