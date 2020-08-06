#include "Dependencies\glew\glew.h" 
#include "Dependencies\freeglut\freeglut.h" 
void	 DisplayFunc(void)
{
	static float alpha = 0;
	//Xoa buffer va xoa Matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//Mot buoc lui sau do quay khoi
	glTranslatef(0, 0, -10);
	glRotatef(30, 1, 0, 0);
	glRotatef(alpha, 0, 1, 0);
	alpha += 0.2;
	//Ve hinh tu giac
	glBegin(GL_QUADS);
	//Cu 4 cuoc goi den glvertext thi mot quad duoc rut ra
	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
	glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);

	glColor3f(1, 0, 0); glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, -1);

	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0); glVertex3f(1, -1, -1);

	glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, -1);

	glColor3f(0, 0, 0); glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0); glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0); glVertex3f(1, 1, -1);
	glColor3f(1, 0, 0); glVertex3f(1, -1, -1);

	glColor3f(0, 0, 1); glVertex3f(-1, -1, 1);
	glColor3f(0, 1, 1); glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1); glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1); glVertex3f(1, -1, 1);
	//Khong con quad nua
	glEnd();
	//Xoay them mot chut
	alpha = alpha + 0.1;
	glFlush();
	glutSwapBuffers();

	glutPostRedisplay();
}

void ReshapeFunc(int width, int height)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(20, width / (float)height, 5, 15);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void KeyboardFunc(unsigned char key, int x, int y)
{
	int foo;

	foo = x + y;
	if ('q' == key || 'Q' == key || 27 == key)
		exit(0);
}
int
main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutCreateWindow("Spinning cube");

	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(&DisplayFunc);
	glutReshapeFunc(&ReshapeFunc);
	glutKeyboardFunc(&KeyboardFunc);
	glutMainLoop();
	return 0;
}