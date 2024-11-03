#include "PaintApp.h"

PaintApp* PaintApp::instance = nullptr;

PaintApp::PaintApp(int argc, char** argv)
    : pencilTool(this),
    eraserTool(this),
    lineTool(this),
    rectangleTool(this),
    circleTool(this),
    currentTool(&pencilTool),
    uiManager(this),
    colorPicker()
{
    instance = this;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("PAINT APP by Vikash");

    glutPositionWindow(100, 50);

    glutDisplayFunc(PaintApp::displayWrapper);
    glutMouseFunc(PaintApp::mouseClickWrapper);
    glutMotionFunc(PaintApp::mouseMotionWrapper);
    glutPassiveMotionFunc(PaintApp::passiveMouseMotionWrapper);
    glutKeyboardFunc(PaintApp::keyboardWrapper);

    glClearColor(0.30f, 0.30f, 0.30f, 1.0f);
}

PaintApp* PaintApp::getInstance() {
    return instance;
}

void PaintApp::run() {
    glutMainLoop();
}

void PaintApp::displayWrapper() {
    instance->display();
}

void PaintApp::keyboardWrapper(unsigned char key, int x, int y) {
    instance->keyboard(key, x, y);
}

void PaintApp::mouseClickWrapper(int button, int state, int x, int y) {
    instance->handleMouseClick(button, state, x, y);
}

void PaintApp::mouseMotionWrapper(int x, int y) {
    instance->handleMouseMotion(x, y);
}

void PaintApp::passiveMouseMotionWrapper(int x, int y) {
    instance->passiveMouseMotion(x, y);
}

float* PaintApp::getCurrentColor() {
    return colorPicker.getCurrentColor();
}

std::vector<std::function<void()>>* PaintApp::getFunctionsToCall() {
    return &functionsToCall;
}

void PaintApp::display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Vẽ nền canvas
    uiManager.drawCanvas();

    // Thực thi các hàm vẽ đã lưu
    for (const auto& func : functionsToCall) {
        func();
    }

    // Vẽ công cụ hiện tại theo thời gian thực
    currentTool->draw();

    // Vẽ các thành phần giao diện người dùng
    uiManager.drawUI();

    // Vẽ color picker
    colorPicker.draw();

    glutSwapBuffers();
}

void PaintApp::keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'E':
    case 'e':
        currentTool = &eraserTool;
        uiManager.setActiveTool(UIManager::ToolType::Eraser);
        break;
    case 'P':
    case 'p':
        currentTool = &pencilTool;
        uiManager.setActiveTool(UIManager::ToolType::Pencil);
        break;
    case 'L':
    case 'l':
        currentTool = &lineTool;
        uiManager.setActiveTool(UIManager::ToolType::Line);
        break;
    case 'R':
    case 'r':
        currentTool = &rectangleTool;
        uiManager.setActiveTool(UIManager::ToolType::Rectangle);
        break;
    case 'C':
    case 'c':
        currentTool = &circleTool;
        uiManager.setActiveTool(UIManager::ToolType::Circle);
        break;
    case 'Z':
    case 'z':
        if (!functionsToCall.empty()) {
            functionsToCall.pop_back();
        }
        break;
    case 'G':
    case 'g':
        colorPicker.setCurrentColor(0.0f, 1.0f, 0.0f);
        break;
    case 'B':
    case 'b':
        colorPicker.setCurrentColor(0.0f, 0.0f, 1.0f);
        break;
    case 'Y':
    case 'y':
        colorPicker.setCurrentColor(1.0f, 1.0f, 0.0f);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void PaintApp::handleMouseClick(int button, int state, int x, int y) {
    float posX = (2.0f * (float)x / glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    float posY = 1.0f - (2.0f * (float)y / glutGet(GLUT_WINDOW_HEIGHT));

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // Kiểm tra nếu click vào color picker
            if (colorPicker.isInside(posX, posY)) {
                colorPicker.pickColor(x, y);
                glutPostRedisplay();
                return;
            }

            // Kiểm tra nếu click vào các nút giao diện
            if (uiManager.handleClick(posX, posY, currentTool)) {
                glutPostRedisplay();
                return;
            }

            // Xử lý sự kiện chuột xuống cho công cụ hiện tại
            currentTool->onMouseDown(posX, posY);
        }
        else if (state == GLUT_UP) {
            // Xử lý sự kiện chuột lên cho công cụ hiện tại
            currentTool->onMouseUp(posX, posY);
        }
    }
    glutPostRedisplay();
}

void PaintApp::handleMouseMotion(int x, int y) {
    float currX = (2.0f * (float)x / glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    float currY = 1.0f - (2.0f * (float)y / glutGet(GLUT_WINDOW_HEIGHT));
    currentTool->onMouseMove(currX, currY);
    glutPostRedisplay();
}

void PaintApp::passiveMouseMotion(int x, int y) {
    float posX = (2.0f * (float)x / glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
    float posY = 1.0f - (2.0f * (float)y / glutGet(GLUT_WINDOW_HEIGHT));

    uiManager.handleHover(posX, posY);
    glutPostRedisplay();
}
