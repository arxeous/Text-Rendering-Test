#pragma once
#include "Menu.h"
#include <string>

namespace test
{
	class TextMenu : public Menu
	{
	public:
		TextMenu();
		~TextMenu();

		void OnUpdate(float deltaTime) override;
		void OnRender(SDL_Renderer* renderer) override;
		void OnImGuiRender() override;

		void OnImGuiRenderCustom(std::string& string, int& xPos, int& yPos, float& scale);
	private:
		char m_TestString[128];
		int m_Positions[2];
	};
}