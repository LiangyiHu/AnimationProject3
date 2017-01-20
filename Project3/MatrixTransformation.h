#pragma once

// Std. Includes
#include <vector>
#include <iostream>;

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Specify if the input is for euler angle or quaternion (will have 7 parameters each line for quaternions).
//For euler input, latter 3 parameters(xyz) specify rotation degrees for X-Y-Z extrinsic (fixed angle)
//Or equivalently Z-Y'-X'' intrinsic (object/body coordinate system).
const bool EULER_INPUT = true;
const bool EULER_INTERPOLATION = false;

//true for CATMUL_ROM, false for B-Spline
const bool CATMUL_ROM_INTERPOLATION = false;

//If true, use will need to specify the speed factor for each curve. number of curve equals number of control points -3.
const bool SPEED_CONTROL_ENABLED = false;

//specify frame and keys
const GLfloat FRAME_PER_SEC = 30;
const GLfloat FRAME_PER_KEY = 40;

//position.x, position.y, position.z, rotate A degrees about X axle, B about Y, C about Z, 6 values per point.
//If EULER_INPUT value false, sequence is xyz position, rotation vector xyz, then w. 7 values per point.
//For quaternions, the last four argumants are [x, y, z, w]
GLfloat keyFramePose[] = {
	-20.0f, 22.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.0f,  22.0f, 0.0f, 0.0f, 0.0f, 0.0f,//1
	 30.0f, 22.0f,  10.0f, 0.0f, 0.0f, 0.0f,
	 60.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 90.0f, 22.0f,  10.0f, 0.0f, 0.0f, 0.0f,
	 120.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 150.0f, 22.0f,  10.0f, 0.0f, 0.0f, 0.0f,
	 180.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 210.0f, 22.0f,  10.0f, 0.0f, 0.0f, 0.0f,
	 240.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 255.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,//10
	 270.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 285.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 300.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 315.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 330.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 345.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,//17
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
	 360.0f, 22.0f,  -10.0f, 0.0f, 0.0f, 0.0f,
};
/*This matrix is used for fighter jet trajectory before.
-40.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//0
-20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//2
30.0f, 10.0f,  0.0f, 0.0f, 0.0f, 45.0f,
50.0f, 50.0f,  0.0f, 0.0f, 0.0f, 100.0f,//4
25.0f, 60.0f,  15.0f, 0.0f, -15.0f, 145.0f,
0.0f, 70.0f, 20.0f, 0.0f, -30.0f, 180.0f,//6
-30.0f, 70.0f, 30.0f, 0.0f, -120.0f, 45.0f,
-50.0f, 40.0f, -10.0f, 0.0f, 60.0f, -135.0f,//8
0.0f, 20.0f, -30.0f, 0.0f, 30.0f, 0.0f,
30.0f, 10.0f, -10.0f, 0.0f, 0.0f, 0.0f,//10
70.0f, 10.0f, -10.0f, 60.0f, 0.0f, 0.0f,
100.0f, 10.0f, -10.0f, 120.0f, 0.0f, 0.0f,//12
130.0f, 10.0f, -10.0f, 180.0f, 0.0f, 0.0f,
160.0f, 10.0f, -10.0f, 240.0f, 0.0f, 0.0f,//14
190.0f, 10.0f, -10.0f, 300.0f, 0.0f, 0.0f,
220.0f, 10.0f, -10.0f, 360.0f, 0.0f, 0.0f,//16
250.0f, 10.0f, -10.0f, 420.0f, 0.0f, 0.0f,
280.0f, 10.0f, -10.0f, 480.0f, 0.0f, 0.0f,
310.0f, 10.0f, -10.0f, 540.0f, 0.0f, 0.0f,
*/
//speed factor for each curve
GLfloat speedFactor[] = {
	1.0f, 3.0f, 1.0f,3.0f,1.0f,
	3.0f, 1.0f, 5.0f,1.0f,6.0f,
	1.0f, 3.0f, 1.0f,4.0f,6.0f,
	3.0f, 1.0f,
};


