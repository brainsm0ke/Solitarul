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
                else if(c == '.') T.loc[i][j] = tipLoc::gol;
                else if(c == 'o') T.loc[i][j] = tipLoc::piesa;
            }
        }
    } else throw 0;
    return T;
}