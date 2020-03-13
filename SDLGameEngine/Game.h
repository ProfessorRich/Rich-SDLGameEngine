#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "EntityManager.h"

class AssetManager;

class Game {
private:
    bool m_isRunning;
    SDL_Window* m_window;
    int m_ticksLastFrame = 0;

    // Used for the FPS counter
    char m_fpsCounterBuffer[25];
    SDL_Rect m_fpsBox;

public:
    static SDL_Renderer* g_renderer;
    static AssetManager* g_assetManager;
    static SDL_Event g_event;
    static SDL_Rect g_camera;


    Game();
    ~Game();        
    bool IsRunning() const;
    void Initialise(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void HandleCameraMovement();
    void CheckCollisions();
    void Destroy();
    void SetDrawColour(int r, int g, int b, int opacity);
    void LoadData(int dataFileNumber);

    void UpdateFPSCounter(float deltaTime);
    void RenderFPSCounter();
};

#endif
