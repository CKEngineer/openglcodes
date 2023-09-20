#include"shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Object and get its reference
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader);

	// Create Fragment Shader Object and get its reference
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader);

	// Create Shader Program Object and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Bind Attribute Location here:
    glBindAttribLocation(ID,0,"aPosition");
	glBindAttribLocation(ID,1,"aColor");
    // Wrap-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);
	// Checks if Shaders linked succesfully
    glValidateProgram(ID);
	compileErrors(ID);
	
    glReleaseShaderCompiler();
	// Delete the now useless Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDetachShader(ID,vertexShader);
	glDetachShader(ID,fragmentShader);
	glDeleteProgram(ID);
}





// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int graphic_object)
{
	// Stores status of compilation
	GLint hasCompiled;
	GLint hasLinked;
	GLint isValidate;
	//In case of shader type comes
	GLint shaderType;
	// Character array to store error message in
	

	if (glIsShader(graphic_object))
	{
		glGetShaderiv(graphic_object,GL_SHADER_TYPE,&shaderType);
		glGetShaderiv(graphic_object,GL_COMPILE_STATUS,&hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			GLchar infoLog[1024];
			switch (shaderType)
			{
			case GL_VERTEX_SHADER:
				glGetShaderInfoLog(graphic_object, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << "VERTEX" << "\n" << infoLog << std::endl;
				break;
			case GL_FRAGMENT_SHADER:
				glGetShaderInfoLog(graphic_object, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << "FRAGMENT" << "\n" << infoLog << std::endl;
				break;
			default:
				std::cout << "UNKNOWN ERROR IN SHADER\n" << infoLog << std::endl;
				break;
			}

		}
	}
	else if(glIsProgram(graphic_object))
	{
		GLchar infoLog2[1024];
		glGetProgramiv(graphic_object, GL_LINK_STATUS, &hasLinked);
		if (hasLinked == GL_FALSE)
		{
			glGetProgramInfoLog(graphic_object, 1024, NULL, infoLog2);
			std::cout << "SHADER_LINKING_ERROR for:" << "PROGRAM" << "\n" << infoLog2 << std::endl;
		}

		glGetProgramiv(graphic_object,GL_VALIDATE_STATUS,&isValidate);
		if(isValidate == GL_TRUE){
            std::cout << "VALIDATION is succesfull" << "\n" << std::endl;
		}
		else{
			std::cout << "VALIDATION is failed" << "\n" << std::endl;
		}
		
	}

}





void Shader::QueryActiveAttribs()
{
	if(!glIsProgram(ID)){
		std::cout << "This is not a shader program!" << "\n" << std::endl;
	}
	else{
		GLint isLinked;
		glGetProgramiv(ID,GL_LINK_STATUS,&isLinked);
		if(isLinked == GL_FALSE){
			std::cout << "This program is not linked" << "\n" << std::endl;
		}
		else{
		GLint numActiveAttribs;
		GLint nameMaxLength;
		/*Numbers of attribute*/
		glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
		/*Finds character length of max_variable_length attribute*/
		glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nameMaxLength);

		for (int i = 0; i < numActiveAttribs; i = i + 1) 
		{
        	GLint size;
        	GLenum type;
        	GLchar name[256];
        	// Get attribute information
			/*Shader program object ,Attribute index ,nameMaxLength*/
        	glGetActiveAttrib(ID, i, nameMaxLength, NULL, &size, &type, name);
			switch(type){
				case GL_FLOAT:
            	std::cout << "Attribute #" << i << ": " << name << " (Type: " << "GL_FLOAT" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_VEC2:
				std::cout << "Attribute #" << i << ": " << name << " (Type: " << "GL_FLOAT_VEC2" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_VEC3:
				std::cout << "Attribute #" << i << ": " << name << " (Type: " << "GL_FLOAT_VEC3" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_VEC4:
				std::cout << "Attribute #" << i << ": " << name << " (Type: " << "GL_FLOAT_VEC4" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_MAT2:
				std::cout << "Attribute #" << i << ": " << name << " (Type: " << "GL_FLOAT_MAT2" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_MAT3:
				std::cout << "Attribute #" << i << ": " << name << " (Type: " << "GL_FLOAT_MAT3" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_MAT4:
				std::cout << "Attribute #" << i << ": " << name << " (Type: " << "GL_FLOAT_MAT4" << ", Size: " << size << ")" << std::endl;
				break;
				default:
				std::cout << "Unknown type out" << std::endl;
				break; 
			}
        }
		}
	}
}




void Shader::QueryVertexAttrib(GLuint attrib_index)
{
    if (!glIsProgram(ID)) {
        std::cout << "\nThis is not a shader program!"  << std::endl;
    }
    else {
        GLint isLinked;
        glGetProgramiv(ID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            std::cout << "\nThis program is not linked!"  << std::endl;
        }
        else{
			glUseProgram(ID); //Program must be active before use

            GLint isBounded;
			glGetVertexAttribiv(attrib_index,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,&isBounded);
			if(isBounded == 0){
				std::cout << "Is attribute bounded to any array buffer ?: No it is 0" << std::endl;
			}
			else{
				std::cout << "Is attribute bounded to any array buffer ?: Yes Its Number:"<<isBounded<< std::endl;
			}

            GLint isEnabled;
			glGetVertexAttribiv(attrib_index,GL_VERTEX_ATTRIB_ARRAY_ENABLED,&isEnabled);
			if(isEnabled == 1){
				std::cout << "Is attribute enabled ?: Yes"  << std::endl;
			}
			else{
				std::cout << "Is attribute enabled ?: No"  << std::endl;
			}

			GLint Component_ofData;
			glGetVertexAttribiv(attrib_index,GL_VERTEX_ATTRIB_ARRAY_SIZE,&Component_ofData);
			std::cout << "The attribute consist of "<<Component_ofData<<" Components"<< std::endl;
            
			GLfloat stride_of_data;
			glGetVertexAttribfv(attrib_index,GL_VERTEX_ATTRIB_ARRAY_STRIDE,&stride_of_data);
			std::cout << "Vertex Attribute uses stride and it is "<<stride_of_data/sizeof(GL_BYTE)<< std::endl;

			GLint type_of_array;
            glGetVertexAttribiv(attrib_index,GL_VERTEX_ATTRIB_ARRAY_TYPE,&type_of_array);
			switch(type_of_array){
				case GL_BYTE:
				std::cout << "Array type is GL_BYTE"<< std::endl;
				break;
				case GL_UNSIGNED_BYTE:
				std::cout << "Array type is GL_UNSIGNED_BYTE"<< std::endl;
				break;
				case GL_SHORT:
				std::cout << "Array type is GL_SHORT"<< std::endl;
				break;
				case GL_UNSIGNED_SHORT:
				std::cout << "Array type is GL_UNSIGNED_SHORT"<< std::endl;
				break;
				case GL_FIXED:
				std::cout << "Array type is GL_FIXED"<< std::endl;
				break;
				case GL_FLOAT:
				std::cout << "Array type is GL_FLOAT"<< std::endl;
				break;
				default:
				std::cout << "Unknown array data type" << std::endl;
				break;
			}  
           GLint isNormalized;
		   glGetVertexAttribiv(attrib_index,GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,&isNormalized);
		   if(isNormalized == 0){
			std::cout << "Normalized : No" << std::endl;
		   }
		   else{
			std::cout << "Normalized : Yes" << std::endl;
		   }

		   GLfloat attrib_values[4];
		   glGetVertexAttribfv(attrib_index,GL_CURRENT_VERTEX_ATTRIB,attrib_values);
           std::cout << "{" <<attrib_values[0]<< "}"<<
		   "{"<<attrib_values[1]<< "}"<<
		   "{"<<attrib_values[2]<< "}"<<
		   "{"<<attrib_values[3]<< "}"<<std::endl;
		}
    }
}

/*UNIFORM SETS*/

void Shader::SetUniform1i(GLint v0,const GLchar *uniname){

	glUniform1i(glGetUniformLocation(ID,uniname),v0);
}

void Shader::SetUniform2i(GLint v0,GLint v1,const GLchar *uniname){

	glUniform2i(glGetUniformLocation(ID,uniname),v0,v1);
}

void Shader::SetUniform3i(GLint v0,GLint v1,GLint v2,const GLchar *uniname){

	glUniform3i(glGetUniformLocation(ID,uniname),v0,v1,v2);
}

void Shader::SetUniform4i(GLint v0,GLint v1,GLint v2,GLint v3,const GLchar *uniname){

	glUniform4i(glGetUniformLocation(ID,uniname),v0,v1,v2,v3);
}
/////////////////////////////////////////////////////////
void Shader::SetUniform1f(GLfloat v0,const GLchar *uniname){

	glUniform1f(glGetUniformLocation(ID,uniname),v0);
}

void Shader::SetUniform2f(GLfloat v0,GLfloat v1,const GLchar *uniname){

	glUniform2f(glGetUniformLocation(ID,uniname),v0,v1);
}

void Shader::SetUniform3f(GLfloat v0,GLfloat v1,GLfloat v2,const GLchar *uniname){

	glUniform3f(glGetUniformLocation(ID,uniname),v0,v1,v2);
}

void Shader::SetUniform4f(GLfloat v0,GLfloat v1,GLfloat v2,GLfloat v3,const GLchar *uniname){

	glUniform4f(glGetUniformLocation(ID,uniname),v0,v1,v2,v3);
}
////////////////////////////////////////////////////////////////////////////////////////////

void Shader::SetMat2x2(const GLfloat *matrix,GLboolean isTranspose,const GLchar *matName){
	glUniformMatrix2fv(glGetUniformLocation(ID,matName),1,isTranspose,matrix);
}

void Shader::SetMat3x3(const GLfloat *matrix,GLboolean isTranspose,const GLchar *matName){
	glUniformMatrix3fv(glGetUniformLocation(ID,matName),1,isTranspose,matrix);
}

void Shader::SetMat4x4(const GLfloat *matrix,GLboolean isTranspose,const GLchar *matName){
	glUniformMatrix4fv(glGetUniformLocation(ID,matName),1,isTranspose,matrix);
}

////////////////////////////////////////////////////////////////////////////////////////////
void Shader::RetriveUniformi(const GLchar *name,GLint *params){

	glGetUniformiv(ID,glGetUniformLocation(ID,name),params);

}

void Shader::RetriveUniformf(const GLchar *name,GLfloat *params){

	glGetUniformfv(ID,glGetUniformLocation(ID,name),params);
}




void Shader::QueryUniformVariables()
{
	if(!glIsProgram(ID)){
		std::cout << "This is not a shader program!" << "\n" << std::endl;
	}
	else{
		GLint isLinked;
		glGetProgramiv(ID,GL_LINK_STATUS,&isLinked);
		if(isLinked == GL_FALSE){
			std::cout << "This program is not linked!" << "\n" << std::endl;
		}
		else{
		GLint numUniformAttribs;
		GLint UniformMaxLength;
		/*Numbers of attribute*/
		glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &numUniformAttribs);
		/*Finds character length of max_variable_length uniform*/
		glGetProgramiv(ID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &UniformMaxLength);

		for (int i = 0; i < numUniformAttribs; ++i) 
		{
        	GLint size;
        	GLenum type;
        	GLchar name[256];
        	// Get attribute information
			/*Shader program object ,Attribute index ,nameMaxLength*/
        	glGetActiveUniform(ID, i, UniformMaxLength, NULL, &size, &type, name);
			switch(type){ 
				case GL_FLOAT:
            	std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_FLOAT" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_VEC2:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_FLOAT_VEC2" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_VEC3:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_FLOAT_VEC3" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_VEC4:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_FLOAT_VEC4" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_INT:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_INT" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_INT_VEC2:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_INT_VEC2" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_INT_VEC3:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_INT_VEC3" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_INT_VEC4:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_INT_VEC4" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_BOOL:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_BOOL" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_BOOL_VEC2:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_BOOL_VEC2" << ", Size: " << size << ")" << std::endl;
				break;				
				case GL_BOOL_VEC3:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_BOOL_VEC3" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_BOOL_VEC4:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_BOOL_VEC4" << ", Size: " << size << ")" << std::endl;
				break;				
				case GL_FLOAT_MAT2:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_FLOAT_MAT2" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_MAT3:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_FLOAT_MAT3" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_FLOAT_MAT4:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_FLOAT_MAT4" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_SAMPLER_2D:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_SAMPLER_2D" << ", Size: " << size << ")" << std::endl;
				break;
				case GL_SAMPLER_CUBE:
				std::cout << "Uniform #" << i << ": " << name << " (Type: " << "GL_SAMPLER_CUBE" << ", Size: " << size << ")" << std::endl;
				break;				
				default:
				std::cout << "Unknown type out" << std::endl;
				break; 
			}
        }
		}
	}
}




