#pragma once
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"  //create and compile shader program

//SOIL include
#include <SOIL.h>

class Background
{
private:
	GLuint bgVBO, bgVAO, textureBG;
	int width, height, size, objectID;
	unsigned char* image;
	
public:
	Background(GLchar* path, int objectID) {
		GLfloat background[] = {
			-10.0f,  0.01f, 10.0f,  0.0f,  0.0f,
			10.0f,  0.01f,  10.0f,  1.0f,  0.0f,
			10.0f,   0.01f, -10.0f,  1.0f,  1.0f,
			10.0f,   0.01f, -10.0f,  1.0f,  1.0f,
			-10.0f,  0.01f, -10.0f,  0.0f,  1.0f,
			-10.0f,  0.01f, 10.0f,  0.0f,  0.0f,
		};
		this->objectID = objectID;
		glGenVertexArrays(1, &bgVAO);
		glGenBuffers(1, &bgVBO);
		glBindVertexArray(bgVAO);
		glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(background), background, GL_STATIC_DRAW);
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// TexCoord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(0); // Unbind VAO
							  //Import texture and bind it to the background vertices.
		glGenTextures(1, &textureBG);
		glBindTexture(GL_TEXTURE_2D, textureBG);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		image = SOIL_load_image("background.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);//unbind texture.
	}
	~Background() {
		glDeleteVertexArrays(1, &bgVAO);
		glDeleteBuffers(1, &bgVBO);
	}

	void Draw(Shader shader){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureBG);
		glUniform1i(glGetUniformLocation(shader.Program, "backgroundTex"), 0);
		glUniform1i(glGetUniformLocation(shader.Program, "objectID"), this->objectID);
		glBindVertexArray(bgVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0); //unbind
	}



};

class TrajectoryLine {
private:
	GLuint lineVAO, lineVBO, numberOfPoints;
	int objectID;

public:
	TrajectoryLine(GLfloat framePose[], GLint numberOfPoints, GLint stepSize, int objectID) {
		this->objectID = objectID;
		this->numberOfPoints = numberOfPoints;
		glGenVertexArrays(1, &lineVAO);
		glGenBuffers(1, &lineVBO);
		glBindVertexArray(lineVAO);
		glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
		GLfloat toBuffer[6]; //six values to buffer to draw a line
		std::cout << "Number of Control Points: " << numberOfPoints << std::endl;
		glBufferData(GL_ARRAY_BUFFER, sizeof(toBuffer)*(numberOfPoints - 1), framePose, GL_DYNAMIC_DRAW);
		for (int i = 0; i < numberOfPoints - 1; i++) {
			for (int j = 0; j < 3; j++) {
				toBuffer[j] = framePose[i*stepSize + j];
				toBuffer[j + 3] = framePose[(i + 1)*stepSize + j];
			}
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(toBuffer)*i, sizeof(toBuffer), toBuffer);
		}
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	~TrajectoryLine() {
		glDeleteVertexArrays(1, &lineVAO);
		glDeleteBuffers(1, &lineVBO);
	}
	void Draw(Shader shader) {
		glBindVertexArray(lineVAO);
		glUniform1i(glGetUniformLocation(shader.Program, "objectID"), this->objectID);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_LINES, 0, (this->numberOfPoints - 1) * 2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(0);
	}
};