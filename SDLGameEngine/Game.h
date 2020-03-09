#ifndef GAME_H
#define GAME_H

#include "EntityManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class AssetManager;

class Game {
private:
    bool m_isRunning;
    SDL_Window* m_window;
    int m_ticksLastFrame = 0;
    // int m_colourCycle = 0;

public:
    static EntityManager g_entityManager;
    static SDL_Renderer* g_renderer;
    static AssetManager* g_assetManager;
    static SDL_Event g_event;

    Game();
    ~Game();        
    bool IsRunning() const;
    void Initialise(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
    void SetDrawColour(int r, int g, int b, int opacity);
    void LoadLevel(int levelNumber);
};

#endif
