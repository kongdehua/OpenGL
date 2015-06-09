#include <GL/gl.h>
#include <FreeImage.h>
#include <stdio.h>
#include <GL/glut.h>
#include <unistd.h>

#include "functions.h"

GLuint texture = 2;
double xspin = 0;
double yspin = 0;
double zspin = 0;

GLubyte rasters[24] = {
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xff, 0x00,
    0xff, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xc0, 0x00,
    0xff, 0xc0,
    0xff, 0xc0,
};


void init()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // 黑色背景
    glClearDepth(1.0f);                         // 设置深度缓存
    glEnable(GL_DEPTH_TEST);                        // 启用深度测试
    glDepthFunc(GL_LEQUAL);                         // 所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // 真正精细的透视修正

}


void spinDisplay(void)
{
    xspin += 1.0; if (xspin > 360) xspin = 0;
    yspin += 1.0; if (yspin > 360) yspin = 0;
    zspin += 1.0; if (zspin > 360) zspin = 0;

    usleep(5000);
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3f(1.0, 0.0, 0.0);
    /*
       glRasterPos2i(20, 20);
    //glWindowPos2i(20, 30);
    //glWindowPos2i(20, 20);
    glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
    glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
    glBitmap(10, 12, 0.0, 0.0, 11.0, 0.0, rasters);
    */

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(xspin, 1.0f, 0.0f, 0.0f);
    glRotatef(yspin, 0.0f, 1.0f, 0.0f);
    glRotatef(zspin, 0.0f, 0.0f, 1.0f);

    //printf("texture is %d\n", texture);
    glBindTexture(GL_TEXTURE_2D, texture);               // 选择纹理

    glBegin(GL_QUADS);
    // 前面
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // 纹理和四边形的左上
    // 后面
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // 纹理和四边形的左下
    // 顶面
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // 纹理和四边形的右上
    // 底面
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // 纹理和四边形的右下
    // 右面
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // 纹理和四边形的左下
    // 左面
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // 纹理和四边形的左上
    glEnd();


    glFlush();
}

void mouse( int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        switch (state)
        {
        case GLUT_DOWN:
            glutIdleFunc(spinDisplay);
            break;
        case GLUT_UP:
            glutIdleFunc(NULL);
            break;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        break;
    }
}

void keyboard( unsigned char ch, int x, int y)
{
    switch(ch)
    {
    case 'a':
    case 'A':
        xspin += 2.0;
        yspin += 5.0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width/ (GLfloat)height,
                   0.1f, 100.0f);
    //glOrtho(-50, 50, -50, 50, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    char filename[40] = "./NeHe.bmp";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(400,300);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Hello");

    init();

    if (!loadTexture(&texture, filename)) return -1;

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    //glutIdleFunc(spinDisplay);
    glutMainLoop();


    return 0;
};

