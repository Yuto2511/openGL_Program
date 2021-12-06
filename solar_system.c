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

void mercury();
void venus();
void earth();
void mars();
void jupiter();
void saturn();
void uranus();
void neptune();
void pluto();

void encke();
void halley();
void timer();

typedef struct
{
    GLfloat x;
    GLfloat y;
    GLfloat r;
    GLfloat t;
    GLfloat j_axis;
    GLfloat i_axis;
    GLfloat off;
}
star_elements;

star_elements star[11] = {{0.0, 0.0, 1, 4.2, 0.381, 0.378, 7.0},
                          {0.0, 0.0, 2, 1.62, 0.723, 0.723, 3.4},
                          {0.0, 0.0, 2, 1.0, 1.0, 1.0, 0.0},
                          {0.0, 0.0, 1, 0.53, 1.524, 1.517, 1.8},
                          {0.0, 0.0, 4, 0.08, 5.21, 5.20, 1.3},
                          {0.0, 0.0, 4, 0.4, 9.56, 9.55, 2.5},
                          {0.0, 0.0, 3, 0.12, 19.22, 19.2, 0.7},
                          {0.0, 0.0, 3, 0.006, 30.11, 30.11, 1.7},
                          {0.0, 0.0, 1, 0.004, 39.54, 38.3, 17.1},
                          {0.0, 0.0, 1, 0.1, 2.15, 1.14, 11.8},
                          {0.0, 0.0, 1, 0.1, 17.83, 4.54, 162.3}};

static GLfloat mag = 15;

