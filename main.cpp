#include "sdl_renderer.h"
#include "sdl_input.h"
#include "map_data.h"
#include "map_renderer.h"

#include <thread>

int main()
{
  colpeachstein3d::sdl_renderer foo;
  colpeachstein3d::sdl_input inp;

  map::map m1;

  m1.cells.push_back({});
  m1.location.insert({{0,0}, 0});
  m1.location.insert({{1,0}, 0});
  m1.location.insert({{2,0}, 0});

  m1.location.insert({{0,1}, 0});
  m1.location.insert({{2,1}, 0});

  m1.location.insert({{0,2}, 0});
  m1.location.insert({{1,2}, 0});
  m1.location.insert({{2,2}, 0});

  for (uint32_t i = 0; i < foo.canvas_width(); i++)
  {
    for (uint32_t j = 0; j < foo.canvas_height(); j++)
    {
      inp.poll();
      if (inp.quit())
          return 0;

      foo.frame_begin();

      foo.draw_pixel(i, j, {0, 0, 255});
      map::render_map(m1, 50, 50, foo);

      foo.frame_complete();
    }
  }

}
