//
// Created by User on 01.10.2022.
//
#include <fstream>
#include "Evolution.h"


void Evolution(std::string old_generetion_file_name, std::string new_generetion_file_name, int number_of_battles)
{
    std::ifstream file(old_generetion_file_name, std::ios::in);
    std::vector<Bot> bots;
    for (int j = 0; j < 64; j++)
    {
        int arr[64];
        for (int i = 0; i < 64; i++)
        {
            file>>arr[i];
        }
        bots.push_back(Bot(arr));
    }
    for (int i = 0; i < number_of_battles;i++)
    {
        bots = Battle(bots);
        bots = Mutation(bots);
    }
    std::ofstream out_file(new_generetion_file_name, std::ios::in);
    for (int j = 0; j < 64; j++)
    {
        for (int i = 0; i < 64; i++)
        {
            out_file << bots[j].GetDna(i) << " ";
        }
        out_file << "/n";
    }
}