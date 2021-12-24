#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "func.h"

//ボールを動かすX-Y座標を作る
void frame()
{
    glBegin(GL_LINES);
    //外枠
    glColor3f(RE);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, HIGH + 20);
    glColor3f(BL);
    glVertex2f(0.0, 0.0);
    glVertex2f(WIDTH + 20, 0.0);
    glColor3f(WH);
    glVertex2f(WIDTH, 0.0);
    glVertex2f(WIDTH, HIGH);
    glVertex2f(0.0, HIGH);
    glVertex2f(WIDTH, HIGH);
    //矢印
    glColor3f(RE);
    glVertex2f(0.0, HIGH + 20);
    glVertex2f(5.0, HIGH + 10);
    glVertex2f(0.0, HIGH + 20);
    glVertex2f(-5.0, HIGH + 10);
    glColor3f(BL);
    glVertex2f(WIDTH + 20, 0.0);
    glVertex2f(WIDTH + 10, 5.0);
    glVertex2f(WIDTH + 20, 0.0);
    glVertex2f(WIDTH + 10, -5.0);
    //座標
    glColor3f(0.60, 0.60, 0.60);
    for(int i = 20; i < WIDTH; i+=20)
    {
        glVertex2f(i, 0.0);
        glVertex2f(i, HIGH);
    }
    for(int j = 20; j < HIGH; j+=20)
    {
        glVertex2f(0.0, j);
        glVertex2f(WIDTH, j);
    }
    glEnd();
    //タイトル
    char str[] = {'R', 'o', 'b', 'o', '-', 'K', 'i', 'c', 'k', ' ', 'S', 'i', 'm', 'u', 'l', 'a', 't', 'o', 'r'};
    glRasterPos2f(250, HIGH + 12);
    int size = sizeof(str);
    for(int i = 0; i < size; i++)
    {
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic);
    }
}

//ボールを描く
void circle(GLfloat x, GLfloat y, GLfloat r, GLfloat offs)
{
    float deg;
    GLfloat xo, yo, rad;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(CY);
    for(int i = 0; i < 36; i++)
    {
        if(i >= 0 && i < 32) glColor3f(CY);
        else glColor3f(BL);
        glVertex2f(x, y);
        deg = (i * 10) + offs;
        rad =M_PI/180 * deg;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
        deg = ((i + 1) * 10) + offs;
        rad = M_PI/180 * deg;
        xo = x + r * cos(rad);
        yo = y + r * sin(rad);
        glVertex2f(xo, yo);
    }
    glEnd();
}

//ボールの速度、壁衝突
void rebound_timer()
{
    for(int i = 0; i < DISP_BALL; i++)
    {
        ball[i].time += 0.025 * RATE;
        ball[i].y_sp += GRAV * ball[i].time;
        ball[i].x_cd += ball[i].x_sp * ball[i].time;
        ball[i].y_cd += ball[i].y_sp * ball[i].time;

        //床
        if(ball[i].y_cd <= ball[i].size)
        {
            ball[i].y_sp *= E;
            ball[i].x_sp *= U;
            ball[i].y_cd = ball[i].size;
        }
        //右壁
        if(ball[i].x_cd + ball[i].size >= WIDTH)
        {
            ball[i].x_sp *= E;
            ball[i].y_sp *= U;
            ball[i].x_cd = WIDTH - ball[i].size;
        }
        //左壁
        if(ball[i].x_cd <= ball[i].size)
        {
            ball[i].x_sp *= E;
            ball[i].y_sp *= U;
            ball[i].x_cd = ball[i].size;
        }
        //天井
        if(ball[i].y_cd + ball[i].size >= HIGH)
        {
            ball[i].y_sp *= E;
            ball[i].x_sp *= U;
            ball[i].y_cd = HIGH - ball[i].size;
        }

        if(ball[i].y_cd == ball[i].size)
            ball[i].xy_sp = ball[i].x_sp;
        else if(ball[i].x_sp == 0.0)
            ball[i].xy_sp = 0.0;
        else if(ball[i].x_sp < 0.00005 && ball[i].y_sp < -3.0)
            ball[i].xy_sp = 0.0;
        else ball[i].xy_sp = sqrt(ball[i].x_sp * ball[i].x_sp + ball[i].y_sp * ball[i].y_sp);

    }
    glutPostRedisplay();
    glutTimerFunc(25, rebound_timer, 0);
}
