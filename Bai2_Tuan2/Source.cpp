#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

const int screenWidth = 640;//chieu dai cua cua so
const int screenHeight = 480;//chieu cao cua cua so

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);//mau nen
	glShadeModel(GL_SMOOTH);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); //xoa mau buffer
	glColor3f(1.0, 1.0, 1.0);//mau trang
	glutSolidTeapot(0.5);
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(1.0, -1.0, -1.0, 1.0, -1.0, 1.0);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);//khoi tao glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);//Khoi tao  che do Single buffer va he mau RGB
	glutInitWindowSize(screenWidth, screenHeight);// Mac dinh
	glutInitWindowPosition(100, 100);// Mac dinh
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}