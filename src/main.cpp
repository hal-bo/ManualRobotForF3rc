#include <mbed.h>
#include "motor.h"
#include "wheel.h"
#include "controller.h"

InterruptIn UB(USER_BUTTON);
DigitalOut led(LED2);
Serial pc(USBTX, USBRX); 

CAN can1(PA_11, PA_12, 500000);
Controller controller(can1, 0x334);

PwmOut PWM_R(PA_8);
PwmOut PWM_L(PA_0);
PwmOut PWM_B(PA_6);
PwmOut PWM_A(PB_6);

PwmOut SR(PB_7);
PwmOut SL(PA_15);

DigitalOut PHASE_R(PC_11);
DigitalOut PHASE_L(PD_2);
DigitalOut PHASE_B(PC_9);
DigitalOut PHASE_A(PB_9);

Motor R(PWM_R, PHASE_R, 100, true);
Motor L(PWM_L, PHASE_L, 100, true);
Motor B(PWM_B, PHASE_B, 100, true);
Motor A(PWM_A, PHASE_A, 100, true);

Wheel Whe(R,L,B,100);


int DEFAULT_SPEAD = 100;
int servo_diff = 0;
bool button_RB = false;
bool button_LB = false;
int speed = DEFAULT_SPEAD;
char ch;

void Joystick(int8_t x, int8_t y,int8_t rx, int8_t ay){
    y=-y;
    ay=-ay;

    pc.printf("******************JoyStick %d %d **************************\r\n",x,y);
    if(y>30){
        if(x>30){
            pc.printf("FrontRight\n");
            Whe.FrontRight(speed);
        }else if(x<-30){
            pc.printf("FrontLeft\n");
            Whe.FrontLeft(speed);
        }else{
            pc.printf("Front\n");
            Whe.Front(speed);
        }
    }
     if(y<-30){
        if(x>30){
             pc.printf("BackRight\n");
             Whe.BackRight(speed);
        }else if(x<-30){
             pc.printf("BackLeft\n");
             Whe.BackLeft(speed);
        }else{
             pc.printf("Back\n");
             Whe.Back(speed);
        }
    }
    if((-30<=y)==(y<=30)){
        if(x>30){
            pc.printf("Right\n");
            Whe.Right(speed);
        }else if(x<-30){
            pc.printf("Left\n");
            Whe.Left(speed);
        }else{
            pc.printf("Brake\n");
            Whe.Brake();
        }
    }
    if(rx>30){
        pc.printf("RotateRight\n");
        Whe.RotateRight(speed);
    }else if(rx<-30){
        pc.printf("RotateLeft\n");
        Whe.RotateLeft(speed);
    }
    if(ay>30){
        pc.printf("ArmUp\n");
        A.CW(20);
    }else if(ay<-30){
        pc.printf("ArmDown\n");
        A.CCW(20);
    }
}

//**Buttons**// x, a, b, y, lb, rb, lt, rt, back, start, / / ↑, ↓, ←, → //**Buttons**//
void Button(std::vector<bool> buttons){
    //X ボタン
    if(buttons[0] == 1){
        pc.printf("X\r\n");//閉じたとき
        SR.pulsewidth_us(1000 + servo_diff);
        SL.pulsewidth_us(1500 - servo_diff);
    }
    //B ボタン
    if(buttons[2] == 1){
        pc.printf("B\r\n");//開いたとき
        SR.pulsewidth_us(1500);
        SL.pulsewidth_us(1000);
    }
    //Y ボタン
    if(buttons[3] == 1){
        pc.printf("Y\r\n");
        speed = DEFAULT_SPEAD * 2; //加速
    }else{
        speed = DEFAULT_SPEAD;
    }
    //LB ボタン
    if(buttons[4]){
        if(!button_LB){
            button_LB = true;
            servo_diff = servo_diff - 25; //アームの閉まり具合を強くする
        }
    }else{
        button_LB = false;
    }
    //RB ボタン
    if(buttons[5]){
        if(!button_RB){
            button_RB = true;
            servo_diff = servo_diff + 25; //アームの閉まり具合を弱くする
        }
    }else{
        button_RB = false;
    }
}


int main()
{
  led = 1;
  SR.period_ms(20);
  SL.period_ms(20);
  while(1)
  {
    
    //pc.printf("Axes: %4d %4d %4d %4d ", controller.axes.x, controller.axes.y, controller.axes.z, controller.axes.rz);
    
    for (std::vector<bool>::iterator i = controller.buttons.begin(); i != controller.buttons.end(); i++)
    {
        pc.putc(*i ? '1' : '0');
    }
    Joystick(controller.axes.x, controller.axes.y, controller.axes.z, controller.axes.rz);
    Button(controller.buttons);
    if(pc.readable()){
            pc.printf("#");
            ch = pc.getc();
            if(ch == 'w'){
                pc.printf("front\r\n");
                Joystick(0, -1*speed, 0, 0);
            }else if(ch == 'd'){
                pc.printf("right\r\n");
                Joystick(speed, 0, 0, 0);
            }else if(ch == 's'){
                pc.printf("back\r\n");
                Joystick(0, speed, 0, 0);
            }else if(ch == 'a'){
                pc.printf("left\r\n");
                Joystick(-1*speed, 0, 0, 0);
            }else if(ch == 'g'){
                pc.printf("rotateleft\r\n");
                Joystick(0, 0, -1*speed, 0);
            }else if(ch == 'h'){
                pc.printf("rotateright\r\n");
                Joystick(0, 0, speed, 0);
            }else if(ch == 'i'){
                pc.printf("armup\r\n");
                Joystick(0, 0, 0, -1*speed);
            }else if(ch == 'k'){
                pc.printf("armdown\r\n");
                Joystick(0, 0, 0, speed);
            }else if(ch == 'l'){
                pc.printf("armopen\r\n");
                SR.pulsewidth_us(1500);
                SL.pulsewidth_us(1000);
            }else if(ch == 'j'){
                pc.printf("armclose\r\n");
                SR.pulsewidth_us(1000 + servo_diff);
                SL.pulsewidth_us(1500 - servo_diff);
            }
            //pc.printf("%c\r\n",ch);
        }

    
    wait(0.0166);
    }
}