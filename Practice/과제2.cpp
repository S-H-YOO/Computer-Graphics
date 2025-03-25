#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glui.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_ANIMATION_STEPS 100

/*==================GLUT Parameter===============================*/
int i = 0;
int CC = 0;
int a = 0;
float xy_aspect;
float rotationX = 0.0, rotationY = 0.0;
int Anim = 0;
int wireframe = 0;
std::string text = "60201736 YOO Sang Hoon";

GLfloat xTheta = 0.0, yTheta = 0.0;
GLfloat scale = 1.0, scaleDelta = 1.01;
GLfloat RotationMatrix[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

// Translate
GLfloat translateX = 0.0f;
GLfloat translateY = 0.0f;
GLfloat translateZ = 0.0f;
GLfloat translateXY[2] = { 0.0f, 0.0f };
GLfloat backgroundColor[3] = { 0.0f, 0.0f, 0.0f }; // 초기 배경 색상: 검정색

/*
User IDs for callbacks
*/
#define RED_COLOR 200
#define BLUE_COLOR 201
#define GREEN_COLOR 202

// 애니메이션 구조체
typedef struct
{
    int step;
    char part[4];
    float angle;
} AnimationStep;

AnimationStep animationData[MAX_ANIMATION_STEPS];
int numAnimationSteps = 0;
int currentAnimationStep = 0;

/*=============Custom Color Parameter==========*/
GLfloat upper_arm_color[3] = { 1.0f, 0.0f, 0.0f };
GLfloat lower_arm_color[3] = { 0.0f, 1.0f, 0.0f };
GLfloat upper_leg_color[3] = { 0.0f, 0.0f, 1.0f };
GLfloat lower_leg_color[3] = { 1.0f, 1.0f, 0.0f };
GLfloat robotscolor[3] = { 1.0f, 1.0f, 1.0f };

GLfloat message_color[3] = { 1.0f, 1.0f, 1.0f };

static int rshoulder = 0, lshoulder = 0, relbow = 0, lelbow = 0, lupperleg = 0,
rupperleg = 0, llowerleg = 0, rlowerleg = 0;

/*================GLUI Parameter===================*/
int main_window;
GLUI_Scrollbar* Red_Scrollbar, * Green_Scrollbar, * Blue_Scrollbar;
GLUI_EditText* edittext;

/*=============================myGlutMotion====================================*/


/* myGlutReshape*/

void myGlutReshape(int x, int y)
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);

    xy_aspect = (float)tw / (float)th;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, xy_aspect, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}
void applyAnimationStep(AnimationStep* step)
{
    if (strcmp(step->part, "lll") == 0)
    {
        llowerleg = step->angle;
    }
    else if (strcmp(step->part, "rll") == 0)
    {
        rlowerleg = step->angle;
    }
    else if (strcmp(step->part, "lul") == 0)
    {
        lupperleg = step->angle;
    }
    else if (strcmp(step->part, "rul") == 0)
    {
        rupperleg = step->angle;
    }
    else if (strcmp(step->part, "lua") == 0)
    {
        lshoulder = step->angle;
    }
    else if (strcmp(step->part, "rua") == 0)
    {
        rshoulder = step->angle;
    }
    else if (strcmp(step->part, "lla") == 0)
    {
        lelbow = step->angle;
    }
    else if (strcmp(step->part, "rla") == 0)
    {
        relbow = step->angle;
    }
}

void readAnimationData(const char* filename)
{
    FILE* file;
    fopen_s(&file, filename, "r");
    if (file == NULL)
    {
        printf("Unable to open file %s\n", filename);
        return;
    }

    while (fscanf_s(file, "%d %s %f", &animationData[numAnimationSteps].step, animationData[numAnimationSteps].part, (unsigned)_countof(animationData[numAnimationSteps].part), &animationData[numAnimationSteps].angle) == 3)
    {
        numAnimationSteps++;
    }

    fclose(file);
}

