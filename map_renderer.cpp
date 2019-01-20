//
// Created by PeachJames on 12/01/2019.
//

#include "map_renderer.h"

static const colpeachstein3d::colour map_colours[] = {{255, 100, 0},
                                                      {255, 255, 255}};
static const size_t                  border_col    = 0;
static const size_t                  cell_col      = 1;

struct map_render_context {
    colpeachstein3d::sdl_renderer& renderer;

    // Screen space position / size of map
    int x, y;
    int w{300};
    int h{200};

    // Map translation
    float x_map{2.0};
    float y_map{1.0};
    float scale{5.0};

    map_render_context(const map_render_context&)            = delete;
    map_render_context& operator=(const map_render_context&) = delete;
};

void linear_clip(float& i, int min, int max)
{
    if(i < min) i = min;
    if(i > max) i = max;
}

void ctx_render_line(float               x1,
                     float               y1,
                     float               x2,
                     float               y2,
                     int                 map_col,
                     map_render_context& ctx)
{
    const auto& map_colour = map_colours[map_col];

    {
        // entire line is off screen?
        if (x1 < 0 && x2 < 0 || y1 < 0 && y2 < 0) return;
        if (x1 > ctx.w && x2 > ctx.w || y1 > ctx.h && y2 > ctx.h) return;
    }
    {
        // clipping, assuming we have a vertical/horizontal line
        linear_clip(x1, 0, ctx.w);
        linear_clip(x2, 0, ctx.w);
        linear_clip(y1, 0, ctx.h);
        linear_clip(y2, 0, ctx.h);
    }

    // Screen space translation:
    const auto ux1 = static_cast<uint32_t>(x1 + ctx.x);
    const auto ux2 = static_cast<uint32_t>(x2 + ctx.x);
    const auto uy1 = static_cast<uint32_t>(y1 + ctx.y);
    const auto uy2 = static_cast<uint32_t>(y2 + ctx.y);

    ctx.renderer.draw_line(ux1, uy1, ux2, uy2, map_colour);
}

void render_border(map_render_context& ctx)
{
    ctx_render_line(0, 0, ctx.w, 0, 0, ctx);      // TL -> TR
    ctx_render_line(0, 0, 0, ctx.h, 0, ctx);      // TL -> BL
    ctx_render_line(0, ctx.h, ctx.w, ctx.h, 0, ctx);  // BL -> BR
    ctx_render_line(ctx.w, 0, ctx.w, ctx.h, 0, ctx);  // TR -> BR
}

void render_cell(int x, int y, const map::cell& cell, map_render_context& ctx)
{
    const float size     = ((1 << 3)) * ctx.scale;
    const float x_offset = ((x << 3) + ctx.x_map) * ctx.scale;
    const float y_offset = ((y << 3) + ctx.y_map) * ctx.scale;

    // clang-format off
    ctx_render_line(x_offset, y_offset, x_offset + size, y_offset, cell_col, ctx);      // TL -> TR
    ctx_render_line(x_offset, y_offset, x_offset, y_offset + size, cell_col, ctx);      // TL -> BL
    ctx_render_line(x_offset, y_offset + size, x_offset + size, y_offset + size, cell_col, ctx);  // BL -> BR
    ctx_render_line(x_offset + size, y_offset, x_offset + size, y_offset + size, cell_col, ctx);  // TR -> BR

    // inside
    const float size2    = (1 << 2) * ctx.scale;
    const float c_offset = (1 << 2) * ctx.scale/2.0;

    ctx_render_line(c_offset + x_offset, c_offset +  y_offset, c_offset + x_offset + size2, c_offset + y_offset, cell_col, ctx);      // TL -> TR
    ctx_render_line(c_offset + x_offset, c_offset + y_offset, c_offset + x_offset, c_offset + y_offset + size2, cell_col, ctx);      // TL -> BL
    ctx_render_line(c_offset + x_offset, c_offset + y_offset + size2, c_offset + x_offset + size2, c_offset + y_offset + size2, cell_col, ctx);  // BL -> BR
    ctx_render_line(c_offset + x_offset + size2, c_offset + y_offset, c_offset + x_offset + size2, c_offset + y_offset + size2, cell_col, ctx);  // TR -> BR

    // clang-format on
}

bool cell_visible(int x, int y, map_render_context& ctx)
{
    // Clever?
    return true;
}
void map::render_map(const map&                     map,
                     int                            x,
                     int                            y,
                     colpeachstein3d::sdl_renderer& renderer)
{
    map_render_context ctx{renderer, x, y};

    for (auto it : map.location) {
        if (!cell_visible(it.first.first, it.first.second, ctx))
            continue;

        render_cell(
            it.first.first, it.first.second, map.cells[it.second], ctx);
    }

    render_border(ctx);
}
