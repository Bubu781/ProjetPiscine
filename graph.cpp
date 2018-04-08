#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur surchargé de la classe Vertexeinterface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
   ///Declaration et initialisation des variables
    std::string nom;
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    m_box_label_idx.add_child( m_titre );
    nom = pic_name;
    for(int i = 1; i <=4; i++)
        nom[nom.size()-i] = ' ';
    m_titre.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_titre.set_message(nom);
}

/// Gestion du Vertex avant l'appel de l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}

/// Gestion du Vertex après l'appel de l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();
}

/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}

/***************************************************
                    GRAPH
****************************************************/

/// Le constructeur surchargé de la classe GrapInterface
GraphInterface::GraphInterface(int x, int y, int w, int h, std::string nom)
{
   ///Initialisation des variables
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    ///Ajout couleur et design de la barre d'outils
    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    ///Ajout couleur et design de la barre d'outils
    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);


    ///Si il s'agit du fichier 1
    if(nom == "fichier1.txt")
    {
        ///Le fond est l'ocean
        m_main_box.add_child( m_fond );
        m_fond.set_pic_name("ocean.jpg");
        m_fond.set_pic_idx(0);
        m_fond.set_gravity_x(grman::GravityX::Right);
    }
    ///Si il s'agit du fichier 2
    else if(nom =="fichier2.txt")
    {
        m_main_box.add_child( m_fond );
        ///Le fond est la foret
        m_fond.set_pic_name("forest.png");
        m_fond.set_pic_idx(0);
        m_fond.set_gravity_x(grman::GravityX::Right);
    }
    ///Si il s'agit du fichier 3
    else if(nom =="fichier3.txt")
    {
        m_main_box.add_child( m_fond );
        ///Le fond est le ciel
        m_fond.set_pic_name("ciel.png");
        m_fond.set_pic_idx(0);
        m_fond.set_gravity_x(grman::GravityX::Right);
    }

    ///Ajout du bouton quitter
    m_tool_box.add_child(m_quit);
    m_quit.set_dim(75,30);
    m_quit.set_pos(1,685);
    m_quit.set_bg_color(ROUGE);

    m_quit.add_child(m_txt_quit);
    m_txt_quit.set_dim(75,10);
    m_txt_quit.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_quit.set_message("Quitter");
    m_txt_quit.set_color(BLANC);

    ///Ajout du bouton retour menu
    m_tool_box.add_child(m_return);
    m_return.set_dim(75,30);
    m_return.set_pos(1,650);
    m_return.set_bg_color(makecol(0,128,255));

    m_return.add_child(m_txt_return);
    m_txt_return.set_dim(75,10);
    m_txt_return.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_return.set_message("Menu");
    m_txt_return.set_color(BLANC);

    ///Ajout du bouton sauvegarde
    m_tool_box.add_child(m_save);
    m_save.set_dim(75,30);
    m_save.set_pos(1,615);
    m_save.set_bg_color(makecol(140,0,140));

    m_save.add_child(m_txt_save);
    m_txt_save.set_dim(75,10);
    m_txt_save.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_save.set_message("Sauvegarde");
    m_txt_save.set_color(BLANC);

    ///Ajout du bouton connexité (k-connexité)
    m_tool_box.add_child(m_disconnect);
    m_disconnect.set_dim(75,30);
    m_disconnect.set_pos(1,580);
    m_disconnect.set_bg_color(makecol(225,32,167));

    m_disconnect.add_child(m_txt_disconnect);
    m_txt_disconnect.set_dim(75,10);
    m_txt_disconnect.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_disconnect.set_message("Connexite");
    m_txt_disconnect.set_color(BLANC);

    ///Ajout du bouton simulation
    m_tool_box.add_child(m_simulation);
    m_simulation.set_dim(75,30);
    m_simulation.set_pos(1,545);
    m_simulation.set_bg_color(ROUGE);

    m_simulation.add_child(m_txt_simulation);
    m_txt_simulation.set_dim(75,10);
    m_txt_simulation.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_simulation.set_message("Simulation");
    m_txt_simulation.set_color(BLANC);

    ///Ajout du bouton mod edge permettant d'ajouter et supprimer des aretes
    m_tool_box.add_child(m_mod_edge);
    m_mod_edge.set_dim(75,30);
    m_mod_edge.set_pos(1,510);
    m_mod_edge.set_bg_color(makecol(77,185,185));

    m_mod_edge.add_child(m_txt_mod_edge);
    m_txt_mod_edge.set_dim(75,10);
    m_txt_mod_edge.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_mod_edge.set_message("Mod edge");
    m_txt_mod_edge.set_color(BLANC);

    ///Ajout du bouton graphique
    m_tool_box.add_child(m_grapique);
    m_grapique.set_dim(75,30);
    m_grapique.set_pos(1,475);
    m_grapique.set_bg_color(MARRON);

    m_grapique.add_child(m_txt_grapique);
    m_txt_grapique.set_dim(75,10);
    m_txt_grapique.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_grapique.set_message("Graphique");
    m_txt_grapique.set_color(BLANC);

    ///Ajout du bouton forte connexité
    m_tool_box.add_child(m_ft_connexe);
    m_ft_connexe.set_dim(75,30);
    m_ft_connexe.set_pos(1,440);
    m_ft_connexe.set_bg_color(makecol(249,174,62));

    m_ft_connexe.add_child(m_txt_ft_connexe);
    m_txt_ft_connexe.set_dim(75,10);
    m_txt_ft_connexe.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Center);
    m_txt_ft_connexe.set_message("Ft connexite");
    m_txt_ft_connexe.set_color(BLANC);

}

