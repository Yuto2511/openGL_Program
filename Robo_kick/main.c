#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include "func.h"

void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void display();
void reshape();
void init();


ball_struct ball[NUMBER_BALL] = {{330, 400, 0, 0, 0, 0, 20, 0, 0, 0, 0},
                                 {220, 15, 0, 0, 0, 0, 30, 0, 0, 0, 0},
                                 {600, 400, 80, 0, 0, 0, 20, 0, 0, 0, 0},
                                 {400, 40, 40, 40, 0, 0, 40, 0, 0, 0, 0}};


leg_struct leg[2] = {{-30, 30, -30, -150, 30, -150, 30, 30, 0.01 ,0, 0},
                     {50, -100, 50, -150, 30, -150, 30, -100, 0.01, 0, 0}};


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
    // write polygon
    frame();
    for(int i = 0; i < DISP_BALL; i++) circle(ball[i].x_cd, ball[i].y_cd, ball[i].size, ball[i].rote + 20.0);
    kicking_leg(&leg[0]);
    kicking_leg(&leg[1]);

    glBegin(GL_POINTS);
    glColor3f(BK);
    glVertex2f(DIS_X, DIS_Y);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape()
{
    // specify the drawing area
    glViewport(0, 0, WIDTH, HIGH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 3D cahnge to 2D
    glOrtho(-10.0, WIDTH + 20, -10.0, HIGH + 20, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
    for(int i = 0; i < DISP_BALL; i++) ball_init(&ball[i]);
    for(int i = 0; i < 2; i++) leg_init(&leg[i]);
}

void timer()
{
    for(int i = 0; i < DISP_BALL; i++) rebound_timer(&ball[i]);
    if(DISP_BALL > 1)
    {
        for(int i = 0; i < DISP_BALL; i++)
        {
            for(int j = i; j < DISP_BALL; j++)
            {
                collision_timer(&ball[i], &ball[j]);
            }
        }
    }
    for(int i = 0; i < DISP_BALL; i++) robokick_timer(&leg[1], &leg[0], &ball[i]);
    kick_timer(&leg[0]);
    kick_timer(&leg[1]);
    glutPostRedisplay();
    glutTimerFunc(25, timer, 0);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    // specify the window size
    glutInitWindowSize(WIDTH + 20, HIGH + 20);
    // specify the screen display position
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(100, timer, 0);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
