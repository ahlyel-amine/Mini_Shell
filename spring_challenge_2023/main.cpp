#include "header.hpp"

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

bool cell_allready_called(vector<int> logs, int i)
{
    if (logs.size() > 1)
    {
        for (int j = 0; j < logs.size() - 1; j++){
            if (i == logs[j])
                return (1);
        }
    }
    return (0);
}


bool neighbors_got_eggs(irc a, crc *b, int my_base_index)
{
    int ret = 0;
    if (a[a[my_base_index].neigh_0].type == 1 && (*b)[a[my_base_index].neigh_0].resources > 0)
    {
        cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_0 << " 1;";
        (*b)[a[my_base_index].neigh_0].resources = 0;
        ret = 1;
    }
    if (a[a[my_base_index].neigh_1].type == 1 && (*b)[a[my_base_index].neigh_1].resources > 0)
    {
        cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_1 << " 1;";
        (*b)[a[my_base_index].neigh_1].resources = 0;
        ret = 1;
    }
    if (a[a[my_base_index].neigh_2].type == 1 && (*b)[a[my_base_index].neigh_2].resources > 0)
    {
        cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_2 << " 1;";
        (*b)[a[my_base_index].neigh_2].resources = 0;
        ret = 1;
    }
    if (a[a[my_base_index].neigh_3].type == 1 && (*b)[a[my_base_index].neigh_3].resources > 0)
    {
        cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_3 << " 1;";
        (*b)[a[my_base_index].neigh_3].resources = 0;
        ret = 1;
    }
    if (a[a[my_base_index].neigh_4].type == 1 && (*b)[a[my_base_index].neigh_4].resources > 0)
    {
        cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_4 << " 1;";
        (*b)[a[my_base_index].neigh_4].resources = 0;
        ret = 1;
    }
    if (a[a[my_base_index].neigh_5].type == 1 && (*b)[a[my_base_index].neigh_5].resources > 0)
    {
        cout << "LINE " << my_base_index << " " << a[my_base_index].neigh_5 << " 1;";
        (*b)[a[my_base_index].neigh_5].resources = 0;
        ret = 1;
    }
    return (ret);
}

int main()
{
    irc a;
    crc b;

    int number_of_cells; // amount of hexagonal cells in this map
    cin >> number_of_cells; cin.ignore();
    for (int i = 0; i < number_of_cells; i++) {
        int type; // 0 for empty, 1 for eggs, 2 for crystal
        int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();
        a.push_back(InitialRessourcesClass(type, initial_resources, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5));
    }
    int number_of_bases;
    int my_base_index;
    cin >> number_of_bases; cin.ignore();
    for (int i = 0; i < number_of_bases; i++) {
        cin >> my_base_index; cin.ignore();
    }
    for (int i = 0; i < number_of_bases; i++) {
        int opp_base_index;
        cin >> opp_base_index; cin.ignore();
    }
    // game loop
    while (1) {
		for (int i = 0; i < number_of_cells; i++) {
			int resources; // the current amount of eggs/crystals on this cell
			int my_ants; // the amount of your ants on this cell
			int opp_ants; // the amount of opponent ants on this cell
			cin >> resources >> my_ants >> opp_ants; cin.ignore();
			b.push_back(CurrentRessourcesClass(resources, my_ants, opp_ants));
		}
		vector<pair<int, int>> ressources;
		vector<int> beacons;
		vector<int> logs;

		vector<pair<int,int>> my_spawn;
		vector<pair<int,int>> opp_spawn;
		vector<pair<pair<int,int>,int>> my_ants;
		vector<pair<pair<int,int>,int>> opp_ants;
		crc b_copy = b;
		for (int i = 0; i < number_of_cells; i++){
			if (b[i].ressources > 0){
				if (check_neigh(a, b, i, &beacons, -1, my_base_index, checker_spawn))
				{
					pair <int,int> tmp;
					tmp.first = beacons[0];
					tmp.second = beacons.size();
					add_it_in(&my_spawn, tmp);
				}
				beacons.clear();
				if (check_neigh(a, b, i, &beacons, -1, opp_base_index, checker_spawn))
				{
					pair <int,int> tmp;
					tmp.firts = beacons[0];
					tmp.second = beacons.size();
					add_it_in(&opp_spawn, tmp);
				}
				beacons.clear();
				while (check_neigh(a, b_copy, i, &beacons, -1, opp_base_index, checker_my_ants))
				{
					pair<pair<int,int>,int> tmp;
					tmp.firts.first = beacons[0];
					tmp.firts.second = beacons.back();
					tmp.second = beacons.size();
					b_copy[tmp.firts.second].my_ants = 0;
					add_it_in_dpair(&my_ants, tmp);
					beacons.clear();
				}
				beacons.clear();
				b_copy = b;
				while (check_neigh(a, b_copy, i, &beacons, -1, opp_base_index, checker_opp_ants))
				{
					pair<pair<int,int>,int> tmp;
					tmp.firts.first = beacons[0];
					tmp.firts.second = beacons.back();
					tmp.second = beacons.size();
					b_copy[tmp.firts.second].opp_ants = 0;
					add_it_in_dpair(&opp_ants, tmp);
					beacons.clear();
				}
				beacons.clear();
				b_copy = b;
			}
		}
		// while (check_neigh(a, b, my_base_index, &tmp_beacons, &logs)) {
		// 	pair<int, int> tmp;
		// 	tmp.first = tmp_beacons.back();
		// 	tmp.second = tmp_beacons.size();
		// 	ressources.push_back(tmp);
		// 	b[tmp.first].resources = 0;
		// 	tmp_beacons.clear();
		// 	logs.clear();
		// }
		for (int i = 0; i < ressources.size(); i++){
			if (b[ressources[i].first].resources > 0)
				cout << "LINE " << my_base_index << " " << ressources[i].first << " 1;";
		}
		for (int i = 0; i < number_of_cells; i++){
			if (b[i].resources > 0) {
				cout << "LINE " << my_base_index << " " << i << " 1;";
			}
		}
		cout <<  endl;
		b.clear();
    }
    //------------------------------------------------------------------------------------------------------------------------
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    // cout << "WAIT" << endl;
    // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
}