/// Methode qui charge les fichiers pour pouvoir creer un graphe
void Graph::load(std::string fic)
{
    ///Declaration et initiaisation des variables
    std::ifstream fichier(fic, std::ios::in);
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600, fic);
    int indice, x, y, s1, s2, nb;
    double r;
    double poids;
    bool presence;
    m_nom = fic;
    std::string img;
    ///Si le fichier existe
    if(fichier)
    {
        ///Lire les informations dans le fichier
         fichier >> nb;
        nb_sommet = nb;
        ///Pour i allant de 0 a nb
        for(int i = 0; i < nb; i++)
        {
            fichier >> indice;
            fichier >> poids;
            fichier >> x;
            fichier >> y;
            fichier >> r;
            fichier >> presence;
            fichier.ignore();
            getline(fichier, img, '\n');
            ///Prise en compte des information par les sommets
            add_interfaced_vertex(indice, poids, x, y,r, img, presence, 1);
        }
        fichier >> nb;
        nb_arretes = nb;
        ///Pour i allant de 0 a nb
        for(int i = 0; i < nb; i++)
        {
            fichier >> indice;
            fichier >> s1;
            fichier >> s2;
            fichier >> poids;
            fichier >> presence;
            ///Prise en compte des information par les arretes
            add_interfaced_edge(indice, s1, s2, poids, presence);
        }
       ///Fermeture du fichier
        fichier.close();
    }
}

///Methode qui permet de sauver un graphe dans l'état dans lequel on l'a laisser (après des modifications par ex)
void Graph::save()
{
    ///Declaration d'un fichier
    std::ofstream fichier(m_nom, std::ios::trunc);
   ///Si le fichier existe
    if(fichier)
    {
        fichier << nb_sommet << std::endl;
        ///Pour tous les elements de m_vertices_mem
        for(auto elem : m_vertices_mem)
        {
           ///Ecriture des informations du graphe dans le fichier
            fichier << elem.first<< " ";
            fichier << elem.second.m_value << " ";
            fichier << elem.second.m_interface->m_top_box.get_posx() << " ";
            fichier << elem.second.m_interface->m_top_box.get_posy() << " ";
            fichier << elem.second.m_rythm << " ";
            fichier << elem.second.m_present;
            fichier << std::endl;
            fichier << elem.second.m_img;
            fichier << std::endl;
        }
        fichier << nb_arretes << std::endl;
        ///Pour tous les elements de m_edges_mem
        for(auto elem : m_edges_mem)
        {
            ///Ecriture des informations du graphe dans le fichier
            fichier << elem.first << " ";
            fichier << elem.second.m_from << " ";
            fichier << elem.second.m_to << " ";
            fichier << elem.second.m_weight << " ";
            fichier << elem.second.m_present;
            if(elem.first != nb_arretes-1)
                fichier << std::endl;
        }
       ///Fermeture du fichier
        fichier.close();
    }
}

