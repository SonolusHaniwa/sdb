#include <bits/stdc++.h>
#include <chrono>
#include <cstdlib>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <readline/readline.h>
#include <readline/history.h>
using namespace std;

string readFile(string path) {
    ifstream fin(path, ios::binary);
    fin.seekg(0, ios::end);
    int len = fin.tellg();
    if (len == -1) {
        cerr << "\"" << path << "\": No such file or directory." << endl;
        exit(1);
    }
    fin.seekg(0, ios::beg);
    char* ch = new char[len];
    fin.read(ch, len);
    string s = string(ch, len);
    delete[] ch;
    return s;
}

bool shouldStop = false, stopped = false;
bool forceStop = false;
void signalHandler(int signal) {
    if (shouldStop) {
        if (!stopped) {
            forceStop = true;
        } 
        // else {
        //     cout << "Quit" << endl;
        // }
    } else {
        shouldStop = true;
    }
}

#include "include/json.h"
#include "include/gzip.h"
#include "include/png.h"
#include "include/utils.h"
#include "engine/skin.h"
#include "engine/particle.h"
#include "engine/touch.h"
#include "argparser.h"
void commandLine();
void display(double);
function<void(int, int)> custom_onresize = [](int, int){};
// Command, Mode 共用属性
set<int> activeEntities;
int activePointer = 0;
int targetActiveCount = 0;
vector<double> spawnOrder;
vector<int> spawnQueue;
vector<double> spawnTime, despawnTime;
bool needSkip = false; double skipTime;

// 全局信息
GLFWwindow* window;

Json::Value engineData, levelData;
Json::Value skinData;
image skinTexture;
Json::Value particleData;
image particleTexture;

map<int, glTexture> textures;
map<int, SpriteTransform> skinTransforms;
map<string, int> engineSpriteId;

map<int, ParticleDataEffect> particleEffects;
vector<glTexture> particleTextures;
map<string, int> engineParticleId;

function<void(double)> glEvents[512] = { [](double){} };
int glEventsCount = 0;
pthread_mutex_t touchMtx;
void clearGLEvent() {
    pthread_mutex_lock(&touchMtx);
    glEventsCount = 0;
    pthread_mutex_unlock(&touchMtx);
}
void addGLEvent(function<void(double)> event) { 
    pthread_mutex_lock(&touchMtx);
    glEvents[glEventsCount++] = event;
    pthread_mutex_unlock(&touchMtx);
}

// vector<double> options = { 0, 10, 1, 0, 1, 0, 1, 1, 0, 1, 0.8, 0, 1, 0, 0, 0 }; // For Sirius
// vector<double> options = { 0, 0, 1, 1, 1, 1, 1, 0.5, 0, 0, 0, 0, 1 }; // For Phigros
// vector<double> options = { 1, 10.7, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0.6, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0 }; // For PJSekai
// vector<double> options = { 0, 1, 0, 0 }; // For Snake
vector<double> options;
#include "sonolus.h"
#include "command.h"
#include "opengl.h"

