
#include "sdl_input.h"

#include <SDL2pp/SDL2pp.hh>


namespace colpeachstein3d {
void sdl_input::poll()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          this->_quit=true;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
              case SDLK_ESCAPE:
              case SDLK_q:
                this->_quit = true;
            }
        }
    }
}

bool sdl_input::quit()
{
    return _quit;
}
};
