# Solitarul
Implementarea jocului ***Solitarul*** in BGI pentru disciplina ***Introducere in programare***

## Necesitati
Trebuie instalat [compilatorul tdm-gcc](https://jmeubank.github.io/tdm-gcc/download/) (versiunea de 32 de biti) si [libraria WinBGIm](https://winbgim.codecutter.org/) (headerele vor fi puse in folderul ***include*** al compilatorului, respectiv fisierele **.a** vor fi puse in folderul ***lib*** al compilatorului).
De asemenea trebuie instalat [CMake](https://cmake.org/).

## Configurare (VS Code)
Trebuie instalata extensia _CMake_ si _CMake Tools_ pentru VS Code.
Dupa instalarea extensiilor apasati **Ctrl+Shift+P** si selectati `CMake: Scan for kits` , acesta va genera automat kituri pentru proiect, pentru TDM-GCC va genera kit-ul cu nume _"GCC **versiune** mingw32"_

Din nefericire trebuie facute modificari la kit, altfel da eroarea `Unable to determine what CMake generator to use`. Apasati din nou **Ctrl+Shift+P** si selectati `CMake: Edit User-Local CMake Kits`, va aparea un tab nou numit _cmake-tools-kits.json_, adaugati:
```
"preferredGenerator": {
      "name": "MinGW Makefiles"
},
```
in kit-ul respectiv.

Dupa ce ati finalizat apasati **Ctrl+Shift+P** si selectati `CMake: Select a Kit` dupa care selectati kit-ul respectiv.

Pentru compilare apasati **Ctrl-F5** sau pe butonul _play_ din bara de jos, stanga.
