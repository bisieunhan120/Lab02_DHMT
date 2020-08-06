#include <math.h>
#include <iostream>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
void initGlut(int argc, char** argv);
void displayFunc(void);
void idleFunc(void);
void reshapeFunc(int width, int height);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
//OpenGL chuc nang khac
void countFrames(void);
void renderBitmapString(float x, float y, float z, void* font, char* string);
bool bUsePredefinedCamera = true;
bool bFullsreen = false;
int nWindowID;
//camera thuoc tinh
float viewerPosition[3] = { 0.0 , 0.0 , -50.0 };
float viewerDirection[3] = { 0.0 , 0.0 , 0.0 };
float viewerUp[3] = { 0.0 , 1.0 , 0.0 };
//gia tri xoay cho dieu huong
float navigationRotation[3] = { 0.0 , 0.0 , 0.0 };
//Thong so cho bo khung
char pixelstring[30];
int cframe = 0;
int time = 0;
int timebase = 0;
//Vi tri chuot khi nhan
int mousePressedX = 0, mousePressedY = 0;
float lastXoffset = 0.0, lastYoffset = 0.0, lastZoffset = 0.0;
//Nut trang thai
int leftMouseButtonActive = 0, middleMouseButtonActive = 0, rightMouseButtonActive = 0;
//Nut sua doi
int shiftActive = 0, altActive = 0, ctrlActive = 0;
bool init = false;
void displayFunc(void)
{
	static float alpha = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// xoa buffer



	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.33, 1.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightpos[4] = { 5.0, 15.0, 10.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glTranslatef(viewerPosition[0], viewerPosition[1], viewerPosition[2]);
	//glRotatef(navigationRotation[0], 1.0f, 0.0f, 0.0f);
	//glRotatef(navigationRotation[1], 0.0f, 1.0f, 0.0f);
	//Them dieu huong xoay
	glRotatef(alpha, 1.0f, 1.0f, 1.0f);
	glRotatef(alpha, 0.0f, 1.0f, 0.0f);
	alpha += 0.2;//chinh toc do xoay

	glutSolidTeapot(10.0);
	countFrames();
	glutSwapBuffers();
}



void initGlut(int argc, char** argv)
{
	//Khoi tao cua so glut
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	nWindowID - glutCreateWindow("simpleGLUT");
	//Dang ky lai
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMotionFunc);
	glutIdleFunc(idleFunc);
}


void idleFunc(void) {
	glutPostRedisplay();
}




void reshapeFunc(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, 1.33, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

//Chuot goi lai
void mouseFunc(int button, int state, int x, int y) {
	switch (glutGetModifiers()) {
	case GLUT_ACTIVE_SHIFT:
		shiftActive = 1;
		break;
	case GLUT_ACTIVE_ALT:
		altActive = 1;
		break;
	case GLUT_ACTIVE_CTRL:
		ctrlActive = 1;
		break;
	default:
		shiftActive = 0;
		altActive = 0;
		ctrlActive = 0;
		break;
	}
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {
			leftMouseButtonActive += 1;
		}
		else
			leftMouseButtonActive -= 1;
	else if (button == GLUT_MIDDLE_BUTTON)
		if (state == GLUT_DOWN) {
			middleMouseButtonActive += 1;
			lastXoffset = 0.0;
			lastYoffset = 0.0;
		}
		else
			middleMouseButtonActive -= 1;
	else if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {
			rightMouseButtonActive += 1;
			lastZoffset = 0.0;
		}
		else
			rightMouseButtonActive -= 1;

	mousePressedX = x;
	mousePressedY = y;
}


void mouseMotionFunc(int x, int y) {
	float xOffset = 0.0, yOffset = 0.0, zOffset = 0.0;
	if (leftMouseButtonActive) {
		navigationRotation[0] += ((mousePressedY - y) * 180.0f) / 200.0f;
		navigationRotation[1] += ((mousePressedX - x) * 180.0f) / 200.0f;
		mousePressedY = y;
		mousePressedX = x;
	}
	else if (middleMouseButtonActive) {
		xOffset = (mousePressedX + x);
		if (!lastXoffset == 0.0) {
			viewerPosition[0] -= (xOffset - lastXoffset) / 8.0;
			viewerDirection[0] -= (xOffset - lastXoffset) / 8.0;
		}
		lastXoffset = xOffset;
		yOffset = (mousePressedY + y);
		if (!lastYoffset == 0.0) {
			viewerPosition[1] += (yOffset - lastYoffset) / 8.0;
			viewerDirection[1] += (yOffset - lastYoffset) / 8.0;
		}
		lastYoffset = yOffset;
	}
	else if (rightMouseButtonActive)
	{
		zOffset = (mousePressedX + x);
		if (!lastZoffset == 0.0) {
			viewerPosition[2] -= (zOffset - lastZoffset) / 5.0;
			viewerDirection[2] -= (zOffset - lastZoffset) / 5.0;
		}
		lastZoffset = zOffset;
	}
}


void keyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
#ifdef WIN32
	case '\033':
		exit(0);
		break;
#endif
	case 'f':
		bFullsreen = !bFullsreen;
		if (bFullsreen)
			glutFullScreen();
		else
		{
			glutSetWindow(nWindowID);
			glutPositionWindow(100, 100);
			glutReshapeWindow(640, 480);
		}
		break;
	}
}


void specialFunc(int key, int x, int y) {
}


void countFrames(void) {
	time = glutGet(GLUT_ELAPSED_TIME);
	cframe++;
	if (time - timebase > 50) {
		printf(pixelstring, "fps: %4.2f", cframe * 1000.0 / (time - timebase));
		timebase = time;
		cframe = 0;
	}
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200);
	glMatrixMode(GL_MODELVIEW);
	renderBitmapString(5, 5, 0.0, GLUT_BITMAP_HELVETICA_10, pixelstring);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void renderBitmapString(float x, float y, float z, void* font, char* string)
{
	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


void main(int argc, char** argv) {
	printf("simpleGLUT\n\tGordon Wetzstein [gordon,wetzstein@medien.uni-weimar.de]\n\n");
	printf("keys:\n\tf\t- toggle fullscreen\n\tesc\t- exit\n\n");
	printf("mouse: \n\tleft		button\t-	rotation\n\tmiddle	button\t-panning\n\tright button\\t- zoom in and out\n");
	initGlut(argc, argv);
	glutMainLoop();
}