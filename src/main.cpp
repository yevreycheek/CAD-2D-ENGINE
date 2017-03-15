//#include <GL/glew.h>
#include<GL\freeglut.h>
#include <cmath>
#include <iostream>


double rotate_by_key = 0;

double rotate_x = 0.5;



void drawRect(int x , int y , int dx , int dy) {

	//рисуем линии 
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0); // цвет 
	glVertex2f(x, y); // начало линии 1
	glVertex2f(x, dy); // конец линии 1

	
	glVertex2f(x, dy); // начало линии 2
	glVertex2f(dx, dy); // конец линии 2

	
	glVertex2f(dx, dy); // начало линии 3
	glVertex2f(dx, y); // конец линии 3

	
	glVertex2f(dx, y); // начало линии 4
	glVertex2f(x, y); // конец линии 4
	glEnd();

}

void drawCircle(float x, float y, float r, int amountSegments) // рисуем окружность 
{
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + dx, y + dy);
	}

	glEnd();
}

void mouseWheel(int wheel, int direction, int x, int y)
{

	
	if (direction > 0)
	{
		std::cout <<" mouse ++ " << std::endl;// Zoom in
		rotate_x += .05;
		glutPostRedisplay();
	}
	else if (direction < 0)
	{
		// Zoom out
		std::cout << " mouse -- " << std::endl;
		rotate_x -= .05;
		glutPostRedisplay();
	}

	return;
}


////////////////////////////////////////////////



void keyPress(int key, int x, int y)
{

	if (key == 27)
		exit(0);
	if (key == GLUT_KEY_UP)
		rotate_x += .05;
	if (key == GLUT_KEY_DOWN)
		rotate_x -= .05;

	glutPostRedisplay();

}

void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}


//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

								 //Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
		(double)w / (double)h, //The width-to-height ratio
		1.0,                   //The near z clipping coordinate
		200.0);                //The far z clipping coordinate
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glScalef(rotate_x, rotate_x, 1.0f);
	//glScalef(1.0f,1.0f,rotate_x);
	glRotatef(rotate_by_key, -1.0f, 1.5f, -5.0f);

	


	glBegin(GL_TRIANGLES);

	glVertex3f(1.0f, 0.0f, -5.0f);
	glVertex3f(0.0f, 1.0f, -5.0f);
	glVertex3f(-1.0f, 0.0f, -5.0f);

	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(400, 400);

	glutCreateWindow("My triangle");

	initRendering();

	glutDisplayFunc(drawScene);

	glutSpecialFunc(keyPress);
	glutMouseWheelFunc(mouseWheel);

	glutReshapeFunc(handleResize);

	glutMainLoop();

	return(0);
}
