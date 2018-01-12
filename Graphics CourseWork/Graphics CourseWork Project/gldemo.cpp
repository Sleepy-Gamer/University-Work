
#include "stdafx.h"
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <CoreStructures\CoreStructures.h>
#include "texture_loader.h"
#include "shader_setup.h"
#include "Boat.h"


using namespace std;
using namespace CoreStructures;


// Globals
GLuint locT; // location of "T" uniform variable in myShaderProgram
GLuint locT2;
GLuint locT3;


// Textures
GLuint wavesTexture = 0;
GLuint skyTexture = 1;
GLuint boatPlanks = 2;
GLuint crabPic = 3;
GLuint flyingSeagull = 4;
GLuint seagull = 5;
GLuint sail = 6;

// Mouse input (rotation) example
// Variable we'll use to animate (rotate)
float theta = 0.0f;

// Variables needed to track where the mouse pointer is so we can determine which direction it's moving in
int mouse_x, mouse_y;
bool mDown = false;

//Boat variables
//Boat *myBoat = nullptr;
//
//float boatX = -0.7f;
//float boatY = 0.7f;
//float boatOrientation = 0.0f;

// Shader program object for applying textures to our shapes
GLuint myShaderProgram;
// Second shader progam object for non textured shapes
GLuint myShaderProgramNoTexture;
// Vertex Buffer Object IDs for the sea texture object
GLuint quadPosVBO, quadColourVBO, quadTexCoordVBO, quadIndicesVBO;
// Vertex Buffer Object IDs for the sky texture object
GLuint quadMPosVBO, quadMColourVBO, quadMTexCoordVBO, quadMIndicesVBO;
//Vertext Buffer Object IDs for the Crab
GLuint crabPosVBO, crabColourVBO, crabTexCoordVBO, crabIndicesVBO;
GLuint birdPosVBO, birdColourVBO, birdTexCoordVBO, birdIndicesVBO;
GLuint seagullPosVBO, seagullColourVBO, seagullTexCoordVBO, seagullIndicesVBO;

// Packed vertex arrays for the sea object

// 1) Position Array - Store vertices as (x,y) pairs
static GLfloat quadVertices[] = 
{
	-1.0, -0.5f,
	-1.0f, 0.5f,
	1.0f, -0.5f,
	1.0f, 0.5f
};

// 2) Colour Array - Store RGB values as unsigned bytes
static GLubyte quadColors[] =
{
	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255
};

// 3) Texture coordinate array (store uv coordinates as floating point values)
static float quadTextureCoords[] =
{
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};

// 4) Index Array - Store indices to quad vertices - this determines the order the vertices are to be processed
static GLubyte quadVertexIndices[] = { 0, 1, 2, 3 };

// -----------------------
// Packed vertex arrays for the sky object

// 1) Position Array - Store vertices as (x,y) pairs
static GLfloat quadMVertices[] = 
{
	-1.0, -0.5f,
	-1.0f, 0.5f,
	1.0f, -0.5f,
	1.0f, 0.5f
};

// 2) Colour Array - Store RGB values as unsigned bytes
static GLubyte quadMColors[] = 
{
	255, 0, 0, 255,
	255, 255, 0, 255,
	0, 255, 0, 255,
	0, 255, 255, 255
};

// 3) Texture coordinate array (store uv coordinates as floating point values)
static float quadMTextureCoords[] =
{
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};

// 4) Index Array - Store indices to quad vertices - this determines the order the vertices are to be processed
static GLubyte quadMVertexIndices[] = { 0, 1, 2, 3 };

//Packed vertex arrays for the Crab object

//Position array in (x,y) pairs
static GLfloat crabVertices[] =
{
	0.7, -0.7,
	0.7, -0.5,
	0.4, -0.5,
	0.4, -0.7,
	0.7, -0.7
};

//Colour array. RGB values.
static GLubyte crabColours[] =
{
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255
};

//Texture coords array for the crab. Floating point values. 
static float crabTexCoord[] =
{
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0
};

//Index array. Determines order.
static GLubyte crabVertextIndex[] = { 0, 1, 2, 3, 4, 5 };


//Packed vertex arrays for the flying seagull object

