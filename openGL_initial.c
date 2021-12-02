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
            break:
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN);
                // write an event    
            break:
        default:
            break:
    }
}

void display()
{
}

void reshape()
{
    // specify the drawing area
    glViewport(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 3D cahnge to 2D
    glOrtho(0, 0, 0, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeMode(GL_FLAT);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    // specify the window size
    glutInitWindowSize(0.0, 0.0);
    // specify the screen display position
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutMainLop();

    return 0;
}

