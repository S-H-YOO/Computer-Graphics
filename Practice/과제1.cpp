#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>// <- 추가할 부분 

GLint mouseX = 0; // <- 추가할 부분
GLint mouseY = 0; // <- 추가할 부분
GLint mouseState = 0; // <- 추가할 부분
GLint mouseButton = 0; // <- 추가할 부분
GLfloat xTheta = 0.0, yTheta = 0.0; // <- 추가할 부분
GLfloat scale = 1.0, scaleDelta = 1.01; // <- 추가할 부분


static int rshoulder = 0, lshoulder = 0, relbow = 0, lelbow = 0, lupperleg = 0, rupperleg = 0, llowerleg = 0, rlowerleg = 0;
static int wireframe = 0;


void display() {

    GLfloat light1Pos[] = { -200.0, 200.0, 300.0, 0.0 };
    GLfloat light2Pos[] = { 0.0, 1.0, 0.0, 0.0 };
    GLfloat grayColor[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);                          // 조명 사용 

    glLightfv(GL_LIGHT0, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grayColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
    glEnable(GL_LIGHT0);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);  // 카메라를 뒤로 이동하여 전체 로봇을 볼 수 있게 합니다.

    glRotatef(xTheta, 1.0, 0.0, 0.0);  // y축을 기준으로 회전
    glRotatef(yTheta, 0.0, 1.0, 0.0);  // x축을 기준으로 회전
    glScalef(scale, scale, scale); // <- 추가할 부분


    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    GLfloat materialColor[4];

    if (wireframe) {
        // 머리 그리기 (노란색 구체)
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0);  // 머리 위치 조정
        glutWireSphere(0.6, 20, 20);  // 구체 그리기
        glPopMatrix();

        // 몸통 그리기 (파란색 큐브)
        materialColor[0] = 0.0; materialColor[1] = 0.0; materialColor[2] = 1.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glScalef(1.8, 2.6, 0.5);  // 몸통 크기 조정
        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();

        // 오른쪽 팔 그리기
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glPushMatrix();
        glTranslatef(0.4, 1.3, 0.0);  // 팔 위치 조정
        glRotatef((GLfloat)rshoulder, 1.0, 0.0, 0.0);  // 어깨 회전
        glTranslatef(0.75, -0.8, 0.0);  // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 팔 크기 조정
        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();

        // 오른쪽 팔꿈치
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(-0.75, -0.8, 0.0);

        glRotatef((GLfloat)relbow, 1.0, 0.0, 0.0);  // 팔꿈치 회전
        glTranslatef(0.75, -0.7, 0.0);  // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 손 크기 조정
        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 팔 그리기 
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(-0.4, 1.3, 0.0);  // 팔 위치 조정
        glRotatef((GLfloat)lshoulder, 1.0, 0.0, 0.0);  // 어깨 회전
        glTranslatef(-0.75, -0.8, 0.0);  // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 팔 크기 조정
        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();

        // 왼쪽 팔꿈치 그리기 
        glTranslatef(0.75, -0.8, 0.0);  // 팔꿈치 위치 조정
        glRotatef((GLfloat)lelbow, 1.0, 0.0, 0.0);  // 팔꿈치 회전
        glTranslatef(-0.75, -0.7, 0.0);  // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 손 크기 조정
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 위다리 그리기
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.25, -1.3, 0.0);  // 다리 위치 조정
        glRotatef((GLfloat)lupperleg, 1.0, 0.0, 0.0);  // 다리 회전
        glTranslatef(-0.75, -0.75, 0.0);  // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 다리 크기 조정
        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();

        // 왼쪽 아래다리 그리기 
        glTranslatef(0.75, -0.8, 0.0);  // 아래다리 위치 조정
        glRotatef((GLfloat)llowerleg, 1.0, 0.0, 0.0);  // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);  // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 아래다리 크기 조정
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();
        glPopMatrix();

        // 오른쪽 위다리 그리기
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.55, -1.3, 0.0);  // 다리 위치 조정
        glRotatef((GLfloat)rupperleg, 1.0, 0.0, 0.0);  // 다리 회전
        glTranslatef(0.0, -0.75, 0.0);  // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 다리 크기 조정
        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();

        // 오른쪽 아래다리 그리기 
        glTranslatef(0.75, -0.8, 0.0);  // 아래다리 위치 조정
        glRotatef((GLfloat)rlowerleg, 1.0, 0.0, 0.0);  // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);  // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 아래다리 크기 조정
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0);  // 큐브 그리기
        glPopMatrix();
        glPopMatrix();


        glutSwapBuffers();
    }

    else {
        // 머리 그리기 (노란색 구체)
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0);  // 머리 위치 조정
        glutSolidSphere(0.6, 20, 20);  // 구체 그리기
        glPopMatrix();

        // 몸통 그리기 (파란색 큐브)
        materialColor[0] = 0.0; materialColor[1] = 0.0; materialColor[2] = 1.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glScalef(1.8, 2.6, 0.5);  // 몸통 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 오른쪽 팔 그리기
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glPushMatrix();
        glTranslatef(0.4, 1.3, 0.0);  // 팔 위치 조정
        glRotatef((GLfloat)rshoulder, 1.0, 0.0, 0.0);  // 어깨 회전
        glTranslatef(0.75, -0.8, 0.0);  // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 팔 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 오른쪽 팔꿈치
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(-0.75, -0.8, 0.0);

        glRotatef((GLfloat)relbow, 1.0, 0.0, 0.0);  // 팔꿈치 회전
        glTranslatef(0.75, -0.7, 0.0);  // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 손 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 팔 그리기 
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(-0.4, 1.3, 0.0);  // 팔 위치 조정
        glRotatef((GLfloat)lshoulder, 1.0, 0.0, 0.0);  // 어깨 회전
        glTranslatef(-0.75, -0.8, 0.0);  // 팔 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 팔 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 왼쪽 팔꿈치 그리기 
        glTranslatef(0.75, -0.8, 0.0);  // 팔꿈치 위치 조정
        glRotatef((GLfloat)lelbow, 1.0, 0.0, 0.0);  // 팔꿈치 회전
        glTranslatef(-0.75, -0.7, 0.0);  // 손 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 손 크기 조정
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // 왼쪽 위다리 그리기
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.25, -1.3, 0.0);  // 다리 위치 조정
        glRotatef((GLfloat)lupperleg, 1.0, 0.0, 0.0);  // 다리 회전
        glTranslatef(-0.75, -0.75, 0.0);  // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 다리 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 왼쪽 아래다리 그리기 
        glTranslatef(0.75, -0.8, 0.0);  // 아래다리 위치 조정
        glRotatef((GLfloat)llowerleg, 1.0, 0.0, 0.0);  // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);  // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 아래다리 크기 조정
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // 오른쪽 위다리 그리기
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.55, -1.3, 0.0);  // 다리 위치 조정
        glRotatef((GLfloat)rupperleg, 1.0, 0.0, 0.0);  // 다리 회전
        glTranslatef(0.0, -0.75, 0.0);  // 다리 중심 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 다리 크기 조정
        glutSolidCube(1.0);
        glPopMatrix();

        // 오른쪽 아래다리 그리기 
        glTranslatef(0.75, -0.8, 0.0);  // 아래다리 위치 조정
        glRotatef((GLfloat)rlowerleg, 1.0, 0.0, 0.0);  // 무릎 회전
        glTranslatef(-0.75, -0.7, 0.0);  // 아래다리 위치 이동
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // 아래다리 크기 조정
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();


        glutSwapBuffers();



    }
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {

    case 'w':  // 솔리드 모드
        wireframe = 0;
        break;
    case 'W':  // 와이어프레임 모드
        wireframe = 1;
        break;

    case 'a':                   // 왼쪽 아래 다리 상승
        llowerleg = (llowerleg + 5) % 360;
        break;
    case 'z':                   // 왼쪽 아래 다리 하강
        llowerleg = (llowerleg - 5) % 360;
        break;
    case 's':
        lupperleg = (lupperleg + 5) % 360;
        break;
    case 'x':
        lupperleg = (lupperleg - 5) % 360;
        break;
    case 'd':
        lelbow = (lelbow + 5) % 360;
        break;
    case 'c':
        lelbow = (lelbow - 5) % 360;
        break;
    case 'f':
        lshoulder = (lshoulder + 5) % 360;
        break;
    case 'v':
        lshoulder = (lshoulder - 5) % 360;
        break;

    case 'n':
        rshoulder = (rshoulder - 5) % 360;
        break;
    case 'j':
        rshoulder = (rshoulder + 5) % 360;
        break;
    case 'm':
        relbow = (relbow - 5) % 360;
        break;
    case 'k':
        relbow = (relbow + 5) % 360;
        break;
    case ',':
        rupperleg = (rupperleg - 5) % 360;
        break;
    case 'l':
        rupperleg = (rupperleg + 5) % 360;
        break;
    case '.':
        rlowerleg = (rlowerleg - 5) % 360;
        break;
    case ';':
        rlowerleg = (rlowerleg + 5) % 360;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void init(void) {
    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 활성화
    glEnable(GL_LIGHTING);    // 조명 활성화
    glEnable(GL_LIGHT0);      // 하나의 조명 활성화

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  // 조명 위치
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat white_light[] = { 1.0, 1.0, 0.0, 0.0 };     // 백색 광원
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    glClearColor(0.0, 0.0, 0.0, 1.0);  // 배경색 설정
    glShadeModel(GL_SMOOTH);
}

void myMouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseState = state;
        mouseButton = btn;
        mouseX = x;
        mouseY = y;
    }
    else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        mouseState = state;
        mouseButton = btn;
        mouseX = x;
        mouseY = y;
    }
    else if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        xTheta = yTheta = 0.0;
        scale = 1.0;
    }
    else return;

    glutPostRedisplay();
}

void myMotion(int x, int y)
{
    if (mouseButton == GLUT_LEFT_BUTTON) {
        yTheta -= (GLfloat)(mouseX - x);
        xTheta -= (GLfloat)(mouseY - y);
    }

    else if (mouseButton == GLUT_RIGHT_BUTTON) {
        if (mouseY != y)
            scale = scale * pow((double)scaleDelta, (double)(mouseY - y));
    }
    else return;

    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Arm");
    init();
    glEnable(GL_DEPTH_TEST); // <- 추가할 부분
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myMouse); // <- 추가할 부분
    glutMotionFunc(myMotion); // <- 추가할 부분

    glutMainLoop();
    return 0;
}