/// Methode update a utiliser dans la boucle de jeu
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

   ///Update de barre doutils
    m_interface->m_top_box.update();

   ///Update sommets
    for (auto &elt : m_vertices)
        elt.second.post_update();

    ///Update aretes
    for (auto &elt : m_edges)
        elt.second.post_update();


    ///Si on clique sur le boouton d'une espece, l'ajouter ou la supprimer du graphe
    for (auto elem : m_interface->m_buton_box)
    {
        if(elem.second->clicked())
            modification(elem.first);
    }
    ///Si on choisi de sauver, sauver les donnees
    if(m_interface->m_save.clicked())
        save();
    if(m_interface->m_quit.clicked())
        exit(0);
    if(m_interface->m_return.clicked())
        m_used = false;
    ///Si on choisi la k-connexité
    if(m_interface->m_disconnect.clicked())
        ///Utiliser le sous prog de k-connexité
        disconnect();
    ///Si on choisi la simulation
    if(m_interface->m_simulation.clicked())
    {
        m_interface->m_simulation.set_bg_color(ROUGE);
        simulation = !simulation;
    }
    ///Si on choisi de modifier les liens
    if(m_interface->m_mod_edge.clicked())
        ///Utiliser le sous prog de modification
        modification_edges();
    if(m_interface->m_grapique.clicked())
        ///Utiliser le sous prog de graphique
        graphic();

    for(auto elem : m_edges)
    {
        elem.second.m_interface->m_top_edge.set_thickness(1+elem.second.m_weight/20);
    }
    ///Si simulation , faire evoluer les pop
    if(simulation)
        animation();
    else
    {
        for(auto &elem : m_edges)
            elem.second.m_interface->m_anim.set_pos(10000,10000);
    }
    if(!reduit)
    {
        for(auto elem : m_edges)
        {
            m_edges[elem.first].m_interface->m_top_edge.set_color(GRISSOMBRE);
        }
        fort_connexe();
    }
    ///Si utlisateur choisi graphe reduit, l'afficher
    if(m_interface->m_ft_connexe.clicked())
    {
        reduit = !reduit;
        ///Utiliser le sous prom de graphe reduit
        graph_reduit();
    }
}

///Methode permettant de creer des dynamiques de population
///(évolution et diminitution de populations des especes par rapport au temps)
void Graph::evol_pop()
{
    ///Declaration des variables
    double K;///K capacité de portage
    double tot;
    double coef, N, R, N1, coef2, N2;
    m_interface->m_simulation.set_bg_color(VERT);
    ///Parcourir la map vertices
    for(auto elem: m_vertices)
    {
        if(elem.second.m_nom != "foret    " )
            m_vertices[elem.first].m_valeurs.push_back(elem.second.m_value);
        ///Initialisation des variables
        K=0;
        tot=0;
        if(elem.second.m_value >0)
        {
        ///Parcourir la map edges
        for(auto arete: m_edges)
        {
            if(m_edges[arete.first].m_to==elem.first && m_vertices[arete.second.m_from].m_value > 0 && m_vertices[arete.second.m_to].m_nom != "foret    ")
            {
                ///Formule pour calculer le coeficient
                coef = m_edges[arete.first].m_weight;

                ///Nombre d'individu dans une espece
                N1 = m_vertices[arete.second.m_from].m_value;

                ///La capacité de portage prend la valeur
                K+=coef*N1;
            }
            else if(m_edges[arete.first].m_from==elem.first && m_vertices[arete.second.m_to].m_value > 0)
            {
               ///Si il ne s'agit pas des ressources
                    if(m_vertices[arete.second.m_to].m_nom != "debrits    " && m_vertices[arete.second.m_to].m_nom != "sels    " && m_vertices[arete.second.m_to].m_nom != "herbe    " && m_vertices[arete.second.m_to].m_nom != "vegetation    " && m_vertices[arete.second.m_to].m_nom != "foret    ")
                {
                    coef2 = m_edges[arete.first].m_weight/20;
                    N2 = m_vertices[arete.second.m_to].m_value;
                    tot+=coef2*N2;
                }
            }

        }

        ///Rythme de croissance d'une population
        R = m_vertices[elem.first].m_rythm;
        N = m_vertices_mem[elem.first].m_value;
        ///Formule pour calculer N(t+1)
        N =N+  R*N*(1-N/K)-tot;
        if(m_vertices[elem.first].m_nom != "foret    ")
            m_vertices[elem.first].m_value = N;

        ///Si N est inferieur a 0, N passe a 0
        if(m_vertices[elem.first].m_value < 0)
            m_vertices[elem.first].m_value = 0;
        ///Si N est superieur a 100, N passe a 100
        if(m_vertices[elem.first].m_value >100)
            m_vertices[elem.first].m_value = 100;

        m_vertices_mem[elem.first].m_value = m_vertices[elem.first].m_value;
        }
    }
}
///Methode permettant de transformer un graphe en graphe reduit
void Graph::graph_reduit()
{
    ///declaration et initialisation des variables
    bool verif;
    bool fort_co;
    for(auto elem : m_vertices)
        {
            if(elem.second.f_connexe != 0)
                fort_co = true;
        }
///Si on veut le graphe reduit
    if(reduit)
    {
        ///Si forte connexite
        if(fort_co)
        {
        for(auto elem : m_vertices)
        {
            if((elem.second.f_connexe != 0 && sommets.empty()) || (elem.second.f_connexe == m_vertices[sommets.front()].f_connexe && elem.second.f_connexe !=0))
            {
               ///Rajouter sommet
                sommets.push_back(elem.first);
            }
        }
            ///Pour i allant de 0 a la taille du vect
            for(unsigned int i = 1; i < sommets.size(); i++)
            {
                for(auto elem : m_vertices[sommets[i]].m_in)
                {
                    verif = false;
                    for(auto v : sommets)
                        if(elem == v)
                            verif = true;
                    if(!verif)
                    {
                        add_interfaced_edge(nb_arretes, elem, sommets[0], 50, true, false);
                        nb_arretes++;
                    }
                }
                for(auto elem : m_vertices[sommets[i]].m_out)
                {
                    verif = false;
                    for(auto v : sommets)
                        if(elem == v)
                            verif = true;
                    if(!verif)
                    {
                        ///Ajout d'une arete
                        add_interfaced_edge(nb_arretes, sommets[0], elem, 50, true, false);
                        ///Incrementation du nb d'arete
                        nb_arretes++;
                    }
                }
                ///Modification des aretes
                modification(sommets[i]);
            }
            ///Pour i allant de 0 a la taille du vect
            for(unsigned int i = 1; i < sommets.size(); i++)
            {
                for(auto elem : m_edges)
                {
                    if((elem.second.m_from == sommets[0] && elem.second.m_to == sommets[i]) || (elem.second.m_from == sommets[i] && elem.second.m_to == sommets[0]))
                    {
                        m_interface->m_main_box.remove_child(m_edges[elem.first].m_interface->m_top_edge);
                        ///Suppression d'arete
                        m_edges.erase(elem.first);
                        nb_arretes--;
                    }
                }
            }
        }
    }
    else
    {
        for(unsigned int i = 0; i < sommets.size(); i++)
        {
            modification(sommets[i]);
        }
        modification(sommets[0]);
        for(auto elem : m_edges)
        {
            m_interface->m_main_box.remove_child(m_edges[elem.first].m_interface->m_top_edge);
            m_edges.erase(elem.first);
        }
        for(auto elem : m_edges_mem)
        {
            m_edges[elem.first] = m_edges_mem[elem.first];
            m_interface->m_main_box.add_child(m_edges[elem.first].m_interface->m_top_edge);
        }
        sommets.erase(sommets.begin(), sommets.end());
    }
}

