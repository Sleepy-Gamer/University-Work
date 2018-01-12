#include "stdafx.h"
#include "Base_Hull.h"

using namespace std;
using namespace CoreStructures;


// Position array in(x, y) pairs
static GLfloat baseVertices[] =
{
	-0.7, 0.0,
	0.7, 0.0,
	0.5, -0.3,
	-0.5, -0.3
};

//Texture coords array for the crab. Floating point values. 
static float baseTexCoord[] =
{
	/*0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0*/

	-0.7, 0.0,
	0.7, 0.0,
	0.5, -0.3,
	-0.5, -0.3
};

//Index array. Determines order.
static GLubyte baseVertextIndex[] = { 0, 1, 2, 3 };

Base_Hull::Base_Hull()
{
	glGenVertexArrays(1, &baseVAO);
	glBindVertexArray(baseVAO);


	//setup VBO for Crab object position data
	glGenBuffers(1, &basePosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, basePosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	// setup VBO for the crab object texture coord data
	glGenBuffers(1, &baseTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, baseTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(baseTexCoord), baseTexCoord, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	//// setup crab vertex index array
	//glGenBuffers(1, &baseIndicesVBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, baseIndicesVBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(baseVertextIndex), baseVertextIndex, GL_STATIC_DRAW);

	/*glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);*/

	glBindVertexArray(0);

}

void Base_Hull::render(void)
{
	glBindVertexArray(baseVAO);
	glDrawArrays(GL_LINE_LOOP,0, 4);
}


