#ifndef COLORPICKER_H
#define COLORPICKER_H

class ColorPicker {
public:
    ColorPicker();
    void draw();
    bool isInside(float x, float y);
    void pickColor(int x, int y);
    void setCurrentColor(float r, float g, float b);
    float* getCurrentColor();

private:
    float currentColor[3];
    void drawCircle(float centerX, float centerY, float radius, int numSegments);
};

#endif // COLORPICKER_H
