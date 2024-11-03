#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "Tool.h"

class RectangleTool : public Tool {
public:
    RectangleTool(PaintApp* app);
    void onMouseDown(float x, float y) override;
    void onMouseUp(float x, float y) override;
    void onMouseMove(float x, float y) override;
    void draw() override;
private:
    std::vector<std::pair<float, float>> rectPoints;
    bool isDrawingRect;
};

#endif // RECTANGLETOOL_H
