#include "Grove_I2C_Motor_Driver.h"
#include "acar.h"


Acar mycar;


void setup()   {
mycar = Acar(Point{1, 0, 0}, Point{13, 2, 3}, right);
mycar.initPoints();


}

void loop()
{
  mycar.goTo();

}

