#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "Tool.h"

class CircleTool : public Tool {
public:
    CircleTool(PaintApp* app);
    void onMouseDown(float x, float y) override;
    void onMouseUp(float x, float y) override;
    void onMouseMove(float x, float y) override;
    void draw() override;
private:
    std::vector<std::pair<float, float>> circlePoints;
    float centerX, centerY;
    bool isCircling;
    const float PI = 3.14159265358979323846f;
};

#endif // CIRCLETOOL_H