///Methode permettant l'animation des animaux
void Graph::animation()
{
   ///declaration et initialisation des variables
    bool verif = false;
    int x = 0, y = 0;
    ///Parcourir la map des aretes
    ///Deplacement des animaux sur les aretes
    for(auto elem : m_edges)
    {
         m_edges[elem.first].m_dx = (m_vertices[elem.second.m_to].m_interface->m_top_box.get_posx()-m_vertices[elem.second.m_from].m_interface->m_top_box.get_posx()) / 25;
         m_edges[elem.first].m_dy = (m_vertices[elem.second.m_to].m_interface->m_top_box.get_posy()-m_vertices[elem.second.m_from].m_interface->m_top_box.get_posy()) / 25;
    }
    for(auto elem : m_edges)
    {
        if(m_vertices[elem.second.m_from].m_value > 0 && m_vertices[elem.second.m_to].m_value > 0)
        {
        verif = false;
        if(m_edges[elem.first].m_interface->m_anim.get_posx() == 10000 || m_edges[elem.first].m_interface->m_anim.get_posy() == 10000)
        {
            x= m_vertices[elem.second.m_from].m_interface->m_top_box.get_posx();
            y= m_vertices[elem.second.m_from].m_interface->m_top_box.get_posy();
            m_edges[elem.first].px = x;
            m_edges[elem.first].py = y;
            m_edges[elem.first].m_interface->m_anim.set_pos(x,y);

        }
        else
        {
            x = m_edges[elem.first].px+m_edges[elem.first].m_dx;
            y = m_edges[elem.first].py+m_edges[elem.first].m_dy;
            m_edges[elem.first].m_interface->m_anim.set_pos(x,y);
            m_edges[elem.first].px = x;
            m_edges[elem.first].py = y;

        }
        if (((elem.second.px >= m_vertices[elem.second.m_to].m_interface->m_top_box.get_posx() && elem.second.m_dx >=0)
                || (elem.second.px <= m_vertices[elem.second.m_to].m_interface->m_top_box.get_posx() && elem.second.m_dx <= 0)) &&
                ((elem.second.py >= m_vertices[elem.second.m_to].m_interface->m_top_box.get_posy() && elem.second.m_dy >=0)
                || (elem.second.py <= m_vertices[elem.second.m_to].m_interface->m_top_box.get_posy() && elem.second.m_dy <= 0)) )
        {
            m_edges[elem.first].m_interface->m_anim.set_pos(10000,10000);
            m_edges[elem.first].px = 10000;
            m_edges[elem.first].py = 10000;
            verif = true;
        }
        }
        else
        {
            m_edges[elem.first].m_interface->m_anim.set_pos(10000,10000);
            m_edges[elem.first].px = 10000;
            m_edges[elem.first].py = 10000;
            verif = true;
        }

    }
  ///Si les animations sont arrivées au bout
    if(verif)
        evol_pop();


}

