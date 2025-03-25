#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>// <- �߰��� �κ� 

GLint mouseX = 0; // <- �߰��� �κ�
GLint mouseY = 0; // <- �߰��� �κ�
GLint mouseState = 0; // <- �߰��� �κ�
GLint mouseButton = 0; // <- �߰��� �κ�
GLfloat xTheta = 0.0, yTheta = 0.0; // <- �߰��� �κ�
GLfloat scale = 1.0, scaleDelta = 1.01; // <- �߰��� �κ�


static int rshoulder = 0, lshoulder = 0, relbow = 0, lelbow = 0, lupperleg = 0, rupperleg = 0, llowerleg = 0, rlowerleg = 0;
static int wireframe = 0;


void display() {

    GLfloat light1Pos[] = { -200.0, 200.0, 300.0, 0.0 };
    GLfloat light2Pos[] = { 0.0, 1.0, 0.0, 0.0 };
    GLfloat grayColor[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);                          // ���� ��� 

    glLightfv(GL_LIGHT0, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grayColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
    glEnable(GL_LIGHT0);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);  // ī�޶� �ڷ� �̵��Ͽ� ��ü �κ��� �� �� �ְ� �մϴ�.

    glRotatef(xTheta, 1.0, 0.0, 0.0);  // y���� �������� ȸ��
    glRotatef(yTheta, 0.0, 1.0, 0.0);  // x���� �������� ȸ��
    glScalef(scale, scale, scale); // <- �߰��� �κ�


    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    GLfloat materialColor[4];

    if (wireframe) {
        // �Ӹ� �׸��� (����� ��ü)
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0);  // �Ӹ� ��ġ ����
        glutWireSphere(0.6, 20, 20);  // ��ü �׸���
        glPopMatrix();

        // ���� �׸��� (�Ķ��� ť��)
        materialColor[0] = 0.0; materialColor[1] = 0.0; materialColor[2] = 1.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glScalef(1.8, 2.6, 0.5);  // ���� ũ�� ����
        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();

        // ������ �� �׸���
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glPushMatrix();
        glTranslatef(0.4, 1.3, 0.0);  // �� ��ġ ����
        glRotatef((GLfloat)rshoulder, 1.0, 0.0, 0.0);  // ��� ȸ��
        glTranslatef(0.75, -0.8, 0.0);  // �� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();

        // ������ �Ȳ�ġ
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(-0.75, -0.8, 0.0);

        glRotatef((GLfloat)relbow, 1.0, 0.0, 0.0);  // �Ȳ�ġ ȸ��
        glTranslatef(0.75, -0.7, 0.0);  // �� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();
        glPopMatrix();

        // ���� �� �׸��� 
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(-0.4, 1.3, 0.0);  // �� ��ġ ����
        glRotatef((GLfloat)lshoulder, 1.0, 0.0, 0.0);  // ��� ȸ��
        glTranslatef(-0.75, -0.8, 0.0);  // �� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();

        // ���� �Ȳ�ġ �׸��� 
        glTranslatef(0.75, -0.8, 0.0);  // �Ȳ�ġ ��ġ ����
        glRotatef((GLfloat)lelbow, 1.0, 0.0, 0.0);  // �Ȳ�ġ ȸ��
        glTranslatef(-0.75, -0.7, 0.0);  // �� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();
        glPopMatrix();

        // ���� ���ٸ� �׸���
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.25, -1.3, 0.0);  // �ٸ� ��ġ ����
        glRotatef((GLfloat)lupperleg, 1.0, 0.0, 0.0);  // �ٸ� ȸ��
        glTranslatef(-0.75, -0.75, 0.0);  // �ٸ� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �ٸ� ũ�� ����
        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();

        // ���� �Ʒ��ٸ� �׸��� 
        glTranslatef(0.75, -0.8, 0.0);  // �Ʒ��ٸ� ��ġ ����
        glRotatef((GLfloat)llowerleg, 1.0, 0.0, 0.0);  // ���� ȸ��
        glTranslatef(-0.75, -0.7, 0.0);  // �Ʒ��ٸ� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �Ʒ��ٸ� ũ�� ����
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();
        glPopMatrix();

        // ������ ���ٸ� �׸���
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.55, -1.3, 0.0);  // �ٸ� ��ġ ����
        glRotatef((GLfloat)rupperleg, 1.0, 0.0, 0.0);  // �ٸ� ȸ��
        glTranslatef(0.0, -0.75, 0.0);  // �ٸ� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �ٸ� ũ�� ����
        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();

        // ������ �Ʒ��ٸ� �׸��� 
        glTranslatef(0.75, -0.8, 0.0);  // �Ʒ��ٸ� ��ġ ����
        glRotatef((GLfloat)rlowerleg, 1.0, 0.0, 0.0);  // ���� ȸ��
        glTranslatef(-0.75, -0.7, 0.0);  // �Ʒ��ٸ� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �Ʒ��ٸ� ũ�� ����
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutWireCube(1.0);  // ť�� �׸���
        glPopMatrix();
        glPopMatrix();


        glutSwapBuffers();
    }

    else {
        // �Ӹ� �׸��� (����� ��ü)
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.0, 2.0, 0.0);  // �Ӹ� ��ġ ����
        glutSolidSphere(0.6, 20, 20);  // ��ü �׸���
        glPopMatrix();

        // ���� �׸��� (�Ķ��� ť��)
        materialColor[0] = 0.0; materialColor[1] = 0.0; materialColor[2] = 1.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glScalef(1.8, 2.6, 0.5);  // ���� ũ�� ����
        glutSolidCube(1.0);
        glPopMatrix();

        // ������ �� �׸���
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glPushMatrix();
        glTranslatef(0.4, 1.3, 0.0);  // �� ��ġ ����
        glRotatef((GLfloat)rshoulder, 1.0, 0.0, 0.0);  // ��� ȸ��
        glTranslatef(0.75, -0.8, 0.0);  // �� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        glutSolidCube(1.0);
        glPopMatrix();

        // ������ �Ȳ�ġ
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glTranslatef(-0.75, -0.8, 0.0);

        glRotatef((GLfloat)relbow, 1.0, 0.0, 0.0);  // �Ȳ�ġ ȸ��
        glTranslatef(0.75, -0.7, 0.0);  // �� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // ���� �� �׸��� 
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(-0.4, 1.3, 0.0);  // �� ��ġ ����
        glRotatef((GLfloat)lshoulder, 1.0, 0.0, 0.0);  // ��� ȸ��
        glTranslatef(-0.75, -0.8, 0.0);  // �� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        glutSolidCube(1.0);
        glPopMatrix();

        // ���� �Ȳ�ġ �׸��� 
        glTranslatef(0.75, -0.8, 0.0);  // �Ȳ�ġ ��ġ ����
        glRotatef((GLfloat)lelbow, 1.0, 0.0, 0.0);  // �Ȳ�ġ ȸ��
        glTranslatef(-0.75, -0.7, 0.0);  // �� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �� ũ�� ����
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // ���� ���ٸ� �׸���
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.25, -1.3, 0.0);  // �ٸ� ��ġ ����
        glRotatef((GLfloat)lupperleg, 1.0, 0.0, 0.0);  // �ٸ� ȸ��
        glTranslatef(-0.75, -0.75, 0.0);  // �ٸ� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �ٸ� ũ�� ����
        glutSolidCube(1.0);
        glPopMatrix();

        // ���� �Ʒ��ٸ� �׸��� 
        glTranslatef(0.75, -0.8, 0.0);  // �Ʒ��ٸ� ��ġ ����
        glRotatef((GLfloat)llowerleg, 1.0, 0.0, 0.0);  // ���� ȸ��
        glTranslatef(-0.75, -0.7, 0.0);  // �Ʒ��ٸ� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �Ʒ��ٸ� ũ�� ����
        materialColor[0] = 1.0; materialColor[1] = 0.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);

        glutSolidCube(1.0);
        glPopMatrix();
        glPopMatrix();

        // ������ ���ٸ� �׸���
        materialColor[0] = 1.0; materialColor[1] = 1.0; materialColor[2] = 0.0; materialColor[3] = 1.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glPushMatrix();
        glTranslatef(0.55, -1.3, 0.0);  // �ٸ� ��ġ ����
        glRotatef((GLfloat)rupperleg, 1.0, 0.0, 0.0);  // �ٸ� ȸ��
        glTranslatef(0.0, -0.75, 0.0);  // �ٸ� �߽� �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �ٸ� ũ�� ����
        glutSolidCube(1.0);
        glPopMatrix();

        // ������ �Ʒ��ٸ� �׸��� 
        glTranslatef(0.75, -0.8, 0.0);  // �Ʒ��ٸ� ��ġ ����
        glRotatef((GLfloat)rlowerleg, 1.0, 0.0, 0.0);  // ���� ȸ��
        glTranslatef(-0.75, -0.7, 0.0);  // �Ʒ��ٸ� ��ġ �̵�
        glPushMatrix();
        glScalef(0.3, 1.5, 0.4);  // �Ʒ��ٸ� ũ�� ����
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

    case 'w':  // �ָ��� ���
        wireframe = 0;
        break;
    case 'W':  // ���̾������� ���
        wireframe = 1;
        break;

    case 'a':                   // ���� �Ʒ� �ٸ� ���
        llowerleg = (llowerleg + 5) % 360;
        break;
    case 'z':                   // ���� �Ʒ� �ٸ� �ϰ�
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
    glEnable(GL_DEPTH_TEST);  // ���� �׽�Ʈ Ȱ��ȭ
    glEnable(GL_LIGHTING);    // ���� Ȱ��ȭ
    glEnable(GL_LIGHT0);      // �ϳ��� ���� Ȱ��ȭ

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  // ���� ��ġ
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    GLfloat white_light[] = { 1.0, 1.0, 0.0, 0.0 };     // ��� ����
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    glClearColor(0.0, 0.0, 0.0, 1.0);  // ���� ����
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
    glEnable(GL_DEPTH_TEST); // <- �߰��� �κ�
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(myMouse); // <- �߰��� �κ�
    glutMotionFunc(myMotion); // <- �߰��� �κ�

    glutMainLoop();
    return 0;
}
