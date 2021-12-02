#include<stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14

static GLfloat ang = 0.0;

void polygon(GLfloat x, GLfloat y, int n, GLfloat r);

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   //画面の色情報のバッファをクリア
    glColor3f(1.0, 1.0, 0.0);   //頂点の色
    glPushMatrix(); //現在の変換行列をスタックへ退避
    //glRotatef(ang, 0.0, 0.0, 1.0);  //回転軸を生成 ang度回転
    polygon(0.0, 0.0, 36, 15);
    //glRectf( -15.0, -15.0, 15.0, 15.0 );    //四角形 (x1, y1, x2, y2)
    glPopMatrix();  //スタックから変換行列を取得し、現在の変換行列として設定
    glutSwapBuffers();  //バッファ交換(アニメーション)
}

void polygon(GLfloat x, GLfloat y, int n, GLfloat r)
{
    GLfloat xo, yo, xt, yt, rad;
    int i;
    float deg, offs = 90.0;
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

void simu(void)
{
    ang = ang + 1.0;
    if ( ang > 360.0 ) ang = ang - 360.0;
    glutPostRedisplay();    //ウインドウ画像を更新
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void reshape(int w, int h)  //ウィンドウサイズ w => width  h => heigth
{
    glViewport( 0, 0, w, h );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();   //
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) //(種類, 状態, x, y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if ( state == GLUT_DOWN)
            glutIdleFunc(simu);     //イベント処理
            break;
        case GLUT_RIGHT_BUTTON:
            if ( state == GLUT_DOWN)
            glutIdleFunc(NULL);
            break; 
        default:
            break; 
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if ( key == '\x1b') exit(0);    //ESCで実行集中
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);  //openGLの初期化
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    //displaymode default
    glutInitWindowSize (400, 400);  //ウィンドウの初期サイズ
    glutInitWindowPosition(100,100);    //ウィンドウの初期表示位置
    glutCreateWindow(argv[0]);  //ウィンドウ生成
    init();
    glutReshapeFunc(reshape);   //ウィンドウサイズ更新
    glutKeyboardFunc(keyboard); //キーボードコールバック関数
    glutMouseFunc(mouse);   //マウスコールバック関数
    glutDisplayFunc(display);   //ディスプレイ描写
    glutMainLoop();

    return 0;
}