void myGlutDisplay()
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);

    xy_aspect = (float)tw / (float)th;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, xy_aspect, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat light1Pos[] = { -200.0, 200.0, 300.0, 0.0 };
    GLfloat light2Pos[] = { 0.0, 1.0, 0.0, 0.0 };
    GLfloat grayColor[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING); // 조명 사용

    glLightfv(GL_LIGHT0, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grayColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
    glEnable(GL_LIGHT0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(translateXY[0], translateXY[1], -10.0f + translateZ);
    glMultMatrixf(RotationMatrix);
    glScalef(scale, scale, scale); // <- 추가할 부분

    if (wireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    GLfloat materialColor[4];

    if (wireframe)
    {
        // 머리 그리기 (노란색 구체)
        materialColor[0] = 1.0;
        materialColor[1] = 1.0;
        materialColor[2] = 0.0;
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0); // 머리 위치 조정
        glutWireSphere(0.6, 20, 20); // 구체 그리기
        glPopMatrix();

        // 몸통 그리기 (파란색 큐브)
        materialColor[0] = 0.0;
        materialColor[1] = 0.0;
        materialColor[2] = 1.0;
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glScalef(1.8, 2.6, 0.5); // 몸통 크기 조정
        glutWireCube(1.0);       // 큐브 그리기
        glPopMatrix();

        // 오른쪽 팔 그리기
        materialColor[0] = upper_arm_color[0];
        materialColor[1] = upper_arm_color[1];
        materialColor[2] = upper_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glPushMatrix();
        glTranslatef(0.4, 1.3, 0.0); // 팔 위치 조정
        glRotatef((GLfloat)rshoulder, 1.0, 0.0, 0.0); // 어깨 회전
        glTranslatef(0.75, -0.8, 0.0);                // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 팔 크기 조정
        glutWireCube(1.0);       // 큐브 그리기
        glPopMatrix();

        // 오른쪽 팔꿈치
        materialColor[0] = lower_arm_color[0];
        materialColor[1] = lower_arm_color[1];
        materialColor[2] = lower_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(-0.75, -0.8, 0.0);

        glRotatef((GLfloat)relbow, 1.0, 0.0, 0.0); // 팔꿈치 회전
        glTranslatef(0.75, -0.7, 0.0);            // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 손 크기 조정
        glutWireCube(1.0);       // 큐브 그리기
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 팔 그리기
        materialColor[0] = upper_arm_color[0];
        materialColor[1] = upper_arm_color[1];
        materialColor[2] = upper_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(-0.4, 1.3, 0.0); // 팔 위치 조정
        glRotatef((GLfloat)lshoulder, 1.0, 0.0, 0.0); // 어깨 회전
        glTranslatef(-0.75, -0.8, 0.0);               // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 팔 크기 조정
        glutWireCube(1.0);       // 큐브 그리기
        glPopMatrix();

        // 왼쪽 팔꿈치 그리기
        glTranslatef(0.75, -0.8, 0.0); // 팔꿈치 위치 조정
        glRotatef((GLfloat)lelbow, 1.0, 0.0, 0.0); // 팔꿈치 회전
        glTranslatef(-0.75, -0.7, 0.0);            // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 손 크기 조정
        materialColor[0] = lower_arm_color[0];
        materialColor[1] = lower_arm_color[1];
        materialColor[2] = lower_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0); // 큐브 그리기
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 위다리 그리기
        materialColor[0] = upper_leg_color[0];
        materialColor[1] = upper_leg_color[1];
        materialColor[2] = upper_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.25, -1.3, 0.0); // 다리 위치 조정
        glRotatef((GLfloat)lupperleg, 1.0, 0.0, 0.0); // 다리 회전
        glTranslatef(-0.75, -0.75, 0.0);              // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 다리 크기 조정
        glutWireCube(1.0);       // 큐브 그리기
        glPopMatrix();

        // 왼쪽 아래다리 그리기
        glTranslatef(0.75, -0.8, 0.0); // 아래다리 위치 조정
        glRotatef((GLfloat)llowerleg, 1.0, 0.0, 0.0); // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);               // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 아래다리 크기 조정
        materialColor[0] = lower_leg_color[0];
        materialColor[1] = lower_leg_color[1];
        materialColor[2] = lower_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0); // 큐브 그리기
        glPopMatrix();
        glPopMatrix();

        // 오른쪽 위다리 그리기
        materialColor[0] = upper_leg_color[0];
        materialColor[1] = upper_leg_color[1];
        materialColor[2] = upper_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.55, -1.3, 0.0); // 다리 위치 조정
        glRotatef((GLfloat)rupperleg, 1.0, 0.0, 0.0); // 다리 회전
        glTranslatef(0.0, -0.75, 0.0);                // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 다리 크기 조정
        glutWireCube(1.0);       // 큐브 그리기
        glPopMatrix();

        // 오른쪽 아래다리 그리기
        glTranslatef(0.75, -0.8, 0.0); // 아래다리 위치 조정
        glRotatef((GLfloat)rlowerleg, 1.0, 0.0, 0.0); // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);               // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 아래다리 크기 조정
        materialColor[0] = lower_leg_color[0];
        materialColor[1] = lower_leg_color[1];
        materialColor[2] = lower_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0); // 큐브 그리기
        glPopMatrix();
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 600.0, 0.0, 600.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3fv(message_color); // 메시지 색상 설정
        materialColor[0] = message_color[0];
        materialColor[1] = message_color[1];
        materialColor[2] = message_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glRasterPos2i(10, 10);
        for (unsigned int i = 0; i < text.length(); ++i)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glutSwapBuffers();
    }
    else
    {
        // 머리 그리기 (노란색 구체)
        materialColor[0] = 1.0;
        materialColor[1] = 1.0;
        materialColor[2] = 0.0;
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0);  // 머리 위치 조정
        glutSolidSphere(0.6, 20, 20); // 구체 그리기
        glPopMatrix();

        // 몸통 그리기 (파란색 큐브)
        materialColor[0] = 0.0;
        materialColor[1] = 0.0;
        materialColor[2] = 1.0;
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glScalef(1.8, 2.6, 0.5); // 몸통 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 오른쪽 팔 그리기
        materialColor[0] = upper_arm_color[0];
        materialColor[1] = upper_arm_color[1];
        materialColor[2] = upper_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glPushMatrix();
        glTranslatef(0.4, 1.3, 0.0); // 팔 위치 조정
        glRotatef((GLfloat)rshoulder, 1.0, 0.0, 0.0); // 어깨 회전
        glTranslatef(0.75, -0.8, 0.0);                // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 팔 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 오른쪽 팔꿈치
        materialColor[0] = lower_arm_color[0];
        materialColor[1] = lower_arm_color[1];
        materialColor[2] = lower_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(-0.75, -0.8, 0.0);

        glRotatef((GLfloat)relbow, 1.0, 0.0, 0.0); // 팔꿈치 회전
        glTranslatef(0.75, -0.7, 0.0);            // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 손 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 팔 그리기
        materialColor[0] = upper_arm_color[0];
        materialColor[1] = upper_arm_color[1];
        materialColor[2] = upper_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(-0.4, 1.3, 0.0); // 팔 위치 조정
        glRotatef((GLfloat)lshoulder, 1.0, 0.0, 0.0); // 어깨 회전
        glTranslatef(-0.75, -0.8, 0.0);               // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 팔 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 왼쪽 팔꿈치 그리기
        glTranslatef(0.75, -0.8, 0.0); // 팔꿈치 위치 조정
        glRotatef((GLfloat)lelbow, 1.0, 0.0, 0.0); // 팔꿈치 회전
        glTranslatef(-0.75, -0.7, 0.0);            // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 손 크기 조정
        materialColor[0] = lower_arm_color[0];
        materialColor[1] = lower_arm_color[1];
        materialColor[2] = lower_arm_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 위다리 그리기
        materialColor[0] = upper_leg_color[0];
        materialColor[1] = upper_leg_color[1];
        materialColor[2] = upper_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.25, -1.3, 0.0); // 다리 위치 조정
        glRotatef((GLfloat)lupperleg, 1.0, 0.0, 0.0); // 다리 회전
        glTranslatef(-0.75, -0.75, 0.0);              // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 다리 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 왼쪽 아래다리 그리기
        glTranslatef(0.75, -0.8, 0.0); // 아래다리 위치 조정
        glRotatef((GLfloat)llowerleg, 1.0, 0.0, 0.0); // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);               // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 아래다리 크기 조정
        materialColor[0] = lower_leg_color[0];
        materialColor[1] = lower_leg_color[1];
        materialColor[2] = lower_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // 오른쪽 위다리 그리기
        materialColor[0] = upper_leg_color[0];
        materialColor[1] = upper_leg_color[1];
        materialColor[2] = upper_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.55, -1.3, 0.0); // 다리 위치 조정
        glRotatef((GLfloat)rupperleg, 1.0, 0.0, 0.0); // 다리 회전
        glTranslatef(0.0, -0.75, 0.0);                // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 다리 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 오른쪽 아래다리 그리기
        glTranslatef(0.75, -0.8, 0.0); // 아래다리 위치 조정
        glRotatef((GLfloat)rlowerleg, 1.0, 0.0, 0.0); // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);               // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4); // 아래다리 크기 조정
        materialColor[0] = lower_leg_color[0];
        materialColor[1] = lower_leg_color[1];
        materialColor[2] = lower_leg_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 600.0, 0.0, 600.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3fv(message_color); // 메시지 색상 설정
        materialColor[0] = message_color[0];
        materialColor[1] = message_color[1];
        materialColor[2] = message_color[2];
        materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glRasterPos2i(10, 10);
        for (unsigned int i = 0; i < text.length(); ++i)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glutSwapBuffers();
    }
}

