#include <iostream>
#include "MainWnd.h"
#include <fstream>
#include <typeinfo>
#include <filesystem>
#include <string>
#include <map>


namespace fs = std::filesystem;

int main(int args, char* argv[])
{
    fs::path startPath;
    startPath = argv[0];
    MainWnd mw;
    mw.LoopMsg(startPath.parent_path());
}