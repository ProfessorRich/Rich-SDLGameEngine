#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include <string>

#include "Game.h"
#include "EntityManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

class PlayerControlComponent : public Component {
public:
	std::string g_moveUpKey, g_moveDownKey, g_moveLeftKey, g_moveRightKey, g_shootKey;
	TransformComponent* g_transform;
	SpriteComponent* g_sprite;

	PlayerControlComponent(){

	}

	PlayerControlComponent(std::string up, std::string down, std::string left, std::string right, std::string shoot) {
		g_moveUpKey = GetSDLKeyStringCode(up);
		g_moveDownKey = GetSDLKeyStringCode(down);
		g_moveLeftKey = GetSDLKeyStringCode(left);
		g_moveRightKey = GetSDLKeyStringCode(right);
		g_shootKey = GetSDLKeyStringCode(shoot);

	}

	// Converts string description of key to SDL key codes
	std::string GetSDLKeyStringCode(std::string key) {
		if (key.compare("up") == 0) return "1073741906";
		if (key.compare("down") == 0) return "1073741905";
		if (key.compare("left") == 0) return "1073741904";
		if (key.compare("right") == 0) return "1073741903";
		if (key.compare("space") == 0) return "32";
		return std::to_string(static_cast<int>(key[0]));  // if it's none of the above then return the standard ASCII mapping and hope for the best...
	}

	void Initialise() override {
		g_transform = g_owner->GetComponent<TransformComponent>();
		g_sprite = g_owner->GetComponent<SpriteComponent>();
	}

	void Update(float deltaTime) override {				//TODO - This should be implimented more from Game.cpp::ProcessInput()
		if (Game::g_event.type == SDL_KEYDOWN) {
			std::string keyCode = std::to_string(Game::g_event.key.keysym.sym);

			if (keyCode.compare(g_moveUpKey) == 0) {
				g_owner->GetComponent<SpriteComponent>()->Play("Up");
				g_owner->GetComponent<TransformComponent>()->g_velocity.y--;
			}


			if (keyCode.compare(g_moveDownKey) == 0) {
				g_owner->GetComponent<SpriteComponent>()->Play("Down");
				g_owner->GetComponent<TransformComponent>()->g_velocity.y++;
			}


			if (keyCode.compare(g_moveLeftKey) == 0) {
				g_owner->GetComponent<SpriteComponent>()->Play("Left");
				g_owner->GetComponent<TransformComponent>()->g_velocity.x--;
			}


			if (keyCode.compare(g_moveRightKey) == 0) {
				g_owner->GetComponent<SpriteComponent>()->Play("Right");
				g_owner->GetComponent<TransformComponent>()->g_velocity.x++;
			}


			if (keyCode.compare(g_shootKey) == 0) {

			}
		}

		if (Game::g_event.type == SDL_KEYUP){

			BringToAStop();
			
			std::string keyCode = std::to_string(Game::g_event.key.keysym.sym);

			/*    Do I need any of this bs? Dunno. Maybe later for ADVANCED PHYSIOKZ
			if (keyCode.compare(g_moveUpKey) == 0) {
				
			}


			if (keyCode.compare(g_moveDownKey) == 0) {
			;
			}


			if (keyCode.compare(g_moveLeftKey) == 0) {
				
			}


			if (keyCode.compare(g_moveRightKey) == 0) {
				
			}


			if (keyCode.compare(g_shootKey) == 0) {
				
			}*/
		}
	}

	void BringToAStop() {
		if (g_owner->GetComponent<TransformComponent>()->g_velocity.y > 0) g_owner->GetComponent<TransformComponent>()->g_velocity.y--;
		if (g_owner->GetComponent<TransformComponent>()->g_velocity.y < 0) g_owner->GetComponent<TransformComponent>()->g_velocity.y++;
		if (g_owner->GetComponent<TransformComponent>()->g_velocity.x > 0) g_owner->GetComponent<TransformComponent>()->g_velocity.x--;
		if (g_owner->GetComponent<TransformComponent>()->g_velocity.x < 0) g_owner->GetComponent<TransformComponent>()->g_velocity.x++;
	}

};

#endif 
