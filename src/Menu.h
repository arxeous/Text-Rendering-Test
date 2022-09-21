#pragma once
#include "SDL.h"
#include "imgui.h"
namespace test {
	class Menu {
	public:
		Menu() {}
		virtual ~Menu() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender(SDL_Renderer* renderer) {}
		virtual void OnImGuiRender() {}
	};
}
