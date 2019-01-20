//
// Created by PeachJames on 12/01/2019.
//

#ifndef COLPEACHSTEIN3D_MAP_DATA_H
#define COLPEACHSTEIN3D_MAP_DATA_H

#include "colour.h"

#include <vector>
#include <unordered_map>
#include <cstddef>

namespace map {
  struct cell {
      colpeachstein3d::colour col;
  };

  struct pair_hash {
     size_t operator()(const std::pair<int, int>& p) const {
       return static_cast<size_t>(p.first ^ p.second);
     }
  };

  struct map {
      std::vector<cell> cells;

      std::unordered_map<std::pair<int, int>, size_t, pair_hash> location; // indexes into cells;
  };
};

#endif //COLPEACHSTEIN3D_MAP_DATA_H
