#pragma once
#include <ImGui/Inc/ImGui.h>

namespace MyGui
{
#pragma region Colors
    static const ImVec4 Red = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    static const ImVec4 Green = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    static const ImVec4 Blue = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
    static const ImVec4 Yellow = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    static const ImVec4 Black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    static const ImVec4 Brown = ImVec4(0.2f, 0.1f, 0.0f, 1.0f); 
    static const ImVec4 DarkBrown = ImVec4(0.1f, 0.05f, 0.0f, 1.0f); 
    static const ImVec4 Cyan = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
    static const ImVec4 Magenta = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
    static const ImVec4 Orange = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
    static const ImVec4 Purple = ImVec4(0.5f, 0.0f, 0.5f, 1.0f);
    static const ImVec4 Pink = ImVec4(1.0f, 0.5f, 0.8f, 1.0f);
    static const ImVec4 Lime = ImVec4(0.75f, 1.0f, 0.0f, 1.0f);
    static const ImVec4 Teal = ImVec4(0.0f, 0.5f, 0.7f, 1.0f);
    static const ImVec4 Indigo = ImVec4(0.294f, 0.0f, 0.51f, 1.0f);
    static const ImVec4 Violet = ImVec4(0.56f, 0.0f, 1.0f, 1.0f);
    static const ImVec4 Maroon = ImVec4(0.5f, 0.0f, 0.0f, 1.0f);
    static const ImVec4 Olive = ImVec4(0.5f, 0.5f, 0.0f, 1.0f);
    static const ImVec4 Navy = ImVec4(0.0f, 0.0f, 0.5f, 1.0f);
    static const ImVec4 Aqua = ImVec4(0.0f, 1.0f, 1.0f, 1.0f);
    static const ImVec4 Salmon = ImVec4(0.98f, 0.5f, 0.45f, 1.0f);
    static const ImVec4 Gold = ImVec4(1.0f, 0.84f, 0.0f, 1.0f);
    static const ImVec4 Grey = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    static const ImVec4 DarkGrey = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    static const ImVec4 LightGrey = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
    static const ImVec4 Beige = ImVec4(0.96f, 0.96f, 0.86f, 1.0f);
    static const ImVec4 Coral = ImVec4(1.0f, 0.5f, 0.31f, 1.0f);
    static const ImVec4 Lavender = ImVec4(0.9f, 0.9f, 0.98f, 1.0f);
    static const ImVec4 Turquoise = ImVec4(0.25f, 0.88f, 0.82f, 1.0f);
    static const ImVec4 SlateBlue = ImVec4(0.41f, 0.54f, 0.64f, 1.0f);
    static const ImVec4 Tomato = ImVec4(1.0f, 0.16f, 0.16f, 1.0f);
    static const ImVec4 Orchid = ImVec4(0.85f, 0.44f, 0.84f, 1.0f);
    static const ImVec4 Chocolate = ImVec4(0.50f, 0.25f, 0.08f, 1.0f);
    static const ImVec4 DarkSlateGray = ImVec4(0.18f, 0.31f, 0.31f, 1.0f);
#pragma endregion

