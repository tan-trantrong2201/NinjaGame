#include "PencilTool.h"
#include "PaintApp.h"

PencilTool::PencilTool(PaintApp* app)
    : Tool(app), isDrawing(false) {
}

void PencilTool::onMouseDown(float x, float y) {
    points.push_back(std::make_pair(x, y));
    isDrawing = true;
}

void PencilTool::onMouseUp(float x, float y) {
    isDrawing = false;
    auto tempPoints = points;
    auto color = app->getCurrentColor();
    app->getFunctionsToCall()->push_back([tempPoints, color]() {
        glColor3f(color[0], color[1], color[2]);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& point : tempPoints) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
        });
    points.clear();
}

void PencilTool::onMouseMove(float x, float y) {
    if (isDrawing) {
        points.push_back(std::make_pair(x, y));
    }
}

void PencilTool::draw() {
    if (isDrawing) {
        auto color = app->getCurrentColor();
        glColor3f(color[0], color[1], color[2]);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& point : points) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
    }
}
