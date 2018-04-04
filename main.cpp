#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "Allegro.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
    BITMAP *fond;
    fond =load_bitmap("pics/fond.bmp",NULL);

    /// Le nom du r�pertoire o� se trouvent les images � charger
    //
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();
    int choix=0;

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {

        if(choix == 0)
            {
                choix = Menu();
            blit(fond, grman::page, 0,0, 0, 0, 1024,768);
        blit(grman::page, screen, 0,0, 0, 0, 1024,768);
            }
        if(choix ==1 )
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
        }

         if(choix==2)
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
        }

         if(choix==3)
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
        }
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