//Position array in (x,y) pairs
static GLfloat birdVertices[] =
{
	0.9, 0.8,
	0.9, 0.6,
	0.6, 0.6,
	0.6, 0.8, 
	0.9, 0.8
	
};

//Colour array. RGB values.
static GLubyte birdColours[] =
{
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255
};

//Texture coords array for the crab. Floating point values. 
static float birdTexCoord[] =
{
	/*0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0*/

	0.0, 0.0,
	0.0, 1.0, 
	1.0, 1.0,
	1.0, 0.0
};

//Index array. Determines order.
static GLubyte birdVertextIndex[] = { 0, 1, 2, 3, 4, 5 };

//Packed vertex arrays for the peaking seagull object

//Position array in (x,y) pairs
static GLfloat seagullVertices[] =
{
	-0.6, 0.1,
	-0.6, 0.0,
	-0.7, 0.0,
	-0.7, 0.1,
	-0.6, 0.1

};

//Colour array. RGB values.
static GLubyte seagullColours[] =
{
	255, 255, 255,
	255, 255, 255,
	255, 255, 255,
	255, 255, 255
};

//Texture coords array for the crab. Floating point values. 
static float seagullTexCoord[] =
{
	0.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0
};

//Index array. Determines order.
static GLubyte seagullVertextIndex[] = { 0, 1, 2, 3, 4, 5 };

// Function Prototypes
void init(int argc, char* argv[]);
void setupQuadTextureWavesVBO(void);
void setupQuadTextureSkyVBO(void);
void setupCrabVBO(void);
void setupBirdVBO(void);
void setupSeagullVBO();
void report_version(void);
void display(void);
void birdSaysHello();
void drawTexturedQuadVBOWaves(void);
void drawTexturedQuadVBOSky(void);
void blendedSun();
float wobbleBirdy();
int whatIsCheese(int);
void drawABoat(void);
void drawCrabVBO(void);
void drawBirds();
void drawBirdVBO();
void drawSeagullVBO();
void update(void);



int _tmain(int argc, char* argv[])
{
	init(argc, argv);

	glutMainLoop();

	// Shut down COM
	shutdownCOM();

	return 0;
}


void init(int argc, char* argv[])
{
	// Initialise COM so we can use Windows Imaging Component
	initCOM();

	// Initialise FreeGLUT
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(64, 64);
	glutCreateWindow("Cheese");

	// Register callback functions
	glutDisplayFunc(display);
	glutIdleFunc(update);
	

	// Initialise GLEW library
	GLenum err = glewInit();

	// Ensure GLEW was initialised successfully before proceeding
	if (err == GLEW_OK) 
	{
		cout << "GLEW initialised okay\n";
	} 

	else 
	{
		cout << "GLEW could not be initialised\n";
		throw;
	}
	
	// Example query OpenGL state (get version number)
	report_version();


	// Report maximum number of vertex attributes
	GLint numAttributeSlots;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributeSlots);
	cout << "GL_MAX_VERTEX_ATTRIBS = " << numAttributeSlots << endl;


	// Initialise OpenGL...

	// Setup colour to clear the window
	glClearColor(0.2f, 0.2f, 0.8f, 0.0f);

	glLineWidth(5.0f);

	// Load demo texture
	wavesTexture = fiLoadTexture("waves.jpg");
	skyTexture = fiLoadTexture("sky3.jpg");
	boatPlanks = fiLoadTexture("planks.jpeg");
	crabPic = fiLoadTexture("Crab.png");
	flyingSeagull = fiLoadTexture("flyingSeagull.jpg");
	seagull = fiLoadTexture("BirdHullo.jpg");
	sail = fiLoadTexture("blueFabric.jpg");
	
	// Shader setup 
	myShaderProgram = setupShaders(string("Shaders\\basic_vertex_shader.txt"), string("Shaders\\basic_fragment_shader.txt"));
	myShaderProgramNoTexture = setupShaders(string("Shaders\\notexture_vertex_shader.txt"), string("Shaders\\notexture_fragment_shader.txt"));

	// Get uniform location of "T" variable in shader program (we'll use this in the play function to give the uniform variable "T" a value)
	locT = glGetUniformLocation(myShaderProgram, "T");
	locT2 = glGetUniformLocation(myShaderProgramNoTexture, "T2");

	// Setup star object using Vertex Buffer Objects (VBOs)
	setupQuadTextureWavesVBO();
	setupQuadTextureSkyVBO();
	setupCrabVBO();
	setupBirdVBO();
	setupSeagullVBO();

	//myBoat = new Boat();

}


