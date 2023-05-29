
# include <iostream>
# include <string>
# include <vector>
#include <utility>
# include <algorithm>
using namespace std;


typedef struct s_map_tree
{
    int index:8;
    struct s_map_tree  *n_0;
    struct s_map_tree  *n_1;
    struct s_map_tree  *n_2;
    struct s_map_tree  *n_3;
    struct s_map_tree  *n_4;
    struct s_map_tree  *n_5;
}   t_tree;

t_tree  *new_node(int index)
{
    t_tree  *new_;

    new_ = (t_tree *)malloc(sizeof(t_tree));
    new_->index = index;
    new_->n_0 = NULL;
    new_->n_1 = NULL;
    new_->n_2 = NULL;
    new_->n_3 = NULL;
    new_->n_4 = NULL;
    new_->n_5 = NULL;
    return (new_);
}

// bool    in_tree(t_tree *map, int index)
// {
//     if (!map)
//         return (0);
//     if (map->index == index)
//         return (1);
//     else if (map->n_0)
//         in_tree(map->n_0, index);
//     else if (map->n_1)
//         in_tree(map->n_1, index);
//     else if (map->n_2)
//         in_tree(map->n_2, index);
//     else if (map->n_3)
//         in_tree(map->n_3, index);
//     else if (map->n_4)
//         in_tree(map->n_4, index);
//     else if (map->n_5 )
//         in_tree(map->n_5 , index);
//     return (0);
// }

bool    in_tree(vector<int> *map_inedxes, int index)
{
    for (int i = 0; i < map_inedxes->size(); i++){
        if ((*map_inedxes)[i] == index)
            return (1);
    }
    return (0);
}

class   InitialRessourcesClass
{
    public :
    InitialRessourcesClass(int type_, int initial_resources_, int neigh_0_, int neigh_1_, int neigh_2_, int neigh_3_, int neigh_4_, int neigh_5_){
        this->type = type_;
        this->initial_resources = initial_resources_;
        this->neigh_0 = neigh_0_; 
        this->neigh_1 = neigh_1_;
        this->neigh_2 = neigh_2_;
        this->neigh_3 = neigh_3_;
        this->neigh_4 = neigh_4_;
        this->neigh_5 = neigh_5_;
    }
    int type; // 0 for empty, 1 for eggs, 2 for crystal
    int initial_resources; // the initial amount of eggs/crystals on this cell
    int neigh_0; // the index of the neighbouring cell for each direction
    int neigh_1;
    int neigh_2;
    int neigh_3;
    int neigh_4;
    int neigh_5;
    ~InitialRessourcesClass(){ };
};

class   CurrentRessourcesClass
{
    public :
    CurrentRessourcesClass(int resources_, int my_ants_, int opp_ants_){
        this->resources = resources_;
        this->my_ants = my_ants_;
        this->opp_ants = opp_ants_;
    }
        int resources; // the current amount of eggs/crystals on this cell
        int my_ants; // the amount of your ants on this cell
        int opp_ants; // the amount of opponent ants on this cell
    ~CurrentRessourcesClass(){};
};

#define irc vector<InitialRessourcesClass> 
#define crc vector<CurrentRessourcesClass>

