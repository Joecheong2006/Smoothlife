#include <mfw.h>
#include "KeyCode.h"
#include "ScreenBufferTest.h"

using namespace mfw;
class DemoSandBox : public Application {
private:
    bool fullScreen = false;

public:
    DemoSandBox(): Application("demo", 1280, 720)
    {}

    virtual void Start() override {
        addLayer(new ScreenBufferTest());
    }

    virtual bool OnInputKey(const KeyEvent& event) override {
        if (event.key == MF_KEY_ESCAPE && event.mode == KeyMode::Down) {
            Terminate();
        }

        auto main = &Application::Get().GetWindow();

        if (Input::KeyPress(MF_KEY_F)) {
            fullScreen = !fullScreen;
            main->setFullScreen(fullScreen);
            glViewport(0, 0, main->width(), main->height());
        }
        return true;
    }

    virtual bool OnWindowFocus(const WindowFocusEvent& event) override {
        LOG_EVENT_INFO(event);
        if (fullScreen) {
            GetWindow().setMode(WindowMode::Maximize);
        }
        return true;
    }

    virtual bool OnWindowNotFocus(const WindowNotFocusEvent& event) override {
        LOG_EVENT_INFO(event);
        if (fullScreen) {
            GetWindow().setMode(WindowMode::Minimize);
        }
        return true;
    }

};

mfw::Application* mfw::CreateApplication() {
    return new DemoSandBox();
}

