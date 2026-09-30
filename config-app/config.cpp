#include <bits/stdc++.h>
using namespace std;
#include "include/imgui.h"
#include "include/argparse.hpp"
#include "include/json.h"
#include "include/gzip.h"
#include "fonts/fa.h"

#ifndef DISABLE_FONT_COMPRESS
#include "fonts/fa-solid-900.h"
#include "fonts/msyh.h"
#include "fonts/msyhbd.h"
#endif

ImFont *normalFont, *boldFont;

string format(const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    char test;
    int size = vsnprintf(&test, 0, fmt, args) + 1;
    va_end(args);

    va_start(args, fmt);
    char buf[size];
    memset(buf, 0, size * sizeof(char));
    vsnprintf(buf, size, fmt, args);
    va_end(args);

    return string(buf, size);
}

string readFile(string path) {
    ifstream fin(path, ios::binary);
    fin.seekg(0, ios::end);
    int len = fin.tellg();
    fin.seekg(0, ios::beg);
    char* ch = new char[len];
    fin.read(ch, len);
    string s = string(ch, len);
    delete[] ch;
    return s;
}

bool fileExists(string path) {
    ifstream fin(path, ios::binary);
    fin.seekg(0, ios::end);
    return fin.tellg() != -1;
}

enum class TextAlignment {
    LeftTop,
    LeftCenter,
    LeftBottom,
    TopCenter,
    Center,
    BottomCenter,
    RightTop,
    RightCenter,
    RightBottom
};
void AlignText(ImVec2 size, TextAlignment align, string str, ImU32 color = IM_COL32(255, 255, 255, 255)) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 text_size = ImGui::CalcTextSize(str.c_str());
    if (size.x == -1) size.x = text_size.x;
    if (size.y == -1) size.y = text_size.y;
    if (text_size.x > size.x || text_size.y > size.y) {
        // Throw an error
    }

    float dx = size.x - text_size.x, dy = size.y - text_size.y;
    float rdx = 0, rdy = 0;
    if (align == TextAlignment::TopCenter || align == TextAlignment::Center || align == TextAlignment::BottomCenter) rdx = dx / 2;
    if (align == TextAlignment::RightTop || align == TextAlignment::RightCenter || align == TextAlignment::RightBottom) rdx = dx;
    if (align == TextAlignment::LeftCenter || align == TextAlignment::Center || align == TextAlignment::RightCenter) rdy = dy / 2;
    if (align == TextAlignment::LeftBottom|| align == TextAlignment::BottomCenter || align == TextAlignment::RightBottom) rdy = dy;
    ImGui::Dummy(size);
    draw_list->AddText(ImVec2(p.x + rdx, p.y + rdy), color, str.c_str());
}

void ToggleButton(string str_id, bool* v, function<void(bool)> callback) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight() * 2;
    float width = height * 2.0f;
    float block_height = height * 0.5f;
    float block_width = (width - height + block_height) * 0.5f;

    ImGui::InvisibleButton(str_id.c_str(), ImVec2(width, height));
    if (ImGui::IsItemClicked()) {
        *v = !*v;
        callback(*v);
    }

    float t = *v ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;
    float ANIM_SPEED = 0.125f;
    if (g.LastActiveId == g.CurrentWindow->GetID(str_id.c_str())) { // && g.LastActiveIdTimer < ANIM_SPEED)
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg;
    if (ImGui::IsItemHovered()) col_bg = IM_COL32(255, 255, 255, 64);
    else col_bg = IM_COL32(255, 255, 255, 32);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg);
    draw_list->AddRectFilled(
        ImVec2(p.x + (height - block_height) / 2 + t * (width - block_height - block_width), p.y + (height - block_height) / 2), 
        ImVec2(p.x + (height - block_height) / 2 + t * (width - block_height - block_width) + block_width, p.y + (height - block_height) / 2 + block_height), 
        t < 0.5 ? IM_COL32(241, 70, 104, 255) : IM_COL32(72, 199, 142, 255)
    );
}

