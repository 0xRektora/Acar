#include <Arduino.h>
#include <Grove_I2C_Motor_Driver.h>

#ifndef ACAR_H
#define ACAR_H

// default I2C address is 0x0f
#define I2C_ADDRESS 0x0f

enum Direction { left, right, up, down };
struct Point{
  short num;
  int y;
  int x;
};


class Acar {
    Direction dir;
    Point pos;
    Point dest;

    Point points[25];

    int  signalPincr =  4;
    int signalPincl =  2;
    int signalPinR =  8;
    int signalPinL =  6;
    boolean detect_point = false;


  public:
    Acar();
    Acar(Point pos, Point dest, Direction dir);
    void avancer();
    void goTo();
    void tourner_droite();
    void tourner_gauche();
    void tout_droit();
    void correction_lente_droite();
    void correction_lente_gauche();
    void correction_rapide_gauche();
    void correction_rapide_droite();
    void changeDirection(Direction dir);
    void getNextDest();
    void initPoints();
    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();
    void addPosX(boolean left);
    void addPosY(boolean up);
};

#endif
