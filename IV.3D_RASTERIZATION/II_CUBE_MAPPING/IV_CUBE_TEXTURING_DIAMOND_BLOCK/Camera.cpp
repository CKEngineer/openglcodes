#include"Camera.h"



Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	Start_Point = Position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 model_x = glm::mat4(1.0f);
	glm::mat4 model_y = glm::mat4(1.0f);
	glm::mat4 model_z = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model_x = glm::rotate(model_x, glm::radians(Rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	model_y = glm::rotate(model_y, glm::radians(Rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	model_y = glm::rotate(model_y, glm::radians(Rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));
	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Orientation+Position, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model_x"), 1, GL_FALSE, glm::value_ptr(model_x));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model_y"), 1, GL_FALSE, glm::value_ptr(model_y));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model_z"), 1, GL_FALSE, glm::value_ptr(model_z));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
	
}



void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

    // Rotating the CUBE for this example

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		Rotation_x -= speed *rotate_sensitivity ;
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)

	{   
		Rotation_y += speed *rotate_sensitivity ;
	}

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		Rotation_x += speed *rotate_sensitivity ;
	}

	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		Rotation_y -= speed *rotate_sensitivity ;
	}

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		Rotation_z += speed *rotate_sensitivity ;
	}

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		Rotation_z -= speed *rotate_sensitivity ;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{   
			Rotation_x += 1; 
			Rotation_y += 1;
			Rotation_z += 1;
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{   
			Rotation_x = 0; 
			Rotation_y = 0;
			Rotation_z = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{   //Kaybolma ihtimaline karşı alınmış bir önlem
		Position = Start_Point;
	}
}