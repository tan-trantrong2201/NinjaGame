#include "ColorPicker.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

ColorPicker::ColorPicker() {
    currentColor[0] = 0.0f;
    currentColor[1] = 0.0f;
    currentColor[2] = 0.0f;
}

void ColorPicker::draw() {
    // Vẽ hình tròn màu sắc
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1.0, 2.0, -1.0, 1.0, -1.0, 1.0); // Mở rộng không gian để vẽ color picker
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(1.51f, 0.3f, 0.0f);

    // Vẽ vòng tròn nền
    glColor3f(0.31f, 0.31f, 0.31f);
    drawCircle(0.0f, 0.0f, 0.28f, 100);

    // Vẽ các màu sắc
    glPushMatrix();
    glScalef(0.25f, 0.25f, 0.25f);
    GLfloat colors[30][3] = {
        {0.0f, 0.0f, 0.0f},
        {0.498f, 0.498f, 0.498f},
        {1.0f, 1.0f, 1.0f},

        {0.388f, 0.102f, 0.102f},
        {1.0f, 0.0f, 0.0f},
        {0.968f, 0.388f, 0.388f},

        {0.588f, 0.012f, 0.263f},
        {0.961f, 0.192f, 0.525f},
        {0.961f, 0.549f, 0.725f},

        {0.290f, 0.208f, 0.137f},
        {0.988f, 0.467f, 0.012f},
        {0.918f, 0.639f, 0.396f},

        {0.4f, 0.345f, 0.063f},
        {1.0f, 1.0f, 0.0f},
        {0.98f, 0.98f, 0.518f},

        {0.082f, 0.322f, 0.082f},
        {0.38f, 0.569f, 0.38f},
        {0.0f, 1.0f, 0.0f},

        {0.047f, 0.047f, 0.678f},
        {0.169f, 0.0f, 1.0f},
        {0.525f, 0.455f, 0.89f},

        {0.376f, 0.075f, 0.529f},
        {0.659f, 0.0f, 0.988f},
        {0.827f, 0.478f, 1.0f},

        {0.439f, 0.329f, 0.8f},
        {0.631f, 0.545f, 0.91f},
        {1.118f, 0.686f, 0.871f},

        {0.0f, 0.816f, 1.0f},
        {0.0f, 1.169f, 1.0f},
        {0.0f, 1.0f, 1.0f},
    };

    for (int i = 0; i < 10; i++) {
        glPushMatrix();
        glRotatef(static_cast<float>(i) * 36.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 0.1f, 0.0f);
        int j = i * 3;

        // Vẽ phần màu thứ nhất
        glBegin(GL_POLYGON);
        glColor3f(colors[j][0], colors[j][1], colors[j][2]);
        glVertex2f(0.5f / 7, 1.0f / 7);
        glVertex2f(1.0f / 7, 2.3f / 7);
        glVertex2f(-1.0f / 7, 2.3f / 7);
        glVertex2f(-0.5f / 7, 1.0f / 7);
        glEnd();

        // Vẽ phần màu thứ hai
        glBegin(GL_POLYGON);
        glColor3f(colors[j + 1][0], colors[j + 1][1], colors[j + 1][2]);
        glVertex2f(1.0f / 7, 2.3f / 7);
        glVertex2f(1.0f / 7, 4.3f / 7);
        glVertex2f(-1.0f / 7, 4.3f / 7);
        glVertex2f(-1.0f / 7, 2.3f / 7);
        glEnd();

        // Vẽ phần màu thứ ba
        glBegin(GL_POLYGON);
        glColor3f(colors[j + 2][0], colors[j + 2][1], colors[j + 2][2]);
        glVertex2f(1.0f / 7, 4.3f / 7);
        glVertex2f(0.0f / 7, 6.6f / 7);
        glVertex2f(-1.0f / 7, 4.3f / 7);
        glEnd();

        glPopMatrix();
    }

    glPopMatrix();
    glPopMatrix();

    // Phục hồi ma trận chiếu
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

bool ColorPicker::isInside(float x, float y) {
    // Kiểm tra xem tọa độ có nằm trong vùng color picker không
    return (x >= 0.64f && x <= 0.995f) && (y >= 0.0f && y <= 0.6f);
}

void ColorPicker::pickColor(int x, int y) {
    glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 1, 1, GL_RGB, GL_FLOAT, currentColor);
}

void ColorPicker::setCurrentColor(float r, float g, float b) {
    currentColor[0] = r;
    currentColor[1] = g;
    currentColor[2] = b;
}

float* ColorPicker::getCurrentColor() {
    return currentColor;
}

// Hàm vẽ hình tròn
void ColorPicker::drawCircle(float centerX, float centerY, float radius, int numSegments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.2f, 0.49f, 0.49f);
    glVertex2f(centerX, centerY); // Center vertex
    for (int i = 0; i <= numSegments; i++) {
        float theta = 2.0f * 3.14159265358979323846f * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}
