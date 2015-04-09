#include "GL/glut.h"
#include "objectWriter.h"
#include "lighting.h"

int mov_x = 3;
int mov_y = 5;
int mov_z = 4;
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
	}
	else if (state == GLUT_KEY_UP){
		mov_z++;
		glutPostRedisplay();
	}
	else if (state == GLUT_KEY_DOWN){
		mov_z--;
		glutPostRedisplay();
	}

}
void keyPress(char key, int x, int y){
	if (key == 'f')
		toggleLightOne();
	else if (key == 's')
		toggleLightTwo();

	glutPostRedisplay();
}
GLuint texture;
void load(){
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height;
	unsigned char* image;
	lodepng_decode32_file(&image, &width, &height, "WoodFine0001_1_thumblarge.png");

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, image);
	glEnable(GL_TEXTURE_2D);

}



void display(void){
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60, w / h, 0.1, 100);




	gluLookAt
		(
		mov_x, mov_y, mov_z,
		0, 0, 0,
		0, 0, 1
		);

	load();
	drawLegAt(1, 1, 0);


	drawLegAt(-1, 1, 0);

	drawLegAt(1, -1, 0);

	drawLegAt(-1, -1, 0);


	//drawLegAt(0, 0, 0.75);
	drawTableCounterAt(0, 0, 0.75);

	drawCupAt(1.2, 0, 1.01);
	

	drawTeapotAt(0, 0, 1.25);
	
	GLfloat defaultDiffuse[4] = { 0.8, 0.8, 0.8, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, defaultDiffuse); //Default

	glutSwapBuffers();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Graphics Assignment 2");
	glutDisplayFunc(display);
	glutSpecialFunc(buttonPressed);
	glutKeyboardFunc(keyPress);

	createLights();


	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	toggleLightOne();

	glutMainLoop();
	return 0;
}