void report_version(void) 
{
	int majorVersion, minorVersion;

	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

	cout << "OpenGL version " << majorVersion << "." << minorVersion << "\n\n";

	cout << "Welcome to my scene!" << endl << "It is called Cheese, for no particular reason." << endl;
	cout << "It features a boat, on the sea during a lovely sun set," << endl << "the sun is partially visable." << endl;
	cout << "There is a happy crab at the bottom." << endl << "You can move him using the Left and Right arrow keys." << endl;
	cout << "Also in this scene is a seagull just flying by, " << endl << "and a strange alien 'bird' who has come to visit." << endl;
	cout << "Thank you and enjoy!!" << endl << "15051013. Katherine Axten" << endl << endl;

}


// Waves
void setupQuadTextureWavesVBO(void) 
{
	// setup VBO for the quad object position data
	glGenBuffers(1, &quadPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	// setup VBO for the quad object colour data
	glGenBuffers(1, &quadColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadColors), quadColors, GL_STATIC_DRAW);

	// setup VBO for the quad object texture coord data
	glGenBuffers(1, &quadTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadTextureCoords), quadTextureCoords, GL_STATIC_DRAW);

	// setup quad vertex index array
	glGenBuffers(1, &quadIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadVertexIndices), quadVertexIndices, GL_STATIC_DRAW);
}

// Sky
void setupQuadTextureSkyVBO(void) 
{
	// setup VBO for the quad object position data
	glGenBuffers(1, &quadMPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadMPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadMVertices), quadMVertices, GL_STATIC_DRAW);

	// setup VBO for the quad object colour data
	glGenBuffers(1, &quadMColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadMColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadMColors), quadMColors, GL_STATIC_DRAW);

	// setup VBO for the quad object texture coord data
	glGenBuffers(1, &quadMTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadMTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadMTextureCoords), quadMTextureCoords, GL_STATIC_DRAW);

	// setup quad vertex index array
	glGenBuffers(1, &quadMIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadMIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadMVertexIndices), quadMVertexIndices, GL_STATIC_DRAW);
}

//Crab
void setupCrabVBO(void)
{
	//setup VBO for Crab object position data
	glGenBuffers(1, &crabPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, crabPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crabVertices), crabVertices, GL_STATIC_DRAW);

	// setup VBO for the crab object colour data
	glGenBuffers(1, &crabColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, crabColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crabColours), crabColours, GL_STATIC_DRAW);

	// setup VBO for the crab object texture coord data
	glGenBuffers(1, &crabTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, crabTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(crabTexCoord), crabTexCoord, GL_STATIC_DRAW);

	// setup crab vertex index array
	glGenBuffers(1, &crabIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, crabIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(crabVertextIndex), crabVertextIndex, GL_STATIC_DRAW);

}

void setupBirdVBO(void)
{
	//setup VBO for Crab object position data
	glGenBuffers(1, &birdPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, birdPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(birdVertices), birdVertices, GL_STATIC_DRAW);

	// setup VBO for the crab object colour data
	glGenBuffers(1, &birdColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, birdColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(birdColours), birdColours, GL_STATIC_DRAW);

	// setup VBO for the crab object texture coord data
	glGenBuffers(1, &birdTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, birdTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(birdTexCoord),birdTexCoord, GL_STATIC_DRAW);

	// setup crab vertex index array
	glGenBuffers(1, &birdIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, birdIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(birdVertextIndex), birdVertextIndex, GL_STATIC_DRAW);

}

