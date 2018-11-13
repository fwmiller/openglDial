#include <GL/glut.h>
#include <math.h>
 
void DisplayDial(void)
{
	float cx = 0.0;
	float cy = 0.0;
	float r = 0.5;
	int num_segments = 32;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++) {
		// Get the current angle
		float theta =
			2.0f * 3.1415926f * float(ii) / float(num_segments);

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex
	}
	glEnd();
	glFlush();
}

void
DisplayTriDial(
	GLfloat x,
	GLfloat y,
	GLfloat z,
	GLfloat radius,
	GLint numberOfSides)
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
		circleVerticesX[i] = x + ( radius * cos( i *  twicePi / numberOfSides ) );
		circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );
		circleVerticesZ[i] = z;
	}
    
	GLfloat allCircleVertices[( numberOfVertices ) * 3];
    
	for ( int i = 0; i < numberOfVertices; i++ ) {
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[( i * 3 ) + 1] = circleVerticesY[i];
		allCircleVertices[( i * 3 ) + 2] = circleVerticesZ[i];
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, allCircleVertices );
	glDrawArrays( GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState( GL_VERTEX_ARRAY );
	glFlush();
}
 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dial");
	//glutDisplayFunc(DisplayDial);
	glutDisplayFunc(DisplayTriDial);
	glutMainLoop();
	return 0;
}
