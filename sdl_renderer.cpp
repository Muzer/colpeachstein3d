#include "sdl_renderer.h"

namespace colpeachstein3d
{

sdl_renderer::sdl_renderer() :
  sdl{SDL_INIT_VIDEO},
  window{
    "colpeachstein3d!",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    SDL_WINDOW_SHOWN},
  renderer{window, -1, SDL_RENDERER_ACCELERATED}
{
}

void sdl_renderer::sleep(uint32_t msec)
{
  SDL_Delay(msec);
}

void sdl_renderer::draw_pixel(
    uint32_t x, uint32_t y, const colour& pixel_colour)
{
  if (pixel_colour != last_colour)
  {
    renderer.SetDrawColor(pixel_colour.r, pixel_colour.g, pixel_colour.b);
    last_colour = pixel_colour;
  }

  renderer.DrawPoint(x, y);
}

void sdl_renderer::draw_line(uint32_t x_start, uint32_t y_start, uint32_t x_end,
                             uint32_t y_end,
                             const colpeachstein3d::colour &line_colour) {
  if (line_colour != last_colour)
  {
    renderer.SetDrawColor(line_colour.r, line_colour.g, line_colour.b);
    last_colour = line_colour;
  }

  renderer.DrawLine(x_start, y_start, x_end, y_end);
}

uint32_t sdl_renderer::canvas_width()
{
  return renderer.GetOutputWidth();
}

uint32_t sdl_renderer::canvas_height()
{
  return renderer.GetOutputHeight();
}

void sdl_renderer::frame_complete()
{
  renderer.Present();
}

void sdl_renderer::frame_begin()
{
  renderer.SetDrawColor(0, 0, 0);
  last_colour = {0, 0, 0};

  renderer.Clear();
}

}
