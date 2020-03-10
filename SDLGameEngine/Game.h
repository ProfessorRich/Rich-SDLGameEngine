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
    // static EntityManager g_entityManager; // I guess it's going TRULY global...
    static SDL_Renderer* g_renderer;
    static AssetManager* g_assetManager;
    static SDL_Event g_event;
    static SDL_Rect g_camera;

    // static unsigned int g_mapWidth, g_mapHeight; - decided against retarded globals for this one...

    Game();
    ~Game();        
    bool IsRunning() const;
    void Initialise(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void HandleCameraMovement();
    void Destroy();
    void SetDrawColour(int r, int g, int b, int opacity);
    void LoadLevel(int levelNumber);
};

#endif