//global variable
GLint stepSize = EULER_INPUT ? 6 : 7;
GLint numberOfPoints = sizeof(keyFramePose) / sizeof(GLfloat) / stepSize;
GLfloat currentPoseMatrixQuat[4][7]; //4X7 matrix, store the 4 points used for quaternion interpolation.
GLfloat currentPoseMatrixEuler[4][6];
GLfloat currentQuaternion[7]; //vector



//function declaration
void printThisMatrix(glm::mat4 printeeMatrix);
void printThisMatrix(GLfloat printeeMatrix[4][7]);
void printThisVector(glm::vec3 printeeVector);
void printThisVector(glm::vec4 printeeVector);
glm::vec4 combineQuatRotations(glm::vec4 firstRotate, glm::vec4 secondRotate);
glm::vec4 getQuaternionByEulerRotation(glm::vec3 eulerRotate);
glm::vec4 getQuaternionByEulerRotationNew(glm::vec3 eulerRotate);
glm::mat4 getRotationMatrixFromQuaternion(glm::vec4 inputQuat);
glm::mat4 getFinalMatrixQuat(glm::vec3 inputPosition, glm::vec4 inputQuat);
glm::mat4 getFinalMatrixEuler(glm::vec3 inputPosition, glm::vec3 inputQuat);
glm::vec3 getEulerAnglesFromEulerInput(int ithPoint);
glm::vec3 getPositionFromInput(int ithPoint);
glm::vec4 getQuaternionFromQuaternionInput(int ithPoint);
glm::vec4 getQuaternionFromAngleAndAxle(GLfloat angle, glm::vec3 axle);
glm::mat4 buildMatrixByPoint(int ithPointer);
glm::mat4 getMatrixXRotation(glm::vec3 eulerAngles);
glm::mat4 getMatrixYRotation(glm::vec3 eulerAngles);
glm::mat4 getMatrixZRotation(glm::vec3 eulerAngles);
glm::mat4 mulMatrix(glm::mat4 matrix1, glm::mat4 matrix2);
glm::vec3 vecCross(glm::vec3 v1, glm::vec3 v2);
GLfloat vecDot(glm::vec3 v1, glm::vec3 v2);
glm::mat4 buildCatmullRomMatrix(GLfloat aValue);
glm::mat4 buildBSplineMatrix();
void updatePoseMatrix(GLint ithPointer, GLfloat matrixToUpdate[4][7]);
void updatePoseMatrixEuler(GLint ithPointer, GLfloat matrixToUpdate[4][6]);
void setInterQuatFromQuat(int ithPoint, GLfloat tValue, glm::mat4 spineMatrix, GLfloat matrixToUpdate[4][7], GLfloat* returnValue);
void setInterEulerFromEuler(int ithPoint, GLfloat tValue, glm::mat4 spineMatrix, GLfloat matrixToUpdate[4][6], GLfloat* interEuler);

