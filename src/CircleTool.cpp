#include "CircleTool.h"
#include "PaintApp.h"
#include <cmath>

CircleTool::CircleTool(PaintApp* app)
    : Tool(app), isCircling(false) {
}

void CircleTool::onMouseDown(float x, float y) {
    centerX = x;
    centerY = y;
    isCircling = true;
}

void CircleTool::onMouseUp(float x, float y) {
    isCircling = false;
    auto tempPoints = circlePoints;
    auto color = app->getCurrentColor();
    app->getFunctionsToCall()->push_back([tempPoints, color]() {
        glColor3f(color[0], color[1], color[2]);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        for (const auto& point : tempPoints) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
        });
    circlePoints.clear();
}

void CircleTool::onMouseMove(float x, float y) {
    if (isCircling) {
        circlePoints.clear();
        float radius = sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y));
        int segments = 100;
        for (int i = 0; i < segments; i++) {
            float theta = 2.0f * PI * float(i) / float(segments);
            float dx = radius * cos(theta);
            float dy = radius * sin(theta);
            circlePoints.push_back(std::make_pair(centerX + dx, centerY + dy));
        }
    }
}

void CircleTool::draw() {
    if (isCircling) {
        auto color = app->getCurrentColor();
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_LINE_LOOP);
        for (const auto& point : circlePoints) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
    }
}
