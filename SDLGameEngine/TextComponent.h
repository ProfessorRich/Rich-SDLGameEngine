#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "FontManager.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "Game.h"

class TextComponent : public Component{
private:
	SDL_Rect m_position;
	std::string m_textContent;
	std::string m_fontId;
	SDL_Colour m_colour; 
	SDL_Texture* m_texture;

public:
	TextComponent(int x, int y, std::string textContent, std::string fontId, const SDL_Colour colour) {
		m_position.x = x;
		m_position.y = y;
		m_textContent = textContent;
		m_fontId = fontId;
		m_colour = colour;

		PrepareText();
	}
	
	// TODO - make safer. Shouldn't crash if can't find font ID!
	void PrepareText() {
		SDL_Surface* textSurface = TTF_RenderText_Blended(Game::g_assetManager->GetFont(m_fontId), m_textContent.c_str(), m_colour);
		m_texture = SDL_CreateTextureFromSurface(Game::g_renderer, textSurface);
		SDL_FreeSurface(textSurface);

		SDL_QueryTexture(m_texture, NULL, NULL, &m_position.w, &m_position.h);				// Looks at m_texture, extracts the width and height and sets it... pretty smooth. Definitely dodgy.
	}

	void Render() override {
		FontManager::Draw(m_texture, m_position);
	}

	void ChangeText(std::string newTextContent) {
		m_textContent = newTextContent;
		PrepareText();
	}
};

#endif