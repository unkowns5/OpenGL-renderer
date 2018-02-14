// Include GLFW

#include "Scene.hpp"
#include <glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "Controls.hpp"

Controls::Controls(Camera* cam, Scene* scene){
	m_camera = cam;
	m_scene = scene;
	keyspeed = 3.0f; // 3 units / second
	mouseSpeed = 0.005f;
	
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	
}



void Controls::update(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	static bool blendEnabled = true;

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	glm::vec3 position = m_camera->getPosition();
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * keyspeed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * keyspeed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * keyspeed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * keyspeed;
	}
	// Enable or Disable opacity 
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) {
			if (blendEnabled) {
				glDisable(GL_BLEND);
				blendEnabled = false;
			}
			else {
				glEnable(GL_BLEND);
				blendEnabled = true;
			}
		}
	}
	// enable comicshader
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		m_scene->setRenderMode(1);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	//enable normal shader
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		m_scene->setRenderMode(2);
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	m_camera->setLookAt(position,position+direction,up );
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