void color_change_cb(int id)
{
    switch (CC)
    {
    case 0:
        upper_arm_color[0] = robotscolor[0];
        upper_arm_color[1] = robotscolor[1];
        upper_arm_color[2] = robotscolor[2];
        break;
    case 1:
        lower_arm_color[0] = robotscolor[0];
        lower_arm_color[1] = robotscolor[1];
        lower_arm_color[2] = robotscolor[2];

        break;
    case 2:
        upper_leg_color[0] = robotscolor[0];
        upper_leg_color[1] = robotscolor[1];
        upper_leg_color[2] = robotscolor[2];

        break;
    case 3:
        lower_leg_color[0] = robotscolor[0];
        lower_leg_color[1] = robotscolor[1];
        lower_leg_color[2] = robotscolor[2];
        break;

    default:
        break;
    }
}

// Timer 함수
void MyTimer(int value)
{
    if (Anim == 1)
    {
        if (currentAnimationStep < numAnimationSteps)
        {
            applyAnimationStep(&animationData[currentAnimationStep]);
            currentAnimationStep++;
        }
        else
        {
            currentAnimationStep = 0;
        }
        glutPostRedisplay();

        glutTimerFunc(40, MyTimer, 0); // 주기적으로 타이머 설정
    }
}

// Start 함수
void Start(int id)
{
    Anim = 1;
    currentAnimationStep = 0;

    if (numAnimationSteps > 0)
    {
        applyAnimationStep(&animationData[currentAnimationStep]);
        currentAnimationStep++;
    }
    glutPostRedisplay();

    glutTimerFunc(40, MyTimer, 0);
}