void setupSeagullVBO(void)
{
	//setup VBO for peaking seagull object position data
	glGenBuffers(1, &seagullPosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, seagullPosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(seagullVertices), seagullVertices, GL_STATIC_DRAW);

	// setup VBO for the peaking seagull object colour data
	glGenBuffers(1, &seagullColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, seagullColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(seagullColours), seagullColours, GL_STATIC_DRAW);

	// setup VBO for the peaking seagull object texture coord data
	glGenBuffers(1, &seagullTexCoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, seagullTexCoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(seagullTexCoord), seagullTexCoord, GL_STATIC_DRAW);

	// setup peaking seagull vertex index array
	glGenBuffers(1, &seagullIndicesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, seagullIndicesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(crabVertextIndex), crabVertextIndex, GL_STATIC_DRAW);

}

void display(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render our scene in sequence
	
	// draw the sky.
	 drawTexturedQuadVBOSky();
	
	// draw the waves
	 drawTexturedQuadVBOWaves();
	 //Call the boooooat
	 blendedSun();
	 drawSeagullVBO();
	 drawABoat();
	 //Crab
	 //crab();
	 drawBirds();
	
	 drawCrabVBO();
	 drawBirdVBO();

	 

	 //glutIdleFunc(birdAnimation);

	 //myBoat->renderBoat(boatX, boatY, 1.5f, boatOrientation);

	glutSwapBuffers();
}

//void birdSaysHello()
//{
//	glUseProgram(0);
//	glColor3ub();
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, seagull);
//	glEnable(GL_TEXTURE_2D);
//	glBegin(GL_TRIANGLE_FAN);
//	{
//		glTexCoord2f(0.0, 1.0);
//		glVertex2f(-0.7, 0.0);
//		glTexCoord2f(0.0, 0.0);
//		glVertex2f(-0.7, 0.1);
//		glTexCoord2f(1.0, 0.0);
//		glVertex2f(-0.6, 0.1);
//		glTexCoord2f(1.0, 1.0);
//		glVertex2f(-0.6, 0.0);
//		glEnd();
//		glDisable(GL_TEXTURE_2D);
//	}
//}
float crabLRControls()
{
	static float speed = 0.001;


	if (GetAsyncKeyState(VK_LEFT))
	{
		speed -= 0.001;
		
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		speed += 0.001;
	}

	return speed;
}

float FlyingBirdy()
{
	static float speed = 0.001;
	
		speed -= 0.001;
		if (speed <= -2.000)
		{
			speed = .5f;
		}


	return speed;
}


//float crabUDControls()
//{
//	
//	static float rotate = 0.0f;
//
//
//	if (GetAsyncKeyState(VK_LEFT) && cheese == 1)
//	{
//		rotate -= 0.01;
//		cheese = 2;
//
//	}
//
//	else if (GetAsyncKeyState(VK_LEFT) && cheese == 2)
//	{
//		rotate += 0.01;
//		cheese = 1;
//
//	}
//
//
//	if (GetAsyncKeyState(VK_RIGHT))
//	{
//		rotate += 0.01;
//	}
//
//	return rotate;
//}



//Draw the strange Space Bird
void drawBirds()
{
	glUseProgram(0);

	glBegin(GL_TRIANGLE_FAN);
	{
		glColor3ub(47, 79, 79);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.6f, 0.4f);
		glVertex2f(0.6f, 0.3f);
		//glVertex2f(0.3f, 0.4f);
		glEnd();
	}

	glBegin(GL_TRIANGLE_FAN);
	{
		glColor3ub(47, 79, 79); //Black?
		glVertex2f(0.4f, 0.4f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, 0.46f);
		glEnd();
	}

	glBegin(GL_TRIANGLE_FAN);
	{
		glColor3ub(47, 79, 79);
		glVertex2f(0.7f, 0.5f);
		glVertex2f(0.6f, 0.3f);
		glVertex2f(0.6f, 0.4f);
		glEnd();
	}

	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex2f(0.7f, 0.5f);
		glVertex2f(0.8f, 0.4f);
		glVertex2f(0.7f, 0.46f);
		glEnd();
	}

}
void drawSeagullVBO(void)
{
	glUseProgram(myShaderProgram);

	//Transform the coords into World Coordinates
	GUMatrix4 T = GUMatrix4::translationMatrix(0.1f, 0.0f, 0.0f) * GUMatrix4::translationMatrix(0.1, 0.0, 0.0);
	//GUMatrix4 R = GUMatrix4::translationMatrix(crabLRControls(), 0.0f, 0.0) * GUMatrix4::rotationMatrix(crabLRControls(), 0.0, 0.0);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);
	//glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&R);

	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, seagull);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, seagullPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, seagullTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, seagullIndicesVBO);

	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);
}

