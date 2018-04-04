#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g1, g2, g3;
    Graph g;
    g1.load("fichier1.txt");
    //g2.load("fichier2.txt");
    //g3.load("fichier3.txt");

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        if(g.get_used())
        {
            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }
        else
        {
            g = g1;
            g.set_used(true);
        }
    }
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


