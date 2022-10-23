//
// Created by User on 23.10.2022.
//

#include "Bot.h"

std::pair<int,int> Bot::NewPosision(std::pair<int,int> pos) const{
  std::pair<int,int> new_posision = pos;
  switch (direction) {
    case (0):new_posision.first--;
      break;
    case (1):new_posision.second++;
      break;
    case (2):new_posision.first++;
      break;
    case (3):new_posision.second--;
      break;
  }
  return new_posision;
}

void Bot::iter(int pos, std::vector<std::vector<Objects>>& table, std::vector <Bot>& bots, std::vector <Bot>& losers,std::vector <std::pair<int,int>>& posision)
{
  if (health == 1) {
    losers.push_back(bots[pos]);
    table[posision[pos].first][posision[pos].second] = Objects(ObjectsType::Poison);
    posision[pos] = std::make_pair(-1,-1);
  }
  else {
    if (dna[iterator] == 0) {
      std::pair<int,int> new_posision = NewPosision(posision[pos]);
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
      std::pair<int,int> new_posision = NewPosision(posision[pos]);
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
      std::pair<int,int> new_posision = NewPosision(posision[pos]);
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