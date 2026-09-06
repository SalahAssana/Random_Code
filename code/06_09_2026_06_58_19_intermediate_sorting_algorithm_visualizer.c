#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#define WIDTH 800
#define HEIGHT 600
#define ITEMS 100

typedef struct {
    int value;
    float x, y;
} Item;

Item items[ITEMS];

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < ITEMS; i++) {
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0 - ((float)items[i].value / (ITEMS - 1)), 0.0);
        glVertex2f(items[i].x, items[i].y);
        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for (int i = 0; i < ITEMS; i++) {
            if (x > items[i].x && x < items[i].x + 10 &&
                y > items[i].y && y < items[i].y + 20) {
                printf("Clicked on item %d with value %d\n", i, items[i].value);
                break;
            }
        }
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char** argv) {
    srand(time(NULL));

    for (int i = 0; i < ITEMS; i++) {
        items[i].value = rand() % 100;
        items[i].x = (float)(i * WIDTH / ITEMS);
        items[i].y = HEIGHT - ((float)items[i].value / 99.0) * HEIGHT;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Sorting Algorithm Visualizer");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);

    while (1) {
        glutMainLoop();
    }

    return 0;
}