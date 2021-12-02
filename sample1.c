#include <GL/glut.h>
#include <math.h>

#define PI 3.14

static GLfloat ang = 0.0;

void display();
void polygon(GLfloat, GLfloat, int, GLfloat);

void display(void)
{  
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(10.0, 10.0);

    glEnd();
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    /*glBegin(GL_LINE_LOOP);
    glVertex2d(-0.9, -0.9);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(-0.9, 0.9);
    glEnd();*/
    //polygon(0, 0, 36, 0.5);
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}


void polygon(GLfloat x, GLfloat y, int n, GLfloat r)
{
    GLfloat xo, yo, xt, yt, rad;
    int i;
    float deg, offs = 90.0;
/*
    glBegin(GL_TRIANGLE_FAN);
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
    xt = 0.5 * tan(15);
    yt = (-1) * 0.5 * tan(15);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.5, xt);
    glVertex2f(0.5, yt);
    glEnd();
    */
    glBegin(GL_TRIANGLE_FAN);
    //glColor3f(0.0, 0.0, 1.0);
    for(i = 0; i < n; i++)
    {
        if(i > 30 && i < 36)
        {
            glColor3f(0.0, 0.0, 1.0);
        }
        else glColor3f(0.0, 1.0, 1.0);

        deg = (360/n) * i + offs;
        rad = PI/180 * deg;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        deg = (360/n) * (i+1) + offs;
        rad = PI/180 * deg;
        xt = x + r * cos(rad);
        yt = y + r * sin(rad);
        glVertex2f(x, y);
        glVertex2f(xo, yo);
        glVertex2f(xt, yt);
    }
    glEnd();

}


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);   //背景色 (red, green, blue, 透明度)
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);  //OpenGLの初期化
    glutInitDisplayMode(GLUT_RGBA); //Window Color Model (Default) 
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);   //ウィンドウ内に描写
    init();
    glutMainLoop(); //イベント待ち
    return 0;
}
