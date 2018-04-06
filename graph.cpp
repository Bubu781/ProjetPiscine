#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
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


/// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex apr�s l'appel � l'interface
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

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h, std::string nom)
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


    if(nom == "fichier1.txt")
    {
        m_main_box.add_child( m_fond );
        m_fond.set_pic_name("ocean.jpg");
        m_fond.set_pic_idx(0);
        m_fond.set_gravity_x(grman::GravityX::Right);
    }
    else if(nom =="fichier2.txt")
    {
        m_main_box.add_child( m_fond );
        m_fond.set_pic_name("forest.png");
        m_fond.set_pic_idx(0);
        m_fond.set_gravity_x(grman::GravityX::Right);
    }
    else if(nom =="fichier3.txt")
    {
        m_main_box.add_child( m_fond );
        m_fond.set_pic_name("ciel.png");
        m_fond.set_pic_idx(0);
        m_fond.set_gravity_x(grman::GravityX::Right);
    }

    m_tool_box.add_child(m_quit);
    m_quit.set_dim(75,30);
    m_quit.set_pos(1,685);
    m_quit.set_bg_color(ROUGE);

    m_quit.add_child(m_txt_quit);
    m_txt_quit.set_dim(75,10);
    m_txt_quit.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_quit.set_message("Quitter");
    m_txt_quit.set_color(BLANC);

    m_tool_box.add_child(m_return);
    m_return.set_dim(75,30);
    m_return.set_pos(1,650);
    m_return.set_bg_color(BLEU);

    m_return.add_child(m_txt_return);
    m_txt_return.set_dim(75,10);
    m_txt_return.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_return.set_message("Menu");
    m_txt_return.set_color(BLANC);

    m_tool_box.add_child(m_save);
    m_save.set_dim(75,30);
    m_save.set_pos(1,615);
    m_save.set_bg_color(VERT);

    m_save.add_child(m_txt_save);
    m_txt_save.set_dim(75,10);
    m_txt_save.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_save.set_message("Sauvegarde");
    m_txt_save.set_color(BLANC);

    m_tool_box.add_child(m_disconnect);
    m_disconnect.set_dim(75,30);
    m_disconnect.set_pos(1,580);
    m_disconnect.set_bg_color(MARRON);

    m_disconnect.add_child(m_txt_disconnect);
    m_txt_disconnect.set_dim(75,10);
    m_txt_disconnect.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_disconnect.set_message("Connexite");
    m_txt_disconnect.set_color(BLANC);

    m_tool_box.add_child(m_simulation);
    m_simulation.set_dim(75,30);
    m_simulation.set_pos(1,545);
    m_simulation.set_bg_color(ROUGE);

    m_simulation.add_child(m_txt_simulation);
    m_txt_simulation.set_dim(75,10);
    m_txt_simulation.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_simulation.set_message("Simulation");
    m_txt_simulation.set_color(BLANC);

    m_tool_box.add_child(m_mod_edge);
    m_mod_edge.set_dim(75,30);
    m_mod_edge.set_pos(1,510);
    m_mod_edge.set_bg_color(MARRON);

    m_mod_edge.add_child(m_txt_mod_edge);
    m_txt_mod_edge.set_dim(75,10);
    m_txt_mod_edge.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_mod_edge.set_message("Mod edge");
    m_txt_mod_edge.set_color(BLANC);

    m_tool_box.add_child(m_grapique);
    m_grapique.set_dim(75,30);
    m_grapique.set_pos(1,475);
    m_grapique.set_bg_color(MARRON);

    m_grapique.add_child(m_txt_grapique);
    m_txt_grapique.set_dim(75,10);
    m_txt_grapique.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_txt_grapique.set_message("Graphique");
    m_txt_grapique.set_color(BLANC);

    m_tool_box.add_child(m_ft_connexe);
    m_ft_connexe.set_dim(75,30);
    m_ft_connexe.set_pos(1,440);
    m_ft_connexe.set_bg_color(MARRON);

    m_ft_connexe.add_child(m_txt_ft_connexe);
    m_txt_ft_connexe.set_dim(75,10);
    m_txt_ft_connexe.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Center);
    m_txt_ft_connexe.set_message("Ft connexite");
    m_txt_ft_connexe.set_color(BLANC);
}


/// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
/// Cette m�thode est � enlever et remplacer par un syst�me
/// de chargement de fichiers par exemple.
/// Bien s�r on ne veut pas que vos graphes soient construits
/// "� la main" dans le code comme �a.
void Graph::load(std::string fic)
{
    std::ifstream fichier(fic, std::ios::in);
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600, fic);
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
            add_interfaced_vertex(indice, poids, x, y, img, presence, 1);
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

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
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
    if(m_interface->m_disconnect.clicked())
        disconnect();
    if(m_interface->m_simulation.clicked())
        {
            m_interface->m_simulation.set_bg_color(ROUGE);
            simulation = !simulation;
        }
    if(m_interface->m_mod_edge.clicked())
        modification_edges();
    if(m_interface->m_grapique.clicked())
        graphic();
    //if(m_interface->m_ft_connexe.clicked())
        fort_connexe();
    if(simulation)
        evol_pop();

    for(auto elem : m_edges)
    {
        elem.second.m_interface->m_top_edge.set_thickness(1+elem.second.m_weight/20);
    }

}

void Graph::evol_pop()
{
    double K;///K capacité de portage
    std::vector<double> liste;
    double tot;
    double coef, N, R;
    m_interface->m_simulation.set_bg_color(VERT);
    for(auto elem: m_vertices)
    {
        m_vertices[elem.first].m_valeurs.push_back(elem.second.m_value);
        K=0;
        tot=0;
        for(auto arete: m_edges)
        {
            if(m_edges[arete.first].m_to==elem.first && m_vertices[arete.second.m_from].m_value > 0)
            {
                coef = 1+ m_edges[arete.first].m_weight/100;
                N = m_vertices[arete.second.m_from].m_value;
                K+=coef*N;
            }
            else if(m_edges[arete.first].m_from==elem.first && m_vertices[arete.second.m_to].m_value > 0)
            {
                if(m_vertices[arete.second.m_to].m_nom != "debrits    " && m_vertices[arete.second.m_to].m_nom != "sels    ")
                {
                    coef = 1+ m_edges[arete.first].m_weight/100;
                    N = m_vertices[arete.second.m_to].m_value;
                    liste.push_back(coef*N);
                }
            }

        }
        for(auto coef : liste)
            tot += coef;
        R = m_vertices[elem.first].m_rythm;
        N = m_vertices[elem.first].m_value;
        N+= R*N*(1-(N/K))-tot;
        m_vertices[elem.first].m_value = K;

        if(m_vertices[elem.first].m_value < 0)
            m_vertices[elem.first].m_value = 0;
        if(m_vertices[elem.first].m_value >100)
            m_vertices[elem.first].m_value = 100;

        liste.erase(liste.begin(),liste.end());
    }
    //system("PAUSE");
}

void Graph::modification_edges()
{
    int s1, s2, num, x, y;
    bool verif = false;
    system("cls");
    std::cout << "Quels sommets relier/supprimer?" << std::endl;
    for(auto elem : m_vertices)
        std::cout << elem.first << ". " << elem.second.m_nom << std::endl;
    std::cin >> s1;
    std::cin >> s2;
    for(auto elem : m_edges)
        if(elem.second.m_from == s1 && elem.second.m_to == s2)
            verif = true, num = elem.first;
    if(!verif)
        {
            add_interfaced_edge(nb_arretes, s1, s2, 50, true);
            nb_arretes++;
            m_vertices[s1].m_out.push_back(s2);
            m_vertices[s2].m_in.push_back(s1);
        }
    else
    {
        for(unsigned int i = 0;i < m_vertices[s1].m_in.size(); i++)
            if(m_vertices[s1].m_in[i] == s2)
                x = i;
        for(unsigned int i = 0;i < m_vertices[s2].m_out.size(); i++)
            if(m_vertices[s2].m_out[i] == s1)
                y = i;
        m_vertices[s1].m_out.erase(m_vertices[s1].m_out.begin() + x);
        m_vertices[s2].m_in.erase(m_vertices[s2].m_in.begin() + y);
        m_interface->m_main_box.remove_child(m_edges[num].m_interface->m_top_edge);
        m_edges_mem[num].set_present(false);
        m_edges.erase(num);
        nb_arretes--;
    }
    system("cls");
}

void Graph::disconnect()
{
    int imin = 200, i, refer;
    for(auto sommets : m_vertices)
    {
        i = 0;
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
        if(i < imin && i != 0)
        {
            imin = i;
            refer = sommets.first;
        }
    }
    for(auto elem : m_edges)
    {
        if(elem.second.m_from == refer)
            modification(elem.second.m_to);
        else if(elem.second.m_to == refer)
            modification(elem.second.m_from);
    }
}