///Methode de modification des liaisons du graphe
//Ajout et suppression d'aretes
void Graph::modification_edges()
{
    ///declaration et initialisation des variables
    int s1, s2, num;
    bool verif = false;
    ///Effacer l'ecran
    system("cls");

   ///Demande a l'utlisateur des sommets qu'il choisi
    std::cout << "Quels sommets relier/supprimer?" << std::endl;

   ///Parcourir tous les sommets pour afficher leur nom
    for(auto elem : m_vertices)
        std::cout << elem.first << ". " << elem.second.m_nom << std::endl;

    ///L'utilisateur choisi les sommets a supprimer ou relier
    std::cin >> s1;
    std::cin >> s2;

    ///Parcourir toutes les aretes jusqu'a trouver les deux sommets choisis
    for(auto elem : m_edges)
        if(elem.second.m_from == s1 && elem.second.m_to == s2)
            verif = true, num = elem.first;
    ///Si verif est egal a false
    if(!verif)
    {
        ///Ajouter une arete entre les sommets
        add_interfaced_edge(nb_arretes, s1, s2, 50, true);
        nb_arretes++;
    }
    ///Sinon supprimer l'arete entre eux
    else
    {
        for(unsigned int i = 0; i < m_vertices[s1].m_out.size(); i++)
        {
            if(m_vertices[s1].m_out[i] == s2)
            {
                m_vertices[s1].m_out.erase(m_vertices[s1].m_out.begin() + i);
                m_vertices_mem[s1].m_out.erase(m_vertices_mem[s1].m_out.begin() + i);
            }
        }
        for(unsigned int i = 0; i < m_vertices[s2].m_in.size(); i++)
        {
            if(m_vertices[s2].m_in[i] == s1)
            {
                m_vertices[s2].m_in.erase(m_vertices[s2].m_in.begin() + i);
                m_vertices_mem[s2].m_in.erase(m_vertices_mem[s2].m_in.begin() + i);
            }
        }


        m_interface->m_main_box.remove_child(m_edges[num].m_interface->m_top_edge);
        m_interface->m_main_box.remove_child(m_edges[num].m_interface->m_anim);
        m_edges_mem.erase(num);
        m_edges.erase(num);
        nb_arretes--;
    }
    system("cls");
}

///Methode permettant la k-connexité (rendre le graphe non simplement connexe)
void Graph::disconnect()
{
    ///declaration et initialisation des variables
    int imin = 200, i, refer;

    ///Parcourir tous les sommets
    for(auto sommets : m_vertices)
    {
        i = 0;
       ///Parcourir toutes les aretes du graphe
        for(auto arretes : m_edges)
        {
            if(arretes.second.m_to == sommets.first)
            {
                i++;
                for(auto arr : m_edges)
                {
                    if(arr.second.m_from == arretes.second.m_from || arr.second.m_to == arretes.second.m_from)
                        i++;
                }
            }
            else if(arretes.second.m_from == sommets.first )
            {
                i++;
                for(auto arr : m_edges)
                {
                    if(arr.second.m_from == arretes.second.m_to || arr.second.m_to == arretes.second.m_to)
                        i++;
                }
            }
        }
       ///Si i inferieur a imin et i different de 0
        if(i < imin && i != 0)
        {
           ///I prend la valeur de imin et refer prend la valeur de sommets.first
            imin = i;
            refer = sommets.first;
        }
    }
   ///Parcourir toutes les aretes
    for(auto elem : m_edges)
    {
        if(elem.second.m_from == refer)
            modification(elem.second.m_to);
        else if(elem.second.m_to == refer)
            modification(elem.second.m_from);
    }
}

