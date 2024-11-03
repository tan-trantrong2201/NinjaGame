#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Tool.h"

class PaintApp;

class UIManager {
public:
    enum class ToolType { Pencil, Eraser, Line, Rectangle, Circle, PaintBucket };
    UIManager(PaintApp* app);
    void drawUI();
    void drawCanvas();
    void setActiveTool(ToolType tool);
    bool handleClick(float x, float y, Tool*& currentTool);
    void handleHover(float x, float y);

private:
    PaintApp* app;
    ToolType activeTool;

    struct UIButton {
        float x;
        float y;
        float width;
        float height;
        ToolType toolType;
        bool isHovering;
    };

    std::vector<UIButton> buttons;

    void initializeButtons();
    void drawButton(const UIButton& button);
    bool isPointInsideButton(float x, float y, const UIButton& button);

    // Khai báo các hàm vẽ biểu tượng
    void drawPencilIcon(float x, float y);
    void drawEraserIcon(float x, float y);
    void drawLineIcon(float x, float y);
    void drawRectangleIcon(float x, float y);
    void drawCircleIcon(float x, float y);
    void drawPaintBucketIcon(float x, float y);
};

#endif // UIMANAGER_H
