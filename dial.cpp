#include <GL/glut.h>
#include <math.h>

static int windowWidth = 800;
static int windowHeight = 800;

static GLfloat x;
static GLfloat y;
static GLfloat z;
static GLfloat radius;
static GLint numberOfSides;
static GLfloat pos = 0.0;

void
DisplayNeedle()
{
	GLfloat twicePi = 2.0f * M_PI;

	glColor3f(0, 0.5, 0.5);
	glLineWidth(64);
	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(radius * 0.92 * cos(pos * twicePi),
		   radius * 0.92 * sin(pos * twicePi),
		   0.0);
	glEnd();

	glFlush();
}

void
DisplayDial()
{
	int numberOfVertices = numberOfSides + 2;
	GLfloat twicePi = 2.0f * M_PI;
	GLfloat circleVerticesX[numberOfVertices];
	GLfloat circleVerticesY[numberOfVertices];
	GLfloat circleVerticesZ[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for ( int i = 1; i < numberOfVertices; i++ ) {
		circleVerticesX[i] =
			x + (radius * cos(i *  twicePi / numberOfSides));
		circleVerticesY[i] =
			y + (radius * sin(i * twicePi / numberOfSides));
		circleVerticesZ[i] = z;
	}
	GLfloat allCircleVertices[( numberOfVertices ) * 3];

	for ( int i = 0; i < numberOfVertices; i++ ) {
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
		allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.8, 0.8, 0.8);

	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
	glDrawArrays( GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState( GL_VERTEX_ARRAY );

	for ( int i = 1; i < numberOfVertices; i++ ) {
		circleVerticesX[i] =
			x + (radius * 0.92 * cos(i *  twicePi / numberOfSides));
		circleVerticesY[i] =
			y + (radius * 0.92 * sin(i * twicePi / numberOfSides));
		circleVerticesZ[i] = z;
	}
	for ( int i = 0; i < numberOfVertices; i++ ) {
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
		allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
	}
	glColor3f(0.95, 0.95, 0.95);

	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
	glDrawArrays( GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState( GL_VERTEX_ARRAY );
}

void
DisplayGauge()
{
	DisplayDial();
	DisplayNeedle();
	glFlush();
}

void
TimerEvent(int te)
{
	/* Update needle position */
	pos += 0.02;
	if (pos > 1.0)
		pos = 0.0;

	glutPostRedisplay();
	glutTimerFunc(20, TimerEvent, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dial");

	x = 0.0;
	y = 0.0;
	z = 0.0;
	radius = 0.75;
	numberOfSides = 256;
	glutDisplayFunc(DisplayGauge);

	glutTimerFunc(20, TimerEvent, 1);

	glutMainLoop();
	return 0;
}