int main(int argc, char** argv) {
    argparser(argc, argv);

    if (key_config_path != "") {
        Json::Value key_config = json_decode(readFile(key_config_path));
        for (int i = 0; i < key_config.size(); i++) {
            keyPos[key_config[i]["key"].asInt()] = {
                key_config[i]["x"].asDouble(),
                key_config[i]["y"].asDouble()
            };
        }
    }

    Json::Value engine_options = json_decode(readFile(engine_configuration_path));
    for (int i = 0; i < engine_options["order"].size(); i++) 
        options.push_back(engine_options["options"][engine_options["order"][i].asString()].asDouble());

    opengl_init();
    engineData = json_decode(decompress_gzip(readFile(engine_data_path)));
    levelData = json_decode(decompress_gzip(readFile(level_data_path)));
    skinData = json_decode(decompress_gzip(readFile(skin_data_path)));
    skinTexture = readImage(skin_texture_path);
    particleData = json_decode(decompress_gzip(readFile(particle_data_path)));
    particleTexture = readImage(particle_texture_data);
    for (int i = 0; i < engineData["skin"]["sprites"].size(); i++)
        engineSpriteId[engineData["skin"]["sprites"][i]["name"].asString()] = engineData["skin"]["sprites"][i]["id"].asInt();
    for (int i = 0; i < skinData["sprites"].size(); i++) {
        if (engineSpriteId.count(skinData["sprites"][i]["name"].asString()) == 0) continue;
        int engineId = engineSpriteId[skinData["sprites"][i]["name"].asString()];
        Json::Value data = skinData["sprites"][i];
        image sprite = image(data["w"].asInt(), data["h"].asInt());
        for (int x = data["x"].asInt(), x0 = 0; x < data["x"].asInt() + data["w"].asInt(); x++, x0++) {
            for (int y = data["y"].asInt(), y0 = 0; y < data["y"].asInt() + data["h"].asInt(); y++, y0++) {
                sprite.data[y0][x0 * 4] = skinTexture.data[y][x * 4];
                sprite.data[y0][x0 * 4 + 1] = skinTexture.data[y][x * 4 + 1];
                sprite.data[y0][x0 * 4 + 2] = skinTexture.data[y][x * 4 + 2];
                sprite.data[y0][x0 * 4 + 3] = skinTexture.data[y][x * 4 + 3];
            }
        }
        textures[engineId] = createTextureFromImage(sprite);
        skinTransforms[engineId] = SpriteTransform(skinData["sprites"][i]["transform"]);
    }

    for (int i = 0; i < engineData["particle"]["effects"].size(); i++)
        engineParticleId[engineData["particle"]["effects"][i]["name"].asString()] = engineData["particle"]["effects"][i]["id"].asInt();
    for (int i = 0; i < particleData["sprites"].size(); i++) {
        Json::Value data = particleData["sprites"][i];
        image sprite = image(data["w"].asInt(), data["h"].asInt());
        for (int x = data["x"].asInt(), x0 = 0; x < data["x"].asInt() + data["w"].asInt(); x++, x0++) {
            for (int y = data["y"].asInt(), y0 = 0; y < data["y"].asInt() + data["h"].asInt(); y++, y0++) {
                sprite.data[y0][x0 * 4] = particleTexture.data[y][x * 4];
                sprite.data[y0][x0 * 4 + 1] = particleTexture.data[y][x * 4 + 1];
                sprite.data[y0][x0 * 4 + 2] = particleTexture.data[y][x * 4 + 2];
                sprite.data[y0][x0 * 4 + 3] = particleTexture.data[y][x * 4 + 3];
            }
        }
        particleTextures.push_back(createTextureFromImage(sprite));
    }
    for (int i = 0; i < particleData["effects"].size(); i++) {
        if (engineParticleId.count(particleData["effects"][i]["name"].asString()) == 0) continue;
        int engineId = engineParticleId[particleData["effects"][i]["name"].asString()];
        particleEffects[engineId] = ParticleDataEffect(particleData["effects"][i]);
    }

    if (engine_rom_path != "") {
        bool isLittleEndian = true;
        uint32_t i = 0x12345678;
        uint8_t *p = (uint8_t*)&i;
        if ((*p == 0x12) & (*(p + 1) == 0x34)) isLittleEndian = false;

        string engineRomData = decompress_gzip(readFile(engine_rom_path));
        for (int i = 0; i < engineRomData.size(); i += 4) {
            float data;
            // Little Endian -> Big Endian if OS is Big Endian
            if (!isLittleEndian) {
                swap(engineRomData[i], engineRomData[i + 3]);
                swap(engineRomData[i + 1], engineRomData[i + 2]);
            }
            memcpy(&data, engineRomData.data() + i, sizeof(float));
            romData.push_back(data);
        }
    }

    if (enable_command) signal(SIGINT, signalHandler);
    if (sim_mode == "play") play::main();
    else if (sim_mode == "tutorial") tutorial::main();
    else if (sim_mode == "watch") watch::main();
}