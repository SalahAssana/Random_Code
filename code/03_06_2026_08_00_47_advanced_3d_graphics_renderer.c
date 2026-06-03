#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>

// Define some constants
#define WIDTH 800
#define HEIGHT 600
#define DEPTH 500
#define RADIUS 200

void display() {
    // Clear the screen and set up the view
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (double)WIDTH / HEIGHT, 0.1, DEPTH);

    // Draw the axes
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(-RADIUS, -RADIUS, -RADIUS); glVertex3f(RADIUS, -RADIUS, -RADIUS);
    glColor3f(0, 1, 0); glVertex3f(-RADIUS, -RADIUS, -RADIUS); glVertex3f(-RADIUS, RADIUS, -RADIUS);
    glColor3f(0, 0, 1); glVertex3f(-RADIUS, -RADIUS, -RADIUS); glVertex3f(-RADIUS, -RADIUS, RADIUS);
    glEnd();

    // Draw the sphere
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 360; i += 10) {
        float theta = (float)i * M_PI / 180;
        float x = RADIUS * cos(theta);
        float y = RADIUS * sin(theta);

        glVertex3f(x, y, 0);
    }
    glEnd();

    // Swap the buffers to show the result
    glFlush();
}

void reshape(int w, int h) {
    // Set up the view based on the new window size
    glViewport(0, 0, w, h);

    // Set up the projection matrix again
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (double)w / h, 0.1, DEPTH);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            // Rotate the sphere
            glRotatef(10, 0, 1, 0);
            break;
        case 'z':
            // Zoom in or out
            if (glGetDoublev(GL_MODELVIEW_MATRIX, &m[0][0]) > 0.5) {
                glScalef(0.9, 0.9, 0.9);
            } else {
                glScalef(1.1, 1.1, 1.1);
            }
            break;
        default:
            // Do nothing
    }

    // Redraw the scene
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Initialize GLUT and set up the view
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("3D Graphics Renderer");
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    // Register the display and reshape functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    // Start the event loop
    glutMainLoop();

    return 0;
}