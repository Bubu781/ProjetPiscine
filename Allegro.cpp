#include "allegro.h"

int Menu()
{
    ///tant qu'on a pas cliqu� sur un bouton
    while(mouse_b != 1)
    {
        if((mouse_x > 300 && mouse_x < 725) && mouse_b){
            if(mouse_y > 105 && mouse_y < 210) return 1;
            else if(mouse_y > 280 && mouse_y < 385) return 2;
            else if(mouse_y > 440 && mouse_y < 545) return 3;
            else if(mouse_y > 615 && mouse_y < 720) exit(0);///pour quitter le jeu
        }
    }


    //std::cout<< "bite";
}
