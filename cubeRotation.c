#include <stdlib.h>
#include <GL/glut.h>

GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },
	{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },{ -1.0,-1.0,1.0 },
	{ 1.0,-1.0,1.0 },{ 1.0,1.0,1.0 },{ -1.0,1.0,1.0 } };

GLfloat colors[][3] = { { 0.0,0.0,0.0 },{ 1.0,0.0,0.0 },
	{ 1.0,1.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 },
	{ 1.0,0.0,1.0 },{ 1.0,1.0,1.0 },{ 0.0,1.0,1.0 } };

static GLint myview = 3;

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);

		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);

		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);

		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube()
{
	polygon(0, 3, 2, 1);

	// write the point number for other sides, shoule be CCW order of points for a polygon

	polygon(4, 5, 6, 7);
	polygon(1, 2, 6, 5);
	polygon(2, 3, 7, 6);
	polygon(0, 1, 5, 4);
	polygon(0, 4, 7, 3);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	switch (myview)
	{
		case 0:	gluLookAt(0.0, 0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  // front view
			break;

		case 1: gluLookAt(0.0, 6.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0); // top view
			break;

		case 2: gluLookAt(6.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // side view
			break;

		case 3: gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // perspective view
			break;
	}

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	colorcube();
	glutSwapBuffers();
}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

		xRot = (GLfloat)((const int)xRot % 360);
		yRot = (GLfloat)((const int)yRot % 360);

	// Refresh the Window
	glutPostRedisplay();
}


void ProcessMenu(int value)
{
	if (value < 4) myview = value;

	xRot = 0.0f;
	yRot = 0.0f;

	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glFrustum (left, right, bottom, top, near distance, far distance)
	if (w <= h)
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0* (GLfloat)h / (GLfloat)w, 2.0, 20.0);
	else
		glFrustum(-2.0, 2.0, -2.0 * (GLfloat)w / (GLfloat)h, 2.0* (GLfloat)w / (GLfloat)h, 2.0, 20.0);

	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube viewpoint");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutSpecialFunc(SpecialKeys);

	// Create the Menu
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("front view", 0);
	glutAddMenuEntry("top view", 1);
	glutAddMenuEntry("side view", 2);
	glutAddMenuEntry("perspective view", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
