//
// Created by User on 01.10.2022.
//

#ifndef GENETICALGORITHM_SCENE_H
#define GENETICALGORITHM_SCENE_H

#endif //GENETICALGORITHM_SCENE_H

#include "Bot.h"

#include <iostream>


class Scene{
 private:
  std::vector <std::pair<int,int>> posision;
 public:
    std::vector <Bot> losers;
    std::vector <Bot> bots;
    std::vector<std::vector<Objects>> table;
  Scene(std::vector <Bot> given_bots): bots(given_bots), losers(std::vector<Bot>()){
    for (int i = 0; i < 66; i++)
    {
      table.push_back(std::vector<Objects>());
      for (int j = 0; j < 66; j++)
      {
        table[i].push_back(Objects());
      }
    }
    for (int i = 0; i < 66; i++)
    {
      for (int j = 0; j < 66; j++)
      {
        table[i][j] = Objects();
      }
    }
    for (int i = 0; i < 66; i++)
    {
      table[i][0] = Objects(ObjectsType::Wall);
      table[i][65] = Objects(ObjectsType::Wall);
      table[0][i] = Objects(ObjectsType::Wall);
      table[65][i] = Objects(ObjectsType::Wall);
    }
    for (int i = 1; i < 65; i++)
    {
      int y = 1 + rand() % 64;
      table[i][y] = Objects(i);
      posision.push_back(std::make_pair(i,y));
    }
    for (int i = 0; i < 66; i++)
    {
      for (int j = 0; j < 66; j ++)
      {
        if ((rand() % 1000) < 225)
        {
          if (table[i][j].GetType() == ObjectsType::Empty)
          {
            table[i][j] = Objects(ObjectsType::Food);
          }
        }
      }
    }
    for (int i = 0; i < 66; i++)
    {
      for (int j = 0; j < 66; j ++)
      {
        if ((rand() % 1000) < 75)
        {
          if (table[i][j].GetType() == ObjectsType::Empty)
          {
            table[i][j] = Objects(ObjectsType::Poison);
          }
        }
      }
    }
    for (int i = 0; i < 66; i++)
    {
      for (int j = 0; j < 66; j ++)
      {
        if ((rand() % 1000) < 105)
        {
          if (table[i][j].GetType() == ObjectsType::Empty)
          {
            table[i][j] = Objects(ObjectsType::Wall);
          }
        }
      }
    }
  }
  void Iteration() {
    for (int i = 0; i < 64; i++)
    {
      //std::cout << "Hi" << std::endl;
      if (posision[i] != std::make_pair(-1,-1)) {
        bots[i].iter(i,table,bots,losers,posision);
      }
    }
  }
  std::vector<Bot> GetWinners() {
    std::vector<Bot> score[100];
    std::vector<Bot> winners;
    for (int i = 0; i < 64; i++) {
      if (posision[i] != std::make_pair(-1,-1)) {
        score[bots[i].health].push_back(bots[i]);
      }
    }
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < score[i].size(); j++) {
        losers.push_back(score[i][j]);
      }
    }
    for (int i = 0; i <= 8; i++) {
        winners.push_back(losers[63 - i]);
        winners[i].health = 99;
    }
    return winners;
  }
};