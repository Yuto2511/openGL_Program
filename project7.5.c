#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.14

void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void display();
void reshape();
void init();
void polygon();

typedef struct
{
    GLfloat x;
    GLfloat y;
}
polygon_coodinate;

polygon_coodinate poly[4] = {{100, -100},
                                {100, 100},
                                {-100, 100},
                                {-100, -100}};

void polygon()
{
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(poly[0].x, poly[0].y);
    glVertex2f(poly[1].x, poly[1].y);
    glVertex2f(poly[2].x, poly[2].y);
    glVertex2f(poly[3].x, poly[3].y);
    glEnd();
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
    //glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.0, 250);
    glVertex2f(0.0, -250);
    glVertex2f(-250, 0.0);
    glVertex2f(250, 0.0);
    glEnd();
    polygon();
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

