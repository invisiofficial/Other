#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glut.h>

#define R 1
#define r 0.5
#define k 0.25

// ���������� ��� ���������� �������
GLfloat angleX = 0.0, angleY = 0.0;

// ������� ��������� ���������� �����������
void drawSpiral(int horizDivisions, int vertDivisions)
{
    // ��������� ���������� �����
    for (int i = 0; i <= horizDivisions; ++i)
    {
        double phi = (2 * M_PI * i) / horizDivisions;

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= vertDivisions; ++j)
        {
            double theta = (6 * M_PI * j) / vertDivisions;

            double x1 = (R + r * cos(phi)) * sin(theta);
            double y1 = (R + r * cos(phi)) * cos(theta);
            double z1 = r * sin(phi) + k * theta;

            double x2 = (R + r * cos(phi + 0.01)) * sin(theta + 0.01);
            double y2 = (R + r * cos(phi + 0.01)) * cos(theta + 0.01);
            double z2 = r * sin(phi + 0.01) + k * theta + 0.01;

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    // ��������� ���������� �����
    for (int i = 0; i <= vertDivisions; ++i)
    {
        double theta = (6 * M_PI * i) / vertDivisions;

        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= horizDivisions; ++j)
        {
            double phi = (2 * M_PI * j) / horizDivisions;

            double x1 = (R + r * cos(phi)) * sin(theta);
            double y1 = (R + r * cos(phi)) * cos(theta);
            double z1 = r * sin(phi) + k * theta;

            double x2 = (R + r * cos(phi + 0.01)) * sin(theta + 0.01);
            double y2 = (R + r * cos(phi + 0.01)) * cos(theta + 0.01);
            double z2 = r * sin(phi + 0.01) + k * theta + 0.01;

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
}

// ������� ��������� ������ ����������
void keyboard(unsigned char key, int x, int y)
{
    switch (key) 
    {
    case 'w':
        angleY += 5.0;
        break;
    case 's':
        angleY -= 5.0;
        break;
    case 'a':
        angleX += 5.0;
        break;
    case 'd':
        angleX -= 5.0;
        break;
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}


// ������� ���������
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION); // ������������� ��������
    glLoadIdentity();
    //gluPerspective(90, 1, 2, 12); // ������������� ��������
    //glMatrixMode(GL_MODELVIEW); // ������������� ��������

    gluLookAt(4.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    glColor3f(1.0, 1.0, 1.0);
    drawSpiral(20, 30);

	glutSwapBuffers();
}

// ������� ������������� �������
void init(void)
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_FLAT);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, 2.0, 12.0);
}

// ������� ��������� ������� ����
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / (GLfloat)w, 5.0 * (GLfloat)h / (GLfloat)w, 2.0, 12.0);
    else
        glOrtho(-5.0 * (GLfloat)w / (GLfloat)h, 5.0 * (GLfloat)w / (GLfloat)h, -5.0, 5.0, 2.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMainLoop();
}
