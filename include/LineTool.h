#ifndef LINETOOL_H
#define LINETOOL_H

#include "Tool.h"

class LineTool : public Tool {
public:
    LineTool(PaintApp* app);
    void onMouseDown(float x, float y) override;
    void onMouseUp(float x, float y) override;
    void onMouseMove(float x, float y) override;
    void draw() override;
private:
    std::vector<std::pair<float, float>> linePoints;
    bool isLining;
};

#endif // LINETOOL_H
