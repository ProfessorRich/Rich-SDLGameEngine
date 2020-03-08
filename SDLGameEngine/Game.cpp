#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "glm.hpp"
#include "TransformComponent.h"
#include "AssetManager.h"
#include "SpriteComponent.h"

EntityManager Game::g_entityManager;
AssetManager* Game::g_assetManager = new AssetManager(&g_entityManager);
SDL_Renderer* Game::g_renderer;         //Initialise static pointer an SDL_Renderer called m_renderer

Game::Game() {
    m_isRunning = false;
    g_renderer = NULL;
    m_window = nullptr;
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

void Game::LoadLevel(int levelNumber) {
    // TODO: add entities and components to the entities from set levels.

    

    // // // Fake level
    //Assets to Load
    std::string textureFilePath = "C:\\Users\\Awareness\\Desktop\\Games Development\\SDLGameEngine\\SDLGameEngine\\assets\\images\\";  //example
    g_assetManager->AddTexture("tank-image-right", (textureFilePath + "tank-big-right.png").c_str());
    g_assetManager->AddTexture("tank-image-left", (textureFilePath + "tank-big-left.png").c_str());

    g_assetManager->AddTexture("heart", (textureFilePath + "heart.png").c_str());
    g_assetManager->AddTexture("man", (textureFilePath + "man.png").c_str());
    g_assetManager->AddTexture("bowling", (textureFilePath + "bowling.png").c_str());
    g_assetManager->AddTexture("dog", (textureFilePath + "dog.png").c_str());
    g_assetManager->AddTexture("park", (textureFilePath + "park.png").c_str());

    //Entities and Components
    /*Entity& newEntity5(g_entityManager.AddEntity("TankTest"));
    newEntity5.AddComponent<TransformComponent>(300, 50, 10, 10, 32, 32, 2);
    newEntity5.AddComponent<SpriteComponent>("tank-image-right");

    Entity& newEntity(g_entityManager.AddEntity("Blob"));
    newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 2);
    newEntity.AddComponent<SpriteComponent>("tank-image-right");

    Entity& newEntity4(g_entityManager.AddEntity("Blob"));
    newEntity4.AddComponent<TransformComponent>(50, 50, 15, 10, 32, 32, 3);
    newEntity4.AddComponent<SpriteComponent>("tank-image-left");

    Entity& newEntity2(g_entityManager.AddEntity("Blob"));
    newEntity2.AddComponent<TransformComponent>(500, 500, -40, 40, 32, 32, 1);
    newEntity2.AddComponent<SpriteComponent>("tank-image-left");

    Entity& newEntity3(g_entityManager.AddEntity("Blob"));
    newEntity3.AddComponent<TransformComponent>(1000, 900, -35, -45, 32, 32, 1);
    newEntity3.AddComponent<SpriteComponent>("tank-image-left");*/

    Entity& manEntity(g_entityManager.AddEntity("Man"));
    manEntity.AddComponent<TransformComponent>(1600, 0, -35, 10, 32, 32, 3);
    manEntity.AddComponent<SpriteComponent>("man");

    Entity& heartEntity(g_entityManager.AddEntity("Heart"));
    heartEntity.AddComponent<TransformComponent>(800, 450, 1, -10, 32, 32, 1);
    heartEntity.AddComponent<SpriteComponent>("heart");

    Entity& bowlingEntity(g_entityManager.AddEntity("Bowling"));
    bowlingEntity.AddComponent<TransformComponent>(1600, 30, -119, 13, 32, 32, 1);
    bowlingEntity.AddComponent<SpriteComponent>("bowling");

    Entity& dogEntity(g_entityManager.AddEntity("Dog"));
    bowlingEntity.AddComponent<TransformComponent>(1700, 30, -120, 11, 32, 32, 1);
    bowlingEntity.AddComponent<SpriteComponent>("dog");

    Entity& parkEntity(g_entityManager.AddEntity("Park"));
    bowlingEntity.AddComponent<TransformComponent>(50, 700, 0, 0, 32, 32, 8);
    bowlingEntity.AddComponent<SpriteComponent>("park");



    g_entityManager.ListAllEntities();
}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT: {
            m_isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
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
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksLastFrame + G_TARGET_DELTA_MS));
    
    // How much time in s has passed since last frame?
    float deltaTime = (SDL_GetTicks() - m_ticksLastFrame) / 1000.0f;    

    // Clamp the deltaTime to allow for pauses and breaks and prevent timewarping
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    m_ticksLastFrame = SDL_GetTicks();

    // FPS Counter
    // std::cout << 1.0/deltaTime << std::endl; 

    // Move the projectile by proportionally how much deltaTime has passed in s since last frame.
    g_entityManager.Update(deltaTime);   
}

void Game::Render() {

    // Clear the buffer
    SetDrawColour(21, 21, 21, 255); //the grey background
    // SetDrawColour(255, 255, 255, 255);  //white
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

void Game::Destroy() {
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::SetDrawColour(int red, int green, int blue, int opacity) {
    SDL_SetRenderDrawColor(g_renderer, red, green, blue, opacity);
}
