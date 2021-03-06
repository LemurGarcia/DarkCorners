
#include "Engine/Engine.h"
#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Inputs.h"
#include "Engine/Font.h"
#include "Game/Board.h"
#include <global.h>
#include <memory>

static int CalcFPS(uint64_t delta)
{
    static int fps = 0;
    static int frames = 0;
    static uint64_t time = 0;

    frames++;
    time += delta;

    if (time > 1000)
    {
        fps = frames;
        frames = 0;
        time -= 1000;
    }
    return fps;
}

class Application : public Engine
{
public:
    Application()
        : Engine()
        , m_board(std::make_unique<Board>())
    {
        OnSize(Engine::GetWidth(), Engine::GetHeight());
        PV_INFO("Load game complete");
    }

    ~Application() override
    {
        PV_INFO("Deinitialization of game");
    }

protected:
    void OnSize(int width, int height) override
    {
        Font::Resize(height / 32.f);
    }

    void Loop(uint64_t delta) override
    {
        //m_board->Update(delta);
        m_board->Render();

        Font::Render(L"#gFPS = " + std::to_wstring(CalcFPS(delta)), { -0.95f, -0.85f });
    }
private:
    std::unique_ptr<Board> m_board;
};

int main(int argc, const char* argv[])
{
    Application app;
    app.Run();
    return 0;
}