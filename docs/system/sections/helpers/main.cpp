#include <iostream>

float st(float x)
{
  if(x < 0.5)
    return 4.f * x * x * x;

  return 1.f - (-2.f * x + 2.f) * (-2.f * x + 2.f) * (-2.f * x + 2.f) / 2.f;
}

int main()
{
  for(float i = 0; i < 1.f; i += 0.05)
  {
    std::cout << '(' << i - 0.5 << ", " << st(i) << ") -- ";
  }
}
