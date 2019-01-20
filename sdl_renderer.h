#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <cstdint>

#include <SDL2pp/SDL2pp.hh>

#include "colour.h"

namespace colpeachstein3d
{

class sdl_renderer
{
public:
  sdl_renderer();
  sdl_renderer(const sdl_renderer&) = delete;
  sdl_renderer(sdl_renderer&&) = default;
  sdl_renderer& operator=(const sdl_renderer&) = delete;
  sdl_renderer& operator=(sdl_renderer&&) = default;

  uint32_t canvas_width();
    // Returns the width of the drawing canvas
  uint32_t canvas_height();
    // Returns the height of the drawing canvas
  void draw_line(
      uint32_t x, uint32_t y_start, uint32_t y_end, const colour &line_colour);
    // Draws a line in column x starting at y_start and ending at y_end-1, of
    // the specified colour
  void draw_line(
            uint32_t x_start, uint32_t y_start, uint32_t x_end, uint32_t y_end, const colour &line_colour);
    // Draws a line starting at (x_start, y_start) and ending at (x_end,y_end), of
    // the specified colour
  void draw_rectangle(
      uint32_t x_start,
      uint32_t y_start,
      uint32_t x_end,
      uint32_t y_end,
      const colour &line_colour);
    // Draws a rectangle with upper-left coords (x_start, y_start) and
    // lower-right coords (x_end-1, y_end-1), of the specified colour
  void draw_pixel(uint32_t x, uint32_t y, const colour &pixel_colour);
    // Draws a pixel in the specified colour.
  void frame_complete();
    // Signal that frame rendering has finished and the buffers may be swapped
  void frame_begin();
    // Start rendering a new frame
  void sleep(uint32_t msec);
    // Tell the renderer to sleep

private:
  SDL2pp::SDL sdl;
  SDL2pp::Window window;
  SDL2pp::Renderer renderer;
  colour last_colour;
};

}

#endif // SDL_RENDERER_H