void Combo(string str_id, ImVec2 size, int* v, vector<string> options, function<void(int)> callback) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGuiContext& g = *GImGui;

    float width = size.x, height = size.y;
    ImRect bb = ImRect(p.x, p.y, p.x + width, p.y + height);
    
    ImGui::InvisibleButton(str_id.c_str(), ImVec2(width, height));
    bool hovered, held;
    ImGuiID id = g.CurrentWindow->GetID(str_id.c_str());
    // bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    bool pressed = ImGui::IsItemClicked();
    const ImGuiID popup_id = ImHashStr("##ComboPopup", 0, id);
    bool popup_open = ImGui::IsPopupOpen(popup_id, ImGuiPopupFlags_None);
    if (pressed && !popup_open)
    {
        ImGui::OpenPopupEx(popup_id, ImGuiPopupFlags_None);
        popup_open = true;
    }
    if (popup_open) {
        ImGui::BeginComboPopup(popup_id, bb, 0);
        for (int i = 0; i < options.size(); i++) {
            bool is_selected = (*v == i);
            if (ImGui::Selectable(options[i].c_str(), is_selected)) {
                *v = i;
                callback(i);
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImU32 col_bg;
    if (ImGui::IsItemHovered()) col_bg = IM_COL32(255, 255, 255, 64);
    else col_bg = IM_COL32(255, 255, 255, 32);

    ImVec2 text_size = ImGui::CalcTextSize(options[*v].c_str());
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg);
    draw_list->AddText(ImVec2(p.x + (size.x - text_size.x) / 2, p.y + (size.y - text_size.y) / 2), IM_COL32(255, 255, 255, 255), options[*v].c_str());
}

void Slider(string str_id, ImVec2 size, float* v, float minval, float maxval, float step, function<void(float)> callback) {
    assert(minval <= maxval);
    assert(step > 0); 

    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = ImGui::GetCurrentWindow();

    float box1_width = size.x, box1_height = size.y;
    float box2_x = box1_height / 4, box2_y = box1_height / 4;
    float box2_width = box1_width - box1_height / 2, box2_height = box1_height / 2;
    float box3_x = box2_x + box2_height / 3, box3_y = box2_y + box2_height / 3;
    float box3_width = box2_width - box2_height / 3 * 2, box3_height = box2_height / 3;
    
    ImGui::InvisibleButton(str_id.c_str(), ImVec2(box1_width, box1_height));
    ImGuiID id = g.CurrentWindow->GetID(str_id.c_str());
    bool clicked = ImGui::IsItemHovered() && ImGui::IsMouseClicked(0, ImGuiInputFlags_None, id);
    bool make_active = clicked || g.NavActivateId == id;
    if (make_active) {
        if (ImGui::IsMouseReleased(0)) {
            ImGui::ActivateItemByID(0);
        } else {
            if (clicked) ImGui::SetKeyOwner(ImGuiKey_MouseLeft, id);
            ImGui::ActivateItemByID(id);
            ImVec2 pos = ImGui::GetMousePos();
            float newval = round((pos.x - box3_x - p.x) / box3_width * (maxval - minval) / step) * step + minval;
            if (newval < minval) newval = minval;
            if (newval > maxval) newval = maxval;
            *v = newval;
            callback(newval);
        }
    }

    ImU32 col_bg;
    if (ImGui::IsItemHovered()) col_bg = IM_COL32(255, 255, 255, 64);
    else col_bg = IM_COL32(255, 255, 255, 32);

    float t = (*v - minval) / (maxval - minval);

    draw_list->AddRectFilled(p, ImVec2(p.x + box1_width, p.y + box1_height), col_bg);
    draw_list->AddRectFilled(ImVec2(p.x + box2_x, p.y + box2_y), ImVec2(p.x + box2_x + box2_width, p.y + box2_y + box2_height), IM_COL32(0, 0, 0, 64));
    draw_list->AddRectFilled(ImVec2(p.x + box3_x, p.y + box3_y), ImVec2(p.x + box3_x + t * box3_width, p.y + box3_y + box3_height), IM_COL32(255, 255, 255, 255));
}

void IconButton(string str_id, const char* icon, float fontBase, function<void()> callback, bool disabled) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight() * 2;
    float width = height;

    ImGui::InvisibleButton(str_id.c_str(), ImVec2(width, height));
    if (ImGui::IsItemClicked() && !disabled) callback();

    ImU32 col_bg;
    if (disabled) col_bg = IM_COL32(255, 255, 255, 8);
    else if (ImGui::IsItemHovered()) col_bg = IM_COL32(255, 255, 255, 64);
    else col_bg = IM_COL32(255, 255, 255, 32);

    ImVec2 textSize = ImGui::CalcTextSize(icon);
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg);
    draw_list->AddText(ImVec2(p.x + (width - textSize.x) / 2, p.y + (height - fontBase) / 2), disabled ? IM_COL32(255, 255, 255, 64) : IM_COL32(255, 255, 255, 255), icon);
}

string currConfigPath;
Json::Value engineConfig;
Json::Value currConfig;
void saveConfig() {
    string content = json_encode(currConfig);
    ofstream fout(currConfigPath, ios::binary);
    fout.write(content.c_str(), content.size());
}

