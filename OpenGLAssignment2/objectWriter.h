#ifndef OBJECT_WRITER_H
#define OBJECT_WRITER_H

#define PI 3.1415926535897932384626433832795

void drawTableLeg(void);
void drawTableSurface(void);
void drawTeapotAt(float, float, float);
void drawLegAt(float, float, float);
void drawTableCounterAt(float, float, float);
void drawCupAt(float, float, float);


typedef struct vector{
	float x;
	float y;
	float z;
}vector;

#endif