//Print matrix to console for debugging purpose
void printThisMatrix(glm::mat4 printeeMatrix) {
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			std::cout << printeeMatrix[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
//Print matrix to console for debugging purpose
void printThisMatrix(GLfloat printeeMatrix[4][7]) {
	for (int i = 0; i <4; i++) {
		for (int j = 0; j <7; j++) {
			std::cout << printeeMatrix[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}
//Print vector to console for debugging purpose
void printThisVector(glm::vec3 printeeVector) {
	for (int i = 0; i < 3; i++) {
		std::cout << printeeVector[i]<<", ";
	}
	std::cout<<std::endl;
}
//Print vector to console for debugging purpose
void printThisVector(glm::vec4 printeeVector) {
	for (int i = 0; i < 4; i++) {
		std::cout << printeeVector[i] << ", ";
	}
	std::cout << std::endl;
}
//Build rotation matrix given ith point in the keyframe input, this is used to check is each key is setup correctly before a complete run.
glm::mat4 buildMatrixByPoint(int ithPointer) {
	glm::mat4 rotationMatrix;
	glm::vec4 quaternionInput;
	glm::vec3 positionInput;

	positionInput = getPositionFromInput(ithPointer);
	if (EULER_INPUT) {
		quaternionInput = getQuaternionByEulerRotation(getEulerAnglesFromEulerInput(ithPointer));
		rotationMatrix = getFinalMatrixQuat(positionInput, quaternionInput);
	}
	else{
		quaternionInput = getQuaternionFromQuaternionInput(ithPointer);
		rotationMatrix = getFinalMatrixQuat(positionInput, quaternionInput);
	}
	return rotationMatrix;
}

//return the final model matrix, given the objects position in world coordinate and its direction in quaternion form
glm::mat4 getFinalMatrixQuat(glm::vec3 inputPosition, glm::vec4 inputQuat) {
	glm::mat4 outputMatrix;
	inputQuat = glm::normalize(inputQuat);
	outputMatrix= getRotationMatrixFromQuaternion(inputQuat);
	outputMatrix[0][3] = inputPosition.x;
	outputMatrix[1][3] = inputPosition.y;
	outputMatrix[2][3] = inputPosition.z;
	return outputMatrix;
}
//return final model matrix given objects position in world coordinate and its directin in euler form
glm::mat4 getFinalMatrixEuler(glm::vec3 inputPosition, glm::vec3 inputEuler) {
	glm::mat4 outputMatrix;
	outputMatrix=mulMatrix(mulMatrix(getMatrixZRotation(inputEuler), getMatrixYRotation(inputEuler)), getMatrixXRotation(inputEuler));
	outputMatrix[0][3] = inputPosition.x;
	outputMatrix[1][3] = inputPosition.y;
	outputMatrix[2][3] = inputPosition.z;
	return outputMatrix;
}

//convert an Euler angle rotation input into quaternion, method is provided from wiki.
glm::vec4 getQuaternionByEulerRotation(glm::vec3 eulerRotate) {
	glm::vec4 outQuaternion = glm::vec4();
	outQuaternion.x = glm::sin(glm::radians(eulerRotate.x) / 2)*glm::cos(glm::radians(eulerRotate.y) / 2)*glm::cos(glm::radians(eulerRotate.z) / 2)- glm::cos(glm::radians(eulerRotate.x) / 2)*glm::sin(glm::radians(eulerRotate.y) / 2)*glm::sin(glm::radians(eulerRotate.z) / 2);
	outQuaternion.y = glm::cos(glm::radians(eulerRotate.x) / 2)*glm::sin(glm::radians(eulerRotate.y) / 2)*glm::cos(glm::radians(eulerRotate.z) / 2) + glm::sin(glm::radians(eulerRotate.x) / 2)*glm::cos(glm::radians(eulerRotate.y) / 2)*glm::sin(glm::radians(eulerRotate.z) / 2);
	outQuaternion.z = glm::cos(glm::radians(eulerRotate.x) / 2)*glm::cos(glm::radians(eulerRotate.y) / 2)*glm::sin(glm::radians(eulerRotate.z) / 2) - glm::sin(glm::radians(eulerRotate.x) / 2)*glm::sin(glm::radians(eulerRotate.y) / 2)*glm::cos(glm::radians(eulerRotate.z) / 2);
	outQuaternion.w = glm::cos(glm::radians(eulerRotate.x) / 2)*glm::cos(glm::radians(eulerRotate.y) / 2)*glm::cos(glm::radians(eulerRotate.z) / 2) + glm::sin(glm::radians(eulerRotate.x) / 2)*glm::sin(glm::radians(eulerRotate.y) / 2)*glm::sin(glm::radians(eulerRotate.z) / 2);
	outQuaternion=glm::normalize(outQuaternion);
	outQuaternion.x = std::round(outQuaternion.x * 1000) / 1000;
	outQuaternion.y = std::round(outQuaternion.y * 1000) / 1000;
	outQuaternion.z = std::round(outQuaternion.z * 1000) / 1000;
	outQuaternion.w = std::round(outQuaternion.w * 1000) / 1000;
	/*if (outQuaternion.w < 0) { 
		outQuaternion.x= -outQuaternion.x;
		outQuaternion.y = -outQuaternion.y;
		outQuaternion.z = -outQuaternion.z;
		outQuaternion.w = -outQuaternion.w;
	}*/
	return outQuaternion;
}

//convert an Euler angle rotation input into quaternion, method is provided from course slides.
glm::vec4 getQuaternionByEulerRotationNew(glm::vec3 eulerRotate) {
	glm::vec4 outQuaternion = glm::vec4(0.0f, 0.0f, glm::sin(glm::radians(eulerRotate.z / 2)), glm::cos(glm::radians(eulerRotate.z / 2)));
	outQuaternion = combineQuatRotations(outQuaternion, glm::vec4(0.0f, glm::sin(glm::radians(eulerRotate.y / 2)), 0.0f, glm::cos(glm::radians(eulerRotate.y / 2))));
	outQuaternion = combineQuatRotations(outQuaternion, glm::vec4(glm::sin(glm::radians(eulerRotate.x / 2)), 0.0f, 0.0f, glm::cos(glm::radians(eulerRotate.x / 2))));
	outQuaternion = glm::normalize(outQuaternion);
	outQuaternion.x = std::round(outQuaternion.x * 1000) / 1000;
	outQuaternion.y = std::round(outQuaternion.y * 1000) / 1000;
	outQuaternion.z = std::round(outQuaternion.z * 1000) / 1000;
	outQuaternion.w = std::round(outQuaternion.w * 1000) / 1000;
	/*if (outQuaternion.w < 0) {
		outQuaternion.x = -outQuaternion.x;
		outQuaternion.y = -outQuaternion.y;
		outQuaternion.z = -outQuaternion.z;
		outQuaternion.w = -outQuaternion.w;
	}*/
	
	return outQuaternion;
}

glm::vec4 getQuaternionFromAngleAndAxle(GLfloat angle, glm::vec3 axle) {
	glm::vec4 returnQuat;
	returnQuat.w = glm::cos(angle/2);
	returnQuat.x = axle.x*glm::sin(angle/2);
	returnQuat.y = axle.y*glm::sin(angle / 2);
	returnQuat.z = axle.z*glm::sin(angle / 2);
	return returnQuat;
}

GLfloat getAngleFromQuat(glm::vec4 inputQuat) {
	glm::vec4 reshapedQuat = glm::normalize(inputQuat);
	GLfloat returnAngle = 2*glm::acos(reshapedQuat.w);
	return returnAngle;
}
glm::vec3 getAxleFromQuat(glm::vec4 inputQuat) {
	glm::vec3 returnAxle;
	glm::vec4 reshapedQuat = glm::normalize(inputQuat);
	if (getAngleFromQuat(reshapedQuat)==0) {
		return glm::vec3(0.0f,1.0f,0.0f);
	}
	returnAxle.x = reshapedQuat.x / (glm::sqrt(1 - glm::pow(reshapedQuat.w,2)));
	returnAxle.y = reshapedQuat.y / (glm::sqrt(1 - glm::pow(reshapedQuat.w, 2)));
	returnAxle.z = reshapedQuat.z / (glm::sqrt(1 - glm::pow(reshapedQuat.w, 2)));
	return returnAxle;
}
//Combine two quaternions to get a new joint quaternion
glm::vec4 combineQuatRotations(glm::vec4 firstRotate, glm::vec4 secondRotate) {
	GLfloat w1=firstRotate.w, w2=secondRotate.w;
	glm::vec3 v1=glm::vec3(firstRotate.x, firstRotate.y, firstRotate.z), v2 = glm::vec3(secondRotate.x, secondRotate.y, secondRotate.z);
	return glm::vec4(w1*v2+w2*v1+vecCross(v1,v2), w1*w2 - vecDot(v1, v2));
}

//get the rotation matrix from a given quaternion.
glm::mat4 getRotationMatrixFromQuaternion(glm::vec4 inputQuat) {
	glm::normalize(inputQuat);
	glm::mat4 rotationMatrix=glm::mat4();
	rotationMatrix[0][0] = 1 - 2 * glm::pow(inputQuat.y,2) - 2 * glm::pow(inputQuat.z,2);
	rotationMatrix[0][1] = 2 * inputQuat.x*inputQuat.y - 2 * inputQuat.w*inputQuat.z;
	rotationMatrix[0][2] = 2 * inputQuat.x*inputQuat.z + 2 * inputQuat.w*inputQuat.y;
	rotationMatrix[1][0] = 2 * inputQuat.x*inputQuat.y + 2 * inputQuat.w*inputQuat.z;
	rotationMatrix[1][1] = 1 - 2 * glm::pow(inputQuat.x, 2) - 2 * glm::pow(inputQuat.z, 2);
	rotationMatrix[1][2] = 2 * inputQuat.y*inputQuat.z - 2 * inputQuat.w*inputQuat.x;
	rotationMatrix[2][0] = 2 * inputQuat.x*inputQuat.z - 2 * inputQuat.w*inputQuat.y;
	rotationMatrix[2][1] = 2 * inputQuat.y*inputQuat.z + 2 * inputQuat.w*inputQuat.x;
	rotationMatrix[2][2] = 1 - 2 * glm::pow(inputQuat.x, 2) - 2 * glm::pow(inputQuat.y, 2);
	return rotationMatrix;
}

//Extract position input
glm::vec3 getPositionFromInput(int ithPoint) {
	if (EULER_INPUT) {
		return glm::vec3(keyFramePose[ithPoint * 6], keyFramePose[ithPoint * 6 + 1], keyFramePose[ithPoint * 6 + 2]);
	}
	return glm::vec3(keyFramePose[ithPoint * 7], keyFramePose[ithPoint * 7 + 1], keyFramePose[ithPoint * 7 + 2]);
}

//Extract euler angles input
glm::vec3 getEulerAnglesFromEulerInput(int ithPoint) {
	return glm::vec3(keyFramePose[ithPoint * 6+3], keyFramePose[ithPoint * 6 + 4], keyFramePose[ithPoint * 6 + 5]);
}

//Extract quaternion input
glm::vec4 getQuaternionFromQuaternionInput(int ithPoint) {
	return glm::vec4(keyFramePose[ithPoint * 7 + 3], keyFramePose[ithPoint * 7 + 4], keyFramePose[ithPoint * 7 + 5], keyFramePose[ithPoint * 7 + 6]);
}

//return rotatin matrix given rotating about X for eulerAngles.x degrees
glm::mat4 getMatrixXRotation(glm::vec3 eulerAngles) {
	glm::mat4 outputMatrix = glm::mat4();
	outputMatrix[1][1] = glm::cos(glm::radians(eulerAngles.x));
	outputMatrix[1][2] = -glm::sin(glm::radians(eulerAngles.x));
	outputMatrix[2][1] = glm::sin(glm::radians(eulerAngles.x));
	outputMatrix[2][2] = glm::cos(glm::radians(eulerAngles.x));
	return outputMatrix;
}

//return rotatin matrix given rotating about Y for eulerAngles.y degrees
glm::mat4 getMatrixYRotation(glm::vec3 eulerAngles) {
	glm::mat4 outputMatrix = glm::mat4();
	outputMatrix[0][0] = glm::cos(glm::radians(eulerAngles.y));
	outputMatrix[0][2] = glm::sin(glm::radians(eulerAngles.y));
	outputMatrix[2][0] = -glm::sin(glm::radians(eulerAngles.y));
	outputMatrix[2][2] = glm::cos(glm::radians(eulerAngles.y));
	return outputMatrix;
}

//return rotatin matrix given rotating about Z for eulerAngles.z degrees
glm::mat4 getMatrixZRotation(glm::vec3 eulerAngles) {
	glm::mat4 outputMatrix = glm::mat4();
	outputMatrix[0][0] = glm::cos(glm::radians(eulerAngles.z));
	outputMatrix[0][1] = -glm::sin(glm::radians(eulerAngles.z));
	outputMatrix[1][0] = glm::sin(glm::radians(eulerAngles.z));
	outputMatrix[1][1] = glm::cos(glm::radians(eulerAngles.z));
	return outputMatrix;
}

//Multiply two matrices
glm::mat4 mulMatrix(glm::mat4 matrix1, glm::mat4 matrix2) {
	glm::mat4 returnMatrix;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			returnMatrix[i][j] = matrix1[i][0] * matrix2[0][j] + matrix1[i][1] * matrix2[1][j] + matrix1[i][2] * matrix2[2][j] + matrix1[i][3] * matrix2[3][j];
		}
	}
	return returnMatrix;
}

//Cross multiply two vectors
glm::vec3 vecCross(glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 returnVector;
	returnVector[0] = v1[1] * v2[2] - v1[2] * v2[1];
	returnVector[1] = v1[2] * v2[0] - v1[0] * v2[2];
	returnVector[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return returnVector;
}

//Multiply two vectors
GLfloat vecDot(glm::vec3 v1, glm::vec3 v2) {
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

//build Catmull Rom Matrix
glm::mat4 buildCatmullRomMatrix(GLfloat aValue=0.5f) {
	glm::mat4 returnMatrix;
	returnMatrix[0][0] = -aValue;
	returnMatrix[0][1] = 2-aValue;
	returnMatrix[0][2] = aValue-2;
	returnMatrix[0][3] = aValue;
	returnMatrix[1][0] = 2*aValue;
	returnMatrix[1][1] = aValue-3;
	returnMatrix[1][2] = 3-2*aValue;
	returnMatrix[1][3] = -aValue;
	returnMatrix[2][0] = -aValue;
	returnMatrix[2][1] = 0.0f;
	returnMatrix[2][2] = aValue;
	returnMatrix[2][3] = 0.0f;
	returnMatrix[3][0] = 0.0f;
	returnMatrix[3][1] = 1.0f;
	returnMatrix[3][2] = 0.0f;
	returnMatrix[3][3] = 0.0f;
	return returnMatrix;
}
//build B-Spline Matrix
glm::mat4 buildBSplineMatrix() {
	glm::mat4 returnMatrix;
	returnMatrix[0][0] = -1.0f/6.0f;
	returnMatrix[0][1] = 1.0f /2.0f;
	returnMatrix[0][2] = -1.0f /2.0f;
	returnMatrix[0][3] = 1.0f /6.0f;
	returnMatrix[1][0] = 1.0f /2.0f;
	returnMatrix[1][1] = -1.0f;
	returnMatrix[1][2] = 1.0f /2.0f;
	returnMatrix[1][3] = 0.0f;
	returnMatrix[2][0] = -1.0f /2.0f;
	returnMatrix[2][1] = 0.0f;
	returnMatrix[2][2] = 1.0f /2.0f;
	returnMatrix[2][3] = 0.0f;
	returnMatrix[3][0] = 1.0f /6.0f;
	returnMatrix[3][1] = 4.0f /6.0f;
	returnMatrix[3][2] = 1.0f /6.0f;
	returnMatrix[3][3] = 0.0f;
	return returnMatrix;
}

//ith pointer is the second point in pose matrix, it's begin point of a new interpolation.
//Pose Matrix stored position and direction (7 arguments) for the four points currently active.
void updatePoseMatrix(GLint ithPointer, GLfloat matrixToUpdate[4][7]) {
	glm::vec3 eulerInput;
	glm::vec4 quatInput;
	for (int row = 0; row < 4; row++) {
		if (EULER_INPUT) {

			for (int col = 0; col < 3; col++) {
				matrixToUpdate[row][col] = keyFramePose[(ithPointer - 1 + row)*stepSize + col];
			}
			eulerInput = glm::vec3(keyFramePose[(ithPointer - 1 + row)*stepSize + 3], keyFramePose[(ithPointer - 1 + row)*stepSize + 4], keyFramePose[(ithPointer - 1 + row)*stepSize + 5]);
			quatInput = getQuaternionByEulerRotationNew(eulerInput);
		}
		else {
			for (int col = 0; col < 3; col++) {
				matrixToUpdate[row][col] = keyFramePose[(ithPointer - 1 + row)*stepSize + col];
			}
			quatInput = glm::vec4(keyFramePose[(ithPointer - 1 + row)*stepSize + 3], keyFramePose[(ithPointer - 1 + row)*stepSize + 4], keyFramePose[(ithPointer - 1 + row)*stepSize + 5], keyFramePose[(ithPointer - 1 + row)*stepSize + 6]);

		}
		for (int col = 0; col < 4; col++) {
			matrixToUpdate[row][col + 3] = quatInput[col];
		}
	}
}
	//ith pointer is the second point in pose matrix, it's begin point of a new interpolation.
	//Pose Matrix stored position and direction (7 arguments) for the four points currently active.
void updatePoseMatrixEuler(GLint ithPointer, GLfloat matrixToUpdate[4][6]) {
	glm::vec3 eulerInput;
	glm::vec4 quatInput;
	for (int row = 0; row < 4; row++) {
		if (EULER_INPUT) {

			for (int col = 0; col < 6; col++) {
				matrixToUpdate[row][col] = keyFramePose[(ithPointer - 1 + row)*stepSize + col];
			}
			//eulerInput = glm::vec3(keyFramePose[(ithPointer - 1 + row)*stepSize + 3], keyFramePose[(ithPointer - 1 + row)*stepSize + 4], keyFramePose[(ithPointer - 1 + row)*stepSize + 5]);
			//quatInput = getQuaternionByEulerRotationNew(eulerInput);
		}
		else {
			std::cout << "dude, it's sick and pointless if you want to interpolate by euler value but input quaternions." << std::endl;
		}
	}
}

//Calculate intermedia quaternion given which curve (ith point) we are, what tValue is it now, what Spine matrix we are using and 4 points' position and direction info.
void setInterQuatFromQuat(int ithPoint, GLfloat tValue, glm::mat4 spineMatrix, GLfloat matrixToUpdate[4][7], GLfloat* interQuat) {
	glm::vec4 pVector;
	for (int iteration = 0; iteration < 7; iteration++) {
		for (int i = 0; i < 4; i++){
			pVector[i] = matrixToUpdate[i][iteration];
		}
		interQuat[iteration]=glm::dot(glm::vec4(tValue*tValue*tValue, tValue*tValue, tValue, 1),(glm::transpose(spineMatrix)*pVector));
	}
}

//Calculate intermedia euler given which curve (ith point) we are, what tValue is it now, what Spine matrix we are using and 4 points' position and direction info.
void setInterEulerFromEuler(int ithPoint, GLfloat tValue, glm::mat4 spineMatrix, GLfloat matrixToUpdate[4][6], GLfloat* interEuler) {
	glm::vec4 pVector;
	for (int iteration = 0; iteration < 6; iteration++) {
		for (int i = 0; i < 4; i++) {
			pVector[i] = matrixToUpdate[i][iteration];
		}
		interEuler[iteration] = glm::dot(glm::vec4(tValue*tValue*tValue, tValue*tValue, tValue, 1), (glm::transpose(spineMatrix)*pVector));
	}
}
