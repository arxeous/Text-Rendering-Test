#include "Tile.h"
#include "Texture.h"
#include "renderUtil.h"
#include "TileSet.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "BitMask.h"
#include "eventFlagUtil.h"
#include "TileSetterMenu.h"
#include "PanAndZoom.h"
#include "Font.h"
#include "TextMenu.h"

Uint8 bitmaskCellValues3[3][3] = {
	{0x01, 0x02, 0x04 },
	{0x08, 0x00, 0x10 },
	{0x20, 0x40, 0x80 }
};

Uint8 bitmaskCellValues2[2][2] = {
	{0x01, 0x02},
	{0x04, 0x08}
};

SDL_Window* Window = NULL;

SDL_Renderer* Renderer = NULL;

Texture* TileTexture = new Texture();

TileSet* TileMap = new TileSet();

Texture* FontTexture = new Texture();
Font* TestFont = new Font();

test::TextMenu* textMenu = new test::TextMenu();

PanAndZoom* PanZoom = new PanAndZoom(-SCREEN_WIDTH/2, -SCREEN_HEIGHT/2);

SDL_Color lineColor = {0, 255, 255, 255 };
SDL_Color backgroundColor = { 115, 140, 153, 255 };
SDL_Color clickedColor = { 255, 20, 20, 120 };

std::string filePath = "res/pngs/font.png";

int main(int argc, char* args[]) {
	int mouseX;
	int mouseY;
	int screenX = 0;
	int screenY = 0;
	float worldX = 0;
	float worldY = 0;
	std::string test = "";

	if (!init(Window, Renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		test::TileSetterMenu* menu = new test::TileSetterMenu(); 

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForSDLRenderer(Window, Renderer);
		ImGui_ImplSDLRenderer_Init(Renderer);

		//Load media
		if (!FontTexture->loadFontFromFile(Renderer, filePath))
		{
			printf("Failed to load media!\n");
		}
		else
		{
			if (!TestFont->buildFont(FontTexture)) 
			{
				printf("Failed to build font!\n");
			}
			else 
			{
				//Main loop flag
				bool quit = false;
				bool setTile = false;
				bool unsetTile = false;
				bool saveTiles = false;
				bool loadTiles = false;
				bool startPan = false;
				bool startZoom = false;
				bool buttonHold = false;

				float currScale = 1.0;
				int xPos = 0;
				int yPos = 0;

				//Event handler
				SDL_Event event;

				int cellSize ;

				while (!quit)
				{
					// ImGui new frame
					ImGui_ImplSDLRenderer_NewFrame();
					ImGui_ImplSDL2_NewFrame();
					ImGui::NewFrame();

					SDL_GetMouseState(&mouseX, &mouseY);

					saveTiles = false;
					loadTiles = false;
					while (SDL_PollEvent(&event) != 0)
					{
						ImGui_ImplSDL2_ProcessEvent(&event);

						if (!io.WantCaptureKeyboard && !io.WantCaptureMouse)
							getEventFlags(event, quit, saveTiles, loadTiles, setTile, unsetTile, startPan, buttonHold);
					}


					SDL_SetRenderDrawColor(Renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
					SDL_RenderClear(Renderer);
					textMenu->OnImGuiRenderCustom(test, xPos, yPos, currScale);
					TestFont->renderText(Renderer, xPos, yPos, test, currScale);

					ImGui::Render();
					ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
					SDL_RenderPresent(Renderer);
				}
			}
		}

		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		//Free resources and close SDL
		close(Window, Renderer, TileMap);
		TileTexture->free();
	}

	return 0;
}

