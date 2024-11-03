#include "RectangleTool.h"
#include "PaintApp.h"

RectangleTool::RectangleTool(PaintApp* app)
    : Tool(app), isDrawingRect(false) {
}

void RectangleTool::onMouseDown(float x, float y) {
    rectPoints.clear();
    rectPoints.push_back(std::make_pair(x, y));
    rectPoints.push_back(std::make_pair(x, y));
    rectPoints.push_back(std::make_pair(x, y));
    rectPoints.push_back(std::make_pair(x, y));
    rectPoints.push_back(std::make_pair(x, y));
    isDrawingRect = true;
}

void RectangleTool::onMouseUp(float x, float y) {
    isDrawingRect = false;
    rectPoints[1].first = rectPoints[0].first;
    rectPoints[1].second = y;
    rectPoints[2].first = x;
    rectPoints[2].second = y;
    rectPoints[3].first = x;
    rectPoints[3].second = rectPoints[0].second;
    rectPoints[4].first = rectPoints[0].first;
    rectPoints[4].second = rectPoints[0].second;

    auto tempPoints = rectPoints;
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
}

void RectangleTool::onMouseMove(float x, float y) {
    if (isDrawingRect) {
        rectPoints[1].first = rectPoints[0].first;
        rectPoints[1].second = y;
        rectPoints[2].first = x;
        rectPoints[2].second = y;
        rectPoints[3].first = x;
        rectPoints[3].second = rectPoints[0].second;
        rectPoints[4].first = rectPoints[0].first;
        rectPoints[4].second = rectPoints[0].second;
    }
}

void RectangleTool::draw() {
    if (isDrawingRect) {
        auto color = app->getCurrentColor();
        glColor3f(color[0], color[1], color[2]);
        glLineWidth(2.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& point : rectPoints) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
    }
}
