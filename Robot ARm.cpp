#include <stdlib.h>
#include <gl/glut.h>
static int rshoulder = 0, lshoulder = 0, relbow = 0, lelbow = 0, lupperleg = 0, rupperleg = 0, llowerleg = 0, rlowerleg = 0;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glScalef(1.0, 3.0, 1.0);
    glutWireCube(1.0);
    glPushMatrix();

    // Pivot ���� �� ��ü �̵�
    glTranslatef(-1.0, 0.0, 0.0);
    // ������ �������� ȸ��
    glRotatef((GLfloat)rshoulder, 0.0, 0.0, 1.0);
    // Pivot���� ������ ��ġ�� �������� �̵�
    glTranslatef(1.0, 0.0, 0.0);
    // ������ �������� ��ü ���� �� ���/Ȯ��
    glPushMatrix();
    glColor3f(2.0, 0.0, 0.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Pivot ���� �� ��ü �̵�
    glTranslatef(1.0, 0.0, 0.0);                            // x�� ���� 0.0���� �ٲٸ� elbow�� ���� ���� �������� ���ư�
    // ������ �������� ȸ��
    glRotatef((GLfloat)relbow, 0.0, 0.0, 1.0);
    // Pivot���� ������ ��ġ�� �������� �̵�
    glTranslatef(1.0, 0.0, 0.0);                            // x�� ���� 0.0���� �ٲٸ� elbow�� ��� ���� �������� ���ư� 
    // ������ �������� ��ü ���� �� ���/Ȯ��
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    /*
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glScalef(0.4, 0.4, 1.0);
    glutWireCube(1.0);

    glPopMatrix();
    */
    glPopMatrix();


    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 's':
        lshoulder = (lshoulder + 5) % 360;
        break;
    case 'S':
        lshoulder = (lshoulder - 5) % 360;
        break;
    case 'e':
        lelbow = (lelbow + 5) % 360;
        break;
    case 'E':
        lelbow = (lelbow - 5) % 360;
        break;
/*
    case 'h':
        hand = (hand + 5) % 360;
        break;
    case 'H':
        hand = (hand - 5) % 360;
        break;
        */
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-100, 100, -100, 100, -1.0, -1.0);

    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glOrtho(-400, 400, -300, 300, -10.0, 1.0);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Arm");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
