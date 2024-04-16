#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

// Globals
int windowWidth = 800;
int windowHeight = 600;
float rotationX = 0.0f;
float rotationY = 0.0f;
float translationX = 0.0f;
float translationY = 0.0f;
float scale = 1.0f;

// Trackball variables
bool isDragging = false;
int prevMouseX = 0;
int prevMouseY = 0;

// Function to handle mouse drag events for trackball rotation
void mouseMotion(int x, int y) {
    if (isDragging) {
        int deltaX = x - prevMouseX;
        int deltaY = y - prevMouseY;

        rotationY += deltaX;
        rotationX += deltaY;

        prevMouseX = x;
        prevMouseY = y;

        glutPostRedisplay();
    }
}

// Function to handle mouse click events
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isDragging = true;
        prevMouseX = x;
        prevMouseY = y;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        isDragging = false;
    }
}

// Function to handle keyboard events
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0);
            break;
        case 'w':
            translationY += 0.1f;
            break;
        case 's':
            translationY -= 0.1f;
            break;
        case 'a':
            translationX -= 0.1f;
            break;
        case 'd':
            translationX += 0.1f;
            break;
        case '+':
            scale += 0.1f;
            break;
        case '-':
            scale -= 0.1f;
            break;
    }
    glutPostRedisplay();
}

// Function to draw the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(translationX, translationY, 0.0f);
    glScalef(scale, scale, scale);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);

    // Draw your scene here
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL Trackball Example");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
