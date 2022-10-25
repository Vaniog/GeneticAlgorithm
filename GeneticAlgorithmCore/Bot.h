//
// Created by User on 01.10.2022.
//

#ifndef GENETICALGORITHM_BOT_H
#define GENETICALGORITHM_BOT_H

#endif //GENETICALGORITHM_BOT_H

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
  int GetDna(int i)
  {
    return dna[i];
  }
  void iter(int pos, std::vector<std::vector<Objects>>& table, std::vector <Bot>& bots, std::vector <Bot>& losers,std::vector <std::pair<int,int>>& posision)
  {
    if (health == 1) {
      losers.push_back(bots[pos]);
      table[posision[pos].first][posision[pos].second] = Objects(ObjectsType::Poison);
      posision[pos] = std::make_pair(-1,-1);
    }
    else {
      if (dna[iterator] == 0) {
        std::pair<int,int> new_posision = posision[pos];
        //std::cout << "Hi2" << new_posision.first << " " << new_posision.second << std::endl;
        switch (direction) {
          case(0):
            new_posision.first--;
            break;
          case(1):
            new_posision.second++;
            break;
          case(2):
            new_posision.first++;
            break;
          case(3):
            new_posision.second--;
            break;
        }
        //std::cout << "Hi2" << new_posision.first << " " << new_posision.second << std::endl;
        switch (table[new_posision.first][new_posision.second].GetType()) {
          case(ObjectsType::Empty):
            table[posision[pos].first][posision[pos].second] = Objects(ObjectsType::Empty);
            posision[pos] = new_posision;
            table[posision[pos].first][posision[pos].second] = Objects(pos);
            health--;
            break;
          case(ObjectsType::Wall):
            health--;
            break;
          case(ObjectsType::Poison):
            losers.push_back(bots[pos]);
            table[posision[pos].first][posision[pos].second] = Objects(ObjectsType::Poison);
            posision[pos] = std::make_pair(-1,-1);
            break;
          case(ObjectsType::Food):
            table[posision[pos].first][posision[pos].second] = Objects(ObjectsType::Empty);
            posision[pos] = new_posision;
            table[posision[pos].first][posision[pos].second] = Objects(pos);
            health= min(health + 11,99);
            break;
          case (ObjectsType::Bot):
            health--;
            break;
        }
        iterator = (iterator + 1) % 64;
      } else if ((1 <= dna[iterator]) && (dna[iterator] <= 4)) {
        direction = (direction + (dna[iterator] - 1)) % 4;
        iterator = (iterator + 1) % 64;
        health--;
      } else if (dna[iterator] == 5) {
        std::pair<int,int> new_posision = posision[pos];
        switch (direction) {
          case(0):
            new_posision.first--;
            break;
          case(1):
            new_posision.second++;
            break;
          case(2):
            new_posision.first++;
            break;
          case(3):
            new_posision.second--;
        }
        switch (table[new_posision.first][new_posision.second].GetType()) {
          case(ObjectsType::Empty):
            iterator = (iterator + 1) % 64;
            break;
          case(ObjectsType::Wall):
            iterator = (iterator + 2) % 64;
            break;
          case(ObjectsType::Poison):
            iterator = (iterator + 3) % 64;
            break;
          case(ObjectsType::Food):
            iterator = (iterator + 4) % 64;
            break;
          case (ObjectsType::Bot):
            iterator = (iterator + 5) % 64;
            break;
        }
        health--;
      } else if (dna[iterator] == 6) {
        std::pair<int,int> new_posision = posision[pos];
        switch (direction) {
          case(0):
            new_posision.first--;
            break;
          case(1):
            new_posision.second++;
            break;
          case(2):
            new_posision.first++;
            break;
          case(3):
            new_posision.second--;
            break;
        }
        switch (table[new_posision.first][new_posision.second].GetType()) {
          case(ObjectsType::Poison):
            table[new_posision.first][new_posision.second] = Objects(ObjectsType::Food);
            break;
          default:
            break;
        }
        health--;
      } else if (7 <= dna[iterator] && dna[iterator] <= 70) {
        iterator = (iterator + dna[iterator] - 6) % 64;
        health--;
      } else {
        dna[iterator] = dna[iterator] % 70;
      }
    }
  }
};