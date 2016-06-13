#pragma once
#include <string>
#include <array>
class Path{
public:
    Path(const char * path);
    Path operator=(const char* path);
    Path& operator+=(const char* path);
private:
    std::string buff;
};

const Path PATH_INSTALL_DIR = _INSTALL_PREFIX;

const std::array<std::string, 2> SEARCH_PATHS_PREFIX= {
        _INSTALL_PREFIX, // /usr/local in OSX and Mac and C:\Program Files (x86) in Windows
        _SRC_DIR, // Source directory
};

const std::array<std::string, 3> SEARCH_PATHS_SUFFIX = {
#ifdef WIN32
        "share",
        "assets",
        "share\\superteacher"
#else
        "share/superteacher",
        "share",
        "assets",
#endif
};


std::string get_file(std::string file);

const std::string MATHLETE = "fonts/ThirdParty/Mathlete/Mathlete-Skinny.otf";
const std::string SONG_MENU = "audio/ThirdParty/ForgottenClocktower.wav";
//const std::string SONG_1 = "audio/ThirdParty/generic-8-bit-jrpg-soundtrack/08 - Overworld.ogg";
const std::string SONG_1 = "audio/ThirdParty/Super Teacher.wav";
//const std::string SONG_1 = "audio/ThirdParty/hold-the-line-orchestral-remix/hold the line_0.flac";

