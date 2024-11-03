#include "UIManager.h"
#include "PaintApp.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

UIManager::UIManager(PaintApp* app)
    : app(app), activeTool(ToolType::Pencil) {
    initializeButtons();
}

void UIManager::initializeButtons() {
    // Khởi tạo các nút công cụ với tọa độ và kích thước
    buttons.push_back({ -0.94f, 0.43f, 0.06f, 0.06f, ToolType::Pencil, false });      // Nút bút chì
    buttons.push_back({ -0.88f, 0.43f, 0.06f, 0.06f, ToolType::Eraser, false });      // Nút tẩy
    buttons.push_back({ -0.94f, 0.32f, 0.06f, 0.06f, ToolType::PaintBucket, false }); // Nút thùng sơn
    buttons.push_back({ -0.88f, 0.32f, 0.06f, 0.06f, ToolType::Line, false });        // Nút vẽ đường thẳng
    buttons.push_back({ -0.94f, 0.21f, 0.06f, 0.06f, ToolType::Circle, false });      // Nút vẽ hình tròn
    buttons.push_back({ -0.88f, 0.21f, 0.06f, 0.06f, ToolType::Rectangle, false });   // Nút vẽ hình chữ nhật
}

void UIManager::drawUI() {
    // Vẽ các nút công cụ
    for (const auto& button : buttons) {
        drawButton(button);
    }
}

void UIManager::drawCanvas() {
    // Vẽ nền canvas
    glColor3f(1.0f, 1.0f, 1.0f); // Màu trắng
    glBegin(GL_QUADS);
    glVertex2f(-0.77f, -0.9f); // Góc dưới bên trái
    glVertex2f(-0.77f, 0.9f);  // Góc trên bên trái
    glVertex2f(0.63f, 0.9f);   // Góc trên bên phải
    glVertex2f(0.63f, -0.9f);  // Góc dưới bên phải
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Màu đen
    glLineWidth(4.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.77f, -0.9f); // Góc dưới bên trái
    glVertex2f(-0.77f, 0.9f);  // Góc trên bên trái
    glVertex2f(0.63f, 0.9f);   // Góc trên bên phải
    glVertex2f(0.63f, -0.9f);  // Góc dưới bên phải
    glEnd();

    glLineWidth(1.0f);
}

void UIManager::setActiveTool(ToolType tool) {
    activeTool = tool;
}

bool UIManager::handleClick(float x, float y, Tool*& currentTool) {
    for (auto& button : buttons) {
        if (isPointInsideButton(x, y, button)) {
            switch (button.toolType) {
            case ToolType::Pencil:
                currentTool = &app->pencilTool;
                activeTool = ToolType::Pencil;
                break;
            case ToolType::Eraser:
                currentTool = &app->eraserTool;
                activeTool = ToolType::Eraser;
                break;
            case ToolType::Line:
                currentTool = &app->lineTool;
                activeTool = ToolType::Line;
                break;
            case ToolType::Rectangle:
                currentTool = &app->rectangleTool;
                activeTool = ToolType::Rectangle;
                break;
            case ToolType::Circle:
                currentTool = &app->circleTool;
                activeTool = ToolType::Circle;
                break;
            case ToolType::PaintBucket:
                // Xử lý cho công cụ Paint Bucket nếu có
                break;
            }
            return true;
        }
    }
    return false;
}

void UIManager::handleHover(float x, float y) {
    for (auto& button : buttons) {
        button.isHovering = isPointInsideButton(x, y, button);
    }
}

bool UIManager::isPointInsideButton(float x, float y, const UIButton& button) {
    return x >= button.x - button.width / 2 && x <= button.x + button.width / 2 &&
        y >= button.y - button.height / 2 && y <= button.y + button.height / 2;
}

