#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include "func.h"

void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void display();
void reshape();
void init();


ball_struct ball[NUMBER_BALL] = {{330, 400, 100, 0, 0, 0, 30, 0, 0, 0, 0},
                                 {100, 200, -150, 60, 0, 0, 20, 0, 0, 0, 0}};

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
    circle(ball[0].x_cd, ball[0].y_cd, ball[0].size, ball[0].rote + 20.0);
    circle(ball[1].x_cd, ball[1].y_cd, ball[1].size, ball[1].rote + 20.0);
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
}

void timer()
{
    for(int i = 0; i < DISP_BALL; i++)
        rebound_timer(&ball[i]);
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

