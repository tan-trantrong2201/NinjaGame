#include "LineTool.h"
#include "PaintApp.h"

LineTool::LineTool(PaintApp* app)
    : Tool(app), isLining(false), linePoints(2) {
}

void LineTool::onMouseDown(float x, float y) {
    linePoints[0] = std::make_pair(x, y);
    linePoints[1] = std::make_pair(x, y);
    isLining = true;
}

void LineTool::onMouseUp(float x, float y) {
    isLining = false;
    auto tempPoints = linePoints;
    auto color = app->getCurrentColor();
    app->getFunctionsToCall()->push_back([tempPoints, color]() {
        glColor3f(color[0], color[1], color[2]);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(tempPoints[0].first, tempPoints[0].second);
        glVertex2f(tempPoints[1].first, tempPoints[1].second);
        glEnd();
        });
}

void LineTool::onMouseMove(float x, float y) {
    if (isLining) {
        linePoints[1] = std::make_pair(x, y);
    }
}

void LineTool::draw() {
    if (isLining) {
        auto color = app->getCurrentColor();
        glColor3f(color[0], color[1], color[2]);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(linePoints[0].first, linePoints[0].second);
        glVertex2f(linePoints[1].first, linePoints[1].second);
        glEnd();
    }
}
