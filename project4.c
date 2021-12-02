#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.14

/*----------------------------------------------------------*/

void reshape(int width, int high);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void simu();
void display();
void display_02();
void timer();
void polygon(GLfloat x, GLfloat y, int n, GLfloat r);
GLfloat posx(GLfloat x);
GLfloat posy(GLfloat y);

/*---------------------------------------------------------*/

GLfloat x_0 = 640.0;
GLfloat x_1 = 0.0;
GLfloat vx_0 = -50.0;
GLfloat vx_1 = 0.0;
GLfloat ax_0 = 0.0;

GLfloat y_0 = 480.0;
GLfloat y_1 = 0.0;
GLfloat vy_0 = 100.0;
GLfloat vy_1 = 0.0;
GLfloat ay_0 = 0.0;
static GLfloat grav = -10;

GLfloat time_x = 0.0;
GLfloat time_x2 = 0.0;
GLfloat time_y = 0.0;
GLfloat time_y2 = 0.0;
static GLfloat e = -1.2;
static GLfloat u = 0.98;

static GLfloat cubes = 15.0;

static GLfloat window_width = 640;
static GLfloat window_high = 480;

/*-------------------------------------------------------*/

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    polygon(posx(x_1), posy(y_1), 35, cubes);
    //glRectf(posx(x_1), posy(y_1), posx(x_1+cubes), posy(y_1-cubes));
    glPopMatrix();
    glutSwapBuffers();
    //glEnd();
    glFlush();
}

void display_02()
{
    glClear(GL_COLOR_BUFFER_BIT);
    polygon(posx(320), posy(240), 35, cubes);
    glFlush();
}

/*-----------------------------------------------------*/

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
    glOrtho(-(window_width/2), window_width/2, -(window_high/2), window_high/2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*----------------------------------------------------*/

void keyboard(unsigned char key, int x, int y)
{
    if(key == '\x1b') exit(0);
}

void mouse(int button, int state, int x, int y)
{
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
            glutTimerFunc(100, timer, 0);
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN)
            glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}

/*--------------------------------------------------*/

void polygon(GLfloat x, GLfloat y, int n, GLfloat r)
{
    GLfloat xx, yy, rad;
    int i;
    float deg, offs = 90.0;
    glBegin(GL_LINE_LOOP);
    //glColor3f(1.0, 1.0, 0.0);
    for(i = 0; i < n; i++)
    {
        deg = (360.0/n) * i + offs;
        rad = PI/180 * deg;
        xx = x + r * cos(rad);
        yy = y + r * sin(rad);
        glVertex2d(xx, yy);
    }
    glEnd();
    //printf("unko\n");
}

/*------------------------------------------------*/

void simu()
{

}


void timer()
{
    GLfloat time_y2;
    time_x = time_x + 0.025;
    time_y = time_y + 0.025;
    time_x2 = 0.5 * time_x * time_x;
    time_y2 = 0.5 * time_y * time_y;
    vx_1 = vx_0 + ax_0 * time_x;
    vy_1 = vy_0 + (ay_0 + grav) * time_y;
    x_1 = x_0 + (vx_0 * time_x) + (ax_0 * time_x2);
    y_1 = y_0 + (vy_0 * time_y) + ((ay_0 + grav) * time_y2);
    
    if( x_1+cubes > window_width )
    {
        time_x = 0.0;
        x_0 = 640 - cubes;
        vx_0 = vx_1 * e;
        vx_1 = 0.0;
        ax_0 *= e;
    }
    if( y_1-cubes < 0.0 )
    {
        time_y = 0.0;
        y_0 = 0.0 + cubes;
        vy_0 = vy_1 * e;
        vy_1 = 0.0;
        ay_0 *= e;
    }
    if( x_1 < 0.0 )
    {
        time_x = 0.0;
        x_0 = 0.0;
        vx_0 = vx_1 * e;
        vx_1 = 0.0;
        ax_0 *= e;
    }
    if( y_1 > window_high )
    {
        time_y = 0.0;
        y_0 = 480;
        vy_0 = vy_1 * e;
        vy_1 = 0.0;
        ay_0 *= e;
    }

    printf("x = %f,  y = %f\n", vx_1, vy_1);
    glutPostRedisplay();
    glutTimerFunc(25, timer, 0);
}

/*---------------------------------------------------*/

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

/*---------------------------------------------------*/

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(/*GLUT_DOUBLE |*/ GLUT_RGB);
    glutInitWindowSize(window_width, window_high);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    Window_Init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
