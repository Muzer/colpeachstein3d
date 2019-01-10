#ifndef COLOUR_H
#define COLOUR_H

namespace colpeachstein3d
{

struct colour 
{
  uint8_t r, g, b;

  friend bool operator==(const colour& lhs, const colour& rhs)
  {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
  }

  friend bool operator!=(const colour& lhs, const colour& rhs)
  {
    return !(lhs == rhs);
  }
};

}

#endif // COLOUR_H