void drawCrabVBO(void)
{
	glUseProgram(myShaderProgram);

	//Transform the coords into World Coordinates
	GUMatrix4 T = GUMatrix4::translationMatrix(0.1f, 0.0f, 0.0f) * GUMatrix4::translationMatrix(crabLRControls(), 0.0, 0.0);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, crabPic);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, crabPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, crabTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, crabIndicesVBO);

	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);
}
void drawBirdVBO(void)
{
	glUseProgram(myShaderProgram);

	//Transform the coords into World Coordinates
	GUMatrix4 G = GUMatrix4::translationMatrix(0.1f, 0.0f, 0.0) * GUMatrix4::translationMatrix(FlyingBirdy(), 0.0, 0.0);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&G);

	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, flyingSeagull);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, birdPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, birdTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, birdIndicesVBO);

	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);
	glUseProgram(0);
}

//Sun
void blendedSun()
{
	glUseProgram(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glBegin(GL_POLYGON);
	{
		//glColor3f(1.0, 0.0, 0.0); //Red
		glVertex2f(-0.4, 0.0); 
		glVertex2f(-0.3, 0.12);
		glColor3f(0.0, 1.0, 0.0); //Green
		glVertex2f(0.0, 0.2f);
		glVertex2f(0.3, 0.12);
		glColor3f(0.0, 0.0, 1.0); //Blue
		glVertex2f(0.4, 0.0f);
		//glVertex2f(-0.1f, 0.0f);
		glEnd();
		glDisable(GL_BLEND);
	}

}

//BOAT
void drawABoat(void)
{
	glUseProgram(0);
	//glUseProgram(myShaderProgram);

	glBegin(GL_QUADS);
	{
		glColor3ub(128, 0, 0); 
		glVertex2f(-0.2f, 0.0f);
		glColor3ub(222, 184, 135);
		glVertex2f(-0.2f, 0.2f);
		glColor3ub(139, 69, 19); 
		glVertex2f(-0.1f, 0.2f);
		glVertex2f(-0.1f, 0.0f);
		glEnd();
	}

	//Right Pole
	glBegin(GL_QUADS);
	{
		glColor3ub(128, 0, 0);
		glVertex2f(0.0f, 0.0f);
		glColor3ub(222, 184, 135);
		glVertex2f(0.0f, 0.2f);
		glColor3ub(139, 69, 19);
		glVertex2f(0.1f, 0.2f);
		glVertex2f(0.1f, 0.0f);
		glEnd();
	}

	//Left Flag
	//This tells OpenGL to ignore any glColor and replace it with teh colours in the texture image.
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sail);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN);
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-0.09f, 0.2f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-0.4f, 0.2f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-0.09f, 0.6f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	//Right Flag
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sail);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN);
	{
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-0.01f, 0.2f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.4f, 0.2f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-0.01f, 0.6f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	//Boat Base
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, boatPlanks);
	/*glUniform1i(glGetUniformLocation(myShaderProgram, "boatPlanks"), 0);*/
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN);
	{
		//glColor3ub(255, 0, 0);
		glTexCoord2f(1.0, 0.0);
		//glTexCoord2f(-0.7, 0.0);
		glVertex2f(-0.7, 0.0);
		glTexCoord2f(0.0, 0.0);
		//glTexCoord2f(0.7, 0.0);
		glVertex2f(0.7, 0.0);
		glTexCoord2f(0.0, 1.0);
		//glTexCoord2f(0.5, -0.3);
		glVertex2f(0.5, -0.3);
		glTexCoord2f(1.0, 1.0);
		//glTexCoord2f(-0.5, -0.3);
		glVertex2f(-0.5, -0.3);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}
	//boat coords
	/*glEnable(GL_TEXTURE_2D);
	glBegin(GL_LINE_LOOP);
	{
		glColor3ub(255, 0, 1);
		glVertex2f(-0.7, 0.0);
		glVertex2f(-0.2, 0.0);
		glVertex2f(-0.2, 0.2);
		glVertex2f(-0.4, 0.2);
		glVertex2f(-0.1, 0.5);
		glVertex2f(-0.1, 0.2);
		glVertex2f(-0.1, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 0.2);
		glVertex2f(0.0, 0.6);
		glVertex2f(0.4, 0.2);
		glVertex2f(0.1, 0.2);
		glVertex2f(0.1, 0.0);
		glVertex2f(0.7, 0.0);
		glVertex2f(0.5, -0.3);
		glVertex2f(-0.5, -0.3);
		glEnd();
	}*/
	