void Graph::modification(int i)
{
    std::vector<int> x;
    if(m_vertices_mem[i].get_present())
    {
        for(auto elem : m_edges)
        {

            if((elem.second.m_from == i || elem.second.m_to == i))
            {
                m_interface->m_main_box.remove_child(elem.second.m_interface->m_top_edge);
                m_edges_mem[elem.first].set_present(false);
                m_edges.erase(elem.first);
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

void Graph::fort_connexe()
{
    std::vector<int> liste;
    std::vector<std::vector<int>> mat;
    Vertex v;
    bool verif;
    for(auto elem : m_vertices)
    {
        v = m_vertices[elem.first];
        for(auto som : m_vertices)
            m_vertices[som.first].m_marqued = false;
        retour:
            liste.push_back(v.m_idx);
            retour2:
            verif = false;
        for(auto conn : v.m_out)
        {
            if(conn == elem.first)
            {
                liste.push_back(elem.first);
                m_vertices[elem.first].m_marqued = true;
                break;
            }
            else if(!m_vertices[conn].m_marqued)
            {
                v = m_vertices[conn];
                m_vertices[conn].m_marqued = true;
                goto retour;
            }
        }
            if(v.m_out.empty() && liste.back() != elem.first)
                verif = true;
        if(verif)
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
    if(!mat.empty())
    {
        for(auto elem : m_edges)
        {
            m_edges[elem.first].m_interface->m_top_edge.set_color(GRISSOMBRE);
        }
        for(auto elem : mat)
        {
            liste = elem;
            for(unsigned int i=0; i < liste.size()-1; i++)
            {
                for(auto arete : m_edges)
                {
                    if(arete.second.m_from == liste[i] && arete.second.m_to == liste[i+1])
                        m_edges[arete.first].m_interface->m_top_edge.set_color(ROUGE);
                }
            }
        }
    }
}

void Graph::graphic()
{
    BITMAP *graphic;
    graphic = create_bitmap( 1024, 768);
    int x1, x2, y1, y2;
    x1=0;
    x2=10;
    y1=0;
    y2=10;
    clear_to_color(graphic, NOIR);
    for (auto elem : m_vertices)
        {
           rectfill(graphic, x1,  y1, x2, y2, elem.second.m_couleur);
           for(auto lettre : elem.second.m_nom)
           {
               textprintf_ex(graphic, font , x2+3, y1, BLANC, NOIR, "%c",lettre);
               x2+=7;
           }
           x2 = 10;
           y1=y1+10;
           y2=y2+10;
        }
        line(graphic, 230, 50, 230, 650, BLANC);
        line(graphic, 230, 650, 850, 650, BLANC);
    while (!key[KEY_SPACE])
    {
        for (auto elem : m_vertices)
        {


        if(!elem.second.m_valeurs.empty())
        {
            circlefill(graphic, 230, 650-elem.second.m_valeurs[0]*5,5,elem.second.m_couleur);
        for (unsigned int i=0;i<elem.second.m_valeurs.size()-1;i++)
        {
            if(elem.second.m_valeurs[i+1] != 0 || elem.second.m_valeurs[i] != 0)
            {
                line(graphic, 20*i+230, 650-elem.second.m_valeurs[i]*5, 20*(i+1)+230, 650-elem.second.m_valeurs[i+1]*5, elem.second.m_couleur);
                circlefill(graphic, 20*(i+1)+230, 650-elem.second.m_valeurs[i+1]*5,5,elem.second.m_couleur);
            }
        }
        }
        }
        blit(graphic, screen, 0, 0, 0, 0, 1024, 768);
        evol_pop();
        rest(500);
    }
}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, bool presence, int pic_idx)
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);

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
        else if(idx == 15)
            m_vertices[idx].m_couleur=SABLE;
    m_vertices_mem[idx] = m_vertices[idx];
    }
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
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight, bool presence)
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
        m_vertices[id_vert1].m_in.push_back(id_vert2);
        m_vertices[id_vert2].m_out.push_back(id_vert1);
        m_vertices[id_vert1].set_idx(id_vert1);
        m_vertices[id_vert2].set_idx(id_vert2);
        m_edges_mem[idx] = m_edges[idx];
        m_vertices_mem[id_vert1] = m_vertices[id_vert1];
        m_vertices_mem[id_vert2] = m_vertices[id_vert2];
    }
    else
    {
        m_edges_mem[idx] = Edge(weight, ei);
        m_edges_mem[idx].m_from = id_vert1;
        m_edges_mem[idx].m_to = id_vert2;
        m_edges_mem[idx].set_idx(idx);
        m_vertices_mem[id_vert1].m_out.push_back(id_vert2);
        m_vertices_mem[id_vert2].m_in.push_back(id_vert1);
        m_vertices_mem[id_vert1].set_idx(id_vert1);
        m_vertices_mem[id_vert2].set_idx(id_vert2);
    }
    m_edges_mem[idx].set_present(presence);
}

