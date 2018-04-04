#include "allegro.h"

int Menu()
{
    ///Declaration des variables

    int fond;

    ///tant qu'on a pas cliqué sur un bouton
    if((mouse_b&1) && (mouse_x>300 && mouse_x<725))
    {

        if(mouse_y>105 && mouse_y<210)
        {
            fond=1;
            return fond;
        }
        if(mouse_y>280 && mouse_y<385)
        {
            fond=2;
            return fond;
        }
        if(mouse_y>440 && mouse_y<545)
        {
            fond=3;
            return fond;
        }
        ///pour quitter le jeu
        if(mouse_y>615 && mouse_y<720)
            exit(0);
    }
}
