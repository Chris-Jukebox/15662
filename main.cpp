#define _CRT_SECURE_NO_WARNINGS

#include "sph_header.h"
#include "sph_data.h"
#include "sph_timer.h"
#include "sph_system.h"
#include <gl/freeglut.h>

SPHSystem *sph;

Timer *sph_timer;

void init();
void display(void);
void centerOnScreen();
void drawObject();
void update();

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 480;
int window_height = 480;

//  variable representing the window title
char *window_title;

void main(int argc, char **argv) {
	glutInit(&argc, argv);
	centerOnScreen();
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(window_x, window_y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("?(*´? ?*)?");

	//  Set OpenGL program initial state.
	init();

	// Set the callback functions -> call in every frame
	glutDisplayFunc(display);

	// ??? make it refresh every frame
	glutIdleFunc(update);

	// Start GLUT event processing loop
	glutMainLoop(); 
}

void update()
{
	glutPostRedisplay();
}

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init()
{
	//  Set the frame buffer clear color to black. 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	// SPH
	sph = new SPHSystem();
	sph->init_system();
	sph->sys_running = 1;

	// Timer
	sph_timer = new Timer();

	window_title = (char *)malloc(sizeof(char) * 50);
}

//-------------------------------------------------------------------------
//  Update()
//-------------------------------------------------------------------------
void display(void)
{
	// clear the canvas
	glClear(GL_COLOR_BUFFER_BIT);
	
	// sph.Update()
	sph->animation();

	// timer.Update()  <- this is for framerate display
	sph_timer->update();

	// draw par!ti!cle!
	drawObject();

	glutSwapBuffers();

	// display fps on window title  <- for debug wwwww
	memset(window_title, 0, 50);
	sprintf(window_title, "FPS: %f", sph_timer->get_fps());
	glutSetWindowTitle(window_title);
}

//-------------------------------------------------------------------------
//  Draws the particles =w=
//-------------------------------------------------------------------------
void drawObject()
{
	glPointSize(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	for (uint i = 0; i < sph->num_particle; i++) {
		glBegin(GL_POINTS);
		// scale the positions ???
		glVertex3f(sph->mem[i].pos.x * 2 - 0.8, sph->mem[i].pos.y * 2 - 0.8, sph->mem[i].pos.z);
		glEnd();
	}
}

void centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}