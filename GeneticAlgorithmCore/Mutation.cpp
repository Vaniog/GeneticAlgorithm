//
// Created by User on 01.10.2022.
//

#include "Evolution.h"

std::vector <Bot> Mutation(std::vector <Bot> bots)
{
    std::vector <Bot> new_bots;
    for (int i = 0; i < 6; i ++)
    {
        for (int j = 0; j < 8; j++)
        {
            new_bots.push_back(bots[j]);
        }
    }
    for (int i = 0; i < 2; i ++)
    {
        for (int j = 0; j < 8; j++)
        {
            Bot new_bot = bots[j];
            for (int x = 0; x < 3; x++)
            {
                new_bot.ChangeDna(rand() % 64,rand() % 71);
            }
            new_bots.push_back(new_bot);
        }
    }
    return new_bots;
}