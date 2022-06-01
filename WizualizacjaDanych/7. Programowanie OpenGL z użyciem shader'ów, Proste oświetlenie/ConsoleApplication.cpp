#include <iostream>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/System/Time.hpp>
using namespace std;

const GLchar* vertexSource = R"glsl(
#version 150 core
in vec3 position;
in vec3 color;	
out vec3 Color;
in vec3 aNormal;
in vec3 lightPos;
out vec3 Normal;
out vec3 FragPos;
in vec2 aTexCoord;
out vec2 TexCoord;
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 proj;

void main(){
TexCoord = aTexCoord;
Color = color;
Normal=aNormal;
FragPos=lightPos;
gl_Position = proj * view * model * vec4(position, 1.0);
}
)glsl";

const GLchar* fragmentSource = R"glsl(
#version 150 core
in vec3 Color;
out vec4 outColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;
uniform sampler2D texture1;

void main(){
outColor = vec4(Color, 1.0);
outColor=texture(texture1, TexCoord);
float ambientStrength = 0.1;// ambient
vec3 ambientlightColor = vec3(1.0,1.0,1.0);
vec4 ambient = ambientStrength * vec4(ambientlightColor,1.0);
vec3 difflightColor = vec3(1.0,1.0,1.0);
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(lightPos -FragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = diff * difflightColor;
outColor = (ambient+vec4(diffuse,1.0)) * texture(texture1, TexCoord);
}
)glsl";

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
int lastX, lastY;
double yaw = -90;
double pitch = 0;

void cube(int buffer) {
	int points = 36;
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, -1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * points * 8, vertices, GL_STATIC_DRAW);
}

void ustawKamereKlawisze(GLint _uniView, float _time) {
	float cameraSpeed = 0.000002f * _time;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		cameraPos += cameraSpeed * cameraFront;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		cameraPos -= cameraSpeed * cameraFront;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	
	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(_uniView, 1, GL_FALSE, glm::value_ptr(view));

}



void setOnKey(GLint _uniView, float _time) {

	float cameraSpeed = 0.000002f * _time;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}


	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(_uniView, 1, GL_FALSE, glm::value_ptr(view));

}

void setOnMouse(GLint _uniView, float _elapsedTime, const sf::Window& _window) {

	sf::Vector2i localPosition = sf::Mouse::getPosition(_window);

	sf::Vector2i position;
	bool relocation = false;

	if (localPosition.x <= 0) {
		position.x = _window.getSize().x;
		position.y = localPosition.y;
		relocation = true;
	}
	if (localPosition.x >= _window.getSize().x - 1) {
		position.x = 0;
		position.y = localPosition.y;
		relocation = true;
	}
	if (localPosition.y <= 0) {
		position.y = _window.getSize().y;
		position.x = localPosition.x;
		relocation = true;
	}
	if (localPosition.y >= _window.getSize().y - 1) {
		position.y = 0;
		position.x = localPosition.x;
		relocation = true;
	}

	if (relocation) {
		sf::Mouse::setPosition(position, _window);
		firstMouse = true;
	}
	localPosition = sf::Mouse::getPosition(_window);

	if (firstMouse) {
		lastX = localPosition.x;
		lastY = localPosition.y;
		firstMouse = false;
	}

	double xoffset = localPosition.x - lastX;
	double yoffset = localPosition.y - lastY;
	lastX = localPosition.x;
	lastY = localPosition.y;

	double sensitivity = 0.8f;
	double cameraSpeed = 0.00005f * _elapsedTime;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset * cameraSpeed;
	pitch -= yoffset * cameraSpeed;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(_uniView, 1, GL_FALSE, glm::value_ptr(view));
}


int main(){
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	sf::Window window(sf::VideoMode(800, 800, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);

	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);

	glewExperimental = GL_TRUE;
	glewInit();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	cube(vbo);
	GLuint vertexShader =glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (!status) {
		cout<<"vertexShader compilation error"<<endl;
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		cout<<buffer<<endl;
		return 1;
	}
	else 
		cout<<"vertexShader compilation OK"<<endl;
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (!status) {
		cout<<"fragmentShader compilation error"<<endl;
		char buffer[512];

		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
		cout<<buffer<<endl;
		return 1;
	}
	else
		cout <<"fragmentShader compilation OK"<<endl;

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLint NorAttrib = glGetAttribLocation(shaderProgram, "aNormal"); glEnableVertexAttribArray(NorAttrib);
	glVertexAttribPointer(NorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat))); 

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f); 
	GLint uniLightPos = glGetUniformLocation(shaderProgram, "lightPos");
	glUniform3fv(uniLightPos, 1, &lightPos[0]);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	GLint TexCoord = glGetAttribLocation(shaderProgram, "aTexCoord");
	glEnableVertexAttribArray(TexCoord);
	glVertexAttribPointer(TexCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));

	GLint uniView = glGetUniformLocation(shaderProgram, "view");

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.06f, 100.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	GLint figure = GL_TRIANGLES;
	glEnable(GL_DEPTH_TEST);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("met.bmp", &width, &height, &nrChannels, 0);

	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		cout << "Failed to load texture" << endl;

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

	bool running = true;
	sf::Time time;
	sf::Clock clock;
	window.setFramerateLimit(69);
	int iter = 0;
	while (running) {

		time = clock.restart();
		iter++;
		float ffps = 1000000 / time.asMicroseconds();
		if (iter > ffps) {
			window.setTitle(std::to_string(ffps));
			iter = 0;
		}

		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {
			case sf::Event::Closed:
				running = false;
				break;

			case sf::Event::MouseMoved:
				setOnMouse(uniView, time.asMicroseconds(), window);
				break;

			case sf::Event::KeyPressed:
				switch (windowEvent.key.code) {
				case sf::Keyboard::Escape:
					running = false;
					break;
				case sf::Keyboard::Num0:
					figure = GL_POLYGON;
					break;
				case sf::Keyboard::Num1:
					figure = GL_TRIANGLES;
					break;
				case sf::Keyboard::Num2:
					figure = GL_LINE_STRIP;
					break;
				case sf::Keyboard::Num3:
					figure = GL_TRIANGLE_STRIP;
					break;
				case sf::Keyboard::Num4:
					figure = GL_QUADS;
					break;
				case sf::Keyboard::Num5:
					figure = GL_TRIANGLE_FAN;
					break;
				case sf::Keyboard::Num6:
					figure = GL_QUAD_STRIP;
					break;
				case sf::Keyboard::Num7:
					figure = GL_LINE_LOOP;
					break;
				case sf::Keyboard::Num8:
					figure = GL_LINES;
					break;
				case sf::Keyboard::Num9:
					figure = GL_POINTS;
					break;
				}
				break;
			}
		}
		setOnKey(uniView, time.asMicroseconds());
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glDrawArrays(figure, 0, 36);
		window.display();
	}
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	window.close();
	return 0;
}
