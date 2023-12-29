#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
#include <windows.h> 
#define COLUMNS 40
#define ROWS 40
#define FPS 10
#define RIGHT 2
#define DOWN -1
#define UP 1
#define LEFT -2
#define MAX 60
int score = 0;
bool gameOver = false;
using namespace std;

short sDirection = RIGHT;
int posX[60] = { 20,20,20,20,20 }, posY[60] = { 20,19,18,17,16 };
int snake_length = 5;
int gridX, gridY;
bool food = true;
int foodX, foodY;

void randomFood() {
    int maxX = gridX - 2;
    int maxY = gridY - 2;
    int minX = 1;
    srand(time(NULL));
    foodX = minX + rand() % (maxX - minX);
    foodY = minX + rand() % (maxY - minX);
}

void drawFood() {
    if (food) {
        randomFood();
        food = false;
    }
    glColor3f(1.0, 0.0, 0.0);
    glRectf(foodX, foodY, foodX + 1.0, foodY + 1.0);
}

void drawSnake() {
    for (int i = snake_length - 1; i > 0; i--) {
        posX[i] = posX[i - 1];
        posY[i] = posY[i - 1];
    }

    if (sDirection == UP)
        posY[0]++;
    else if (sDirection == DOWN)
        posY[0]--;
    else if (sDirection == RIGHT)
        posX[0]++;
    else if (sDirection == LEFT)
        posX[0]--;

   
    for (int i = 1; i < snake_length; i++) {
        if (posX[0] == posX[i] && posY[0] == posY[i]) {
            gameOver = true;
            return;
        }
    }

    for (int i = 0; i < snake_length; i++) {
        if (i == 0)
            glColor3f(0.0, 1.0, 0.0);
        else
            glColor3f(0.0, 0.0, 1.0);
        glRectd(posX[i], posY[i], posX[i] + 1.0, posY[i] + 1.0);
    }

    if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
        gameOver = true;

    if (posX[0] == foodX && posY[0] == foodY) {
        score++;
        snake_length++;
        if (snake_length > MAX)
            snake_length = MAX;
        food = true;
    }
}


void keyboard(int key, int, int) {
    switch (key) {
    case GLUT_KEY_UP:
        if (sDirection != DOWN)
            sDirection = UP;
        break;
    case GLUT_KEY_DOWN:
        if (sDirection != UP)
            sDirection = DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if (sDirection != LEFT)
            sDirection = RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if (sDirection != RIGHT)
            sDirection = LEFT;
        break;
    }
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

void unit(int x, int y) {
    if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) {
        glLineWidth(3.0);
        glColor3f(1.0, 0.0, 0.0);
    }
    else {
        glLineWidth(1.0);
        glColor3f(1.0, 1.0, 1.0);
    }
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 1.0, y);
    glVertex2f(x + 1.0, y + 1.0);
    glVertex2f(x, y + 1.0);
    glEnd();
}

void initGrid(int x, int y) {
    gridX = x;
    gridY = y;
}

void drawGrid() {
    for (int x = 0; x < gridX; x++) {
        for (int y = 0; y < gridY; y++) {
            unit(x, y);
        }
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    drawFood();
    glutSwapBuffers();
    if (gameOver) {
        wchar_t score_str[20];
        swprintf(score_str, 20, L"Your Score: %d", score);
        MessageBox(NULL, score_str, L"Game Over", MB_OK);
        exit(0);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initGrid(COLUMNS, ROWS);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Snake Game ");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
