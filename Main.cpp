#include "Menu.h"
#include <iostream>

using namespace std;


int main() {
    // Crear el objeto menu


    Menu* menuPrincipal = new Menu();

 
    // Ejecutar el programa
    menuPrincipal->ejecutar();

    // Liberar memoria
    delete menuPrincipal;

    return 0;
}