#include "include/Screen.hpp"
#include <ctime>


int main(){
    srand(static_cast<unsigned>(time(NULL)));
    Screen screen;
    while(screen.running()){
        
        screen.update();
        screen.render();
    }

    return 0;
}


