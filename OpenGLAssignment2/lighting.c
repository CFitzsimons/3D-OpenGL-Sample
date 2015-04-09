#include "lighting.h"
#include "GL\glut.h"


void createLights(){
	GLfloat lightpos[] = { 4, 4, 4, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	GLfloat lightIntensity[] = { 1, 1, 1, 1 };
	GLfloat secondPosition[] = { 1.5, 0, 1.5, 1.0f };
	GLfloat attenuation[] = { 1, 0, 0 };
	GLfloat direction[] = { -2, 0, -2 };

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightIntensity);

	glLightfv(GL_LIGHT1, GL_POSITION, secondPosition);

	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f);
}

void switchLightType(){

}
int light1 = 0;
int light2 = 0;
void toggleLightOne(){
	if (light1)
		glDisable(GL_LIGHT0);
	else
		glEnable(GL_LIGHT0);
	light1 ^= 1;
	printf("Current state of point light: %d\n", light1);
}

void toggleLightTwo(){
	if (light2)
		glDisable(GL_LIGHT1);
	else
		glEnable(GL_LIGHT1);
	light2 ^= 1;
	printf("Current state of spot light: %d\n", light2);
}