#include <iostream>

float st(float t)
{
  return t * t * (3 - 2 * t);
}

int main()
{
  for(float i = 0; i < 1.f; i += 0.05)
  {
    std::cout << '(' << i - 0.5 << ", " << st(i) << ") -- ";
  }
}
