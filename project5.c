#include<stdio.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.14

/*----------------------------------------------------------*/

void reshape(int width, int high);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void display();
void rebounding_function();
void rotate_function(int m);
void circle_function(GLfloat x, GLfloat y, int n, int huga, GLfloat r);
void collision_function(int flag1, int j);

/*---------------------------------------------------------*/

// Position cahange function
GLfloat posx(GLfloat x);
GLfloat posy(GLfloat y);

// Window size
static GLfloat window_width = 640;
static GLfloat window_high = 480;

// Number of objects
static int number = 2;

// X-Y Position, Speed, and Acceleraton
/* GLfloat x_elements[][5] = {(x0_1, x_1, vx0_1, vx_1, ax1_1), (x0_2, x_2, vx0_2, vx_2, ax_2), ・・・・}; */
GLfloat x_elements[][5] = {{320, 320, 200, 0, 0}, {20, 20, 100, 0, 0}};
GLfloat y_elements[][5] = {{460, 460, -50, 0, -10}, {20, 20, 100, 0, -10}};
GLfloat xy_speed[] = {0.0, 0.0};

// Gravity acceleration
//set it to Zero
static GLfloat grav = 0;

// Object time
/* GLfloat time[][4] = {(x1_1, x2_1, y1_1, y2_1), (x1_2, x2_2, y1_2, y2_2), ・・・・}; */
GLfloat time[][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}};

// Coefficient of restitution
static GLfloat e = -0.9;

// Dynamic friction coefficient
static GLfloat u = 1.0;

// Object size
/* object[] = {object_1, object_2, ・・・・}; */
GLfloat object[] = {30.0, 40.0};
static GLfloat ang = 0.0;
float rotate[] = {1, 1};
int flag[] = {0, 0};

/*-------------------------------------------------------*/

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    for(int i = 0; i < number; i++)
    {
        circle_function(posx(x_elements[i][1]), posy(y_elements[i][1]), 36, i, object[i]);
        rotate_function(i);

    }
    glPopMatrix();
    glutSwapBuffers();
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

/*---------------------------------------------------*/