///Methode permettant l'ajout et la suppression de sommets
void Graph::modification(int i)
{
    ///declaration et initialisation des variables
    std::vector<int> x;
   ///Si le sommet est deja present sur le graphe, le supprimer si on clique sur le bouton
    if(m_vertices_mem[i].get_present())
    {
        for(auto elem : m_edges_mem)
        {
            ///On supprime toutes les arretes liées au sommet
            if((elem.second.m_from == i || elem.second.m_to == i))
            {
                m_interface->m_main_box.remove_child(elem.second.m_interface->m_anim);
                m_interface->m_main_box.remove_child(elem.second.m_interface->m_top_edge);
                m_edges_mem[elem.first].set_present(false);
                m_edges.erase(elem.first);
            }
        }
        m_interface->m_main_box.remove_child(m_vertices[i].m_interface->m_top_box);
        m_vertices_mem[i].set_present(false);
        m_vertices.erase(i);
        ///Le bouton du sommet devient rouge
        m_interface->m_buton_box[i]->set_bg_color(ROUGE);
    }
    ///Sinon, si il n'est pas deja present et que l'utilisateur clique sur son bouton, le rajouter
    else
    {
        m_vertices_mem[i].set_present(true);
        m_vertices[i] = m_vertices_mem[i];
        m_interface->m_main_box.add_child(m_vertices[i].m_interface->m_top_box);
        for(auto elem : m_edges_mem)
        {
            ///On ajoute toutes les arretes liées au sommet
            if((m_vertices_mem[elem.second.m_to].get_present() && elem.second.m_from == i)
                    || (m_vertices_mem[elem.second.m_from].get_present() && elem.second.m_to == i))
            {
                m_edges_mem[elem.first].set_present(true);
                m_edges[elem.first] = elem.second;
                m_interface->m_main_box.add_child(m_edges[elem.first].m_interface->m_top_edge);
                m_interface->m_main_box.add_child(m_edges[elem.first].m_interface->m_anim);
            }
        }
        ///Le bouton du sommet devient vert
        m_interface->m_buton_box[i]->set_bg_color(VERT);
    }
}

void Graph::fort_connexe()
{
    ///declaration et initialisation des variables
    std::vector<int> liste;
    int nb = 1;
    Vertex v;
    //Pour tous les sommets
    for(auto elem : m_vertices)
    {
        //v prend la valeur du sommet
        v = m_vertices[elem.first];
        //On retire le marquage de tous les sommets
        for(auto som : m_vertices)
            m_vertices[som.first].m_marqued = false;
retour:
        liste.push_back(v.m_idx); //On ajoute a notre liste le numero du sommet
retour2:
    ///Pour tous les sommets liés au sommet regardé
        for(auto conn : v.m_out)
        {
            if(conn == elem.first) //Si on peut rejoindre le sommet initial
            {
                liste.push_back(elem.first);
                m_vertices[elem.first].m_marqued = true;
                break; //fin de la boucle
            }
            else if(!m_vertices[conn].m_marqued) //Si le sommet n'est pas marqué, on regarde ce sommet
            {
                v = m_vertices[conn];
                m_vertices[conn].m_marqued = true;
                goto retour;
            }
        }
        if(v.m_out.empty() || liste.back() != elem.first) //Si le sommmet ne mène nulle part
        {
            liste.pop_back();
            if(liste.empty())
                goto next;
            v = m_vertices[liste.back()];
            goto retour2;
        }
        if(liste.back() == elem.first && liste.size() != 1)
            mat.push_back(liste);
next:
        liste.erase(liste.begin(), liste.end());

    }
    for(auto elem : m_vertices)
        m_vertices[elem.first].f_connexe = 0;
    if(!mat.empty())
    {
        for(auto elem : mat)
        {
            liste = elem;
            for(unsigned int i=0; i < liste.size()-1; i++)
            {
                m_vertices[liste[i]].f_connexe = nb;
                for(auto arete : m_edges)
                {
                    if(arete.second.m_from == liste[i] && arete.second.m_to == liste[i+1])
                        m_edges[arete.first].m_interface->m_top_edge.set_color(ROUGE);
                }
            }
            nb++;
        }
    }
}

