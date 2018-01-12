#include "stdafx.h"
#include "Boat.h"
#include "Base_Hull.h""

using namespace std;
using namespace CoreStructures;

Boat::Boat()
{
	boatBaseComponent = new Base_Hull();

	//Load texture images
	boatHullTexture = wicLoadTexture(wstring(L"planks.jpeg"));

	//Load shaders
	boatShader = setupShaders(string("Shaders\\basic_vertex_shader.txt"), string("Shaders\\basic_fragment_shader.txt"));

	//Setup uniform locations
	locT = glGetUniformLocation(boatShader, "T");

}


void Boat::renderBoat(float x, float y, float scale, float orientation)
{
	//Boat shader
	glUseProgram(boatShader);

	//Draw the hull

	// Create matrices based on input parameters
	GUMatrix4 bodyTransform = GUMatrix4::translationMatrix(x, y, 0.0f) *
		GUMatrix4::rotationMatrix(0.0f, 0.0f, orientation*gu_radian) *
		GUMatrix4::scaleMatrix(scale, scale, scale);

	// Upload body transform to shader
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&bodyTransform);

	// Use the snow texture for the main body
	glBindTexture(GL_TEXTURE_2D, boatHullTexture);

	// Draw the circle for the body
	boatBaseComponent->render();
}

