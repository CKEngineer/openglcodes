#include"Texture.h"

Texture::Texture(const GLvoid *bytes,GLsizei width,GLsizei height,GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	// Assigns the type of the texture ot the texture object
	type = texType;
	slot_holder = slot;
    
	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Configures the way the texture repeats (if it does at all)

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	//float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	//Queries the textures according to active slot
	//Process is has been done while texture creating process 
	glGetTexParameteriv(texType,GL_TEXTURE_MAG_FILTER,&texparameters[0]);
	glGetTexParameteriv(texType,GL_TEXTURE_MIN_FILTER,&texparameters[1]);
	glGetTexParameteriv(texType,GL_TEXTURE_WRAP_S,&texparameters[2]);
	glGetTexParameteriv(texType,GL_TEXTURE_WRAP_T,&texparameters[3]);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, format, width, height, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}








Texture::Texture(
	const GLvoid *positive_x,
	const GLvoid *negative_x,
	const GLvoid *positive_y,
	const GLvoid *negative_y,
	const GLvoid *positive_z,
	const GLvoid *negative_z,GLsizei width,GLsizei height,GLenum texType, GLenum slot, GLenum format, GLenum pixelType){

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	// Assigns the type of the texture ot the texture object
	type = texType;
	slot_holder = slot;

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Configures the way the texture repeats (if it does at all)

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	//float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	//Queries the textures according to active slot
	//Process is has been done while texture creating process 
	glGetTexParameteriv(texType,GL_TEXTURE_MAG_FILTER,&texparameters[0]);
	glGetTexParameteriv(texType,GL_TEXTURE_MIN_FILTER,&texparameters[1]);
	glGetTexParameteriv(texType,GL_TEXTURE_WRAP_S,&texparameters[2]);
	glGetTexParameteriv(texType,GL_TEXTURE_WRAP_T,&texparameters[3]);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width, height, 0, format, pixelType, positive_x);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width, height, 0, format, pixelType, negative_x);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width, height, 0, format, pixelType, positive_y);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width, height, 0, format, pixelType, negative_y);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width, height, 0, format, pixelType, positive_z);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width, height, 0, format, pixelType, negative_z);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);

}


void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

void Texture::QueryTexture()
{   std::cout << "Query Texture Results:" << std::endl;
	if(!glIsTexture(ID)){
        std::cout << "This object is not a texture" << std::endl;
	}
	else{
		switch(texparameters[0]){
			case GL_LINEAR:
			std::cout << "GL_TEXTURE_MAG_FILTER = GL_LINEAR" << std::endl;
			break;
			case GL_NEAREST:
			std::cout << "GL_TEXTURE_MAG_FILTER = GL_NEAREST" << std::endl;
			break;
			default:
			std::cout << "GL_TEXTURE_MAG_FILTER = Unknown Type" << std::endl;
			break;
		}

		switch(texparameters[1]){
			case GL_NEAREST:
			std::cout << "GL_TEXTURE_MIN_FILTER = GL_NEAREST" << std::endl;
			break;
			case GL_LINEAR:
			std::cout << "GL_TEXTURE_MIN_FILTER = GL_LINEAR" << std::endl;
			break;
			case GL_NEAREST_MIPMAP_NEAREST:
			std::cout << "GL_TEXTURE_MIN_FILTER = GL_NEAREST_MIPMAP_NEAREST" << std::endl;
			break;
			case GL_LINEAR_MIPMAP_NEAREST:
			std::cout << "GL_TEXTURE_MIN_FILTER = GL_LINEAR_MIPMAP_NEAREST" << std::endl;
			break;
			case GL_NEAREST_MIPMAP_LINEAR:
			std::cout << "GL_TEXTURE_MIN_FILTER = GL_NEAREST_MIPMAP_LINEAR" << std::endl;
			break;
			case GL_LINEAR_MIPMAP_LINEAR:
			std::cout << "GL_TEXTURE_MIN_FILTER = GL_LINEAR_MIPMAP_LINEAR" << std::endl;
			break;
			default:
			std::cout << "GL_TEXTURE_MIN_FILTER = Unknown Type" << std::endl;
			break;
		}

		switch(texparameters[2]){
			case GL_CLAMP_TO_EDGE:
			std::cout << "GL_TEXTURE_WRAP_S = GL_CLAMP_TO_EDGE" << std::endl;
			break;
			case GL_MIRRORED_REPEAT:
			std::cout << "GL_TEXTURE_WRAP_S = GL_MIRRORED_REPEAT" << std::endl;
			break;
			case GL_REPEAT:
			std::cout << "GL_TEXTURE_WRAP_S = GL_REPEAT" << std::endl;
			break;
			default:
			std::cout << "GL_TEXTURE_WRAP_S = Unknown Type" << std::endl;
			break;
		}
		switch(texparameters[3]){
			case GL_CLAMP_TO_EDGE:
			std::cout << "GL_TEXTURE_WRAP_T = GL_CLAMP_TO_EDGE" << std::endl;
			break;
			case GL_MIRRORED_REPEAT:
			std::cout << "GL_TEXTURE_WRAP_T = GL_MIRRORED_REPEAT" << std::endl;
			break;
			case GL_REPEAT:
			std::cout << "GL_TEXTURE_WRAP_T = GL_REPEAT" << std::endl;
			break;
			default:
			std::cout << "GL_TEXTURE_WRAP_T = Unknown Type" << std::endl;
			break;			
		}
	}
}

void Texture::UpdateTexture(const GLvoid *bytes,GLint xoffset,GLint yoffset,GLsizei width_of_update,GLsizei height_of_update,GLenum texType,GLenum format, GLenum pixelType){
    glActiveTexture(slot_holder);
	glBindTexture(GL_TEXTURE_2D,ID);
}