#include <mbed.h>
#include "motor.h"

/* 
 * オムニホイール4輪を制御するためのクラス．
 * motor.hをインクルードする前提．
 * メカナム4輪や，オムニ3輪も少し改造すれば簡単に実装できるはず．
 */

class Wheel
{
private:
    Motor &R, &L, &B;
    const uint32_t pow;

public:
    /* Constructor */
    Wheel(Motor &, Motor &, Motor &, uint32_t pow);

    void Brake(void);
    void Front(uint32_t PulseWidth);
    void Right(uint32_t PulseWidth);
    void Left(uint32_t PulseWidth);
    void Back(uint32_t PulseWidth);
    void FrontRight(uint32_t PulseWidth);
    void FrontLeft(uint32_t PulseWidth);
    void BackRight(uint32_t PulseWidth);
    void BackLeft(uint32_t PulseWidth);
    void RotateRight(uint32_t PulseWidth);
    void RotateLeft(uint32_t PulseWidth);
};