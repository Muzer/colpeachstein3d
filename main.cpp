#include "sdl_renderer.h"

#include <thread>

int main()
{
  colpeachstein3d::sdl_renderer foo;

  for (uint32_t i = 0; i < foo.canvas_width(); i++)
  {
    for (uint32_t j = 0; j < foo.canvas_height(); j++)
    {
      foo.frame_begin();

      foo.draw_pixel(i, j, {0, 0, 255});

      foo.frame_complete();
    }
  }

}
