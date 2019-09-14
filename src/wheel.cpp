#include "wheel.h"

Wheel::Wheel(Motor &_R, Motor &_L, Motor &_B,  uint32_t _pow) : R(_R), L(_L), B(_B), pow(_pow)
{
}

void Wheel::Brake(void)
{
    R.Brake();
    L.Brake();
    B.Brake();

}

void Wheel::Front(uint32_t pulsewidth)
{
    R.CCW(pulsewidth);
    L.CW(pulsewidth);
    B.Brake();

}

void Wheel::FrontRight(uint32_t pulsewidth)
{
    R.Brake();
    L.CW(pulsewidth);
    B.CCW(pulsewidth);

}

void Wheel::FrontLeft(uint32_t pulsewidth)
{
    R.CCW(pulsewidth);
    L.Brake();
    B.CW(pulsewidth);

}

void Wheel::Right(uint32_t pulsewidth)
{
    R.CW(pulsewidth/2);
    L.CW(pulsewidth/2);
    B.CCW(pulsewidth);

}

void Wheel::Left(uint32_t pulsewidth)//mis
{
    R.CCW(pulsewidth/2);
    L.CCW(pulsewidth/2);
    B.CW(pulsewidth);

}

void Wheel::BackRight(uint32_t pulsewidth)
{
    R.CW(pulsewidth);
    L.Brake();
    B.CCW(pulsewidth);

}

void Wheel::BackLeft(uint32_t pulsewidth)
{
    R.Brake();
    L.CCW(pulsewidth);
    B.CW(pulsewidth);

}

void Wheel::Back(uint32_t pulsewidth)
{
    R.CW(pulsewidth);
    L.CCW(pulsewidth);
    B.Brake();

}

void Wheel::RotateRight(uint32_t pulsewidth)
{
    R.CW(pulsewidth);
    L.CW(pulsewidth);
    B.CW(pulsewidth);

}

void Wheel::RotateLeft(uint32_t pulsewidth)
{
    R.CCW(pulsewidth);
    L.CCW(pulsewidth);
    B.CCW(pulsewidth);

}