//}

//void crab(void)
//{
//	glUseProgram(0); //what does this do. 
//	glBindTexture(GL_TEXTURE_2D, crabPic);
//	glEnable(GL_TEXTURE_2D);
//	glBegin(GL_TRIANGLE_FAN);
//	{
//		glColor3ub(255, 255, 255);
//		glTexCoord2f(0.0f, 1.0f);
//		glVertex2f(0.7, -0.7);
//		glTexCoord2f(0.0f, 0.0f);
//		glVertex2f(0.7, -0.5);
//		glTexCoord2f(1.0f, 0.0f);
//		glVertex2f(0.4, -0.5);
//		glTexCoord2f(1.0f, 1.0f);
//		glVertex2f(0.4, -0.7);
//		glEnd();
//		glDisable(GL_TEXTURE_2D);
//	}
//}
// Draw the waves function
void drawTexturedQuadVBOWaves(void) 
{
	glUseProgram(myShaderProgram);

	// Move our ground shape to the bottom half of the screen
	GUMatrix4 T = GUMatrix4::translationMatrix(0.0f, -0.5f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)
	
	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, wavesTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);
	
	glBindBuffer(GL_ARRAY_BUFFER, quadPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, quadColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesVBO);

	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);

	// use to force disable our shaderprogram
 	// glUseProgram(0);
}

// Draw the sky
void drawTexturedQuadVBOSky(void)
{
	glUseProgram(myShaderProgram);

	//Move our shape into the top position
	GUMatrix4 T = GUMatrix4::translationMatrix(0.0f, 0.5f, 0.0f);
	glUniformMatrix4fv(locT, 1, GL_FALSE, (GLfloat*)&T);

	// Bind each vertex buffer and enable
	// The data is still stored in the GPU but we need to set it up (which also includes validation of the VBOs behind-the-scenes)

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skyTexture);
	glUniform1i(glGetUniformLocation(myShaderProgram, "texture"), 0);
	glEnable(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, quadPosVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, quadColourVBO);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, quadTexCoordVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
	glEnableVertexAttribArray(2);

	// Bind the index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndicesVBO);

	// Draw the object - same function call as used for vertex arrays but the last parameter is interpreted as an offset into the currently bound index buffer (set to 0 so we start drawing from the beginning of the buffer).
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, (GLvoid*)0);

	glDisable(GL_TEXTURE_2D);
}

// square movement -------------------------------------------------------------
// update is called every frame
void update(void) 
{
	theta += 0.0025f;
	// Redraw the screen
	glutPostRedisplay();
}
//#pragma region Event handling functions
//
//void mouseButtonDown(int button_id, int state, int x, int y) {
//
//	if (button_id == GLUT_LEFT_BUTTON) {
//
//		if (state == GLUT_DOWN) {
//
//			mouse_x = x;
//			mouse_y = y;
//
//			mDown = true;
//
//		}
//		else if (state == GLUT_UP) {
//
//			mDown = false;
//		}
//	}
//}
//
//
//void mouseMove(int x, int y) {
//
//	if (mDown) {
//
//		int dx = x - mouse_x;
//		int dy = y - mouse_y;
//
//		theta += (float)dy * (3.142f * 0.01f);
//
//		mouse_x = x;
//		mouse_y = y;
//
//		glutPostRedisplay();
//	}
//}
//
//
//void keyDown(unsigned char key, int x, int y) {
//
//	if (key == 'r') {
//
//		theta = 0.0f;
//		glutPostRedisplay();
//	}
//}
//
//#pragma endregion