void Shader::QueryShaders()
{
    if (!glIsProgram(ID)) {
        std::cout << "\nThis is not a shader program!" << "\n" << std::endl;
    }
    else {
        GLint isLinked;
        glGetProgramiv(ID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            std::cout << "\nThis program is not linked!" << "\n" << std::endl;
        }
        else {
            GLint numShaders;
            GLint numShaders_InProgram;
            glGetProgramiv(ID, GL_ATTACHED_SHADERS, &numShaders);
            if (numShaders == 0 || numShaders < 0) {
                std::cout << "\nNo shader found in program!" << "\n" << std::endl;
            }
            else {
                std::cout << "\nThere are " << numShaders << " shader in this program" << "\n" << std::endl;
                GLuint shaders[2]; // Since there can be only 2 in OpenGL ES 2.0
                GLint length_SourceHolder;
                GLint length_InfoLogolder;
                glGetAttachedShaders(ID, 2, &numShaders_InProgram, shaders);

                glGetShaderiv(shaders[0], GL_SHADER_SOURCE_LENGTH, &length_SourceHolder);
                glGetShaderiv(shaders[0], GL_INFO_LOG_LENGTH, &length_InfoLogolder);
                char* ShaderSourceHolder = new char [length_SourceHolder];

                if(length_InfoLogolder > 0){
					char* ShaderInfoLogHolder = new char [length_InfoLogolder];
					std::cout << "Information about Vertex shader in this program" << "\n" << std::endl;
					/*Generates infolog only if there is a warning or error*/
                	glGetShaderInfoLog(shaders[0], length_InfoLogolder, NULL, ShaderInfoLogHolder);
                	std::cout << ShaderInfoLogHolder << std::endl;
					delete(ShaderInfoLogHolder);
				}

                std::cout << "Source code of the Vertex shader" << "\n" << std::endl;
                glGetShaderSource(shaders[0], length_SourceHolder, NULL, ShaderSourceHolder);
                std::cout << ShaderSourceHolder << std::endl;

                delete(ShaderSourceHolder);
                

                glGetShaderiv(shaders[1], GL_SHADER_SOURCE_LENGTH, &length_SourceHolder);
                glGetShaderiv(shaders[1], GL_INFO_LOG_LENGTH, &length_InfoLogolder);
                ShaderSourceHolder = new char [length_SourceHolder];


				if(length_InfoLogolder > 0){
					char* ShaderInfoLogHolder2 = new char [length_InfoLogolder];
                	std::cout << "Information about Fragment shader in this program" << "\n" << std::endl;
                	glGetShaderInfoLog(shaders[1], length_InfoLogolder, NULL, ShaderInfoLogHolder2);
                	std::cout << ShaderInfoLogHolder2  << std::endl;
					delete(ShaderInfoLogHolder2);
				}
				
                std::cout << "Source code of the Fragment shader" << "\n" << std::endl;
                glGetShaderSource(shaders[1], length_SourceHolder, NULL, ShaderSourceHolder);
                std::cout << ShaderSourceHolder << std::endl;

                free(ShaderSourceHolder);
            }
        }
    }
}