///Methode d'affichage des graphiques representant les dynamiques de populations
void Graph::graphic()
{
    ///Declaration et initialisation des variables
    BITMAP *graphic;
    BITMAP *fond;
    BITMAP *buffer;
    graphic = create_bitmap( 1024, 768);
    fond = create_bitmap( 1024, 768);
    buffer = create_bitmap( 1024, 768);
    int x1, x2, y1, y2;
    x1=0;
    x2=10;
    y1=0;
    y2=10;
    clear_to_color(graphic, makecol(255,0,255));
    clear_to_color(fond, NOIR);
    for (auto elem : m_vertices)
    {
        ///Legende du graphique
        rectfill(fond, x1,  y1, x2, y2, elem.second.m_couleur);
        for(auto lettre : elem.second.m_nom)
        {
            textprintf_ex(fond, font, x2+3, y1, BLANC, NOIR, "%c",lettre);
            x2+=7;
        }
        x2 = 10;
        y1=y1+10;
        y2=y2+10;
    }
    line(fond, 230, 50, 230, 650, BLANC);
    textprintf_ex(fond, font, 850, 655, BLANC, NOIR, "temps");
    line(fond, 230, 650, 850, 650, BLANC);
    textprintf_ex(fond, font, 230-23*3, 40, BLANC, NOIR, "taille de la population");

    ///Dans la boucle de jeu
    while (!key[KEY_SPACE])
    {
       ///Tracer les courbes pour toutes les especes
        for (auto elem : m_vertices)
        {
       ///Si les courbes arrivent au bout de l'ecran, effacer leur début et afficher leur suite
         if((elem.second.m_valeurs.size()-1)*50+230 >=1024)
                {
                    m_vertices[elem.first].m_valeurs.erase(m_vertices[elem.first].m_valeurs.begin(),m_vertices[elem.first].m_valeurs.end());
                    clear_to_color(graphic, makecol(255,0,255));
                }
        }
        for (auto elem : m_vertices)
        {
            if(!elem.second.m_valeurs.empty())
            {
                ///Ajout des points sur les courbes
                circlefill(graphic, 230, 650-elem.second.m_valeurs[0]*6,5,elem.second.m_couleur);
                for (unsigned int i=0; i<elem.second.m_valeurs.size()-1; i++)
                {
                   ///Tracage des courbes
                    if(elem.second.m_valeurs[i+1] != 0 || elem.second.m_valeurs[i] != 0)
                    {
                        line(graphic, 50*i+230, 650-elem.second.m_valeurs[i]*6, 50*(i+1)+230, 650-elem.second.m_valeurs[i+1]*6, elem.second.m_couleur);
                        circlefill(graphic, 50*(i+1)+230, 650-elem.second.m_valeurs[i+1]*6,5,elem.second.m_couleur);

                    }
                }
            }
        }

        ///Affichage des courbes sur l'ecran
        blit(fond, buffer, 0, 0, 0, 0, 1024, 768);
        masked_blit(graphic, buffer, 0, 0, 0, 0, 1024, 768);
        blit(buffer, screen, 0, 0, 0, 0, 1024, 768);
        evol_pop();
        rest(500);
    }
    m_interface->m_simulation.set_bg_color(ROUGE);
}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y,double r, std::string pic_name, bool presence, int pic_idx)
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);

    ///Si l'espece est presente sur le graphique
    if(presence)
    {
        // Ajout de la top box de l'interface de sommet
        m_interface->m_main_box.add_child(vi->m_top_box);
        // On peut ajouter directement des vertices dans la map avec la notation crochet :
        m_vertices[idx] = Vertex(value, vi);
        m_vertices[idx].m_img = pic_name;
        m_vertices[idx].m_nom = m_vertices[idx].m_img;
        m_vertices[idx].m_idx = idx;
        for(int i = 1; i <= 4; i++)
            m_vertices[idx].m_nom[m_vertices[idx].m_nom.size()-i] = ' ';
        ///Coloration en fonction de l'espece
        if(idx == 1)
            m_vertices[idx].m_couleur=GRIS;
        else if(idx == 2)
            m_vertices[idx].m_couleur=BLANC;
        else if(idx == 3)
            m_vertices[idx].m_couleur=FUCHSIA;
        else if(idx == 4)
            m_vertices[idx].m_couleur=ROSE;
        else if(idx == 5)
            m_vertices[idx].m_couleur=VIOLET;
        else if(idx == 6)
            m_vertices[idx].m_couleur=VERTCLAIR;
        else if(idx == 7)
            m_vertices[idx].m_couleur=KAKI;
        else if(idx == 8)
            m_vertices[idx].m_couleur=CYAN;
        else if(idx == 9)
            m_vertices[idx].m_couleur=BLEU;
        else if(idx == 10)
            m_vertices[idx].m_couleur=ROUGE;
        else if(idx == 11)
            m_vertices[idx].m_couleur=ROUGECLAIR;
        else if(idx == 12)
            m_vertices[idx].m_couleur=ORANGE;
        else if(idx == 13)
            m_vertices[idx].m_couleur=JAUNE;
        else if(idx == 14)
            m_vertices[idx].m_couleur=JAUNECLAIR;
        else if(idx == 0)
            m_vertices[idx].m_couleur=SABLE;
        m_vertices[idx].m_rythm=r;
        m_vertices_mem[idx] = m_vertices[idx];
    }
    ///sinon
    else
    {
        m_vertices_mem[idx] = Vertex(value, vi);
        m_vertices_mem[idx].m_img = pic_name;
        m_vertices_mem[idx].m_nom = m_vertices_mem[idx].m_img;
        m_vertices_mem[idx].m_idx = idx;
        for(int i = 1; i <= 4; i++)
            m_vertices_mem[idx].m_nom[m_vertices_mem[idx].m_nom.size()-i] = ' ';
        if(idx == 0)
            m_vertices_mem[idx].m_couleur=SABLE;
        else if(idx == 1)
            m_vertices_mem[idx].m_couleur=GRIS;
        else if(idx == 2)
            m_vertices_mem[idx].m_couleur=BLANC;
        else if(idx == 3)
            m_vertices_mem[idx].m_couleur=FUCHSIA;
        else if(idx == 4)
            m_vertices_mem[idx].m_couleur=ROSE;
        else if(idx == 5)
            m_vertices_mem[idx].m_couleur=VIOLET;
        else if(idx == 6)
            m_vertices_mem[idx].m_couleur=VERTCLAIR;
        else if(idx == 7)
            m_vertices_mem[idx].m_couleur=KAKI;
        else if(idx == 8)
            m_vertices_mem[idx].m_couleur=CYAN;
        else if(idx == 9)
            m_vertices_mem[idx].m_couleur=BLEU;
        else if(idx == 10)
            m_vertices_mem[idx].m_couleur=ROUGE;
        else if(idx == 11)
            m_vertices_mem[idx].m_couleur=ROUGECLAIR;
        else if(idx == 12)
            m_vertices_mem[idx].m_couleur=ORANGE;
        else if(idx == 13)
            m_vertices_mem[idx].m_couleur=JAUNE;
        else if(idx == 14)
            m_vertices_mem[idx].m_couleur=JAUNECLAIR;
        m_vertices_mem[idx].m_rythm=r;
    }
    m_vertices_mem[idx].set_present(presence);

    m_interface->m_noms[idx] = new grman::WidgetText(m_vertices_mem[idx].m_nom);
    m_interface->m_buton_box[idx] = new grman::WidgetButton;

    m_interface->m_tool_box.add_child(*m_interface->m_noms[idx]);
    m_interface->m_noms[idx]->set_dim(75-24,10);
    m_interface->m_noms[idx]->set_pos(32,14*idx+2);
    if(idx  == 0)
        m_interface->m_noms[idx]->set_pos(32,0);
    m_interface->m_noms[idx]->set_bg_color(BLANCBLEU);
    m_interface->m_tool_box.add_child(*m_interface->m_buton_box[idx]);
    m_interface->m_buton_box[idx]->set_dim(20,10);
    m_interface->m_buton_box[idx]->set_pos(1,14*idx);
    if(presence)
        m_interface->m_buton_box[idx]->set_bg_color(VERT);
    else
        m_interface->m_buton_box[idx]->set_bg_color(ROUGE);


}



