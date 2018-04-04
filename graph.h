#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <fstream>

/**************************************************************
    Ici sont proposï¿½es 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Arï¿½te ou Arc)
            Graph (=Graphe)

    Les arï¿½tes et les sommets et le graphe qu'ils constituent
    "travaillent" ï¿½troitement ensemble : pour cette raison les
    Vertex et Edge se dï¿½clarent amis (friend) de Graph pour que
    ce dernier puisse librement accï¿½der aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent ï¿½tres complï¿½tï¿½es. Il est ï¿½galement possible
    de les dï¿½river mais il est malheureusement assez difficile
    de dï¿½river le "triplet" des 3 classes en maintenant des relations
    cohï¿½rentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute prï¿½fï¿½rable, si possible,
    de "customiser" ces classes de base directement, sans hï¿½ritage.

    Le modï¿½le proposï¿½ permet de reprï¿½senter un graphe orientï¿½ ï¿½ventuellement
    pondï¿½rï¿½, les arcs portent une ou des informations supplï¿½mentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse ï¿½tre assez facilement
    lue et ï¿½crite en fichier, et bï¿½nï¿½ficie d'une bonne lisibilitï¿½ en cas de bugs...

    Chaque arc possï¿½de 2 attributs principaux (en plus de son ï¿½ventuelle pondï¿½ration)
        -> m_from (indice du sommet de dï¿½part de l'arc )
        -> m_to (indice du sommet d'arrivï¿½e de l'arc )

    Chaque sommet possï¿½de 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : accï¿½s aux prï¿½dï¿½cesseurs)
        -> m_out (liste des indices des arcs partant du sommet : accï¿½s aux successeurs)

    Cependant le problï¿½me des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entitï¿½ (un arc et/ou un sommet sont enlevï¿½s du graphe) alors :

    - Soit il faut reprendre toute la numï¿½rotation pour "boucher le trou"
      (par exemple on a supprimï¿½ le sommet nï¿½4, le sommet nï¿½5 devient le 4, 6 devient 5 etc...)
      ce qui pose des problï¿½mes de stabilitï¿½ et de cohï¿½rence, et une difficultï¿½ ï¿½ rï¿½-introduire
      le(s) mï¿½me(s) ï¿½lï¿½ment supprimï¿½ (au mï¿½me indice)

    - Soit on admet que la numï¿½rotation des sommets et arcs n'est pas contigue, cï¿½d qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La numï¿½rotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet ï¿½ des indices arbitraires (pas forcï¿½ment contigus)

    C'est cette 2ï¿½me approche qui est proposï¿½e ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra ï¿½tre attentif au fait que par rapport ï¿½ un simple vecteur, le parcours des ï¿½lï¿½ments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours ï¿½ itï¿½rateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'intï¿½rï¿½t se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associï¿½e ï¿½ chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non reprï¿½sentï¿½s ï¿½ l'ï¿½cran
    Imaginons par exemple qu'on doive gï¿½nï¿½rer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas reprï¿½senter graphiquement ces 1000 graphes, et les
    interfaces pï¿½sent lourd en ressource, avec cette organisation on est libre de rï¿½server ou
    pas une interface de prï¿½sentation associï¿½e aux datas (dï¿½couplage donnï¿½es/interface)

***********************************************************************************************/

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "grman/grman.h"

/***************************************************
                    VERTEX
****************************************************/

class VertexInterface
{
    // Les (methodes des) classes amies pourront accï¿½der
    // directement aux attributs (y compris privï¿½s)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de dï¿½clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramï¿½trer ( voir l'implï¿½mentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // Un slider de visualisation/modification de la valeur du sommet
        grman::WidgetVSlider m_slider_value;

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value;

        // Une image de "remplissage"
        grman::WidgetImage m_img;

        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        // Une boite pour le label prï¿½cï¿½dent
        grman::WidgetText m_box_label_idx;

    public :