    static ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }
    static ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    static void ProgressBar(float numerator, float denominator, const ImVec2& size = ImVec2(0,0), const ImVec4& barColor = Green, const ImVec4& bgColor = Red, const ImVec4& borderColor = Black)
	{
        ImGuiStyle& style = ImGui::GetStyle();
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 startPos = ImGui::GetCursorScreenPos();
        ImVec2 endPos = ImVec2(startPos.x + size.x, startPos.y + size.y);

        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, barColor);
        //ImGui::PushStyleColor(ImGuiCol_FrameBg, bgColor);

        drawList->AddRectFilled(startPos, endPos, ImGui::GetColorU32(bgColor)); 

        startPos -= ImVec2(1, 1);
        endPos += ImVec2(1, 1);   
        drawList->AddRect(startPos, endPos, ImGui::GetColorU32(borderColor));

        // Render progress bar with modified foreground color
        ImGui::ProgressBar(numerator / denominator, size);
        ImGui::PopStyleColor();
	}
    static void TestColors() {
        ImGui::Text("Red"); ImGui::SameLine(); ImGui::ColorButton("##Red", Red);
        ImGui::Text("Green"); ImGui::SameLine(); ImGui::ColorButton("##Green", Green);
        ImGui::Text("Blue"); ImGui::SameLine(); ImGui::ColorButton("##Blue", Blue);
        ImGui::Text("Yellow"); ImGui::SameLine(); ImGui::ColorButton("##Yellow", Yellow);
        ImGui::Text("Cyan"); ImGui::SameLine(); ImGui::ColorButton("##Cyan", Cyan);
        ImGui::Text("Magenta"); ImGui::SameLine(); ImGui::ColorButton("##Magenta", Magenta);
        ImGui::Text("Orange"); ImGui::SameLine(); ImGui::ColorButton("##Orange", Orange);
        ImGui::Text("Purple"); ImGui::SameLine(); ImGui::ColorButton("##Purple", Purple);
        ImGui::Text("Pink"); ImGui::SameLine(); ImGui::ColorButton("##Pink", Pink);
        ImGui::Text("Lime"); ImGui::SameLine(); ImGui::ColorButton("##Lime", Lime);
        ImGui::Text("Teal"); ImGui::SameLine(); ImGui::ColorButton("##Teal", Teal);
        ImGui::Text("Indigo"); ImGui::SameLine(); ImGui::ColorButton("##Indigo", Indigo);
        ImGui::Text("Violet"); ImGui::SameLine(); ImGui::ColorButton("##Violet", Violet);
        ImGui::Text("Maroon"); ImGui::SameLine(); ImGui::ColorButton("##Maroon", Maroon);
        ImGui::Text("Olive"); ImGui::SameLine(); ImGui::ColorButton("##Olive", Olive);
        ImGui::Text("Navy"); ImGui::SameLine(); ImGui::ColorButton("##Navy", Navy);
        ImGui::Text("Aqua"); ImGui::SameLine(); ImGui::ColorButton("##Aqua", Aqua);
        ImGui::Text("Salmon"); ImGui::SameLine(); ImGui::ColorButton("##Salmon", Salmon);
        ImGui::Text("Gold"); ImGui::SameLine(); ImGui::ColorButton("##Gold", Gold);
        ImGui::Text("Grey"); ImGui::SameLine(); ImGui::ColorButton("##Grey", Grey);
        ImGui::Text("Dark Grey"); ImGui::SameLine(); ImGui::ColorButton("##DarkGrey", DarkGrey);
        ImGui::Text("Light Grey"); ImGui::SameLine(); ImGui::ColorButton("##LightGrey", LightGrey);
        ImGui::Text("Beige"); ImGui::SameLine(); ImGui::ColorButton("##Beige", Beige);
        ImGui::Text("Coral"); ImGui::SameLine(); ImGui::ColorButton("##Coral", Coral);
        ImGui::Text("Lavender"); ImGui::SameLine(); ImGui::ColorButton("##Lavender", Lavender);
        ImGui::Text("Turquoise"); ImGui::SameLine(); ImGui::ColorButton("##Turquoise", Turquoise);
        ImGui::Text("Slate Blue"); ImGui::SameLine(); ImGui::ColorButton("##SlateBlue", SlateBlue);
        ImGui::Text("Tomato"); ImGui::SameLine(); ImGui::ColorButton("##Tomato", Tomato);
        ImGui::Text("Orchid"); ImGui::SameLine(); ImGui::ColorButton("##Orchid", Orchid);
        ImGui::Text("Chocolate"); ImGui::SameLine(); ImGui::ColorButton("##Chocolate", Chocolate);
        ImGui::Text("Dark Slate Gray"); ImGui::SameLine(); ImGui::ColorButton("##DarkSlateGray", DarkSlateGray);
        ImGui::Text("Black"); ImGui::SameLine(); ImGui::ColorButton("##Black", Black);
        ImGui::Text("Brown"); ImGui::SameLine(); ImGui::ColorButton("##Brown", Brown);
        ImGui::Text("DarkBrown"); ImGui::SameLine(); ImGui::ColorButton("##DarkBrown", DarkBrown);
    }
}