void mouse(int button, int state, int x, int y)
{
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
            glutTimerFunc(100, rebounding_function, 0);
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

void circle_function(GLfloat x, GLfloat y, int n, int huga, GLfloat r)
{
    GLfloat xo, yo, xt, yt, rad;
    int i, k, l;
    float deg, offs = 90.0;
    if(rotate[huga] > 36) rotate[huga] = 1;
    if(rotate[huga] < 0) rotate[huga] = 36;
    glBegin(GL_TRIANGLE_FAN);
    for(i = 0; i <= n; i++)
    {
        if(i <= rotate[huga] && i > rotate[huga]-1)
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

/*------------------------------------------------*/

void rotate_function(int m)
{
    if(flag[m] == 0) /*printf("no rotation\n")*/;
    else if(flag[m] == 1) rotate[m] += ( xy_speed[m] / (2 * PI * object[m]) ) / 1;
    else if(flag[m] == 2) rotate[m] -= ( xy_speed[m] / (2 * PI * object[m]) ) / 1;
    else printf("error\n");
    //printf("%f\n", rotate[m]);
}

/*------------------------------------------------*/

void rebounding_function()
{

    for(int i = 0; i < number; i++)
    {
        time[i][0] = time[i][0] + 0.025;
        time[i][2] = time[i][2] + 0.025;
        time[i][1] = 0.5 * time[i][0] * time[i][0];
        time[i][3] = 0.5 * time[i][2] * time[i][2];
        x_elements[i][3] = x_elements[i][2] + x_elements[i][4] * time[i][0];
        y_elements[i][3] = y_elements[i][2] + (grav + y_elements[i][4]) * time[i][2];
        x_elements[i][1] = x_elements[i][0] + (x_elements[i][3] * time[i][0]) + (x_elements[i][4] * time[i][1]);
        y_elements[i][1] = y_elements[i][0] + (y_elements[i][3] * time[i][2]) + ((grav + y_elements[i][4]) * time[i][3]);
        xy_speed[i] = sqrt( x_elements[i][3] * x_elements[i][3] + y_elements[i][3] * y_elements[i][3] );

        //printf("x_%d = %f,  y_%d = %f\n", i+1, x_elements[i][1], i+1, y_elements[i][1]);
        printf("v_x_%d = %f,  v_y_%d = %f\n", i+1, x_elements[i][3], i+1, y_elements[i][3]);
        //printf("a_x_%d = %f,  a_y_%d = %f\n", i+1, x_elements[i][4], i+1, grav + y_elements[i][4]);
        //printf("%f\n", time[i][2]);
    
        if( x_elements[i][1] + object[i] > window_width )
        {
            if(x_elements[i][3] != 0.0)
            {
                if(y_elements[i][3] > 0)
                {
                    flag[i] = 1;
                }
                else if(y_elements[i][3] < 0.0)
                {
                    flag[i] = 2;
                }
                else if(y_elements[i][3] == 0.0)
                {
                    if(flag[i] == 1) flag[i] = 2;
                    else if(flag[i] == 2) flag[i] = 1;
                }
            }
            time[i][0] = 0.0;
            x_elements[i][0] = 640 - object[i];
            x_elements[i][2] = x_elements[i][3] * e;
            x_elements[i][3] = 0.0;
            x_elements[i][4] *= e;

        }

        if( y_elements[i][1] < object[i] )
        {
            time[i][2] = 0.0;
            y_elements[i][0] = 0.0 + object[i];
            y_elements[i][2] = y_elements[i][3] * (-1);
            y_elements[i][3] = 0.0;
        }

        if( x_elements[i][1] - object[i] < 0.0 )
        {
            if(x_elements[i][3] != 0.0)
            {
                if(y_elements[i][3] > 0)
                {
                    flag[i] = 2;
                }
                else if(y_elements[i][3] < 0.0)
                {
                    flag[i] = 1;
                }
                else if(y_elements[i][3] == 0.0)
                {
                    if(flag[i] == 1) flag[i] = 2;
                    else if(flag[i] == 2) flag[i] = 1;
                }
            }
            time[i][0] = 0.0;
            x_elements[i][0] = 0.0 + object[i];
            x_elements[i][2] = x_elements[i][3] * e;
            x_elements[i][3] = 0.0;
            x_elements[i][4] *= e;
        }

        if( y_elements[i][1] + object[i] > window_high )
        {
            time[i][2] = 0.0;
            y_elements[i][0] = 480 - object[i];
            y_elements[i][2] = y_elements[i][3] * e;
            y_elements[i][3] = 0.0;
        }

        if( y_elements[i][3] > -0.025 && y_elements[i][3] < 0.025 )
        {
            if( y_elements[i][1] > object[i] * 0.99 && y_elements[i][1] < object[i] * 1.01 )
            {
                y_elements[i][1] = y_elements[i][0] = object[i];
                y_elements[i][2] = y_elements[i][3] = y_elements[i][4] = 0.0;
                if(x_elements[i][3] > 0.0) flag[i] = 2;
                if(x_elements[i][3] < 0.0) flag[i] = 1;
            }
        }
        if(number > 1)
        {
            GLfloat x_posi, y_posi, squares, distance;
            x_posi = posx(x_elements[i][1]) - posx(x_elements[i+1][1]);
            y_posi = posy(y_elements[i][1]) - posy(y_elements[i+1][1]);
            squares = sqrt( (x_posi * x_posi) + (y_posi * y_posi) );
            distance = object[i] + object[i+1];
            if( squares == distance )
            {
                 GLfloat speed_x, speed_y;
                 speed_x = x_elements[i][3] * e;
                 x_elements[i][3] = x_elements[i+1][3] * e;
                 x_elements[i+1][3] = speed_x;
                 speed_y = y_elements[i+1][3] * e;
                 y_elements[i+3][3] = y_elements[i][3] * e;
                 y_elements[i][3] = speed_y;
                 if(flag[i] = 1)
                 {
                    flag[i] = 2;
                    flag[i+2] = 1;
                 }
                 else if(flag[i] = 2)
                 {
                     flag[i] = 1;
                     flag[i+1] = 2;
                 }
            }
        }

    }
    glutPostRedisplay();
    glutTimerFunc(25, rebounding_function, 0);
}

void collision_function(int flag1, int j)
{
    if(flag1 == 0)
    {
         printf("----------------------------\n");
         GLfloat speed_x, speed_y;
         speed_x = x_elements[j][3] * e;
         x_elements[j][3] = x_elements[j+1][3] * e;
         x_elements[j+1][3] = speed_x;
         speed_y = y_elements[j+1][3] * e;
         y_elements[j+3][3] = y_elements[j][3] * e;
         y_elements[j][3] = speed_y;
         if(flag[j] = 1)
         {
             flag[j] = 2;
             flag[j+2] = 1;
         }
         else if(flag[j] = 2)
         {
             flag[j] = 1;
             flag[j+1] = 2;
         }
    }
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
