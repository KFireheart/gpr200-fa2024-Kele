#include "../core/ew/Jeff/shader.hpp"
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ew/external/stb_image.h>

//Include IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float texCoordMulip = 10.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); 
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); 
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 60.0f;

bool isPerspective = true;
bool tabKeyPressed = false;

bool isMouseDown = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;



float vertices[] = {
	// Px    Py		Pz     Nx     Ny     Nz     U    V
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};


glm::vec3 cubeLocations[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f),
	glm::vec3(1.0f,  0.0f,  0.0f),
	glm::vec3(-2.0f,  5.0f, -15.0f),
	glm::vec3(-3.5f, -2.2f, -2.5f),
	glm::vec3(-5.8f, -2.0f, -12.3f),
	glm::vec3(9.4f, -0.4f, -3.5f),
	glm::vec3(-0.7f,  3.0f, -7.5f),
	glm::vec3(-1.3f, -2.0f, -2.5f),
	glm::vec3(4.5f,  2.0f, -2.5f),
	glm::vec3(2.5f,  0.2f, -1.5f),
	glm::vec3(-2.3f,  1.0f, -1.5f),
}; 

//light position
glm::vec3 lightPos(1.0f, 0.5f, 2.0f); 

//light color
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);



const char* vertexShaderSource = "assets/vertexShader.vert";
const char* fragmentShaderSource = "assets/fragShader.frag";
const char* lightVertSource = "assets/lightSource.vert"; 
const char* lightFragSource = "assets/lightSource.frag";



void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lighting", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	stbi_set_flip_vertically_on_load(true);

	//Lighting stuff
	/*float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;*/

	//Initialize IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//cubes
	unsigned int VBO, VAO;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);  

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Normal XYZ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); 
	glEnableVertexAttribArray(1); 

	//UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); 
	glEnableVertexAttribArray(2); 

	//------------------------------------------------------------------------------------------------

	//light cube
	unsigned int VBO2, VAO2;

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2); 

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	//light position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); 
	glEnableVertexAttribArray(0); 

	//____________________________________________________________________________________________________

	// load and create a texture 
	unsigned int tex1, tex2;
	// texture 1
	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// texture 2
	glGenTextures(1, &tex2);
	glBindTexture(GL_TEXTURE_2D, tex2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("assets/happyMushroom.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	
	//Create and compile vertex shader
	jeff::Shader lightShader(lightVertSource, lightFragSource); 
	jeff::Shader cubesShader(vertexShaderSource, fragmentShaderSource); 
	
	
	cubesShader.use();
	cubesShader.setInt("tex1", 0);
	cubesShader.setInt("tex2", 1);

	//Render loop
	while (!glfwWindowShouldClose(window)) {

		glEnable(GL_DEPTH_TEST); 

		//ambient strength
		float ambientStrength = 1;
		//Specular strength
		float specularStrength = 0.5;


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//gets input from user 
		processInput(window); 
		glfwSetScrollCallback(window, scroll_callback); 

		//Clear framebuffer
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		

		if (isMouseDown) {
			
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		//start drawing IMGUI
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//lighting shader processing
		cubesShader.use();
		cubesShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		cubesShader.setVec3("lightPos", lightPos);
		cubesShader.setFloat("ambientStrenth", ambientStrength);
		cubesShader.setFloat("specularStrenth", specularStrength);

		//Settings window
		ImGui::Begin("Settings");
		ImGui::PushItemWidth(40);
		ImGui::DragFloat("X", &lightPos.x, 1.0f); 
		ImGui::SameLine();
		ImGui::DragFloat("Y", &lightPos.y, 1.0f);
		ImGui::SameLine(); 
		ImGui::DragFloat("Z Light Position", &lightPos.z, 1.0f);
		ImGui::PopItemWidth();
		//ImGui::ColorEdit3("Light Color", &lightColor, 1.0f);
		ImGui::SliderFloat("Ambient", &ambientStrength, 0.0f, 1.0f);
		ImGui::End();

		//Render the IMGUI elements using OpenGL
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//initializes view, and projection
		glm::mat4 view = glm::mat4(1.0f); 
		glm::mat4 projection; 

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); 
		cubesShader.setMat4("projection", projection);
		cubesShader.setMat4("view", view);
		cubesShader.setVec3("veiwPos", cameraPos);
		

		//background texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		//overlay texture
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex2);

		


		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw));
		direction.z = sin(glm::radians(yaw));

		

		if (isPerspective) {
			projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f); 
		}
		else {
			float orthoSize = 10.0f;
			projection = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize, 0.1f, 100.0f); 
		}
		 

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 20; i++)
		{
			glm::mat4 model = glm::mat4(1.0f); 
			model = glm::translate(model, cubeLocations[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubesShader.setMat4("model", model);


			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//Draw lamp
		lightShader.use();
		lightShader.setMat4("projection", projection); 
		lightShader.setMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		lightShader.setMat4("model", model);

		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 36); 
	
		//Drawing happens here!
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	printf("Shutting down...");
	
}

//input processing
void processInput(GLFWwindow* window)
{
	float baseSpeed = 2.0f;
	float cameraSpeed = baseSpeed * deltaTime;

	//Sprint
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
		cameraSpeed *= 4.0f; 

	//Basic movements
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) 
		cameraPos += cameraSpeed * cameraUp; 
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;
	
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tabKeyPressed) {
		isPerspective = !isPerspective;
		tabKeyPressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) 
	{
		tabKeyPressed = false;
	}

	//Checks to see if the mouse button is pressed, then allows the user to move the camera around
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		isMouseDown = true;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) { 
		isMouseDown = false;
	}
}

//Mouse movement
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; 
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;


	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

//Mouse scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 120.0f)
		fov = 120.0f;
}


