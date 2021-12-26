#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "func.h"

//ボール要素の初期化
void ball_init(ball_struct *ptr)
{
    ptr->xy_sp = sqrt(ptr->x_sp * ptr->x_sp + ptr->y_sp * ptr->y_sp);
    ptr->mass = M_PI * ptr->size * ptr->size;
}

//脚の初期化
void leg_init(leg_struct *ptr)
{
    GLfloat rad, save, x, y;
    ptr->mass = (ptr->b_x - ptr->c_x) * (ptr->a_y - ptr->b_y);
    if(ptr->mass < 0) ptr->mass *= -1;
    rad = (M_PI / 180) * -60;
    save = ptr->a_x * cos(rad) - ptr->a_y * sin(rad);
    ptr->a_y = ptr->a_x * sin(rad) + ptr->a_y * cos(rad);
    ptr->a_x = save;

    save = ptr->b_x * cos(rad) - ptr->b_y * sin(rad);
    ptr->b_y = ptr->b_x * sin(rad) + ptr->b_y * cos(rad);
    ptr->b_x = save;

    save = ptr->c_x * cos(rad) - ptr->c_y * sin(rad);
    ptr->c_y = ptr->c_x * sin(rad) + ptr->c_y * cos(rad);
    ptr->c_x = save;

    save = ptr->d_x * cos(rad) - ptr->d_y * sin(rad);
    ptr->d_y = ptr->d_x * sin(rad) + ptr->d_y * cos(rad);
    ptr->d_x = save;
}

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
            ptr->rote += (2 * M_PI * ptr->omega) / (0.05 * ptr->size * RATE);
        if(ptr->rote >= 360) ptr->rote = 0.0;
    }

}

//ボール同士の衝突
void collision_timer(ball_struct *pt1, ball_struct *pt2)
{
    //円であることを考慮しない
    GLfloat x_dist, y_dist, pp_dist, x1_save, x2_save, y1_save, y2_save;

    x_dist = (pt1->x_cd - pt2->x_cd) * (pt1->x_cd - pt2->x_cd);
    y_dist = (pt1->y_cd - pt2->y_cd) * (pt1->y_cd - pt2->y_cd);
    pp_dist = sqrt(x_dist + y_dist);
    if(pp_dist <= pt1->size + pt2->size)
    {
        x1_save = ((pt1->mass - pt2->mass) * pt1->x_sp + 2 * pt2->mass * pt2->x_sp) / (pt1->mass + pt2->mass);
        y1_save = ((pt1->mass - pt2->mass) * pt1->y_sp + 2 * pt2->mass * pt2->y_sp) / (pt1->mass + pt2->mass);
        x2_save = ((pt2->mass - pt1->mass) * pt2->x_sp + 2 * pt1->mass * pt1->x_sp) / (pt1->mass + pt2->mass);
        y2_save = ((pt2->mass - pt1->mass) * pt2->y_sp + 2 * pt1->mass * pt1->y_sp) / (pt1->mass + pt2->mass);

        if(pt1->y_cd == pt1->size && pt2->y_cd == pt2->size)
        {
            pt1->x_sp = x1_save;
            pt2->x_sp = x2_save;
        }
        else
        {
            pt1->x_sp = x1_save;
            pt1->y_sp = y1_save;
            pt2->x_sp = x2_save;
            pt2->y_sp = y2_save;
        }
    }
    
}

//ロボットの脚の描写
void kicking_leg(leg_struct *ptr)
{
    glBegin(GL_QUADS);
    if(ptr->flag != 0) glColor3f(RE);
    else glColor3f(YE);
    glVertex2f(ptr->a_x + DIS_X, ptr->a_y + DIS_Y);
    glVertex2f(ptr->b_x + DIS_X, ptr->b_y + DIS_Y);
    glVertex2f(ptr->c_x + DIS_X, ptr->c_y + DIS_Y);
    glVertex2f(ptr->d_x + DIS_X, ptr->d_y + DIS_Y);
    glEnd();
}

//脚の回転
void kick_timer(leg_struct *ptr)
{
    GLfloat rad, save, delta = 0;
    ptr->omega ++;
    if(ptr->c_y > DIS_Y-100) ptr->omega = 0.0;
    if(ptr->flag != 0) ptr->omega = 0.0;
    rad = (M_PI / 180) * ptr->omega;
    save = ptr->a_x * cos(rad) - ptr->a_y * sin(rad);
    ptr->a_y = ptr->a_x * sin(rad) + ptr->a_y * cos(rad);
    ptr->a_x = save;

    save = ptr->b_x * cos(rad) - ptr->b_y * sin(rad);
    ptr->b_y = ptr->b_x * sin(rad) + ptr->b_y * cos(rad);
    ptr->b_x = save;

    save = ptr->c_x * cos(rad) - ptr->c_y * sin(rad);
    ptr->c_y = ptr->c_x * sin(rad) + ptr->c_y * cos(rad);
    ptr->c_x = save;

    save = ptr->d_x * cos(rad) - ptr->d_y * sin(rad);
    ptr->d_y = ptr->d_x * sin(rad) + ptr->d_y * cos(rad);
    ptr->d_x = save;
}

//脚とボールの当たり判定
void robokick_timer(leg_struct *leg1, leg_struct *leg2, ball_struct *ball)
{
    GLfloat o_x, o_y, x_dist, y_dist, pp_dist, r_dist, save, leg_v;
    o_x = (leg1->b_x - leg1->c_x) / 2 + leg1->c_x + DIS_X;
    o_y = (leg1->a_y - leg1->b_y) / 2 + leg1->c_y + DIS_Y;
    x_dist = (ball->x_cd - o_x) * (ball->x_cd - o_x);
    y_dist = (ball->y_cd - o_y) * (ball->y_cd - o_y);
    pp_dist = sqrt(x_dist + y_dist);
    r_dist = sqrt((leg1->c_x + DIS_X - o_x) * (leg1->c_x + DIS_X - o_x) + (leg1->c_y + DIS_Y - o_y) * (leg1->c_y + DIS_Y - o_y));
    leg_v = leg1->omega * (leg1->b_y + DIS_Y - o_y);
    if(leg_v < 0) leg_v *= -1;
    if(leg1->flag == 0)
    {
        if(pp_dist <= r_dist + ball->size)
        {
            save = ((ball->mass - (leg1->mass + leg2->mass)) * ball->x_sp + 2 * (leg2->mass + leg2->mass) * leg_v) / (ball->mass + leg2->mass + leg2->mass);
            ball->x_sp = save;
            save = ((ball->mass - (leg1->mass + leg2->mass)) * ball->y_sp + 2 * (leg1->mass + leg2->mass) * leg_v) / (ball->mass + leg1->mass + leg2->mass);
            ball->y_sp = save;
            leg1->flag = 1;
            leg2->flag = 1;
        }
    }
}
