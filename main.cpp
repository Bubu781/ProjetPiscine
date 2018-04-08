#include "grman/grman.h"
#include <iostream>

///Inclusion des headers
#include "graph.h"
#include "Allegro.h"

int main()
{
    /// Initialisation d'allegro et déclaration de variables
    grman::init();
    BITMAP *fond;
    int choix=0;
    fond =load_bitmap("pics/fond.bmp",NULL);

    /// Chargement des images des differents réseaux trophiques

    grman::set_pictures_path("pics");

    /// Declaration des trois graphes
    Graph g1, g2, g3;
    Graph g;

    /// Chagement des fichiers
    g1.load("fichier1.txt");
    g2.load("fichier2.txt");
    g3.load("fichier3.txt");

    /// Mise du fond d'ecran sur le buffer (page) pur sur le screnn
    stretch_blit(fond,grman::page,0,0,1024,768,0,0,1024,800);
    blit(grman::page,screen,0,0,0,0,1024,768);
    ///Boucle de jeu
    while ( !key[KEY_ESC] )
    {
        if(!g.get_used())
            {
                ///Tant que l'utilisateur n'a pas choisi
                while(choix == 0)
                {
                    choix = Menu();
                    ///Affichage du menu sur l'écran
                    blit(fond, grman::page, 0,0, 0, 0, 1024,768);
                    blit(grman::page, screen, 0,0, 0, 0, 1024,768);
                }
               ///Prise en compte du choix de l'utilisateur lorqu'il a choisi
                if(choix == 1)
                    g = g1;
                else if(choix==2)
                    g = g2;
                else if(choix==3)
                    g = g3;
                choix = 0;
                g.set_used(true);
                g.fort_connexe();
            }
        if(g.get_used())
        {
            /// Appel de la fonction update
        g.update();

        /// Misa a jour du clavier, de la souris, du buffer...
        grman::mettre_a_jour();
        }
    }

    ///A la fin de la boucle de jeu, fermeture d'allegro
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
