#pragma once

#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include "texture_loader.h"
#include "shader_setup.h"

class Base_Hull
{
	//Variables for VBO
	GLuint baseVAO, basePosVBO, baseTexCoordVBO;

public:
	Base_Hull();

	void render(void);

};