/// Aide � l'ajout d'arcs interfac�s
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight, bool presence, bool memoire)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices_mem.find(id_vert1)==m_vertices_mem.end() || m_vertices_mem.find(id_vert2)==m_vertices_mem.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices_mem[id_vert1], m_vertices_mem[id_vert2]);
    if(presence)
    {
        m_interface->m_main_box.add_child(ei->m_top_edge);
        m_edges[idx] = Edge(weight, ei);
        m_edges[idx].m_from = id_vert1;
        m_edges[idx].m_to = id_vert2;
        m_edges[idx].set_idx(idx);

        m_interface->m_main_box.add_child( m_edges[idx].m_interface->m_anim );
        m_edges[idx].m_interface->m_anim.set_pic_name(m_vertices[id_vert1].m_img);
        m_edges[idx].m_interface->m_anim.set_pic_idx(1);
        m_edges[idx].m_interface->m_anim.set_pos(10000,10000);

        if(memoire)
        {
            m_vertices[id_vert1].m_out.push_back(id_vert2);
            m_vertices[id_vert2].m_in.push_back(id_vert1);
            m_edges_mem[idx] = m_edges[idx];
            m_vertices_mem[id_vert1] = m_vertices[id_vert1];
            m_vertices_mem[id_vert2] = m_vertices[id_vert2];
            m_edges_mem[idx].set_present(presence);
        }
    }
    else
    {
        m_edges_mem[idx] = Edge(weight, ei);
        m_edges_mem[idx].m_from = id_vert1;
        m_edges_mem[idx].m_to = id_vert2;
        m_edges_mem[idx].set_idx(idx);
        m_interface->m_main_box.add_child( m_edges_mem[idx].m_interface->m_anim );
        m_edges_mem[idx].m_interface->m_anim.set_pic_name(m_vertices[id_vert1].m_img);
        m_edges_mem[idx].m_interface->m_anim.set_pic_idx(1);
        m_edges_mem[idx].m_interface->m_anim.set_pos(10000,10000);
        m_vertices_mem[id_vert1].m_out.push_back(id_vert2);
        m_vertices_mem[id_vert2].m_in.push_back(id_vert1);
        m_vertices_mem[id_vert1].set_idx(id_vert1);
        m_vertices_mem[id_vert2].set_idx(id_vert2);
        m_edges_mem[idx].set_present(presence);
    }

}

