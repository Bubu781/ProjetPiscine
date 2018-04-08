#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <fstream>

/**************************************************************
    Ici sont propos�es 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Ar�te ou Arc)
            Graph (=Graphe)

    Les ar�tes et les sommets et le graphe qu'ils constituent
    "travaillent" �troitement ensemble : pour cette raison les
    Vertex et Edge se d�clarent amis (friend) de Graph pour que
    ce dernier puisse librement acc�der aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent �tres compl�t�es. Il est �galement possible
    de les d�river mais il est malheureusement assez difficile
    de d�river le "triplet" des 3 classes en maintenant des relations
    coh�rentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute pr�f�rable, si possible,
    de "customiser" ces classes de base directement, sans h�ritage.

    Le mod�le propos� permet de repr�senter un graphe orient� �ventuellement
    pond�r�, les arcs portent une ou des informations suppl�mentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse �tre assez facilement
    lue et �crite en fichier, et b�n�ficie d'une bonne lisibilit� en cas de bugs...

    Chaque arc poss�de 2 attributs principaux (en plus de son �ventuelle pond�ration)
        -> m_from (indice du sommet de d�part de l'arc )
        -> m_to (indice du sommet d'arriv�e de l'arc )

    Chaque sommet poss�de 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs)
        -> m_out (liste des indices des arcs partant du sommet : acc�s aux successeurs)

    Cependant le probl�me des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entit� (un arc et/ou un sommet sont enlev�s du graphe) alors :

    - Soit il faut reprendre toute la num�rotation pour "boucher le trou"
      (par exemple on a supprim� le sommet n�4, le sommet n�5 devient le 4, 6 devient 5 etc...)
      ce qui pose des probl�mes de stabilit� et de coh�rence, et une difficult� � r�-introduire
      le(s) m�me(s) �l�ment supprim� (au m�me indice)

    - Soit on admet que la num�rotation des sommets et arcs n'est pas contigue, c�d qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La num�rotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet � des indices arbitraires (pas forc�ment contigus)

    C'est cette 2�me approche qui est propos�e ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra �tre attentif au fait que par rapport � un simple vecteur, le parcours des �l�ments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours � it�rateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'int�r�t se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associ�e � chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non repr�sent�s � l'�cran
    Imaginons par exemple qu'on doive g�n�rer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas repr�senter graphiquement ces 1000 graphes, et les
    interfaces p�sent lourd en ressource, avec cette organisation on est libre de r�server ou
    pas une interface de pr�sentation associ�e aux datas (d�couplage donn�es/interface)

***********************************************************************************************/
///Inclusion des headers
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "grman/grman.h"

/***************************************************
                    VERTEX
****************************************************/

///Declaration de la class VertexInterface
class VertexInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;

   ///Declaration des attributs
    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

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

        grman::WidgetText m_titre;

        // Une boite pour le label pr�c�dent
        grman::WidgetText m_box_label_idx;

   ///Constructeur
    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};

///Declaration de la classe Sommet
class Vertex
{
    /// Les methodes de classes amies peuvent acceder aux attributs de cette classe
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;

   ///Declaration des attributs
    private :
        /// liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs
        std::vector<int> m_in;
        std::vector<double> m_valeurs;
        std::string m_nom;
        std::string m_img;
        int m_couleur;
        int m_idx;
        int f_connexe;
        double m_rythm=0.02; ///Rythme de croissance
        /// liste des indices des arcs partant du sommet : acc�s aux successeurs
        std::vector<int> m_out;
        bool m_marqued;
        /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
        double m_value = 0; ///N

        bool m_present = true;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<VertexInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne pr�c�dente est en gros �quivalent � la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Vertex (double value=0, VertexInterface *interface=nullptr) :
            m_value(value), m_interface(interface)  {  }


        /// Vertex �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();


        ///Getters et setters de vertex
        void set_marqued(bool mark) { m_marqued = mark;}
        bool get_marqued() {return m_marqued;}
        void set_idx(int idx) {m_idx = idx;}
        int get_idx() {return m_idx;}
        bool get_present(){ return m_present; }
        void set_present(bool setter)
                        { m_present = setter; }
};



/***************************************************
                    EDGE
****************************************************/

///Declaration de la class EdgeInterface
class EdgeInterface
{
    /// Les methodes de classes amies peuvent acceder aux attributs de cette classe
    friend class Edge;
    friend class Graph;

