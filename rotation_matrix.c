#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.141592

void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void display();
void reshape();
void init();
void coodinate();
void polygon();
void circle(GLfloat x, GLfloat y, GLfloat r);
void timer_1();
void timer_2();

GLfloat dis_x = -50, dis_y = 170;

typedef struct
{
    GLfloat x;
    GLfloat y;
}
polygon_coodinate;

polygon_coodinate poly[4] = {{30, -170},
                                {30, 30},
                                {-30, 30},
                                {-30, -170}};

polygon_coodinate elli = {200, 0};

void polygon()
{
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(poly[0].x + dis_x, poly[0].y + dis_y);
    glVertex2f(poly[1].x + dis_x, poly[1].y + dis_y);
    glVertex2f(poly[2].x + dis_x, poly[2].y + dis_y);
    glVertex2f(poly[3].x + dis_x, poly[3].y + dis_y);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(poly[0].x + dis_x, poly[0].y + dis_y);
    glVertex2f(poly[2].x + dis_x, poly[2].y + dis_y);
    glVertex2f(poly[1].x + dis_x, poly[1].y + dis_y);
    glVertex2f(poly[3].x + dis_x, poly[3].y + dis_y);
    glEnd();
}

void circle(GLfloat x, GLfloat y, GLfloat r)
{
    GLfloat rad, xo, yo;
    int i;
    x += dis_x;
    y += dis_x;
    for(i = 0; i < 36; i ++)
    {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(x, y);
        rad = PI/180 * i * 10;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
        rad = PI/180 * (i+1) * 10;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
    }
    glEnd();
}

void timer_1()
{
    GLfloat omega = 0.5, rad, a, b, save;
    rad = PI/180 * omega;
    save = poly[0].x * cos(rad) - poly[0].y * sin(rad);
    poly[0].y = poly[0].x * sin(rad) + poly[0].y * cos(rad);
    poly[0].x = save;

    save = poly[1].x * cos(rad) - poly[1].y * sin(rad);
    poly[1].y = poly[1].x * sin(rad) + poly[1].y * cos(rad);
    poly[1].x = save;

    save = poly[2].x * cos(rad) - poly[2].y * sin(rad);
    poly[2].y = poly[2].x * sin(rad) + poly[2].y * cos(rad);
    poly[2].x = save;

    save = poly[3].x * cos(rad) - poly[3].y * sin(rad);
    poly[3].y = poly[3].x * sin(rad) + poly[3].y * cos(rad);
    poly[3].x = save;
    glutPostRedisplay();
    glutTimerFunc(50, timer_1, 0);
}

void coodinate()
{
    int i;
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    for(i = 50; i < 250; i+=50)
    {
        glVertex2f(i, 250);
        glVertex2f(i, -250);
        glVertex2f(-i, 250);
        glVertex2f(-i, -250);
        glVertex2f(250, i);
        glVertex2f(-250, i);
        glVertex2f(250, -i);
        glVertex2f(-250, -i);
    }
    glEnd();
}

void timer_2()
{   
    GLfloat rad, deg, rate, save;
    rate = 1;
    deg = 0.5;
    rad = PI/180 * deg;
    save = elli.x * cos(rad) - elli.y * sin(rad);
    elli.y = elli.x * sin(rad) + elli.y * cos(rad);
    elli.x = save;
    glutPostRedisplay();
    glutTimerFunc(50, timer_2, 0);
}


void keyboard(unsigned char key, int x, int y)
{
    // end with ESC
    if(key == '\x1b') exit(0);
}

void mouse(int button, int state, int x, int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN);
                // write an event    
                glutTimerFunc(100, timer_1, 0);
                glutTimerFunc(100, timer_2, 0);
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN);
                // write an event    
            break;
        default:
            break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 250);
    glVertex2f(0.0, -250);
    glVertex2f(-250, 0.0);
    glVertex2f(250, 0.0);
    glEnd();
    coodinate();
    polygon();
    circle(elli.x, elli.y*0.8, 10);
    glPopMatrix();
    glutSwapBuffers();
}

void reshape()
{
    // specify the drawing area
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 3D cahnge to 2D
    glOrtho(-250, 250, -250, 250, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    // specify the window size
    glutInitWindowSize(500.0, 500.0);
    // specify the screen display position
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
