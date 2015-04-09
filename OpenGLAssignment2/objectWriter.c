#include "objectWriter.h"
#include "GL\glut.h"


/* Push these two definitoins to somewhere else */
double tableLegs[8][3] = {
	{ -0.25, 0.25, -0.75 },
	{ -0.25, 0.25, 0.75 },
	{ 0.25, 0.25, 0.75 },
	{ 0.25, 0.25, -0.75 },
	{ -0.25, -0.25, -0.75 },
	{ -0.25, -0.25, 0.75 },
	{ 0.25, -0.25, 0.75 },
	{ 0.25, -0.25, -0.75 }
};


double tableSurface[8][3] = {
	{ -2, 2, -0.25 },
	{ -2, 2, 0.25 },
	{ 2, 2, 0.25 },
	{ 2, 2, -0.25 },
	{ -2, -2, -0.25 },
	{ -2, -2, 0.25 },
	{ 2, -2, 0.25 },
	{ 2, -2, -0.25 }
};

void drawLegAt(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x, y, z);
	drawTableLeg();
	glPopMatrix();
}

void drawTableCounterAt(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x, y, z);
	drawTableSurface();
	glPopMatrix();
}

void drawTeapotAt(float x, float y, float z){
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);

	GLfloat color[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f }; //Gold
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25);

	glTranslatef(x, y, z);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(0.5);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawCupAt(float x, float y, float z){
	glPushMatrix();

	GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glTranslatef(x, y, z);
	GLUquadric* quad = gluNewQuadric();
	gluQuadricNormals(quad, GL_SMOOTH);
	gluCylinder(quad, 0.2, 0.2, 0.4, 10, 10);
	/* Render the base of the cup */
	glBegin(GL_POLYGON);
	{
		for (double i = 0; i < 2 * PI; i += PI / 8)
			glVertex3f(cos(i) * 0.2, sin(i) * 0.2, 0.0);
	}
	glEnd();

	glPopMatrix();
}

vector normaliseSurface(double a[3], double b[3], double c[3], double d[3]){
	double V1[3] = { a[0] - b[0], a[1] - b[1], a[2] - b[2] };
	double V2[3] = { b[0] - d[0], b[1] - d[1], b[2] - d[2] };
	vector normal;
	normal.x = V1[1] * V2[2] - V1[2] * V2[1];
	normal.y = V1[0] * V2[2] - V1[2] * V2[0];
	normal.z = V1[0] * V2[1] - V1[1] * V2[0];

	return normal;
}

void drawLegQuad(int a, int b, int c, int d){
	glBegin(GL_QUADS);
	{
		vector normal = normaliseSurface(tableLegs[a], tableLegs[b], tableLegs[c], tableLegs[d]);
		glNormal3d(normal.x, normal.y, normal.z);
		glTexCoord2f(0.0f, 0.0f); glVertex3dv(tableLegs[a]);
		glTexCoord2f(1.0f, 0.0f); glVertex3dv(tableLegs[b]);
		glTexCoord2f(1.0f, 1.0f); glVertex3dv(tableLegs[c]);
		glTexCoord2f(0.0f, 1.0f); glVertex3dv(tableLegs[d]);
	}
	glEnd();
}
void drawTableQuad(int a, int b, int c, int d){

	glBegin(GL_QUADS);
	{
		vector normal = normaliseSurface(tableSurface[a], tableSurface[b], tableSurface[c], tableSurface[d]);
		glNormal3d(normal.x, normal.y, normal.z);
		glTexCoord2f(0.0f, 0.0f); glVertex3dv(tableSurface[a]);
		glTexCoord2f(1.0f, 0.0f); glVertex3dv(tableSurface[b]);
		glTexCoord2f(1.0f, 1.0f); glVertex3dv(tableSurface[c]);
		glTexCoord2f(0.0f, 1.0f); glVertex3dv(tableSurface[d]);
	}
	glEnd();
}

void drawTableLeg(){
	drawLegQuad(0, 1, 2, 3);
	drawLegQuad(1, 5, 6, 2);
	drawLegQuad(4, 5, 6, 7);
	drawLegQuad(0, 4, 7, 3);
	drawLegQuad(0, 1, 5, 4);
	drawLegQuad(3, 2, 6, 7);
}

void drawTableSurface(){
	drawTableQuad(0, 1, 2, 3);
	drawTableQuad(1, 5, 6, 2);
	drawTableQuad(4, 5, 6, 7);
	drawTableQuad(0, 4, 7, 3);
	drawTableQuad(0, 1, 5, 4);
	drawTableQuad(3, 2, 6, 7);
}

void drawTeapot(){

}