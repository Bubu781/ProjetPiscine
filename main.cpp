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
    //std::cout<<"ouston"<<std::endl;
    g1.load("fichier1.txt");
    //g2.load("fichier1.txt");
    //g3.load("fichier1.txt");

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    stretch_blit(fond,grman::page,0,0,1024,768,0,0,900,600);
    blit(grman::page,screen,0,0,0,0,900,600);
    while ( !key[KEY_ESC] )
    {
        grman::rafraichir_clavier_souris();
        if(g.get_used())
        {
            /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
            // std::cout<<"we've"<<std::endl;
             g.update();

            /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }
        //else
        //{
            choix=Menu();
            if(choix != 0) Menu();
            if(choix == 1)
                g = g1;
            else if(choix == 2)
                g=g2;
            else if(choix==3)
                g=g3;
            g.set_used(true);

//        }
    }
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


