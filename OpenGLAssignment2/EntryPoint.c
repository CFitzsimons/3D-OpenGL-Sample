#include "GL/glut.h"
#include <stdio.h>

#define RECT_X 1
#define RECT_Y 1
#define RECT_Z 0.5
int rotate_x = 0;

double rect[8][3] = {
		{ -RECT_X, RECT_Y, -RECT_Z },
		{ -RECT_X, RECT_Y, RECT_Z },
		{ RECT_X, RECT_Y, RECT_Z },
		{ RECT_X, RECT_Y, -RECT_Z },
		{ -RECT_X, -RECT_Y, -RECT_Z },//-1,-1,-1
		{ -RECT_X, -RECT_Y, RECT_Z },//-1,-1,1
		{ RECT_X, -RECT_Y, RECT_Z },//1,-1,1
		{ RECT_X, -RECT_Y, -RECT_Z }//1,-1,-1
};

int spotLight = 1;

void press(char key, int x, int y){
	if (key == 'f')
		spotLight = 0;
	else if (key == 's')
		spotLight = 1;

	glutPostRedisplay();
}
void normaliseSurface(double normal[3], int a, int b, int c, int d){

	double V1[3] = { rect[a][0] - rect[b][0], rect[a][1] - rect[b][1], rect[a][2] - rect[b][2] };
	double V2[3] = { rect[b][0] - rect[d][0], rect[b][1] - rect[d][1], rect[b][2] - rect[d][2] };

	//	double* normal = (double*)malloc(sizeof(double) * 3);

	normal[0] = V1[1] * V2[2] - V1[2] * V2[1];
	normal[1] = V1[0] * V2[2] - V1[2] * V2[0];
	normal[2] = V1[0] * V2[1] - V1[1] * V2[0];

}

void writeQuad(int a, int b, int c, int d){
	glBegin(GL_QUADS);
	{
		double normal[3];
		normaliseSurface(normal, a, b, c, d);
		printf("%d, %d, %d\n", normal[0], normal[1], normal[2]);
		glNormal3dv(normal);
		glVertex3dv(rect[a]);
		glVertex3dv(rect[b]);
		glVertex3dv(rect[c]);
		glVertex3dv(rect[d]);
	}
	glEnd();
}


void drawCube(){
	GLfloat color[] = { 0.f, 1.f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	writeQuad(0, 1, 2, 3);
	writeQuad(1, 5, 6, 2);
	writeQuad(4, 5, 6, 7);
	writeQuad(0, 4, 7, 3);
	writeQuad(0, 1, 5, 4);
	writeQuad(3, 2, 6, 7);
	
}
void drawFloor(){
	glBegin(GL_POLYGON);
	{
		/* Normalisation block */
		double V1[3] = { 8, 8, 0 };
		double V2[3] = { 8, -8, 0 };
		double normal[3];
		normal[0] = V1[1] * V2[2] - V1[2] * V2[1];
		normal[1] = V1[0] * V2[2] - V1[2] * V2[0];
		normal[2] = V1[0] * V2[1] - V1[1] * V2[0];

		glVertex3dv(normal);
		glVertex3d(-4, -4.0, -2);//br
		glVertex3d(-4, 4.0, -2);//tr
		glVertex3d(4, 4.0, -2); //tl
		glVertex3d(4, -4.0, -2);//bl
	}
	glEnd();
}
void setMaterial(float r, float g, float b, GLenum lightType){
	GLfloat color[] = { 0.f, 1.f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
}

void setSpotLight(){
	GLfloat lightpos[] = { 0, 3, 3, 1.0f };
	GLfloat direction[] = { 0, -3, -3 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 8.0f);
}


void setPointLight(){
	GLfloat lightpos[] = { 0, 3, 3, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
}


void renderLighting(){

	//glPushMatrix();

	if (spotLight == 1)
		setSpotLight();
	else
		setPointLight();

	//glPopMatrix();
	//glLoadIdentity();
}


double count_x = 3;
int add_x = 1;
double count_y = 3;
int add_y = 1;
int mov_x = -4;
int mov_y = 4;
void display()
{
	//glClearColor(1, 1, 1, 1);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	renderLighting();

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60, w / h, 0.1, 100);



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	


	gluLookAt
		(
		mov_x, mov_y, 4,
		0, 0, 0,
		0, 0, 1
		);

	//glPushMatrix();
	////glMatrixMode(GL_PROJECTION);
	////glLoadIdentity();
	//glTranslatef(0, 0, 3);
	//renderLighting();
	//glPopMatrix();

	//count_x = add_x == 1 ? count_x + 0.2 : count_x - 0.2;
	count_y = add_y == 1 ? count_y + 0.2 : count_y - 0.2;
	//glPushMatrix();
	//glRotatef(rotate_x, 0, 0, 1);
	/* Draw objects */

	drawCube();
	//glutSolidSphere(1, 10, 10);

	/* Make sure the teapot is the right way up */
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 1, 0);

	GLfloat color[] = { 0.5f, 0.5f, 0.5f, 0.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glutSolidTeapot(0.5);


	/*glRotatef(270, 1, 0, 0);
	glTranslatef(0, 0, 3);
	color[0] = 0.0f;
	color[1] = 1.0f;
	color[2] = 0.5f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	
	glTranslatef(0, 0, 0);*/
	//renderLighting();
	//glPopMatrix();
	//glLoadIdentity();



	//glFlush();
	glutSwapBuffers();
}

void buttonPressed(int state, int x, int y){
	if (state == GLUT_KEY_LEFT){
		if (mov_x <= -4 && mov_y <= 4)
			mov_y++;
		else if (mov_y <= -4 && mov_x >= -4)
			mov_x--;
		else if (mov_x >= 4 && mov_y >= -4)
			mov_y--;
		else if (mov_y >= 4 && mov_x <= 4)
			mov_x++;
		glutPostRedisplay();
	}
	else if (state == GLUT_KEY_RIGHT){
		if (mov_x <= -4 && mov_y >= -4)
			mov_y--;
		else if (mov_y <= -4 && mov_x <= 4)
			mov_x++;
		else if (mov_x >= 4 && mov_y <= 4)
			mov_y++;
		else if (mov_y >= 4 && mov_x >= -4)
			mov_x--;
		glutPostRedisplay();
	}else if (state == GLUT_KEY_DOWN){
		add_y = 1;
	}
	else if (state == GLUT_KEY_UP){
		add_y = 0;
	}
	
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Graphics Assignment 2");
	glutDisplayFunc(display);
	glutSpecialFunc(buttonPressed);
	glutKeyboardFunc(press);



	//GLfloat lightpos[] = { 0, 4, -4, 0.0f };


	//setSpotlight();
	

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	renderLighting();
	glEnable(GL_LIGHT0);



	//glEnable(GL_COLOR_MATERIAL);
	
	//glShadeModel(GL_SMOOTH);

	//glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}