t_tree  *build_tree_up(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_1 = build_tree_up(a, a[index].neigh_1, map_inedxes);
        new_->n_2 = build_tree_up(a, a[index].neigh_2, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree_down(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_4 = build_tree_down(a, a[index].neigh_4, map_inedxes);
        new_->n_5 = build_tree_down(a, a[index].neigh_5, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree_left(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_0 = build_tree_left(a, a[index].neigh_0, map_inedxes);
        new_->n_1 = build_tree_left(a, a[index].neigh_1, map_inedxes);
        new_->n_5 = build_tree_left(a, a[index].neigh_5, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree_right(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_2 = build_tree_right(a, a[index].neigh_2, map_inedxes);
        new_->n_3 = build_tree_right(a, a[index].neigh_3, map_inedxes);
        new_->n_4 = build_tree_right(a, a[index].neigh_4, map_inedxes);
        return (new_);
    }
    return (NULL);
}

t_tree  *build_tree(irc a, int index, vector<int> *map_inedxes)
{
    t_tree  *new_;

    if (index != -1 && !in_tree(map_inedxes, index))
    {
        map_inedxes->push_back(index);
        new_ = new_node(index);
        new_->n_0 = build_tree_left(a, a[index].neigh_0, map_inedxes);
        new_->n_1 = build_tree_up(a, a[index].neigh_1, map_inedxes);
        new_->n_2 = build_tree_up(a, a[index].neigh_2, map_inedxes);
        new_->n_3 = build_tree_right(a, a[index].neigh_3, map_inedxes);
        new_->n_4 = build_tree_down(a, a[index].neigh_4, map_inedxes);
        new_->n_5 = build_tree_down(a, a[index].neigh_5, map_inedxes);
        return (new_);
    }
    return (NULL);
}

void    print_tree(t_tree *map)
{
    if (!map)
        return ;
    cout << map->index << endl;
    print_tree((t_tree *)map->n_0);
    print_tree((t_tree *)map->n_1);
    print_tree((t_tree *)map->n_2);
    print_tree((t_tree *)map->n_3);
    print_tree((t_tree *)map->n_4);
    print_tree((t_tree *)map->n_5);
}

int each_neighbor(irc a, int number_of_cells, int *neigh_indx, int target)
{
    for (int i = 0; i < number_of_cells; i++){
        if (a[i].neigh_0 == target){
            *neigh_indx = 0;
            return (i);
        }
        if (a[i].neigh_1 == target){
            *neigh_indx = 1;
            return (i);
        }
        if (a[i].neigh_2 == target){
            *neigh_indx = 2;
            return (i);
        }
        if (a[i].neigh_3 == target){
            *neigh_indx = 3;
            return (i);
        }
        if (a[i].neigh_4 == target){
            *neigh_indx = 4;
            return (i);
        }
        if (a[i].neigh_5 == target){
            *neigh_indx = 5;
            return (i);
        }
    }
    return (-1);
}

void    add_in_map(t_tree *map, int missing, int neigh_indx)
{
    cout << "missing " << missing << " at index "<< neigh_indx << " of " << map->index << endl;
    if (neigh_indx == 0)
        map->n_0 = new_node(missing);
    else if (neigh_indx == 1)
        map->n_1 = new_node(missing);
    else if (neigh_indx == 2)
        map->n_2 = new_node(missing);
    else if (neigh_indx == 3)
        map->n_3 = new_node(missing);
    else if (neigh_indx == 4)
        map->n_4 = new_node(missing);
    else if (neigh_indx == 5)
        map->n_5 = new_node(missing);
}

bool    add_in_map_at(t_tree *map, int missing, int missing_neighbor, int neigh_indx)
{
    if (!map)
        return (0);
    else if (map->index == missing_neighbor)
        return (add_in_map(map, missing, neigh_indx), 1);
    else if (map->n_0 && add_in_map_at(map->n_0, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_1 && add_in_map_at(map->n_1, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_2 && add_in_map_at(map->n_2, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_3 && add_in_map_at(map->n_3, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_4 && add_in_map_at(map->n_4, missing, missing_neighbor, neigh_indx))
        return (1);
    else if (map->n_5 && add_in_map_at(map->n_5, missing, missing_neighbor, neigh_indx))
        return (1);
    return (0);
}

int main()
{
    irc a;
    crc b;

    int number_of_cells; // amount of hexagonal cells in this map
    cin >> number_of_cells; cin.ignore();
    for (int i = 0; i < number_of_cells; i++) {
        // int type; // 0 for empty, 1 for eggs, 2 for crystal
        // int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        cin >> /*type >> initial_resources >> */neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
        a.push_back(InitialRessourcesClass(0, 0, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5));
    }
    vector<int> map_inedxes;
    int neigh_indx;
    int missing_neighbor;
    t_tree  *map = build_tree(a, 0, &map_inedxes);
    if (number_of_cells > map_inedxes.size())
        ;
    t_tree  *holder = map;
    for (int missing =0; missing < number_of_cells; missing++){
        if (!in_tree(&map_inedxes, missing)){
            missing_neighbor = each_neighbor(a, number_of_cells, &neigh_indx, missing);
            add_in_map_at(map, missing, missing_neighbor, neigh_indx);
        }
    }

    // printf ("%p\n", holder);
    print_tree(map);

    // cout << "neighbor 0 : " << endl;
    // print_tree(map->n_0, 0);
    // cout << "neighbor 1 : " << endl;
    // print_tree(map->n_0, 1);
    // cout << "neighbor 2 : " << endl;
    // print_tree(map->n_0, 2);
    // cout << "neighbor 3 : " << endl;
    // print_tree(map->n_0, 3);
    // cout << "neighbor 4 : " << endl;
    // print_tree(map->n_0, 4);
    // cout << "neighbor 5 : " << endl;
    // print_tree(map->n_0, 5);
    // cout << "vector : " << endl;
}



















































int check_neghibors(irc a, crc b, int index, int base_index)
{
    if (a[index].neigh_0 == base_index)
        return (a[index].neigh_0);
    else if (a[index].neigh_1 == base_index)
        return (a[index].neigh_1);
    else if (a[index].neigh_2 == base_index)
        return (a[index].neigh_2);
    else if (a[index].neigh_3 == base_index)
        return (a[index].neigh_3);
    else if (a[index].neigh_4 == base_index)
        return (a[index].neigh_4);
    else if (a[index].neigh_5 == base_index)
        return (a[index].neigh_5);
    return (-1);
}

int    get_shortest_path(irc a, crc b, int index, int base_index, vector<int> *beacons)
{
    int tmp;

    beacons->push_back(index);
    tmp = check_neghibors(a, b, index, base_index);
    if (tmp != -1)
    {
        beacons->push_back(tmp);
        return (1);
    }
    else if (get_shortest_path(a, b, a[index].neigh_0, base_index, beacons))
        return (1);
    else if (get_shortest_path(a, b, a[index].neigh_1, base_index, beacons))
        return (1);
    else if (get_shortest_path(a, b, a[index].neigh_2, base_index, beacons))
        return (1);
    else if (get_shortest_path(a, b, a[index].neigh_3, base_index, beacons))
        return (1);
    else if (get_shortest_path(a, b, a[index].neigh_4, base_index, beacons))
        return (1);
    else if (get_shortest_path(a, b, a[index].neigh_5, base_index, beacons))
        return (1);
    else
    {
        beacons->pop_back();
        return (0);
    }
}