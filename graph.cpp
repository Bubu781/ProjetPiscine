#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les ï¿½lï¿½ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de rï¿½glage de valeur
    m_top_box.add_child( m_slider_value );
<<<<<<< Ilana
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, ï¿½ adapter...
=======
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
>>>>>>> Remise prec.
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
}


/// Gestion du Vertex avant l'appel ï¿½ l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnï¿½e m_value vers le slider associï¿½
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnï¿½e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex aprï¿½s l'appel ï¿½ l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnï¿½e m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les ï¿½lï¿½ments de l'interface
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

    // Une boite pour englober les widgets de rï¿½glage associï¿½s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de rï¿½glage de valeur
    m_box_edge.add_child( m_slider_weight );
<<<<<<< Ilana
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, ï¿½ adapter...
=======
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
>>>>>>> Remise prec.
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel ï¿½ l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnï¿½e m_weight vers le slider associï¿½
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnï¿½e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge aprï¿½s l'appel ï¿½ l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnï¿½e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de prï¿½parer un cadre d'accueil des
/// ï¿½lï¿½ments qui seront ensuite ajoutï¿½s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_tool_box.add_child(m_quit);
    m_quit.set_dim(75,30);
    m_quit.set_pos(1,685);
    m_quit.set_bg_color(ROUGE);

    m_tool_box.add_child(m_return);
    m_return.set_dim(75,30);
    m_return.set_pos(1,650);
    m_return.set_bg_color(BLEU);

    m_tool_box.add_child(m_save);
    m_save.set_dim(75,30);
    m_save.set_pos(1,615);
    m_save.set_bg_color(VERT);

    m_tool_box.add_child(m_txt_quit);
    m_txt_quit.set_dim(75,10);
    m_txt_quit.set_pos(15,700);
    m_txt_quit.set_message("Quitter");
    m_txt_quit.set_color(BLANC);

    m_tool_box.add_child(m_txt_return);
    m_txt_return.set_dim(75,10);
    m_txt_return.set_pos(24,665);
    m_txt_return.set_message("Menu");
    m_txt_return.set_color(BLANC);

    m_tool_box.add_child(m_txt_save);
    m_txt_save.set_dim(75,10);
    m_txt_save.set_pos(1,630);
    m_txt_save.set_message("Sauvegarde");
    m_txt_save.set_color(BLANC);
}


/// Mï¿½thode spï¿½ciale qui construit un graphe arbitraire (dï¿½mo)
/// Cette mï¿½thode est ï¿½ enlever et remplacer par un systï¿½me
/// de chargement de fichiers par exemple.
/// Bien sï¿½r on ne veut pas que vos graphes soient construits
/// "ï¿½ la main" dans le code comme ï¿½a.
void Graph::load(std::string fic)
{
<<<<<<< Ilana
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne prï¿½cï¿½dente est en gros ï¿½quivalente ï¿½ :
    // m_interface = new GraphInterface(50, 0, 750, 600);
=======
>>>>>>> Remise prec.
    std::ifstream fichier(fic, std::ios::in);
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    int indice, x, y, s1, s2, nb;
    double poids;
    bool presence;
    m_nom = fic;
    std::string img;
    if(fichier)
    {
        fichier >> nb;
        nb_sommet = nb;
        for(int i = 0; i < nb; i++)
        {
            fichier >> indice;
            fichier >> poids;
            fichier >> x;
            fichier >> y;
            fichier >> presence;
            fichier.ignore();
            getline(fichier, img, '\n');
            add_interfaced_vertex(indice, poids, x, y, img, presence);
        }
        fichier >> nb;
        nb_arretes = nb;
        for(int i = 0; i < nb; i++)
        {
            fichier >> indice;
            fichier >> s1;
            fichier >> s2;
            fichier >> poids;
            fichier >> presence;
            add_interfaced_edge(indice, s1, s2, poids, presence);
        }
        fichier.close();
    }
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

<<<<<<< Ilana
    /*/// Les sommets doivent ï¿½tre dï¿½finis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent ï¿½tre dï¿½finis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);*/
=======
    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    /*add_interfaced_vertex(0, 30.0, 200, 100, "clown1.jpg");
      add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
      add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
      add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
      add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
      add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
      add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
      add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

      /// Les arcs doivent être définis entre des sommets qui existent !
      // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
      add_interfaced_edge(0, 1, 2, 50.0);
      add_interfaced_edge(1, 0, 1, 50.0);
      add_interfaced_edge(2, 1, 3, 75.0);
      add_interfaced_edge(3, 4, 1, 25.0);
      add_interfaced_edge(4, 6, 3, 25.0);
      add_interfaced_edge(5, 7, 3, 25.0);
      add_interfaced_edge(6, 3, 4, 0.0);
      add_interfaced_edge(7, 2, 0, 100.0);
      add_interfaced_edge(8, 5, 2, 20.0);
      add_interfaced_edge(9, 3, 7, 80.0);*/
>>>>>>> Remise prec.
}

