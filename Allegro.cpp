#include "allegro.h"

///Fonction Menu

int Menu()
{
    ///tant qu'on a pas cliqué sur un bouton
    while(mouse_b != 1)
    {
        ///Si l'utilisateur choisi la premiere option en cliquant dessus
        if((mouse_x > 300 && mouse_x < 725) && mouse_b){
            if(mouse_y > 105 && mouse_y < 210) return 1;

        /// Si l'utilisateur choisi la deuxieme option en cliquant dessus
            else if(mouse_y > 280 && mouse_y < 385) return 2;

        ///Si l'utilisateur choisi la deuxieme option en cliquant dessus
            else if(mouse_y > 440 && mouse_y < 545) return 3;

        ///Si l'utilisateur choisi de quitter le jeu
            else if(mouse_y > 615 && mouse_y < 720) exit(0);///pour quitter le jeu
        }
    }
}
