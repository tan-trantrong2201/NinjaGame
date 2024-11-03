#ifndef PENCILTOOL_H
#define PENCILTOOL_H

#include "Tool.h"

class PencilTool : public Tool {
public:
    PencilTool(PaintApp* app);
    void onMouseDown(float x, float y) override;
    void onMouseUp(float x, float y) override;
    void onMouseMove(float x, float y) override;
    void draw() override;
private:
    std::vector<std::pair<float, float>> points;
    bool isDrawing;
};

#endif // PENCILTOOL_H
