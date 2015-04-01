#include "GL/glut.h"
#include "objectWriter.h"


float look_x = 3;
float look_y = 3;
float look_z = 3;

void specialPress(int key, int x, int y){
	/* Rewrite this less shit */
	if (key == GLUT_KEY_LEFT)
		look_y -= 0.2;
	else if (key == GLUT_KEY_RIGHT)
		look_y += 0.2;
	else if (key == GLUT_KEY_UP)
		look_x += 0.2;
	else if (key == GLUT_KEY_DOWN)
		look_y -= 0.2;

	glutPostRedisplay();
}

void display(void){
	glClearColor(0, 0, 0, 1);
	//glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	//renderLighting();

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60, w / h, 0.1, 100);



	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();




	gluLookAt
		(
		look_x, look_y, look_z,
		0, 0, 0,
		0, 0, 1
		);
	glPushMatrix();
	glTranslatef(1, 1, 0);//Red
	//glColor3f(1, 0, 0);
	drawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 1, 0);//Green
	//glColor3f(0, 1, 0);
	drawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -1, 0);//Blue
	//glColor3f(0, 0, 1);
	drawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, -1, 0);//Odd
	//glColor3f(0.75, 0.75, 0.75);
	drawTableLeg();
	glPopMatrix();

	glPushMatrix();
	//glColor3f(0, 0, 1);
	glTranslatef(0, 0, 0.75);
	drawTableSurface();
	glPopMatrix();

	//glutSolidCone(1, 2, 10, 10);
	glColor3f(0, 0, 1);
	glTranslatef(0, 0, 1.25);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(0.5);


	glColor3f(0.75, 0.75, 0.75);
	glutSwapBuffers();
	//glFlush();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Graphics Assignment 2");
	glutDisplayFunc(display);
	glutSpecialFunc(specialPress);
	//glutKeyboardFunc(keyPressed);



	//GLfloat lightpos[] = { 0, 4, -4, 0.0f };


	//setSpotlight();
	

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//renderLighting();
	//glEnable(GL_LIGHT0);



	//glEnable(GL_COLOR_MATERIAL);
	
	//glShadeModel(GL_SMOOTH);

	//glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}