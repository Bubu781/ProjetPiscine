#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "Allegro.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
    BITMAP *fond;
    int choix=0;
    fond =load_bitmap("pics/fond.bmp",NULL);

    /// Le nom du r�pertoire o� se trouvent les images � charger
    //
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g1, g2, g3;
    Graph g;
    g1.load("fichier1.txt");
    g2.load("fichier2.txt");
    //g3.load("fichier3.txt");

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    stretch_blit(fond,grman::page,0,0,1024,768,0,0,1024,800);
    blit(grman::page,screen,0,0,0,0,1024,768);
    while ( !key[KEY_ESC] )
    {
        if(!g.get_used())
            {
                while(choix == 0)
                {
                    choix = Menu();
                    blit(fond, grman::page, 0,0, 0, 0, 1024,768);
                    blit(grman::page, screen, 0,0, 0, 0, 1024,768);
                }
                if(choix == 1)
                    g = g1;
                else if(choix==2)
                    g = g2;
                else if(choix==3)
                    g = g3;
                choix = 0;
                g.set_used(true);
            }
        if(g.get_used())
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
