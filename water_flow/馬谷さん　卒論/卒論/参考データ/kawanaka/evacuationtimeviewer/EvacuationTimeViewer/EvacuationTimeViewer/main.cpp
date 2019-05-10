#include <iostream>
#include <cstdio>
#include <GL/glut.h>
#include "EvacuationTimeViewer.h"
#include "gl_screenshot.h"
using namespace std;

//--- Const Variables (don't change it)
int    ADX = 0;
int    ADY = 0;
double ALP = 1.0;
int    DISP_SIZE_W = 800;
int    DISP_SIZE_H = 600;
gl_screenshot gs;

//-------------------
// Initialize Display
//-------------------
void initDisp(int argc, char *argv[])
{
	// Initialize Window
	glutInit(&argc, argv);
	glutInitWindowSize(DISP_SIZE_W, DISP_SIZE_H);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("UMEDA UNDERGROUND");

	// Initialize Background Color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//-------------------
// Display Function
//-------------------
void display(void)
{
	glutSwapBuffers();
	drowLegend(DISP_SIZE_W, DISP_SIZE_H);

	initViewPort(DISP_SIZE_W, DISP_SIZE_H, ADX, ADY, ALP);
	drowEvacuationTime(DISP_SIZE_W, DISP_SIZE_H);
	drowWall(DISP_SIZE_W, DISP_SIZE_H);
}

//-------------------
// Idle Function
//-------------------
void idle(void)
{
	glutPostRedisplay();
}

//-------------------
// Keyboard Function
//-------------------
void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case  27: // ESC
		exit(0);
		break;
	//--- Moving View Area
	case 108: case 54: // KEY "l or 5"
		ADX += 2;
		break;
	case 107: case 56: // KEY "k or 8"
		ADY += 2;
		break;
	case 106: case  52: // KEY "j or 4"
		ADX -= 2;
		break;
	case 105: case  50: // KEY "i or 2"
		ADY -= 2;
		break;

	//--- Wide and Close
	case 119: // KEY "w"
		ALP -= 0.01;
		if (ALP <= 0.0) ALP = 0.01;
		break;
	case  87: // KEY "W"
		ALP += 0.01;
		break;

	//--- Reset View Area
	case 82: case 48: // KEY "R or 0"
		ADX = ADY = 0;
		ALP = 1.0;
		break;
	case 's':
		gs.screenshot("./snapshot.bmp", 32);
		break;
	}
}

//-------------------
// Main
//-------------------
int main(int argc, char *argv[])
{
	initialize(argc, argv);
	initDisp  (argc, argv);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}