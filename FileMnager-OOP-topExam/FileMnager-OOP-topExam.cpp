#include <iostream>
#include "MainWnd.h"
#include <fstream>
#include <typeinfo>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void createFile(fs::path fn)
{
    std::ofstream file;
    file.open(fn);
    file.close();
}

void deleteFile(fs::path fn)
{
    fs::remove(fn);
}

void showDirR(fs::path fn)
{
    std::cout << "\nCatalog " << fn << ":";
    std::cout << "\n";
    for (auto p : fs::recursive_directory_iterator(fn))
        std::cout << "\n" << p;
}

int Menu(int size, std::string* punkts)
{
    std::cout << "\n\t\tmenu";
    for (int i = 0; i < size; i++)
    {
        std::cout << "\n\t" << i + 1 << ". " << punkts[i];
    }
    std::cout << "\n\t0. Exit";
    std::cout << "\n\tWhat you want? -> ";
    int sel;
    std::cin >> sel;
    return sel;
}

int Menu(std::list<std::string>& punkts)
{
    int num = -1;
    if (!punkts.empty())
    {
        int active = 1;
        int key = 0;
        while (key != 13)
        {
            num = 1;
            system("cls");
            showDirR("e:\\1\\");
            std::cout << "\n\t\tMenu";
            for (auto p = punkts.begin(); p != punkts.end(); p++)
            {
                if (active == num)
                    std::cout << "\x1b[30;47m";
                std::cout << "\n\t#" << num << ". " << *p;
                if (active == num)
                    std::cout << "\x1b[0m";
                num++;
            }
            key = _getch();
            if (key == 224)
                key = _getch();
            switch (key)
            {
            case 72:
                active--;
                if (active < 1)
                    active = punkts.size();
                break;
            case 80:
                active++;
                if (active > punkts.size())
                    active = 1;
                break;
            case 13:
                return active;
            }
        }
    }
}

int main(int args, char* argv[])
{
    MainWnd mw;
    mw.LoopMsg();
    std::list<std::string> menuItems
    {
        "Create file",
        "Delete file",
        "Rename file",
        "Move file",
        "Show file",
        "Exit"
    };

    std::string tmp;
    if (args > 1 && fs::exists(argv[1]))
        tmp = argv[1];
    else
        tmp = "e:\\1";
    tmp += "\\";
    fs::path cur(tmp);
    fs::path fiio;
    bool exit = false;
    while (!exit)
    {
        system("cls");
        switch (Menu(menuItems))
        {
        case 1:
        {
            std::cout << "\nInpun file name\n";
            std::cin >> tmp;
            fiio = cur;
            fiio.replace_filename(tmp);
            createFile(fiio);
            break;
        }
        case 2:
        {
            std::cout << "\nInpun file name\n";
            std::cin >> tmp;
            fiio = cur;
            fiio.replace_filename(tmp);
            deleteFile(fiio);
            break;
        }
        case 3:
        {
            std::cout << "\nInpun file name\n";
            std::cin >> tmp;
            fiio = cur;
            fiio.replace_filename(tmp);
            std::cout << "\nInpun new file name\n";
            std::cin >> tmp;
            fs::path newName = cur;
            newName.replace_filename(tmp);
            fs::rename(fiio, newName);
            break;
        }
        case 4:
        {
            std::cout << "\nInpun file name\n";
            std::cin >> tmp;
            fiio = cur;
            fiio.replace_filename(tmp);
            fs::path newName;
            std::cout << "\nInpun destination folder\n";
            std::cin >> newName;
            newName.replace_filename(tmp);
            fs::rename(fiio, newName);
            break;
        }
        case 5:
        {
            std::cout << "\nInpun file name\n";
            std::cin >> tmp;
            fiio = cur;
            fiio.replace_filename(tmp);
            std::ifstream file;
            file.open(fiio);
            if (!file.is_open())
                std::cout << "\nCan't open file " << fiio;
            else
                while (!file.eof())
                {
                    getline(file, tmp);
                    std::cout << "\n" << tmp;
                }
            system("pause");
            break;
        }
        case 6:
        {
            exit = true;
            break;
        }
        default:
            break;
        }

    }

}
