#pragma once

namespace colpeachstein3d {
  class sdl_input {
    public:
      void poll();
      bool quit();
    private:
      bool _quit{false};
  };
}