bool *bool_opt, *bool_array;
int *int_opt, *int_array;
float *float_opt, *float_array;

bool firstLoop = true;
void renderLoop() {
    ImGui::Begin(
        "ImGui", 
        NULL,
        ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoBackground
    );
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    int realw = (w > 1280 ? 1280 : w);
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::SetWindowSize(ImVec2(w, h));
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only

    int bool_num = 0, int_num = 0, float_num = 0;
    
    for (int i = 0; i < engineConfig["options"].size(); i++) {
        Json::Value option = engineConfig["options"][i];
        if (option["type"].asString() == "toggle") bool_num++;
        else if (option["type"].asString() == "select") int_num++;
        else if (option["type"].asString() == "slider") float_num++;
    }

    if (firstLoop) {
        bool_array = new bool[bool_num];
        int_array = new int[int_num];
        float_array = new float[float_num];
    }
    bool_opt = bool_array, int_opt = int_array, float_opt = float_array;
    float height = ImGui::GetFrameHeight();

    for (int i = 0; i < engineConfig["options"].size(); i++) {
        Json::Value option = engineConfig["options"][i];
        if (option["type"].asString() == "toggle") {
            if (!currConfig["options"].isMember(option["name"].asString()) || !currConfig["options"][option["name"].asString()].isDouble())
                currConfig["options"][option["name"].asString()] = option["def"].asFloat();
            *bool_opt = currConfig["options"][option["name"].asString()].asFloat();
            
            ImGui::Dummy(ImVec2((w - realw) / 2, 0));
            ImGui::SameLine(0, 0);
            ImGui::PushFont(boldFont);
            AlignText(ImVec2(-1, height * 2), TextAlignment::LeftCenter, option["name"].asString());
            ImGui::PopFont();

            ImGui::Dummy(ImVec2((w - realw) / 2, 0));
            ImGui::SameLine(0, height * 2);
            AlignText(ImVec2(height / 3 * 8, height * 2), TextAlignment::Center, format("%s", *bool_opt ? "ON" : "OFF"));
            ImGui::SameLine(0, realw - height * 2 - height / 3 * 8 - height * 4 - height / 2 - height * 2);
            ToggleButton("toggle #" + to_string(i), bool_opt++, [option](bool newval){
                currConfig["options"][option["name"].asString()] = float(newval);
                saveConfig();
            });
            ImGui::SameLine(0, height / 2);
            IconButton("clear #" + to_string(i), ICON_FA_ARROW_ROTATE_LEFT, 16, [option, i](){
                currConfig["options"][option["name"].asString()] = option["def"].asFloat();
                ImGui::ActivateItemByID(GImGui->CurrentWindow->GetID(("toggle #" + to_string(i)).c_str()));
                saveConfig();
            }, currConfig["options"][option["name"].asString()].asFloat() == option["def"].asFloat());
        }
        else if (option["type"].asString() == "select") {
            if (!currConfig["options"].isMember(option["name"].asString()) || !currConfig["options"][option["name"].asString()].isDouble())
                currConfig["options"][option["name"].asString()] = option["def"].asFloat();
            *int_opt = currConfig["options"][option["name"].asString()].asFloat();

            vector<string> options;
            for (int j = 0; j < option["values"].size(); j++)
                options.push_back(option["values"][j].asString());
            
            ImGui::Dummy(ImVec2((w - realw) / 2, 0));
            ImGui::SameLine(0, 0);
            ImGui::PushFont(boldFont);
            AlignText(ImVec2(-1, height * 2), TextAlignment::LeftCenter, option["name"].asString());
            ImGui::PopFont();

            ImGui::Dummy(ImVec2((w - realw) / 2, height * 2)); 
            ImGui::SameLine(0, realw - 8 * height - height / 2 - height * 2);
            ImGui::SetNextItemWidth(8 * height);
            Combo(("select #" + to_string(i)).c_str(), ImVec2(8 * height, 2 * height), int_opt++, options, [option](int newval){
                currConfig["options"][option["name"].asString()] = float(newval);
                saveConfig();
            });
            ImGui::SameLine(0, height / 2);
            IconButton("clear #" + to_string(i), ICON_FA_ARROW_ROTATE_LEFT, 16, [option, i](){
                currConfig["options"][option["name"].asString()] = option["def"].asFloat();
                saveConfig();
            }, currConfig["options"][option["name"].asString()].asFloat() == option["def"].asFloat());
        }
        else if (option["type"].asString() == "slider") {
            if (!currConfig["options"].isMember(option["name"].asString()) || !currConfig["options"][option["name"].asString()].isDouble())
                currConfig["options"][option["name"].asString()] = option["def"].asFloat();
            *float_opt = currConfig["options"][option["name"].asString()].asFloat();
            
            ImGui::Dummy(ImVec2((w - realw) / 2, 0));
            ImGui::SameLine(0, 0);
            ImGui::PushFont(boldFont);
            AlignText(ImVec2(-1, height * 2), TextAlignment::LeftCenter, option["name"].asString());
            ImGui::PopFont();

            ImGui::Dummy(ImVec2((w - realw) / 2, 0));
            ImGui::SameLine(0, height * 2);
            AlignText(ImVec2(height / 3 * 8, height * 2), TextAlignment::Center, format("%.3f", *float_opt));
            ImGui::SameLine(0, height / 2);
            IconButton("left #" + to_string(i), ICON_FA_CHEVRON_LEFT, 16, [option, i](){
                float step = option["step"].asFloat();
                float minval = option["min"].asFloat();
                float maxval = option["max"].asFloat();
                float value = currConfig["options"][option["name"].asString()].asFloat() - step;

                float newval = round((value - minval) / step) * step + minval;
                if (newval < minval) newval = minval;
                if (newval > maxval) newval = maxval;
                currConfig["options"][option["name"].asString()] = newval;
                saveConfig();
            }, currConfig["options"][option["name"].asString()].asFloat() == option["min"].asFloat());
            ImGui::SameLine(0, 0);
            Slider(
                "slider #" + to_string(i), 
                ImVec2(realw - height * 2 - height / 3 * 8 - height / 2 - height * 2 - height * 2 - height / 2 - height * 2, height * 2), 
                float_opt++,
                option["min"].asFloat(),
                option["max"].asFloat(),
                option["step"].asFloat(),
                [option](float val){
                    currConfig["options"][option["name"].asString()] = val;
                    saveConfig();
                }
            );
            ImGui::SameLine(0, 0);
            IconButton("right #" + to_string(i), ICON_FA_CHEVRON_RIGHT, 16, [option, i](){
                float step = option["step"].asFloat();
                float minval = option["min"].asFloat();
                float maxval = option["max"].asFloat();
                float value = currConfig["options"][option["name"].asString()].asFloat() + step;

                float newval = round((value - minval) / step) * step + minval;
                if (newval < minval) newval = minval;
                if (newval > maxval) newval = maxval;
                currConfig["options"][option["name"].asString()] = newval;
                saveConfig();
            }, currConfig["options"][option["name"].asString()].asFloat() == option["max"].asFloat());
            ImGui::SameLine(0, height / 2);
            IconButton("clear #" + to_string(i), ICON_FA_ARROW_ROTATE_LEFT, 16, [option, i](){
                currConfig["options"][option["name"].asString()] = option["def"].asFloat();
                saveConfig();
            }, currConfig["options"][option["name"].asString()].asFloat() == option["def"].asFloat());
        }
    }

    if (firstLoop) {
        saveConfig();
        firstLoop = false;
    }

    ImGui::End();
}

