#pragma once
#include "Menu.h"
#include "BitMask.h"


namespace test
{
	class TileSetterMenu : public Menu
	{
	public:
		TileSetterMenu();
		~TileSetterMenu();

		void OnUpdate(float deltaTime) override;
		void OnRender(SDL_Renderer* renderer) override;
		void OnImGuiRender() override;

		void OnImGuiRenderCustom(bool& saveTile, bool& loadTile, std::string& string);
		char* getFilePath();
	private:
		char m_filePath[128];
		std::string m_dirPath;
	};
}