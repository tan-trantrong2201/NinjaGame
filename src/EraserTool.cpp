#include "EraserTool.h"
#include "PaintApp.h"

EraserTool::EraserTool(PaintApp* app)
    : Tool(app), isErasing(false) {
}

void EraserTool::onMouseDown(float x, float y) {
    eraserPoints.push_back(std::make_pair(x, y));
    isErasing = true;
}

void EraserTool::onMouseUp(float x, float y) {
    isErasing = false;
    auto tempPoints = eraserPoints;
    app->getFunctionsToCall()->push_back([tempPoints]() {
        glColor3f(1.0f, 1.0f, 1.0f);
        glPointSize(20.0f);
        glBegin(GL_POINTS);
        for (const auto& point : tempPoints) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
        });
    eraserPoints.clear();
}

void EraserTool::onMouseMove(float x, float y) {
    if (isErasing) {
        eraserPoints.push_back(std::make_pair(x, y));
    }
}

void EraserTool::draw() {
    if (isErasing) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glPointSize(20.0f);
        glBegin(GL_POINTS);
        for (const auto& point : eraserPoints) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
    }
}