void Shader::QueryShaderPrecision(GLenum precision_format)
{
	GLint range[2], precision;
    switch(precision_format){

		case GL_LOW_FLOAT:
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_LOW_FLOAT, range, &precision);
    	std::cout << "Vertex Shader Low Float Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
    	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_LOW_FLOAT, range, &precision);
    	std::cout << "Fragment Shader Low Float Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
		break;

		case GL_MEDIUM_FLOAT:
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_FLOAT, range, &precision);
    	std::cout << "Vertex Shader Medium Float Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
    	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_FLOAT, range, &precision);
    	std::cout << "Fragment Shader Medium Float Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
		break;

		case GL_HIGH_FLOAT:
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGH_FLOAT, range, &precision);
    	std::cout << "Vertex Shader High Float Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
    	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_FLOAT, range, &precision);
    	std::cout << "Fragment Shader High Float Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
		break;

        case GL_LOW_INT:
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_LOW_INT, range, &precision);
    	std::cout << "Vertex Shader Low Integer Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
    	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_LOW_INT, range, &precision);
    	std::cout << "Fragment Shader Low Integer Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
		break;

		case GL_MEDIUM_INT:
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_INT, range, &precision);
    	std::cout << "Vertex Shader Medium Integer Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
    	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_INT, range, &precision);
    	std::cout << "Fragment Shader Medium Integer Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
		break;

		case GL_HIGH_INT:
		glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGH_INT, range, &precision);
    	std::cout << "Vertex Shader High Integer Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
    	glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_INT, range, &precision);
    	std::cout << "Fragment Shader High Integer Precision:" << std::endl;
    	std::cout << "Minimum range: -2^" << range[0] << std::endl;
    	std::cout << "Maximum range: 2^" << range[1] << std::endl;
    	std::cout << "Precision: " << precision << std::endl;
		break;

		default:
		std::cout << "You have entered invalid precision format" << std::endl;
		std::cout << "Allowed GL enum's are:" << std::endl;
		std::cout << "GL_LOW_FLOAT, GL_MEDIUM_FLOAT, GL_HIGH_FLOAT, GL_LOW_INT, GL_MEDIUM_INT, or GL_HIGH_INT." << std::endl;
		break;
		}
	}




