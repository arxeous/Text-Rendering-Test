#include "TextMenu.h"

test::TextMenu::TextMenu()
	: m_TestString(""), m_Positions{0,0}
{
}

test::TextMenu::~TextMenu()
{
}

void test::TextMenu::OnUpdate(float deltaTime)
{
}

void test::TextMenu::OnRender(SDL_Renderer* renderer)
{
}

void test::TextMenu::OnImGuiRender()
{
}

void test::TextMenu::OnImGuiRenderCustom(std::string& string, int& xPos, int& yPos, float& scale)
{
	if (ImGui::Begin("Text Test"))
	{
		ImGui::InputText("Enter string here", m_TestString, IM_ARRAYSIZE(m_TestString));
		ImGui::SliderInt2("Text position", m_Positions, 0, 400);
		ImGui::SliderFloat("Scale", &scale, 1.0, 2.0);
		string = m_TestString;
		xPos = m_Positions[0];
		yPos = m_Positions[1];

	}
	ImGui::End();
}
