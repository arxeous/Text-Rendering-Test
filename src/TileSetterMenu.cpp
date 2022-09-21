#include "TileSetterMenu.h"

test::TileSetterMenu::TileSetterMenu()
	: m_dirPath("res/maps/"), m_filePath("")
{
}

test::TileSetterMenu::~TileSetterMenu()
{
}

void test::TileSetterMenu::OnUpdate(float deltaTime)
{
}

void test::TileSetterMenu::OnRender(SDL_Renderer* renderer)
{

}

void test::TileSetterMenu::OnImGuiRender()
{
    
}

void test::TileSetterMenu::OnImGuiRenderCustom(bool& saveTile, bool& loadTile, std::string& string)
{
    bool popupModalSave = false;
    bool popupModalLoad = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save", "Ctrl+S"))
            {
                popupModalSave = true;
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) 
            {
                popupModalLoad = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (popupModalSave)
    {
        ImGui::OpenPopup("Save File");
        popupModalSave = false;
    }
    if (popupModalLoad)
    {
        ImGui::OpenPopup("Load File");
        popupModalLoad = false;
    }

    if (ImGui::BeginPopupModal("Save File"))
    {
        ImGui::Text("Enter file name");
        ImGui::Separator();

        //static int unused_i = 0;
        //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

        static bool dont_ask_me_next_time = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::InputText("File Name", m_filePath, IM_ARRAYSIZE(m_filePath));
        ImGui::PopStyleVar();

        if (ImGui::Button("OK", ImVec2(120, 0))) 
        { 
            saveTile = true;
            string = m_filePath;
            string = m_dirPath + string;
            ImGui::CloseCurrentPopup(); 
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Load File"))
    {
        ImGui::Text("Enter file name");
        ImGui::Separator();

        //static int unused_i = 0;
        //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

        static bool dont_ask_me_next_time = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::InputText("File Name", m_filePath, IM_ARRAYSIZE(m_filePath));
        ImGui::PopStyleVar();

        if (ImGui::Button("OK", ImVec2(120, 0))) 
        { 
            loadTile = true;
            string = m_filePath;
            string = m_dirPath + string;
            ImGui::CloseCurrentPopup(); 
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }


}

char* test::TileSetterMenu::getFilePath()
{
    return m_filePath;
}

