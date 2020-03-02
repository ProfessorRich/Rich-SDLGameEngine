#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "glm.hpp"
#include "TransformComponent.h"

EntityManager Game::g_entityManager;
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

    //Fake level
    Entity& newEntity(g_entityManager.AddEntity("Blob"));
    newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 16, 16, 2);

    Entity& newEntity4(g_entityManager.AddEntity("Blob"));
    newEntity4.AddComponent<TransformComponent>(50, 50, 15, 10, 16, 16, 3);

    Entity& newEntity2(g_entityManager.AddEntity("Blob"));
    newEntity2.AddComponent<TransformComponent>(500, 500, -40, 40, 16, 16, 1);

    Entity& newEntity3(g_entityManager.AddEntity("Blob"));
    newEntity3.AddComponent<TransformComponent>(1000, 900, -35, -45, 16, 16, 1);

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
    SetDrawColour(21, 21, 21, 255);
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
