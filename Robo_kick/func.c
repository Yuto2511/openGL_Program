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

//ボールの速度、壁衝突、回転
void rebound_timer(ball_struct *ptr)
{
    for(int i = 0; i < DISP_BALL; i++)
    {
        //速度
        ptr->time = 0.025 * RATE;
        ptr->y_sp += GRAV * ptr->time;
        ptr->x_cd += ptr->x_sp * ptr->time;
        ptr->y_cd += ptr->y_sp * 0.5 * ptr->time;

        //壁衝突
        //床
        if(ptr->y_cd <= ptr->size)
        {
            ptr->flag = 1;
            ptr->y_sp *= E;
            ptr->x_sp *= U;
            ptr->y_cd = ptr->size;
            ptr->omega = ptr->x_sp;
        }
        //右壁
        if(ptr->x_cd + ptr->size >= WIDTH)
        {
            ptr->flag = 1;
            ptr->x_sp *= E;
            ptr->y_sp *= U;
            ptr->x_cd = WIDTH - ptr->size;
            ptr->omega = ptr->y_sp;
        }
        //左壁
        if(ptr->x_cd <= ptr->size)
        {
            ptr->flag = 1;
            ptr->x_sp *= E;
            ptr->y_sp *= U;
            ptr->x_cd = ptr->size;
            ptr->omega = ptr->y_sp;
        }
        //天井
        if(ptr->y_cd + ptr->size >= HIGH)
        {
            ptr->flag = 1;
            ptr->y_sp *= E;
            ptr->x_sp *= U;
            ptr->y_cd = HIGH - ptr->size;
            ptr->omega = ptr->x_sp;
        }

        if(ptr->y_cd == ptr->size)
            ptr->omega = ptr->x_sp;
        else if(ptr->x_sp < 0.00005 && ptr->y_sp < 0.00005 && ptr->y_sp > -0.00005)
            ptr->omega = 0.0;
        if(ptr->omega < 0.0) ptr->omega *= -1;

        //回転
        if(ptr->x_sp != 0.0 && ptr->flag == 1)
        {
            if(ptr->x_sp > 0.0) ptr->omega *= -1;
            ptr->rote += (2 * M_PI * ptr->omega) / (25 * ptr->size * RATE);
            if(ptr->rote >= 360) ptr->rote = 0.0;
        }
        //else ptr->rote = 0.0;

    }
}

//ボール同士の衝突
//void 
