//
// Created by PeachJames on 12/01/2019.
//

#ifndef COLPEACHSTEIN3D_MAP_RENDERER_H
#define COLPEACHSTEIN3D_MAP_RENDERER_H

#include "sdl_renderer.h"
#include "map_data.h"

namespace map {
    void render_map(const map& map, int x, int y, colpeachstein3d::sdl_renderer& renderer);
};

#endif //COLPEACHSTEIN3D_MAP_RENDERER_H
