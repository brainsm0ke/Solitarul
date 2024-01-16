#include <windows.h>
#include <commdlg.h>
#include <winuser.h>

#include <fstream>
#include <iostream>

#include "joc.h"

TablaDeJoc IncarcaTabla(char* path){
    TablaDeJoc T;
    T.height = 400;
    T.width = 400;
    std::ifstream file(path);
    if(file.is_open()){
        file >> T.n;
        char c;
        for(int i=0;i < T.n; i++){
            for(int j=0;j < T.n; j++){
                file.get(c);
                while(c == '\n') file.get(c);
                if(c == '_') T.loc[i][j] = tipLoc::invalid;
                else if(c == 'o') T.loc[i][j] = tipLoc::gol;
                else if(c == '.') T.loc[i][j] = tipLoc::piesa;
            }
        }
    } else throw 0;
    return T;
}

void SelectareFisierTabla(char* c, text& text) {
    OPENFILENAMEA ofn;
    ofn.lStructSize = sizeof(OPENFILENAMEA);
    ofn.hwndOwner = GetFocus();
    ofn.lpstrFilter = "Text file (*.txt)\0*.txt\0\0";
    ofn.lpstrCustomFilter = NULL;
    ofn.lpstrFile = c;
    ofn.nFilterIndex = 0;
    ofn.nMaxFile = 100;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrTitle = text.alege_un_alt_tabel;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if(!GetOpenFileNameA(&ofn)){
        c[0] = '\0';
    }
}