#include <iostream>
#include <glm.hpp>

#include "Constants.h"
#include "Game.h"
#include "TransformComponent.h"
#include "AssetManager.h"
#include "SpriteComponent.h"
#include "KeyboardInputComponent.h"
#include "Map.h"
#include "TileComponent.h"
#include "ColliderComponent.h"
#include "TextComponent.h"
#include "SpawnerComponent.h"

EntityManager g_entityManager;
AssetManager* Game::g_assetManager = new AssetManager(&g_entityManager);
SDL_Renderer* Game::g_renderer;         //Initialise static pointer an SDL_Renderer called m_renderer
SDL_Event Game::g_event;
SDL_Rect Game::g_camera = { 0,0,G_WINDOW_WIDTH, G_WINDOW_HEIGHT };
Map* g_map;

Game::Game() {
    m_isRunning = false;
    g_renderer = NULL;
    m_window = nullptr;
    // g_mapHeight = g_mapWidth = 0; GIMPED
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return m_isRunning;
}

void Game::Initialise(int width, int height) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }

    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL_ttf." << std::endl;
        return;
    }

   m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );

    if (!m_window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    g_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (!g_renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    m_isRunning = true;
    return;
}

// Add the player and make global! (l33t progr@ming skillz)
Entity& g_playerEntity(g_entityManager.AddEntity("player", G_PLAYER_LAYER));

//Create the fpsCounterEntity (for debugging) Obv global for mad props / skillz.    
Entity& g_fpsCounterEntity(g_entityManager.AddEntity("fps_counter", G_GUI_LAYER));

void Game::LoadLevel(int levelNumber) {
    //Load fonts
    std::string fontFilePath = ".\\assets\\fonts\\";        //Sets fonts path

    g_assetManager->AddFont("system", 24, (fontFilePath + "arial.ttf").c_str());
    g_assetManager->AddFont("normal", 14, (fontFilePath + "charriot.ttf").c_str());

    //Load tilemap
    int mapScale, mapTileSize, mapWidth, mapHeight;         //temperary for debugging
    mapScale = 3;
    mapTileSize = 32;                                       // probably will never change
    mapWidth = 25;
    mapHeight = 20;

    std::string mapFilePath = ".\\assets\\tilemaps\\";      //Sets the tilemaps file path

    g_assetManager->AddTexture("jungle-tiletexture", (mapFilePath + "jungle.png").c_str());
    g_map = new Map("jungle-tiletexture", mapScale, mapTileSize);
    g_map->LoadMap(".\\assets\\tilemaps\\jungle.map", mapWidth, mapHeight);

    //Load assets
    std::string textureFilePath = ".\\assets\\images\\";                        //Sets the images file path
    Game::g_assetManager->AddTexture("player", (textureFilePath + "chopper-spritesheet.png").c_str());

    g_assetManager->AddTexture("heart", (textureFilePath + "heart.png").c_str());
    g_assetManager->AddTexture("man", (textureFilePath + "man.png").c_str());
    g_assetManager->AddTexture("bowl", (textureFilePath + "bowling.png").c_str());
    g_assetManager->AddTexture("dog", (textureFilePath + "dog.png").c_str());
    g_assetManager->AddTexture("flame", (textureFilePath + "flame-basic.png").c_str());

    //Load player components
    g_playerEntity.AddComponent<TransformComponent>(300, 300, 0, 0, 32, 32, 2);
    g_playerEntity.AddComponent<SpriteComponent>("player", 2, 6, true, false);
    g_playerEntity.AddComponent<KeyboardInputComponent>("up", "down", "left", "right", "space");
    g_playerEntity.AddComponent<ColliderComponent>("PLAYER", 300, 300, 32, 32);

    //Load entities and related components
    Entity& heartEntity(g_entityManager.AddEntity("Heart", G_COLLECTABLE_LAYER));
    heartEntity.AddComponent<TransformComponent>(800, 450, 1, -10, 32, 32, 1);
    heartEntity.AddComponent<SpriteComponent>("heart");
    heartEntity.AddComponent<ColliderComponent>("HEART", 800, 450, 32, 32);

    Entity& manEntity(g_entityManager.AddEntity("Man", G_NPC_LAYER));
    manEntity.AddComponent<TransformComponent>(1600, 0, -35, 10, 32, 32, 1);
    manEntity.AddComponent<SpriteComponent>("man");
    manEntity.AddComponent<ColliderComponent>("MAN", 1600, 0, 32, 32);

    Entity& dogEntity(g_entityManager.AddEntity("Dog", G_NPC_LAYER));
    dogEntity.AddComponent<TransformComponent>(1700, 30, -120, 11, 32, 32, 1);
    dogEntity.AddComponent<SpriteComponent>("dog");
    dogEntity.AddComponent<ColliderComponent>("DOG", 1700, 30, 32, 32);

    Entity& flameEntity(g_entityManager.AddEntity("Flame", G_GUI_LAYER));
    flameEntity.AddComponent<TransformComponent>(0, G_WINDOW_HEIGHT-64, 0, 0, 64, 64, 1);
    flameEntity.AddComponent<SpriteComponent>("flame", 2, 3, false, true);

    Entity& projectileEntity(g_entityManager.AddEntity("Bowl", G_PROJECTILE_LAYER));
    projectileEntity.AddComponent<TransformComponent>(1600, 30, -119, 13, 32, 32, 1);
    projectileEntity.AddComponent<SpriteComponent>("bowl");
    projectileEntity.AddComponent<ColliderComponent>("PROJECTILE", 1600, 30, 32, 32);
    projectileEntity.AddComponent<SpawnerComponent>(180, 200, 300, true);

    Entity& parkEntity(g_entityManager.AddEntity("Park", G_DECOR_LAYER));
    parkEntity.AddComponent<TransformComponent>(50, 700, 0, 0, 32, 32, 8);
    parkEntity.AddComponent<SpriteComponent>("park");

    //Add text labels
    Entity& textTest(g_entityManager.AddEntity("FontTest", G_GUI_LAYER));
    textTest.AddComponent<TextComponent>(100, 100, "LEVEL ONE...", "normal", G_WHITE_COLOUR);

    // DEBUG - list entities and components, and create TextComponent for the fps_counter entity
    if (G_DEBUG) {
        g_entityManager.ListAllEntities();

        g_fpsCounterEntity.AddComponent<TextComponent>(G_FPS_COUNTER_POSX, G_FPS_COUNTER_POSY, "WAIT", "system", G_RED_COLOUR);
    }
}

// TODO:: Ideally the player controls should ALSO be processed here rather than in the KeyboardInputComponent...
void Game::ProcessInput() {
    SDL_PollEvent(&g_event);

    switch (g_event.type) {
        case SDL_QUIT: {
            m_isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                m_isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

// globals for debug testing - speed is in pixels per second?
glm::vec2 g_projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 g_projectileVel = glm::vec2(20.0f, 20.0f);

void Game::Update() {
    // Wait till G_TARGET_DELTA_MS passed since m_ticksLastFrame thereby allowing function to loop maximally G_TARGET_FPS times per second.
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), static_cast<float>(m_ticksLastFrame) + G_TARGET_DELTA_MS));
    
    // How much time in s has passed since last frame?
    float deltaTime = (SDL_GetTicks() - m_ticksLastFrame) / 1000.0f;    

    // Clamp the deltaTime to allow for pauses and breaks and prevent timewarping
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    m_ticksLastFrame = SDL_GetTicks();

    //FPS Counter
    if (G_DEBUG) {
        UpdateFPSCounter(deltaTime);
    }

    // Move entities by proportionally how much deltaTime has passed in s since last frame.
    g_entityManager.Update(deltaTime);   

    // Move the g_camera SDL_Rect
    HandleCameraMovement();

    // Check Collisions
    CheckCollisions();
}

void Game::Render() {

    // Clear the buffer
    SetDrawColour(21, 21, 21, 255); //the grey background
    SDL_RenderClear(g_renderer);

    // Render some game stuff in the buffer
    if (g_entityManager.HasNoEntities()) {
        return;
    }
    else {
        g_entityManager.Render();
    }
  
    // Swap the buffer with what is on screen
    SDL_RenderPresent(g_renderer);
}

void Game::HandleCameraMovement() {
    TransformComponent* trackingObjectTransform = g_playerEntity.GetComponent<TransformComponent>();
    
    g_camera.x = static_cast<int>(trackingObjectTransform->g_position.x - (G_WINDOW_WIDTH / 2));
    g_camera.y = static_cast<int>(trackingObjectTransform->g_position.y - (G_WINDOW_HEIGHT / 2));

    // CLAMP the camera to the play area
    if (g_camera.x < 0) g_camera.x = 0;
    if (g_camera.y < 0) g_camera.y = 0;

    int cameraXLimit = (g_map->GetMapWidth() * g_map->GetTileSize() * g_map->GetScale()) - (G_WINDOW_WIDTH);             // Centre of camera max X is Map width * tile pixels * scale - full window width (as camera point is the top-left corner of the bloody thing
    int cameraYLimit = (g_map->GetMapHeight() * g_map->GetTileSize() * g_map->GetScale()) - (G_WINDOW_HEIGHT);

    if (g_camera.x > cameraXLimit) g_camera.x = cameraXLimit;
    if (g_camera.y > cameraYLimit) g_camera.y = cameraYLimit;
}

void Game::CheckCollisions() {
    std::cout << g_entityManager.CheckAllCollisions();
}

void Game::Destroy() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

// Why did I bother? TODO - remove this 
void Game::SetDrawColour(int red, int green, int blue, int opacity) {
    SDL_SetRenderDrawColor(g_renderer, red, green, blue, opacity);
}

void Game::UpdateFPSCounter(float deltaTime) {
    sprintf_s(m_fpsCounterBuffer, "FPS: %.2f", 1.0 / deltaTime);                                             // take deltaTime, use sprintf to convert to char array and update m_fpsCounterBuffer
    g_fpsCounterEntity.GetComponent<TextComponent>()->ChangeText(m_fpsCounterBuffer);
}
