#ifndef _FUNC_H_
#define _FUNC_H_

#include <GL/glut.h>

//色
#define WH 1.0, 1.0, 1.0
#define BK 0.0, 0.0, 0.0
#define RE 1.0, 0.0, 0.0
#define GR 0.0, 1.0, 0.0
#define BL 0.0, 0.0, 1.0
#define MA 1.0, 0.0, 1.0
#define CY 0.0, 1.0, 1.0
#define YE 1.0, 1.0, 0.0

//ボールの数
#define NUMBER_BALL 4

//ディスプレイに表示するボールの数
#define DISP_BALL 4 

//描写倍率
#define RATE 8

//重力加速度
#define GRAV -9.8

//反発係数
#define E -0.94

//動摩擦係数
#define U 0.99

//ボールの運動領域
#define WIDTH 640
#define HIGH 480

//脚の回転中心
#define DIS_X 100
#define DIS_Y 150


//ボールの要素
typedef struct 
{
    GLfloat x_cd;   //x座標
    GLfloat y_cd;   //y座標
    GLfloat x_sp;   //x速度
    GLfloat y_sp;   //y速度
    GLfloat xy_sp;  //合成の速度
    GLfloat omega;  //角速度
    GLfloat size;   //半径
    GLfloat rote;
    GLfloat mass;   //質量
    GLfloat time;   //時間
    int flag;
}
ball_struct;

//脚の要素
typedef struct
{
    GLfloat a_x;
    GLfloat a_y;
    GLfloat b_x;
    GLfloat b_y;
    GLfloat c_x;
    GLfloat c_y;
    GLfloat d_x;
    GLfloat d_y;
    GLfloat omega;  //角速度
    GLfloat mass;   //質量
    int flag;
    
}
leg_struct;

//プロトタイプ宣言
void ball_init(ball_struct *ptr);
void leg_init(leg_struct *ptr);
void frame();
void circle(GLfloat x, GLfloat y, GLfloat r, GLfloat offs);
void rebound_timer(ball_struct *ptr);
void collision_timer(ball_struct *pt1, ball_struct *pt2);
void kicking_leg(leg_struct *ptr);
void kick_timer(leg_struct *ptr);
void robokick_timer(leg_struct *leg, leg_struct *leg2, ball_struct *ball);

#endif