GLfloat rad_save[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
GLfloat rate[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
GLfloat dist_x[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
GLfloat dist_y[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void xy_init()
{
    int number;
    GLfloat a, b, offs, save;
    for(number = 0; number < 11; number ++)
    {
        offs = PI/180 * star[number].off;
        a = star[number].j_axis * mag;
        b = star[number].i_axis * mag;
        dist_x[number] = sqrt(a * a - b * b) /* cos(offs)*/;
        dist_y[number] = 0/*sqrt(a * a - b * b) * sin(offs)*/;
        star[number].x = a /* cos(offs)*/;
        star[number].y = 0/*a * sin(offs)*/;
        rate[number] = b / a;
    }
}

void circle(GLfloat x, GLfloat y, GLfloat r, GLfloat red, GLfloat green, GLfloat blue)
{
    GLfloat xo, yo, rad;
    int i;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(red, green, blue);
    for(i = 0; i < 36; i ++)
    {
        glVertex2f(x, y);
        rad = PI/180 * (10 * i);
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
        rad = PI/180 * (10 * (i+1));
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
    }
    glEnd();
}       

void ellipse(GLfloat a, GLfloat b, GLfloat offs, int j)
{
    GLfloat f, fx, fy, xt, yt, rad;
    int i;
    float deg;
    offs = PI/180 * offs;
    f = sqrt(a * a - b * b);
    fx = f /* cos(offs)*/;
    fy = 0 /* sin(offs)*/;
    glBegin(GL_LINE_LOOP);
    glColor3f(0.66, 0.66, 0.66);
    for(i = 0; i < 72; i ++)
    {
        rad = PI/180 * (5 * i);
        xt = fx + a * cos(rad);
        yt = fy + b * sin(rad);
        /*if(offs != 0.0)
        {
            GLfloat save;
            save = xt * cos(offs) - yt * sin(offs);
            yt = xt * sin(offs) + yt * cos(offs);
            xt = save;
        }*/
        glVertex2f(xt, yt);
    }
    glEnd();
}

void mercury()
{
    ellipse(star[0].j_axis*mag, star[0].i_axis*mag, 7.0, 0);
    circle(star[0].x + dist_x[0], (star[0].y + dist_y[0]) * rate[0], star[0].r, 0.68, 0.87, 0.89);
}

void venus()
{
    ellipse(star[1].j_axis*mag, star[1].i_axis*mag, 3.4, 1);
    circle(star[1].x + dist_x[1], (star[1].y + dist_x[1]) * rate[1], star[1].r, 0.85, 0.64, 0.125);
}

void earth()
{
    ellipse(star[2].j_axis*mag, star[2].i_axis*mag, 0.0, 2);
    circle(star[2].x + dist_x[2], (star[2].y + dist_y[2]) * rate[2], star[2].r, 0.25, 0.41, 0.88);
}

void mars()
{
    ellipse(star[3].j_axis*mag, star[3].i_axis*mag, 1.8, 3);
    circle(star[3].x + dist_x[3], star[3].y * rate[3] + dist_y[3], star[3].r, 0.87, 0.72, 0.53);
}

void jupiter()
{
    ellipse(star[4].j_axis*mag, star[4].i_axis*mag, 1.3, 4);
    circle(star[4].x + dist_x[4], (star[4].y + dist_y[4]) * rate[4], star[4].r, 0.95, 0.86, 0.7);
}

void saturn()
{
    ellipse(star[5].j_axis*mag, star[5].i_axis*mag, 2.5, 5);
    circle(star[5].x + dist_x[5], (star[5].y + dist_y[5]) * rate[5], star[5].r, 0.79, 1.0, 0.4);
}

void uranus()
{
    ellipse(star[6].j_axis*mag, star[6].i_axis*mag, 0.7, 6);
    circle(star[6].x + dist_x[6], (star[6].y + dist_y[6]) * rate[6], star[6].r, 0.2, 1.0, 1.0);
}

void neptune()
{
    ellipse(star[7].j_axis*mag, star[7].i_axis*mag, 1.7, 7);
    circle(star[7].x + dist_x[7], (star[7].y + dist_y[7]) * rate[7], star[7].r, 0.2, 0.6, 1.0);
}

void pluto()
{
    ellipse(star[8].j_axis*mag, star[8].i_axis*mag, 17.1, 8);
    circle(star[8].x + dist_x[8], (star[8].y + dist_y[8]) * rate[8], star[8].r, 0.8, 0.8, 0.6);
}

void encke()
{
    ellipse(star[9].j_axis*mag, star[9].i_axis*mag, 11.8, 9);
    circle(star[9].x + dist_x[9], (star[9].y + dist_y[9]) * rate[9], star[9].r, 0.0, 0.75, 1.0);
}

void halley()
{
    ellipse(star[10].j_axis*mag, star[10].i_axis*mag, 162.3, 10);
    circle(star[10].x + dist_x[10], (star[10].y + dist_y[10]) * rate[10], star[10].r, 1.0, 2.0, 0.0);
}
void timer()
{
    int i;
    GLfloat rad, offs, save, f;
    for(i = 0; i < 11; i ++)
    {
        f = star[i].t * 50;
        offs = PI/180 * star[i].off;
        rad = PI/180 * star[i].t;
        save = star[i].x * cos(rad) - star[i].y * sin(rad);
        star[i].y = star[i].x * sin(rad) + star[i].y * cos(rad);
        star[i].x = save;

        //save = star[i].x * cos(offs) - star[i].y * sin(offs);
        //star[i].y = star[i].x * sin(offs) + star[i].y * cos(offs);
        //star[i].x = save;

    }
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
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
                glutTimerFunc(100, timer, 0);
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
    circle(0.0, 0.0, 6, 1.0, 0.4, 0.0);
    mercury();
    venus();
    earth();
    mars();
    jupiter();
    saturn();
    uranus();
    neptune();
    //encke();
    //halley();
    pluto();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape()
{
    // specify the drawing area
    glViewport(0, 0, 1000, 1000);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 3D cahnge to 2D
    glOrtho(-500, 500, -500, 500, -1.0, 1.0);
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
    glutInitWindowSize(1000.0, 1000.0);
    // specify the screen display position
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    xy_init();
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

