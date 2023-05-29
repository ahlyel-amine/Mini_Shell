#ifndef HEADER_H
#define HEADER_H

# include <iostream>
# include <string>
# include <vector>
#include <utility>
#include <bits/stdc++.h>
# include <algorithm>
using namespace std;

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


int check_neigh(irc a, crc b, int i, vector<int> *beacons, int last_move, int spawn_index ,bool (*checker)(crc, int, int));
bool	checker_spawn(crc b, int index, int spawn_index);
bool	checker_my_spawn(crc b, int index, int spawn_index);
bool	checker_opp_spawn(crc b, int index, int spawn_index);

#endif