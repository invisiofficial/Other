#define _USE_MATH_DEFINES
#include "stb_image.h"
#include <cmath>
#include <GL/glut.h>

#define R 1
#define r 0.5
#define k 0.25

// Переменные для управления материалом
float red = 0.0;
float green = 0.0;
float blue = 0.0;

// Переменные для управления светом
GLfloat posX = 4.0, posY = 0.0, posZ = 4.0;

// Переменные для управления камерой
GLfloat angleX = 0.0, angleY = 0.0;

// Переменные для хранения информации об изображении
unsigned char* data;
int width, height, channels;
static GLuint texName;

// Функция рисования объекта
void drawSpiral(int horizDivisions, int vertDivisions)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);

    // Отрисовка поверхности
    for (int i = 0; i < horizDivisions; ++i)
    {
        double phi1 = (2 * M_PI * i) / horizDivisions;
        double phi2 = (2 * M_PI * (i + 1)) / horizDivisions;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= vertDivisions; ++j)
        {
            double theta = (6 * M_PI * j) / vertDivisions;

            double x1 = (R + r * cos(phi1)) * sin(theta);
            double y1 = (R + r * cos(phi1)) * cos(theta);
            double z1 = r * sin(phi1) + k * theta;

            double x2 = (R + r * cos(phi2)) * sin(theta);
            double y2 = (R + r * cos(phi2)) * cos(theta);
            double z2 = r * sin(phi2) + k * theta;

            double s1 = (double)i / horizDivisions;
            double t1 = (double)j / vertDivisions;

            double s2 = (double)(i + 1) / horizDivisions;
            double t2 = (double)j / vertDivisions;

            glTexCoord2f(s1, t1);
            glVertex3f(x1, y1, z1);

            glTexCoord2f(s2, t2);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

// Функция обработки клавиатуры
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

    case 'i':
        posX += 2.0f;
        break;
    case 'k':
        posX -= 2.0f;
        break;
    case 'l':
        posY += 2.0f;
        break;
    case 'j':
        posY -= 2.0f;
        break;

    case '1':
        red += 0.1;
        break;
    case '2':
        red -= 0.1;
        break;
    case '3':
        green += 0.1;
        break;
    case '4':
        green -= 0.1;
        break;
    case '5':
        blue += 0.1;
        break;
    case '6':
        blue -= 0.1;
        break;
        
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

// Функция отрисовки
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat light[] = { posX, posY, posZ, 1.0f };
    //GLfloat direction[] = { -posX, -posY, -posZ, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light);
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);

    float specular[] = { red, green, blue };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.25);

    gluLookAt(4.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);

    drawSpiral(20, 30);

	glutSwapBuffers();
    glFlush();
}

// Функция инициализации проекта
void init(void)
{
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, 2.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
}

// Функция изменения размера окна
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

// Функция загрузки изображения
void load()
{
    data = stbi_load("image.png", &width, &height, &channels, 3);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
    load();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMainLoop();
}