        // Le constructeur met en place les ï¿½lï¿½ments de l'interface
        // voir l'implï¿½mentation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Vertex
{
    // Les (methodes des) classes amies pourront accï¿½der
    // directement aux attributs (y compris privï¿½s)
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;

    private :
        /// liste des indices des arcs arrivant au sommet : accï¿½s aux prï¿½dï¿½cesseurs
        std::vector<int> m_in;
<<<<<<< Ilana

        /// liste des indices des arcs partant du sommet : accï¿½s aux successeurs
=======
        std::string m_nom;
        std::string m_img;
        /// liste des indices des arcs partant du sommet : accès aux successeurs
>>>>>>> Remise prec.
        std::vector<int> m_out;

        /// un exemple de donnï¿½e associï¿½e ï¿½ l'arc, on peut en ajouter d'autres...
        double m_value;

        bool m_present = true;

        /// le POINTEUR sur l'interface associï¿½e, nullptr -> pas d'interface
        std::shared_ptr<VertexInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne prï¿½cï¿½dente est en gros ï¿½quivalent ï¿½ la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:

        /// Les constructeurs sont ï¿½ complï¿½ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Vertex (double value=0, VertexInterface *interface=nullptr) :
            m_value(value), m_interface(interface)  {  }

<<<<<<< Ilana
        /// Vertex ï¿½tant gï¿½rï¿½ par Graph ce sera la mï¿½thode update de graph qui appellera
=======

        /// Vertex étant géré par Graph ce sera la méthode update de graph qui appellera
>>>>>>> Remise prec.
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'implï¿½mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();

        bool get_present(){ return m_present; }
        void set_present(bool setter)
                        { m_present = setter; }
};



/***************************************************
                    EDGE
****************************************************/

class EdgeInterface
{
    // Les (methodes des) classes amies pourront accï¿½der
    // directement aux attributs (y compris privï¿½s)
    friend class Edge;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de dï¿½clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramï¿½trer ( voir l'implï¿½mentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de rï¿½glage associï¿½s
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        // Le constructeur met en place les ï¿½lï¿½ments de l'interface
        // voir l'implï¿½mentation dans le .cpp
        EdgeInterface(Vertex& from, Vertex& to);
};


class Edge
{
    // Les (methodes des) classes amies pourront accï¿½der
    // directement aux attributs (y compris privï¿½s)
    friend class Graph;
    friend class EdgeInterface;

    private :
        /// indice du sommet de dï¿½part de l'arc
        int m_from;

        /// indice du sommet d'arrivï¿½e de l'arc
        int m_to;

        /// un exemple de donnï¿½e associï¿½e ï¿½ l'arc, on peut en ajouter d'autres...
        double m_weight;

<<<<<<< Ilana
        /// le POINTEUR sur l'interface associï¿½e, nullptr -> pas d'interface
=======
        bool m_present = true;
        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
>>>>>>> Remise prec.
        std::shared_ptr<EdgeInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont ï¿½ complï¿½ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Edge (double weight=0, EdgeInterface *interface=nullptr) :
            m_weight(weight), m_interface(interface)  {  }

        /// Edge ï¿½tant gï¿½rï¿½ par Graph ce sera la mï¿½thode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'implï¿½mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();

        bool get_present(){ return m_present;}
        void set_present(bool setter)
                        { m_present = setter; }
};




/***************************************************
                    GRAPH
****************************************************/

class GraphInterface
{
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de dï¿½clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramï¿½trer ( voir l'implï¿½mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajoutï¿½s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajoutï¿½s des boutons de contrï¿½le etc...
        grman::WidgetBox m_tool_box;

        std::map<int,grman::WidgetButton*> m_buton_box;

        std::map<int,grman::WidgetText*> m_noms;

        grman::WidgetButton m_save;
        grman::WidgetText m_txt_save;

        grman::WidgetButton m_quit;
        grman::WidgetText m_txt_quit;

        grman::WidgetButton m_return;
        grman::WidgetText m_txt_return;

        // A complï¿½ter ï¿½ventuellement par des widgets de dï¿½coration ou
        // d'ï¿½dition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les ï¿½lï¿½ments de l'interface
        // voir l'implï¿½mentation dans le .cpp
        GraphInterface(int x, int y, int w, int h);
};


class Graph
{
    private :
<<<<<<< Ilana

        /// La "liste" des arï¿½tes
=======
        std::string m_nom;
        /// La "liste" des arêtes
>>>>>>> Remise prec.
        std::map<int, Edge> m_edges;
        std::map<int, Edge> m_edges_mem;
        /// La liste des sommets
        std::map<int, Vertex> m_vertices;
        std::map<int, Vertex> m_vertices_mem;

<<<<<<< Ilana
        int nb_sommets;
        int nb_arretes;
        /// le POINTEUR sur l'interface associï¿½e, nullptr -> pas d'interface
=======
        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
>>>>>>> Remise prec.
        std::shared_ptr<GraphInterface> m_interface = nullptr;

        int nb_sommet;
        int nb_arretes;

    public:

        /// Les constructeurs sont ï¿½ complï¿½ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface)  {  }
                                    //indice    valeur    x       y        image
        void add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name="", bool presence=false, int pic_idx=0 );
                                //indice     sommet1    sommet2     poids
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0, bool presence=false);

        /// Mï¿½thode spï¿½ciale qui construit un graphe arbitraire (dï¿½mo)
        /// Voir implï¿½mentation dans le .cpp
        /// Cette mï¿½thode est ï¿½ enlever et remplacer par un systï¿½me
        /// de chargement de fichiers par exemple.
        void load(std::string fic);
        void save(std::string fic);
        void modification(int i);


        /// La mï¿½thode update ï¿½ appeler dans la boucle de jeu pour les graphes avec interface
        void update();
};


#endif // GRAPH_H_INCLUDED