    ///Declaration des attributs
    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de r�glage associ�s
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

        grman::WidgetImage m_anim;

    public :

        ///  constructeur de edgeInterface
        EdgeInterface(Vertex& from, Vertex& to);
};

///Declaration de la class Arrete
class Edge
{
    /// Les methodes de classes amies peuvent acceder aux attributs de cette classe
    friend class Graph;
    friend class EdgeInterface;

///Declaration des attributs
    private :
        /// indice du sommet de d�part de l'arc
        int m_from;

        /// indice du sommet d'arriv�e de l'arc
        int m_to;
        int m_idx;
        double m_dx;
        double m_dy;

        ///Initialisation des variables
        double px = 0;
        double py = 0;
        bool m_marqued;
        /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
        double m_weight;

        bool m_present = true;
        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<EdgeInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Edge (double weight=0, EdgeInterface *interface=nullptr) :
            m_weight(weight), m_interface(interface)  {  }

        /// Edge �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();

       ///Getters et setters de la classe edge
        void set_marqued(bool mark) { m_marqued = mark;}
        bool get_marqued() {return m_marqued;}
        void set_idx(int idx) {m_idx = idx;}
        int get_idx() {return m_idx;}
        bool get_present(){ return m_present;}
        void set_present(bool setter)
                        { m_present = setter; }
};




/***************************************************
                    GRAPH
****************************************************/

///Declaration de la class GraphInterface
class GraphInterface
{
    /// Les methodes de classes amies peuvent acceder aux attributs de cette classe
    friend class Graph;

    ///Declaration des attributs
    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;
        grman::WidgetImage m_fond;

        /// Dans cette boite seront ajout�s des boutons de contr�le etc...
        grman::WidgetBox m_tool_box;

        std::map<int,grman::WidgetButton*> m_buton_box;

        std::map<int,grman::WidgetText*> m_noms;

       ///Widgets
        grman::WidgetButton m_save;
        grman::WidgetText m_txt_save;

        grman::WidgetButton m_quit;
        grman::WidgetText m_txt_quit;

        grman::WidgetButton m_return;
        grman::WidgetText m_txt_return;

        grman::WidgetButton m_disconnect;
        grman::WidgetText m_txt_disconnect;

        grman::WidgetButton m_simulation;
        grman::WidgetText m_txt_simulation;

        grman::WidgetButton m_mod_edge;
        grman::WidgetText m_txt_mod_edge;

        grman::WidgetButton m_grapique;
        grman::WidgetText m_txt_grapique;

        grman::WidgetButton m_ft_connexe;
        grman::WidgetText m_txt_ft_connexe;

        // A compl�ter �ventuellement par des widgets de d�coration ou
        // d'�dition (boutons ajouter/enlever ...)

    public :

        /// Le constructeur de la classe graphinterface
        GraphInterface(int x, int y, int w, int h, std::string nom);
};

///Declaration de la class Graph
class Graph
{

///Declaration des attributs
    private :
        std::string m_nom;
        std::vector<std::string> m_liste_animaux;

        /// La "liste" des arêtes
        std::map<int, Edge> m_edges;
        std::map<int, Edge> m_edges_mem;

        /// La liste des sommets
        std::map<int, Vertex> m_vertices;
        std::map<int, Vertex> m_vertices_mem;
        std::vector<int> sommets;
        std::vector<std::vector<int>> mat;
        //Vertex v;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<GraphInterface> m_interface = nullptr;
        bool simulation = false;
        int nb_sommet;

        int nb_arretes;
        bool m_used = false;
        bool reduit = false;

   ///Ascesseurs
    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface)  {  }
                                    //indice    valeur    x       y        image
        void add_interfaced_vertex(int idx, double value, int x, int y,double r, std::string pic_name="", bool presence=false, int pic_idx=0 );
                                 //indice     sommet1    sommet2     poids
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0, bool presence=false, bool memoire = true);

        /// Methodes de la classe
        void load(std::string fic);
        void save();
        void disconnect();
        void modification_edges();
        void modification(int i);
        void fort_connexe();
        void evol_pop();
        void graphic();
        void graph_reduit();
        void animation();

        ///Getters et setters de la classe Graph
         bool get_simu() {return simulation;}
        bool get_used() {return m_used;}
        void set_used(bool _used) {m_used = _used;}
        /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
        void update();
};


#endif // GRAPH_H_INCLUDED