void UIManager::drawButton(const UIButton& button) {
    // Thiết lập màu sắc và độ rộng đường viền tùy theo trạng thái
    if (button.isHovering || activeTool == button.toolType) {
        glLineWidth(2.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    else {
        glLineWidth(1.0f);
        glColor3f(0.2f, 0.49f, 0.49f);
    }

    // Vẽ hình chữ nhật cho nút
    glBegin(GL_LINE_LOOP);
    glVertex2f(button.x - button.width / 2, button.y + button.height / 2);
    glVertex2f(button.x - button.width / 2, button.y - button.height / 2);
    glVertex2f(button.x + button.width / 2, button.y - button.height / 2);
    glVertex2f(button.x + button.width / 2, button.y + button.height / 2);
    glEnd();

    // Vẽ biểu tượng công cụ
    switch (button.toolType) {
    case ToolType::Pencil:
        drawPencilIcon(button.x, button.y);
        break;
    case ToolType::Eraser:
        drawEraserIcon(button.x, button.y);
        break;
    case ToolType::Line:
        drawLineIcon(button.x, button.y);
        break;
    case ToolType::Rectangle:
        drawRectangleIcon(button.x, button.y);
        break;
    case ToolType::Circle:
        drawCircleIcon(button.x, button.y);
        break;
    case ToolType::PaintBucket:
        drawPaintBucketIcon(button.x, button.y);
        break;
    }
}

// Hàm vẽ biểu tượng bút chì
void UIManager::drawPencilIcon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.08f, 0.08f, 1.0f);
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Vẽ thân bút chì
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.05f, -0.6f);
    glVertex2f(-0.05f, 0.0f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(0.05f, -0.6f);
    glEnd();

    // Vẽ đầu bút chì
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.05f, -0.6f);
    glVertex2f(0.05f, -0.6f);
    glVertex2f(0.0f, -0.75f);
    glEnd();

    glPopMatrix();
}

// Hàm vẽ biểu tượng tẩy
void UIManager::drawEraserIcon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.07f, 0.07f, 1.0f);
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    // Vẽ khối hộp
    glBegin(GL_LINES);

    // Đỉnh của khối hộp
    float vertices[8][2] = {
        {-0.1f, -0.6f}, {0.1f, -0.6f}, {0.1f, -0.2f}, {-0.1f, -0.2f},
        {-0.1f, -0.4f}, {0.1f, -0.4f}, {0.1f, 0.0f},  {-0.1f, 0.0f}
    };

    // Vẽ các cạnh
    for (int i = 0; i < 4; ++i) {
        glVertex2f(vertices[i][0], vertices[i][1]);
        glVertex2f(vertices[(i + 1) % 4][0], vertices[(i + 1) % 4][1]);

        glVertex2f(vertices[i + 4][0], vertices[i + 4][1]);
        glVertex2f(vertices[((i + 1) % 4) + 4][0], vertices[((i + 1) % 4) + 4][1]);

        glVertex2f(vertices[i][0], vertices[i][1]);
        glVertex2f(vertices[i + 4][0], vertices[i + 4][1]);
    }

    glEnd();
    glPopMatrix();
}

// Hàm vẽ biểu tượng đường thẳng
void UIManager::drawLineIcon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.09f, 0.09f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, 0.2f);
    glEnd();

    glPopMatrix();
}

// Hàm vẽ biểu tượng hình chữ nhật
void UIManager::drawRectangleIcon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.06f, 0.06f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

// Hàm vẽ biểu tượng hình tròn
void UIManager::drawCircleIcon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.05f, 0.05f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
    int numSegments = 50;
    float angle;
    for (int i = 0; i < numSegments; ++i) {
        angle = i * 2.0f * 3.1415926f / numSegments;
        glVertex2f(cos(angle), sin(angle));
    }
    glEnd();

    glPopMatrix();
}

// Hàm vẽ biểu tượng thùng sơn (Paint Bucket)
void UIManager::drawPaintBucketIcon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.07f, 0.07f, 1.0f);
    glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
    float* currColor = app->getCurrentColor();
    glColor3f(currColor[0], currColor[1], currColor[2]);

    // Vẽ thân thùng
    glBegin(GL_POLYGON);
    glVertex2f(-0.12f, 0.0f);
    glVertex2f(0.12f, 0.0f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(-0.2f, 0.8f);
    glEnd();

    glPopMatrix();
}
