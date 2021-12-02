#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.14

void reshape(int width, int high);
void display();
void timer_1();
void timer_2();
void polygon(GLfloat x, GLfloat y, int n, GLfloat r);
GLfloat posx(GLfloat x);
GLfloat posy(GLfloat y);

GLfloat x_0 = 50.0;
GLfloat x_1 = 0.0;
GLfloat vx_0 = 200.0;
GLfloat vx_1 = 0.0;

GLfloat y_0 = 120.0;
GLfloat y_1 = 120.0;

GLfloat time_x = 0.0;
GLfloat time_x2 = 0.0;
float degree = 45;
int flag = 0;
int unko = 0;
static GLfloat e = -1.0;

static GLfloat cubes = 50.0;

static GLfloat window_width = 640;
static GLfloat window_high = 240;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    polygon(posx(x_1), posy(y_1), 35, cubes);
    glPopMatrix();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(posx(-cubes - 5), posy(window_high / 2 + cubes + 10));
    glVertex2f(posx(-cubes - 5), posy(window_high / 2 - cubes - 10));
    glVertex2f(posx(window_width + 5),posy(window_high / 2 - cubes - 10));
    glVertex2f(posx(window_width + 5), posy(window_high / 2 + cubes + 10));
    glEnd();

    glutSwapBuffers();
    glFlush();
}

void Window_Init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
}

void reshape(int width, int high)
{
    glViewport(0, 0, width, high);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(window_width/2+cubes+10), window_width/2+10, -(window_high/2+10), window_high/2+10, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void polygon(GLfloat x, GLfloat y, int n, GLfloat r)
{
    GLfloat xo, yo, xt, yt, rad;
    int i;
    float deg, offs = 90.0;
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    for(i = 0; i < n; i++)
    {
        deg = (360.0/n) * i + offs;
        rad = PI/180 * deg;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2d(xo, yo);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.0);
    xt = cubes * tan(degree);
    yt = (-1) * cubes * tan(degree);
    if(flag == 0){
        glVertex2f(posx(x_1), posy(y_1));
        glVertex2f(posx(x_1 + cubes), posy(xt + window_high / 2));
        glVertex2f(posx(x_1 + cubes), posy(yt + window_high / 2));
    }
    else if(flag == 1){
        glVertex2f(posx(x_1), posy(y_1));
        glVertex2f(posx(x_1 - cubes), posy(xt + window_high / 2));
        glVertex2f(posx(x_1 - cubes), posy(yt + window_high / 2));
    }
    glEnd();
}

void timer_1()
{
    GLfloat time_x2;
    int i = 0;
    time_x = time_x + 0.025;
    time_x2 = 0.5 * time_x * time_x;
    vx_1 = vx_0;
    x_1 = x_0 + vx_0 * time_x;
    
    if( x_1+cubes > window_width )
    {
        time_x = 0.0;
        x_0 = 640 - cubes;
        vx_0 = vx_1 * e;
        vx_1 = 0.0;
        flag = 1;
    }
    if( x_1 <= 0.0 )
    {
        time_x = 0.0;
        x_0 = 0.0;
        vx_0 = vx_1 * e;
        vx_1 = 0.0;
        flag = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(25, timer_1, 0);
}

void timer_2()
{
    if(unko == 4) unko = 0;
    if(unko == 0) degree = 45;
    if(unko == 1) degree = 15;
    if(unko == 2) degree = 0;
    if(unko == 3) degree = 15;
    unko += 1;
    //printf("%f,  %d\n", degree, unko);
    glutPostRedisplay();
    glutTimerFunc(150, timer_2, 0);
}


GLfloat posx(GLfloat x)
{
    x = x - (window_width/2);
    return x;
}

GLfloat posy(GLfloat y)
{
    y = y - (window_high/2);
    return y;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(window_width, window_high);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    Window_Init();
    glutTimerFunc(100, timer_1, 0);
    glutTimerFunc(100, timer_2, 0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
