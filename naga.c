#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include<math.h>

// Pi
#define PI 3.14


// The number of balls
#define NUMBER_BALL 2

// Gravity
#define GRAV -9.8

// coefficient of restitution
#define e -0.94

// simple dynamic friction coefficient
#define u 0.99

void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void display();
void reshape();
void init();

void circle(GLfloat x, GLfloat y, GLfloat r);
void rotation(int i, GLfloat x, GLfloat y, GLfloat v, GLfloat r);
void rebound_timer();
void collisions_timer();

// view port size
GLfloat width = 640.0;
GLfloat high = 480.0;

// the number of balls to display
int number = 2;

// Playback speed magnification
GLfloat rate = 10;

// structure of ball
typedef struct 
{
    GLfloat x_cd;
    GLfloat y_cd;
    GLfloat x_sp;
    GLfloat y_sp;
    GLfloat xy_sp;
    GLfloat size;
    GLfloat mass;
    GLfloat time;
}
ball_struct;

ball_struct ball[NUMBER_BALL] = {{330, 400, 0, 0, 0, 30, 0, 0},
                                 {340, 60, -80, 100, 0, 60, 0, 0}};

typedef struct
{
    GLfloat x_r;
    GLfloat y_r;
    GLfloat theta;
}
ball_rotate;

ball_rotate  rotate[NUMBER_BALL] = {{0.0, 0.0, 0.0},
                                    {0.0, 0.0, 0.0}};


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
                glutTimerFunc(100, rebound_timer, 0);
                glutTimerFunc(100, collisions_timer, 0);
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
    for(int i = 0; i < number; i++)
    {
        circle(ball[i].x_cd, ball[i].y_cd, ball[i].size);
        rotation(i, ball[i].x_cd, ball[i].y_cd, ball[i].xy_sp, ball[i].size);
    }
    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void reshape()
{
    glViewport(0, 0, width, high);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, high, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
}


void circle(GLfloat x, GLfloat y, GLfloat r)
{
    int i;
    float deg;
    GLfloat xo, yo, rad;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 1.0, 1.0);
    for(i = 0; i <= 36; i++)
    {
        glVertex2f(x, y);
        deg = 10 * i;
        rad = PI/180 * deg;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
        deg = 10 * (i+1);
        rad = PI/180 * deg;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
    }
    glEnd();
}

void rotation(int i, GLfloat x, GLfloat y, GLfloat v, GLfloat r)
{
    GLfloat xo, yo, offs = 90.0, rad;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(x, y);
    rotate[i].theta = (2 * PI * v) / (0.0025 * r) + offs;
    rad = PI/180 * rotate[i].theta;
    rotate[i].x_r = x +  r * cos(rad);
    rotate[i].y_r = y +  r * sin(rad);
    glVertex2f(rotate[i].x_r, rotate[i].y_r);
    rad = PI/180 * (rotate[i].theta + 20);
    xo = x + r * cos(rad);
    yo = y + r * sin(rad);
    glVertex2f(xo, yo);
    glEnd();
}

void rebound_timer()
{
    for(int i = 0; i < number; i++)
    {
        ball[i].time = 0.0025 * rate;
        ball[i].y_sp += GRAV * ball[i].time;
        ball[i].x_cd += ball[i].x_sp * ball[i].time;
        ball[i].y_cd += ball[i].y_sp * ball[i].time;

        // Flooring
        if(ball[i].y_cd <= ball[i].size)
        {
            ball[i].y_sp *= e;
            ball[i].x_sp *= u;
            ball[i].y_cd = ball[i].size;
        }
        //Right wall
        if(ball[i].x_cd + ball[i].size >= width)
        {
            ball[i].x_sp *= e;
            ball[i].y_sp *= u;
            ball[i].x_cd = width - ball[i].size;
        }
        //Left wall
        if(ball[i].x_cd <= ball[i].size)
        {
            ball[i].x_sp *= e;
            ball[i].y_sp *= u;
            ball[i].x_cd = ball[i].size;
        }
        //Ceiling
        if(ball[i].y_cd + ball[i].size >= high)
        {
            ball[i].y_sp *= e;
            ball[i].x_sp *= u;
            ball[i].y_cd = high - ball[i].size;
        }

        if(ball[i].y_cd == ball[i].size)
            ball[i].xy_sp = ball[i].x_sp;
        else if(ball[i].x_sp == 0.0)
            ball[i].xy_sp = 0.0;
        else if(ball[i].x_sp < 0.0001 && ball[i].y_sp < -3.0)
            ball[i].xy_sp = 0.0;
        else ball[i].xy_sp = sqrt(ball[i].x_sp * ball[i].x_sp + ball[i].y_sp * ball[i].y_sp);
    }   

    glutPostRedisplay();
    glutTimerFunc(25, rebound_timer, 0);
}

void collisions_timer()
{
    int i, j;
    GLfloat x_dist, y_dist, pp_dist, xi_save, xj_save, yi_save, yj_save;
    if(number > 1)
    {
        for(i = 0; i < number; i++)
        {
            for(j = i; j < number; j++)
            {
                x_dist = (ball[i].x_cd - ball[j].x_cd) * (ball[i].x_cd - ball[j].x_cd);
                y_dist = (ball[i].y_cd - ball[j].y_cd) * (ball[i].y_cd - ball[j].y_cd);
                pp_dist = sqrt(x_dist + y_dist);
                ball[i].mass = ball[i].size * ball[i].size;
                ball[j].mass = ball[j].size * ball[j].size;
                if(pp_dist <= ball[i].size + ball[j].size)
                {
                    xi_save = ((ball[i].mass - ball[j].mass) * ball[i].x_sp + 2 * ball[j].mass * ball[j].x_sp) / (ball[i].mass + ball[j].mass);
                    yi_save = ((ball[i].mass - ball[j].mass) * ball[i].y_sp + 2 * ball[j].mass * ball[j].y_sp) / (ball[i].mass + ball[j].mass);
                    xj_save = ((ball[j].mass - ball[i].mass) * ball[j].x_sp + 2 * ball[i].mass * ball[i].x_sp) / (ball[i].mass + ball[j].mass);
                    yj_save = ((ball[j].mass - ball[i].mass) * ball[j].y_sp + 2 * ball[i].mass * ball[i].y_sp) / (ball[i].mass + ball[j].mass);
                    
                    if(ball[i].y_cd == ball[i].size && ball[j].y_cd == ball[j].size)
                    {
                        ball[i].x_sp = xi_save;
                        ball[j].x_sp = xj_save;
                    }
                    else
                    {
                        ball[i].x_sp = xi_save;
                        ball[i].y_sp = yi_save;
                        ball[j].x_sp = xj_save;
                        ball[j].y_sp = yj_save;
                    }
                }
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(25, collisions_timer, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    // specify the window size
    glutInitWindowSize(width, high);
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

