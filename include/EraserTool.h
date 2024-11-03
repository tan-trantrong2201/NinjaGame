#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include "Tool.h"

class EraserTool : public Tool {
public:
    EraserTool(PaintApp* app);
    void onMouseDown(float x, float y) override;
    void onMouseUp(float x, float y) override;
    void onMouseMove(float x, float y) override;
    void draw() override;
private:
    std::vector<std::pair<float, float>> eraserPoints;
    bool isErasing;
};

#endif // ERASERTOOL_H
