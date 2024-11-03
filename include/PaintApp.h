#ifndef PAINTAPP_H
#define PAINTAPP_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <functional>
#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>

#include "Tool.h"
#include "PencilTool.h"
#include "EraserTool.h"
#include "LineTool.h"
#include "RectangleTool.h"
#include "CircleTool.h"
#include "ColorPicker.h"
#include "UIManager.h"

class PaintApp {
public:
    PaintApp(int argc, char** argv);
    void run();

    // Callback functions
    static void displayWrapper();
    static void keyboardWrapper(unsigned char key, int x, int y);
    static void mouseClickWrapper(int button, int state, int x, int y);
    static void mouseMotionWrapper(int x, int y);
    static void passiveMouseMotionWrapper(int x, int y);

    // Get current color
    float* getCurrentColor();

    // Get functions to call
    std::vector<std::function<void()>>* getFunctionsToCall();

    // Tools (make them public for access in UIManager)
    PencilTool pencilTool;
    EraserTool eraserTool;
    LineTool lineTool;
    RectangleTool rectangleTool;
    CircleTool circleTool;

private:
    // Member variables
    std::vector<std::function<void()>> functionsToCall;

    // Current tool
    Tool* currentTool;

    // UI Manager
    UIManager uiManager;

    // Color Picker
    ColorPicker colorPicker;

    // Member functions
    void display();
    void keyboard(unsigned char key, int x, int y);
    void handleMouseClick(int button, int state, int x, int y);
    void handleMouseMotion(int x, int y);
    void passiveMouseMotion(int x, int y);

    // Singleton instance
    static PaintApp* instance;

    // Get instance
    static PaintApp* getInstance();
};

#endif // PAINTAPP_H