void Graph::save()
{

    std::ofstream fichier(m_nom, std::ios::trunc);
    if(fichier)
    {
        fichier << nb_sommet << std::endl;
        for(auto elem : m_vertices_mem)
        {
            fichier << elem.first<< " ";
            fichier << elem.second.m_value << " ";
            fichier << elem.second.m_interface->m_top_box.get_posx() << " ";
            fichier << elem.second.m_interface->m_top_box.get_posy() << " ";
            fichier << elem.second.m_present;
            fichier << std::endl;
            fichier << elem.second.m_img;
            fichier << std::endl;
        }
        fichier << nb_arretes << std::endl;
        for(auto elem : m_edges_mem)
        {
            fichier << elem.first << " ";
            fichier << elem.second.m_from << " ";
            fichier << elem.second.m_to << " ";
            fichier << elem.second.m_weight << " ";
            fichier << elem.second.m_present;
            if(elem.first != nb_arretes-1)
                fichier << std::endl;

        }
        fichier.close();
    }
}

/// La mï¿½thode update ï¿½ appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    for (auto elem : m_interface->m_buton_box)
    {
        if(elem.second->clicked())
            modification(elem.first);
    }
    if(m_interface->m_save.clicked())
        save();
    if(m_interface->m_quit.clicked())
        exit(0);
    if(m_interface->m_return.clicked())
        m_used = false;

}

void Graph::modification(int i)
{
    std::vector<int> x;
    if(m_vertices_mem[i].get_present())
    {
retour:
        for(auto elem : m_edges)
        {

            if((elem.second.m_from == i || elem.second.m_to == i))
            {
                m_interface->m_main_box.remove_child(elem.second.m_interface->m_top_edge);
                m_edges_mem[elem.first].set_present(false);
                m_edges.erase(elem.first);
                goto retour;
            }
        }
        m_interface->m_main_box.remove_child(m_vertices[i].m_interface->m_top_box);
        m_vertices_mem[i].set_present(false);
        m_vertices.erase(i);
        m_interface->m_buton_box[i]->set_bg_color(ROUGE);
    }
    else
    {
        m_vertices_mem[i].set_present(true);
        m_vertices[i] = m_vertices_mem[i];
        m_interface->m_main_box.add_child(m_vertices[i].m_interface->m_top_box);
        for(auto elem : m_edges_mem)
        {
            if((m_vertices_mem[elem.second.m_to].get_present() && elem.second.m_from == i)
                    || (m_vertices_mem[elem.second.m_from].get_present() && elem.second.m_to == i))
            {
                m_edges_mem[elem.first].set_present(true);
                m_edges[elem.first] = elem.second;
                m_interface->m_main_box.add_child(m_edges[elem.first].m_interface->m_top_edge);
            }
        }
        m_interface->m_buton_box[i]->set_bg_color(VERT);
    }
}

<<<<<<< Ilana
/// Aide ï¿½ l'ajout de sommets interfacï¿½s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
=======
/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, bool presence, int pic_idx)
>>>>>>> Remise prec.
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Crï¿½ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);

    if(presence)
    {
        // Ajout de la top box de l'interface de sommet
        m_interface->m_main_box.add_child(vi->m_top_box);
        // On peut ajouter directement des vertices dans la map avec la notation crochet :
        m_vertices[idx] = Vertex(value, vi);
        m_vertices[idx].m_img = pic_name;
        m_vertices[idx].m_nom = m_vertices[idx].m_img;
        for(int i = 1; i <= 4; i++)
            m_vertices[idx].m_nom[m_vertices[idx].m_nom.size()-i] = ' ';
        m_vertices_mem[idx] = m_vertices[idx];
    }
    else
    {
        m_vertices_mem[idx] = Vertex(value, vi);
        m_vertices_mem[idx].m_img = pic_name;
        m_vertices_mem[idx].m_nom = m_vertices_mem[idx].m_img;
        for(int i = 1; i <= 4; i++)
            m_vertices_mem[idx].m_nom[m_vertices_mem[idx].m_nom.size()-i] = ' ';
    }
    m_vertices_mem[idx].set_present(presence);
    m_interface->m_noms[idx] = new grman::WidgetText(m_vertices_mem[idx].m_nom);
    m_interface->m_buton_box[idx] = new grman::WidgetButton;

    m_interface->m_tool_box.add_child(*m_interface->m_noms[idx]);
    m_interface->m_noms[idx]->set_dim(75-24,20);
    m_interface->m_noms[idx]->set_pos(32,26*idx);
    if(idx  == 0)
        m_interface->m_noms[idx]->set_pos(32,6);
    m_interface->m_noms[idx]->set_bg_color(BLANCBLEU);
    m_interface->m_tool_box.add_child(*m_interface->m_buton_box[idx]);
    m_interface->m_buton_box[idx]->set_dim(20,20);
    m_interface->m_buton_box[idx]->set_pos(1,24*idx);
    if(presence)
        m_interface->m_buton_box[idx]->set_bg_color(VERT);
    else
        m_interface->m_buton_box[idx]->set_bg_color(ROUGE);


}

<<<<<<< Ilana
/// Aide ï¿½ l'ajout d'arcs interfacï¿½s
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
=======
/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight, bool presence)
>>>>>>> Remise prec.
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
        m_edges_mem[idx] = m_edges[idx];
    }
    else
    {
        m_edges_mem[idx] = Edge(weight, ei);
        m_edges_mem[idx].m_from = id_vert1;
        m_edges_mem[idx].m_to = id_vert2;
    }
    m_edges_mem[idx].set_present(presence);
}