int main(int argc, char** argv) {
    engineConfig = json_decode(decompress_gzip(readFile(argv[1])));
    if (fileExists(argv[2]))
        currConfig = json_decode(readFile(argv[2]));
    currConfigPath = argv[2];
    currConfig["order"].resize(0);
    for (int i = 0; i < engineConfig["options"].size(); i++) 
        currConfig["order"].append(engineConfig["options"][i]["name"].asString());
    if (!currConfig["options"].isObject())
        currConfig["options"] = Json::ValueType::objectValue;
    initImGui(1920, 1080, "Sonolus Engine Configuration", true, true, 24);
#ifndef DISABLE_FONT_COMPRESS
    normalFont = addFontFromMemory(msyh_compressed_data, msyh_compressed_size, 24);
    addIconFromMemory(fa_solid_900_compressed_data, fa_solid_900_compressed_size, ICON_MIN_FA, ICON_MAX_16_FA, 24);
    boldFont = addFontFromMemory(msyhbd_compressed_data, msyhbd_compressed_size, 24);
    addIconFromMemory(fa_solid_900_compressed_data, fa_solid_900_compressed_size, ICON_MIN_FA, ICON_MAX_16_FA, 24);
#else
    normalFont = addFont("./fonts/msyh.ttf", 24);
    addIcon("./fonts/fa-solid-900.ttf", ICON_MIN_FA, ICON_MAX_16_FA, 24);
    boldFont = addFont("./fonts/msyhbd.ttf", 24);
    addIcon("./fonts/fa-solid-900.ttf", ICON_MIN_FA, ICON_MAX_16_FA, 24);
#endif
    runImGui(renderLoop);
    cleanImGui();
}