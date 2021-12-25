#ifndef _FUNC_H_
#define _FUNC_H_

#include <GL/glut.h>

//
#define WH 1.0, 1.0, 1.0
#define BK 0.0, 0.0, 0.0
#define RE 1.0, 0.0, 0.0
#define GR 0.0, 1.0, 0.0
#define BL 0.0, 0.0, 1.0
#define MA 1.0, 0.0, 1.0
#define CY 0.0, 1.0, 1.0
#define TE 1.0, 1.0, 0.0

//
#define NUMBER_BALL 2

//
#define DISP_BALL 2 

//
#define RATE 1

//
#define GRAV -9.8

//
#define E -0.94

//
#define U 0.99

//
#define WIDTH 640
#define HIGH 480

//
typedef struct 
{
    GLfloat x_cd;
    GLfloat y_cd;
    GLfloat x_sp;
    GLfloat y_sp;
    GLfloat xy_sp;
    GLfloat omega;
    GLfloat size;
    GLfloat rote;
    GLfloat mass;
    GLfloat time;
    int flag;
}
ball_struct;

void frame();
void circle(GLfloat x, GLfloat y, GLfloat r, GLfloat offs);
void rebound_timer(ball_struct *ptr);


#endif
