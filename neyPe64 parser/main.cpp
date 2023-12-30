#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include "peh.hpp"

using namespace std;
bool showMsg = true;


HANDLE open(const CHAR* path, int argc, char* argv[]) {
    HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hFile == INVALID_HANDLE_VALUE){
        CloseHandle(hFile);
        delete[] path;
        cout << "the file does not exist or we were unable to open it" << endl;
        if (argc == 1 || argc < 1) {
            main(argc, argv);
        }
    }
    return hFile;
}



int main(int argc, char* argv[]) {
    string paths;

    if (argc > 1) {
        paths = argv[1];
    } else {
        if (showMsg) {
            cout << MAGENTA << "\n __   __                                                     _ \n"
                    " \\ \\ / /  _   _   _ __     __ _   _ __ ___     __ _   _ __  (_)\n"
                    "  \\ V /  | | | | | '_ \\   / _` | | '_ ` _ \\   / _` | | '__| | |\n"
                    "   | |   | |_| | | | | | | (_| | | | | | | | | (_| | | |    | |\n"
                    "   |_|    \\__,_| |_| |_|  \\__,_| |_| |_| |_|  \\__,_| |_|    |_|" << "\n\n\n";

            cout << "hi, this is a small pe file analyzer. Don't hesitate to join the discord server:\n"
                    "https://discord.gg/420sec, my discord username is \"lunapeiy\"" << RESET << endl;
            showMsg = false;
        }

        cout << GREEN << "\nEnter the path of your PE file: " ;
        getline(cin, paths);
        cout << RESET;
        if (paths == "exit"|| paths == "q"|| paths == "quit" || paths.empty()) {
            cout << "goodbye" << endl;
            return 0;
        }
        paths.erase(remove(paths.begin(), paths.end(), '\"'), paths.end());
    }


    const int size = paths.length();
    char* path = new char[size + 1];
    strcpy(path, paths.c_str());

    HANDLE hFile = open(path, argc, argv);

    header(hFile);
    idata(hFile);
    edata(path);
    symbole(hFile);
    psI(hFile);

    delete[] path;
    CloseHandle(hFile);
    cout << "\n" << endl;


    if (argc == 1 || argc < 1) {
        main(argc, argv);
    }

    return 0;
}
