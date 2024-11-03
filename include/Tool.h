#ifndef TOOL_H
#define TOOL_H

#include <vector>
#include <utility>
#include <functional>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class PaintApp;

class Tool {
public:
    Tool(PaintApp* app);
    virtual void onMouseDown(float x, float y) = 0;
    virtual void onMouseUp(float x, float y) = 0;
    virtual void onMouseMove(float x, float y) = 0;
    virtual void draw() = 0;
protected:
    PaintApp* app;
};

#endif // TOOL_H
