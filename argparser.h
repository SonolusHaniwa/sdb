#include "include/argparse.hpp"

string sim_mode;
string key_config_path = "";
int width = 1920;
int height = 1080;
double aspectRadio = 1.0 * width / height;
string engine_data_path;
string engine_configuration_path;
string level_data_path;
string skin_data_path;
string skin_texture_path;
string particle_data_path;
string particle_texture_data;
bool enable_command = true;
bool enable_gui = true;
bool use_x11 = false;

void argparser(int argc, char** argv) {
    argparse::ArgumentParser program(argv[0]);
    program.set_usage_max_line_width(80);
    program.add_description("This is Sonolus debugger/simulator (sdb)");
    program.add_usage_newline();
    program.add_argument("-m", "--mode").required().help("select mode for Sonolus simulator.").metavar("<play|watch|tutorial>").choices("play", "watch", "tutorial"); 
    program.add_usage_newline();
    auto &group = program.add_mutually_exclusive_group(true);
    group.add_argument("-c", "--config").help("specify the configuration file.").metavar("config.json");
    group.add_argument("-i", "--input-directory").help("specify the working directory.").metavar("data");
    program.add_argument("-k", "--key-mapping").help("specify the key mapping file.").metavar("key.json");
    program.add_usage_newline();
    program.add_argument("--width").help("specify the width of the window").metavar("1920").default_value(1920).scan<'i', int>();
    program.add_argument("--height").help("specify the height of the window").metavar("1080").default_value(1080).scan<'i', int>();
    program.add_usage_newline();
    program.add_argument("--engine-data").metavar("EngineData").help("specify the engine data file.");
    program.add_argument("--engine-configuration").metavar("engine.json").help("specify the engine configuration file.");
    program.add_usage_newline();
    program.add_argument("--level-data").metavar("LevelData").help("specify the level data file.");
    program.add_usage_newline();
    program.add_argument("--skin-data").metavar("SkinData").help("specify the skin data file.");
    program.add_argument("--skin-texture").metavar("SkinTexture").help("specify the skin texture file.");
    program.add_usage_newline();
    program.add_argument("--particle-data").metavar("ParticleData").help("specify the particle data file.");
    program.add_argument("--particle-texture").metavar("ParticleTexture").help("specify the particle texture file.");
    program.add_usage_newline();
    program.add_argument("--disable-command").help("disable interactive command line.").flag();
    program.add_argument("--disable-gui").help("disable GUI.").flag();
    program.add_argument("--use-x11").help("use X11 to render window.").flag();

    try {
        program.parse_args(argc, argv);
        sim_mode = program.get<string>("-m");
        if (program.is_used("-c")) {
            Json::Value config = json_decode(readFile(program.get<string>("-c")));
            engine_data_path = config["engine"][sim_mode].asString();
            engine_configuration_path = config["engine"]["config"].asString();
            level_data_path = config["level"]["data"].asString();
            skin_data_path = config["skin"]["data"].asString();
            skin_texture_path = config["skin"]["texture"].asString();
            particle_data_path = config["particle"]["data"].asString();
            particle_texture_data = config["particle"]["texture"].asString();
            width = config["window"]["width"].asInt();
            height = config["window"]["height"].asInt();
        }
        if (program.is_used("-i")) {
            string base = program.get<string>("-i");
            if (base.back() == '/') base.pop_back();
            if (sim_mode == "play") engine_data_path = base + "/EnginePlayData";
            else if (sim_mode == "watch") engine_data_path = base + "/EngineWatchData";
            else if (sim_mode == "tutorial") engine_data_path = base + "/EngineTutorialData";
            engine_configuration_path = base + "/engine.json";
            level_data_path = base + "/LevelData";
            skin_data_path = base + "/SkinData";
            skin_texture_path = base + "/SkinTexture";
            particle_data_path = base + "/ParticleData";
            particle_texture_data = base + "/ParticleTexture";
        }
        if (program.is_used("-k")) key_config_path = program.get<string>("-k");
        if (program.is_used("--width")) width = program.get<int>("--width");
        if (program.is_used("--height")) height = program.get<int>("--height");
        if (program.is_used("--engine-data")) engine_data_path = program.get<string>("--engine-data");
        if (program.is_used("--engine-configuration")) engine_configuration_path = program.get<string>("--engine-configuration");
        if (program.is_used("--level-data")) level_data_path = program.get<string>("--level-data");
        if (program.is_used("--skin-data")) skin_data_path = program.get<string>("--skin-data");
        if (program.is_used("--skin-texture")) skin_texture_path = program.get<string>("--skin-texture");
        if (program.is_used("--particle-data")) particle_data_path = program.get<string>("--particle-data");
        if (program.is_used("--particle-texture")) particle_texture_data = program.get<string>("--particle-texture");
        if (program.is_used("--disable-command")) enable_command = false;
        if (program.is_used("--disable-gui")) enable_gui = false;
        if (program.is_used("--use-x11")) use_x11 = true;
    } catch(const exception &e) {
        cerr << e.what() << endl;
        exit(1);
    }

    aspectRadio = 1.0 * width / height;
}