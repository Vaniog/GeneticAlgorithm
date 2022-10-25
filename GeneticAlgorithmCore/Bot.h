//
// Created by User on 01.10.2022.
//

#ifndef GENETICALGORITHM_BOT_H
#define GENETICALGORITHM_BOT_H

#endif //GENETICALGORITHM_BOT_H

#include <utility>
#include <vector>
#include <random>

int min(int a,int b);

enum class ObjectsType { Empty, Wall, Food, Poison, Bot};

class Objects {
 private:
  ObjectsType o_type;
 public:
    int bot;
  ObjectsType GetType() {
    return o_type;
  }
  Objects(): o_type(ObjectsType::Empty), bot(-1) {}
  Objects(ObjectsType ob_type): o_type(ob_type), bot(-1) {}
  Objects(int bot): o_type(ObjectsType::Bot), bot(bot) {}
};

class Bot{
 private:
  int dna[64];
  int iterator;
  int direction;
 public:
  int health;
  Bot(const int given_dna[]): iterator(0), health(99), direction(rand() % 4){
    for(int i = 0; i < 64; i ++)
    {
      dna[i] = given_dna[i];
    }
  }
  Bot(const Bot& bot): iterator(0), health(99), direction(rand() % 4) {
    for (int i = 0; i < 64; i++)
    {
      dna[i] = bot.dna[i];
    }
  }
  void ChangeDna(int where,int on_what)
  {
    dna[where] = on_what;
  }
  int GetDna(int i) const
  {
    return dna[i];
  }
  std::pair<int,int> NewPosision(std::pair<int,int> pos) const;
  void iter(int pos, std::vector<std::vector<Objects>>& table, std::vector <Bot>& bots, std::vector <Bot>& losers,std::vector <std::pair<int,int>>& posision);
};