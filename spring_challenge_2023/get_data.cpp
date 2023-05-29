#include "header.h"

int check_neigh_lock_0(irc a, crc b, int i, vector<int> *beacons, int last_move, int spawn_index ,bool (*checker)(crc, int, int))
{
    int tmp;

    if (a[i].neigh_1 != -1)
    {
        (*beacons).push_back(a[i].neigh_1);
        a[i].neigh_1 = -1;
        if (checker(b, a[i].neigh_1, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_1 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_1, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_2 != -1)
    {
        (*beacons).push_back(a[i].neigh_2);
        a[i].neigh_2 = -1;
        if (checker(b, a[i].neigh_2, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_2 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_2, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_3 != -1)
    {
        (*beacons).push_back(a[i].neigh_3);
        a[i].neigh_3 = -1;
        if (checker(b, a[i].neigh_3, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_3 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_3, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
         }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_4 != -1)
    {
        (*beacons).push_back(a[i].neigh_4);
        a[i].neigh_4 = -1;
        if (checker(b, a[i].neigh_4, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_4 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_4, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_5 != -1)
    {
        (*beacons).push_back(a[i].neigh_5);
        a[i].neigh_5 = -1;
        if (checker(b, a[i].neigh_5, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_5 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_5, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    return (0);
}





int check_neigh_lock_1(irc a, crc b, int i, vector<int> *beacons, int last_move, int spawn_index ,bool (*checker)(crc, int, int))
{
    int tmp;

  if (a[i].neigh_0 != -1)
    {
        (*beacons).push_back(a[i].neigh_0); // add beacon neighbor to beacons list
        a[i].neigh_0 = -1;
        if (checker(b, a[i].neigh_0, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_0 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_0, beacons, i, spawn_index, checker); // check neighbor neighbors if got ressources
            if (!tmp)
                (*beacons).pop_back(); // if no ressources remove the becon from the list
            else
                return (1); // else if their is ressources keep the neighbor in the list
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_2 != -1)
    {
        (*beacons).push_back(a[i].neigh_2);
        a[i].neigh_2 = -1;
        if (checker(b, a[i].neigh_2, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_2 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_2, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_3 != -1)
    {
        (*beacons).push_back(a[i].neigh_3);
        a[i].neigh_3 = -1;
        if (checker(b, a[i].neigh_3, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_3 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_3, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
         }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_4 != -1)
    {
        (*beacons).push_back(a[i].neigh_4);
        a[i].neigh_4 = -1;
        if (checker(b, a[i].neigh_4, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_4 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_4, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_5 != -1)
    {
        (*beacons).push_back(a[i].neigh_5);
        a[i].neigh_5 = -1;
        if (checker(b, a[i].neigh_5, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_5 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_5, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    return (0);
}





int check_neigh_lock_0(irc a, crc b, int i, vector<int> *beacons, int last_move, int spawn_index ,bool (*checker)(crc, int, int))
{
    int tmp;

  if (a[i].neigh_0 != -1)
    {
        (*beacons).push_back(a[i].neigh_0); // add beacon neighbor to beacons list
        a[i].neigh_0 = -1;
        if (checker(b, a[i].neigh_0, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_0 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_0, beacons, i, spawn_index, checker); // check neighbor neighbors if got ressources
            if (!tmp)
                (*beacons).pop_back(); // if no ressources remove the becon from the list
            else
                return (1); // else if their is ressources keep the neighbor in the list
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_1 != -1)
    {
        (*beacons).push_back(a[i].neigh_1);
        a[i].neigh_1 = -1;
        if (checker(b, a[i].neigh_1, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_1 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_1, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_2 != -1)
    {
        (*beacons).push_back(a[i].neigh_2);
        a[i].neigh_2 = -1;
        if (checker(b, a[i].neigh_2, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_2 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_2, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_3 != -1)
    {
        (*beacons).push_back(a[i].neigh_3);
        a[i].neigh_3 = -1;
        if (checker(b, a[i].neigh_3, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_3 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_3, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
         }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_4 != -1)
    {
        (*beacons).push_back(a[i].neigh_4);
        a[i].neigh_4 = -1;
        if (checker(b, a[i].neigh_4, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_4 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_4, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_5 != -1)
    {
        (*beacons).push_back(a[i].neigh_5);
        a[i].neigh_5 = -1;
        if (checker(b, a[i].neigh_5, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_5 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_5, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    return (0);
}





int check_neigh_lock_0(irc a, crc b, int i, vector<int> *beacons, int last_move, int spawn_index ,bool (*checker)(crc, int, int))
{
    int tmp;

  if (a[i].neigh_0 != -1)
    {
        (*beacons).push_back(a[i].neigh_0); // add beacon neighbor to beacons list
        a[i].neigh_0 = -1;
        if (checker(b, a[i].neigh_0, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_0 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_0, beacons, i, spawn_index, checker); // check neighbor neighbors if got ressources
            if (!tmp)
                (*beacons).pop_back(); // if no ressources remove the becon from the list
            else
                return (1); // else if their is ressources keep the neighbor in the list
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_1 != -1)
    {
        (*beacons).push_back(a[i].neigh_1);
        a[i].neigh_1 = -1;
        if (checker(b, a[i].neigh_1, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_1 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_1, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_2 != -1)
    {
        (*beacons).push_back(a[i].neigh_2);
        a[i].neigh_2 = -1;
        if (checker(b, a[i].neigh_2, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_2 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_2, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_3 != -1)
    {
        (*beacons).push_back(a[i].neigh_3);
        a[i].neigh_3 = -1;
        if (checker(b, a[i].neigh_3, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_3 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_3, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
         }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_4 != -1)
    {
        (*beacons).push_back(a[i].neigh_4);
        a[i].neigh_4 = -1;
        if (checker(b, a[i].neigh_4, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_4 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_4, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_5 != -1)
    {
        (*beacons).push_back(a[i].neigh_5);
        a[i].neigh_5 = -1;
        if (checker(b, a[i].neigh_5, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_5 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_5, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    return (0);
}





int check_neigh_lock_0(irc a, crc b, int i, vector<int> *beacons, int last_move, int spawn_index ,bool (*checker)(crc, int, int))
{
    int tmp;

  if (a[i].neigh_0 != -1)
    {
        (*beacons).push_back(a[i].neigh_0); // add beacon neighbor to beacons list
        a[i].neigh_0 = -1;
        if (checker(b, a[i].neigh_0, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_0 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_0, beacons, i, spawn_index, checker); // check neighbor neighbors if got ressources
            if (!tmp)
                (*beacons).pop_back(); // if no ressources remove the becon from the list
            else
                return (1); // else if their is ressources keep the neighbor in the list
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_1 != -1)
    {
        (*beacons).push_back(a[i].neigh_1);
        a[i].neigh_1 = -1;
        if (checker(b, a[i].neigh_1, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_1 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_1, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_2 != -1)
    {
        (*beacons).push_back(a[i].neigh_2);
        a[i].neigh_2 = -1;
        if (checker(b, a[i].neigh_2, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_2 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_2, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_3 != -1)
    {
        (*beacons).push_back(a[i].neigh_3);
        a[i].neigh_3 = -1;
        if (checker(b, a[i].neigh_3, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_3 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_3, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
         }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_4 != -1)
    {
        (*beacons).push_back(a[i].neigh_4);
        a[i].neigh_4 = -1;
        if (checker(b, a[i].neigh_4, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_4 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_4, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    if (a[i].neigh_5 != -1)
    {
        (*beacons).push_back(a[i].neigh_5);
        a[i].neigh_5 = -1;
        if (checker(b, a[i].neigh_5, spawn_index)) // if this neighbor contain ressources keep it in the list
            return (1);
        if (a[i].neigh_5 != last_move) // check if this neighbor index is allready called wich it will be saved in logs (last one discluded)
        {
            tmp = check_neigh(a, b, a[i].neigh_5, beacons, i, spawn_index, checker);
            if (!tmp)
                (*beacons).pop_back(); 
            else
                return (1);
        }
        else
            (*beacons).pop_back(); // if neighbor allready called remove it from the list and dont call it
    }
    return (0);
}