// Stop 함수
void Stop(int id)
{
    Anim = 0;
}
// 색상 지정
void C_C(int id)
{

    switch (CC)
    {
    case 0:
        Red_Scrollbar->set_float_val(upper_arm_color[0]);
        Green_Scrollbar->set_float_val(upper_arm_color[1]);
        Blue_Scrollbar->set_float_val(upper_arm_color[2]);
        break;
    case 1:
        Red_Scrollbar->set_float_val(lower_arm_color[0]);
        Green_Scrollbar->set_float_val(lower_arm_color[1]);
        Blue_Scrollbar->set_float_val(lower_arm_color[2]);

        printf("case1");
        break;
    case 2:
        Red_Scrollbar->set_float_val(upper_leg_color[0]);
        Green_Scrollbar->set_float_val(upper_leg_color[1]);
        Blue_Scrollbar->set_float_val(upper_leg_color[2]);
        printf("case2");

        break;
    case 3:
        Red_Scrollbar->set_float_val(lower_leg_color[0]);
        Green_Scrollbar->set_float_val(lower_leg_color[1]);
        Blue_Scrollbar->set_float_val(lower_leg_color[2]);
        break;

    default:
        break;
    }
    glutPostRedisplay(); // 추가: 변경 사항을 즉시 반영
}

void Wireframe(int id)
{
    if (id == 0)
    {
        wireframe = 0;
        glutPostRedisplay();
    }
    else if (id == 1)
    {
        wireframe = 1;
        glutPostRedisplay();
    }
}

void background_color_cb(int color)
{
    switch (a)
    {
    case 0: // black
        backgroundColor[0] = 0.0f;
        backgroundColor[1] = 0.0f;
        backgroundColor[2] = 0.0f;
        break;
    case 1: // white
        backgroundColor[0] = 1.0f;
        backgroundColor[1] = 1.0f;
        backgroundColor[2] = 1.0f;
        break;
    case 2: // red
        backgroundColor[0] = 1.0f;
        backgroundColor[1] = 0.0f;
        backgroundColor[2] = 0.0f;
        break;
    case 3: // green
        backgroundColor[0] = 0.0f;
        backgroundColor[1] = 1.0f;
        backgroundColor[2] = 0.0f;
        break;
    case 4: // blue
        backgroundColor[0] = 0.0f;
        backgroundColor[1] = 0.0f;
        backgroundColor[2] = 1.0f;
        break;
    }
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 0.0);
    glutPostRedisplay();
}

void myGlutIdle(void) {
    glutSetWindow(main_window);
    glutPostRedisplay();
}


void MyInit()
{
    glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
    glEnable(GL_LIGHTING);   // 조명 활성화
    glEnable(GL_LIGHT0);     // 하나의 조명 활성화

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // 조명 위치
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat white_light[] = { 1.0, 1.0, 0.0, 0.0 }; // 백색 광원
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    glClearColor(0.0, 0.0, 0.0, 1.0); // 배경색 설정
    glShadeModel(GL_SMOOTH);
}

