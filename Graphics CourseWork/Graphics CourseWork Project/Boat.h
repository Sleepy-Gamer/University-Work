#pragma once

#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include "texture_loader.h"
#include "shader_setup.h"

class Base_Hull;

class Boat
{
	//The components used to draw the boat.
	Base_Hull *boatBaseComponent;

	//Textures used in the boat. 
	GLuint boatHullTexture;

	//Shader program for drawing the boat.
	GLuint boatShader;

	//Uniform variable locations in BoatShader
	GLuint locT;

public:
	Boat();

	//Render the boat object
	void renderBoat(float x, float y, float scale, float orientation);
};