void myGlutMotion(int x, int y)
{
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{

    readAnimationData("RobotStory.txt");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    main_window = glutCreateWindow("GLUT");

    MyInit();
    glutDisplayFunc(myGlutDisplay);
    glutMotionFunc(myGlutMotion);

    glEnable(GL_DEPTH_TEST);
    GLUI* glui = GLUI_Master.create_glui("Menu", 0, 660, 50);
    glutReshapeFunc(myGlutReshape);
    GLUI_Panel* HW_Sample;
    HW_Sample = glui->add_panel("", GLUI_PANEL_EMBOSSED);
    glui->add_statictext_to_panel(HW_Sample, "HW Sample");
    glui->add_column_to_panel(HW_Sample, false);
    edittext = glui->add_edittext_to_panel(HW_Sample, "msg", text);

    GLUI_Panel* Rotation_Panel;
    Rotation_Panel = glui->add_panel("");
    GLUI_Rotation* rotation = glui->add_rotation_to_panel(Rotation_Panel, "Rotate", RotationMatrix);
    glui->add_column_to_panel(Rotation_Panel, false);
    GLUI_Spinner* scale_spinner = glui->add_spinner_to_panel(Rotation_Panel, "Scale:", GLUI_SPINNER_FLOAT, &scale);
    scale_spinner->set_float_limits(0.1f, 10.0f);
    scale_spinner->set_speed(0.5);
    new GLUI_Checkbox(Rotation_Panel, "Wireframe", &wireframe);

    GLUI_Panel* Translation;
    Translation = glui->add_panel("Translation");
    GLUI_Translation* trans_xy = new GLUI_Translation(Translation, "Objects XY", GLUI_TRANSLATION_XY, translateXY);
    glui->add_column_to_panel(Translation, false);
    trans_xy->set_speed(.05);
    GLUI_Translation* trans_x = new GLUI_Translation(Translation, "Objects X", GLUI_TRANSLATION_X, &translateXY[0]);
    glui->add_column_to_panel(Translation, false);
    trans_x->set_speed(.05);
    GLUI_Translation* trans_y = new GLUI_Translation(Translation, "Objects Y", GLUI_TRANSLATION_Y, &translateXY[1]);
    trans_y->set_speed(.05);
    glui->add_column_to_panel(Translation, false);
    GLUI_Translation* trans_z = new GLUI_Translation(Translation, "Objects Z", GLUI_TRANSLATION_Z, &translateZ);
    trans_z->set_speed(.05);

    GLUI_Rollout* Animation_Control;
    Animation_Control = glui->add_rollout("Animation Control", 1);
    glui->add_button_to_panel(Animation_Control, "Start", 0, Start);
    glui->add_column_to_panel(Animation_Control, false);
    glui->add_button_to_panel(Animation_Control, "Stop", 0, Stop);

    GLUI_Rollout* Custom_Color;
    Custom_Color = glui->add_rollout("Custom Color", 1);

    GLUI_RadioGroup* cc;
    cc = glui->add_radiogroup_to_panel(Custom_Color, &CC, -1, C_C);

    glui->add_radiobutton_to_group(cc, "Upper Arm");
    glui->add_radiobutton_to_group(cc, "Lower Arm");
    glui->add_radiobutton_to_group(cc, "Upper Leg");
    glui->add_radiobutton_to_group(cc, "Lower Leg");
    glui->add_separator_to_panel(Custom_Color);

    Red_Scrollbar = new GLUI_Scrollbar(Custom_Color, "Red", GLUI_SCROLL_HORIZONTAL, &robotscolor[0], RED_COLOR, color_change_cb);
    Green_Scrollbar = new GLUI_Scrollbar(Custom_Color, "Green", GLUI_SCROLL_HORIZONTAL, &robotscolor[1], GREEN_COLOR, color_change_cb);
    Blue_Scrollbar = new GLUI_Scrollbar(Custom_Color, "Blue", GLUI_SCROLL_HORIZONTAL, &robotscolor[2], BLUE_COLOR, color_change_cb);

    GLUI_Listbox* Background_Color;
    Background_Color = glui->add_listbox("Background Color", &a, -1, background_color_cb);
    Background_Color->add_item(a = 0, "Black");
    Background_Color->add_item(a = 1, "White");
    Background_Color->add_item(a = 2, "Red");
    Background_Color->add_item(a = 3, "Green");
    Background_Color->add_item(a = 4, "Blue");

    glui->add_button("Exit", 0, (GLUI_Update_CB)exit);


    glui->set_main_gfx_window(main_window);
    GLUI_Master.set_glutIdleFunc(myGlutIdle);
    glutMainLoop();
    return EXIT_SUCCESS;
}
