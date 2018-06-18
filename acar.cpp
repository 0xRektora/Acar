#include "acar.h"

Acar::Acar() {

}

Acar::Acar(Point pos, Point dest, Direction dir) {
  this->pos = pos;
  this->dest = dest;
  this->dir = dir;

  Motor.begin(I2C_ADDRESS);
  pinMode(this->signalPincr, INPUT);
  pinMode(this->signalPincl, INPUT);
  pinMode(this->signalPinR, INPUT);
  pinMode(this->signalPinL, INPUT);// initialize the digital pin as an output:
  pinMode(3, INPUT);


  Serial.begin(9600);  // initialize serial communications at 9600 bps:
  this->initPoints();
}


void Acar::goTo() {
  while (this->pos.x != this->dest.x && this->pos.y != this->dest.y) {
    this->getNextDest();
    Serial.print(this->pos.x);
    Serial.print(" ");
    Serial.print(this->pos.y);
    Serial.println("");
  }

}



void Acar::getNextDest() {
  boolean isOnPoint = digitalRead(this->signalPinR) + digitalRead(this->signalPinL);
  // Check si on dois monter
  if (this->dest.y - this->pos.y >= 0 && isOnPoint == HIGH) {
    this->turnUp();
    this->avancer();
    while (true) {
      if (digitalRead(this->signalPinR) == HIGH || digitalRead(this->signalPinL) == HIGH) {
        this->addPosY(true);
        break;
      }
    }


  }
  //Check si on dois u descendre
  else if (this->dest.y - this->pos.y <= 0 && isOnPoint == HIGH) {
    this->turnDown();
    this->avancer();

    while (true) {
      if (digitalRead(this->signalPinR) == HIGH || digitalRead(this->signalPinL) == HIGH) {
        this->addPosY(false);
        break;
      }
    }


  }

  isOnPoint = digitalRead(this->signalPinR) + digitalRead(this->signalPinL);
  //Check si on dois tourner à droite
  if (this->dest.x - this->pos.x >= 0 && isOnPoint == HIGH) {
    this->turnRight();
    this->avancer();

    while (true) {
      if (digitalRead(this->signalPinR) == HIGH || digitalRead(this->signalPinL) == HIGH) {
        this->addPosX(false);
        break;
      }
    }



  }
  //Check si on dois tourner à gauche
  else if (this->dest.x - this->pos.x <= 0 && isOnPoint == HIGH) {
    this->turnLeft();
    this->avancer();

    while (true) {
      if (digitalRead(this->signalPinR) == HIGH || digitalRead(this->signalPinL) == HIGH) {
        this->addPosX(true);
        break;
      }
    }
  }

}

void Acar::initPoints() {
  for (int i = 25; i >= 0; i--)
    this->points[i] = Point{ -1, -1, -1};

  this->points[0] = {1, 4, 0};
  this->points[1] = {2, 4, 1};
  this->points[2] = {3, 4, 2};
  this->points[3] = {4, 4, 3};
  this->points[4] = {5, 4, 4};
  this->points[5] = {6, 3, 0};
  this->points[6] = {7, 3, 1};
  this->points[7] = {8, 3, 2};
  this->points[10] = {9, 2, 0};
  this->points[13] = {10, 2, 3};
  this->points[14] = {11, 2, 4};
  this->points[17] = {12, 1, 2};
  this->points[18] = {13, 1, 3};
  this->points[20] = {14, 0, 0};
  this->points[22] = {15, 0, 2};
  this->points[24] = {16, 0, 4};
}

void Acar::turnUp() {
  while (this->dir != Direction::up) {
    this->tourner_gauche();
  }
}

void Acar::turnDown() {
  while (this->dir != Direction::down) {
    this->tourner_gauche();
  }
}

void Acar::turnRight() {
  while (this->dir != Direction::right) {
    this->tourner_droite();
  }
}

void Acar::turnLeft() {
  while (this->dir != Direction::left) {
    this->tourner_gauche();
  }
}


void Acar::changeDirection(Direction dir) {
  switch (this->dir) {
    case Direction::left:
      if (dir == Direction::left) {
        this->dir = Direction::down;
      }
      else {
        this->dir = Direction::up;
      }
      break;
    case Direction::down:
      if (dir == Direction::left) {
        this->dir = Direction::left;
      }
      else {
        this->dir = Direction::right;
      }
      break;
    case Direction::up:
      if (dir == Direction::left) {
        this->dir = Direction::left;
      }
      else {
        this->dir = Direction::right;
      }
      break;
    case Direction::right:

      if (dir == Direction::left) {
        this->dir = Direction::up;
      }
      else {
        this->dir = Direction::down;
      }
      break;
    default:
      break;
  }
}

void Acar::addPosX(boolean left) {
  if (left) {
    if ( this->pos.y == 4 && (this->pos.x == 0 || this->pos.x == 1 || this->pos.x == 2 || this->pos.x == 3 || this->pos.x == 4) ) {
      this->pos.x--;
    }
    else if (this->pos.y == 3 && (this->pos.x == 0 || this->pos.x == 1 || this->pos.x == 2) ) {
      this->pos.x--;
    }
    else if (this->pos.y == 2 && (this->pos.x == 3) ) {
      this->pos.x -= 3;
    }
    else if (this->pos.y == 2 && (this->pos.x == 4) ) {
      this->pos.x--;
    }
    else if (this->pos.y == 1 && (this->pos.x == 3) ) {
      this->pos.x--;
    }
    else if (this->pos.y == 0 && (this->pos.x == 2 || this->pos.x == 4)) {
      this->pos.x -= 2;
    }
  }
  else {
    if ( this->pos.y == 4 ) {
      this->pos.x++;
    }
    else if (this->pos.y == 3 && (this->pos.x == 0 || this->pos.x == 1) ) {
      this->pos.x++;
    }
    else if (this->pos.y == 2 && (this->pos.x == 0) ) {
      this->pos.x += 3;
    }
    else if (this->pos.y == 2 && (this->pos.x == 3) ) {
      this->pos.x++;
    }
    else if (this->pos.y == 1 && (this->pos.x == 2) ) {
      this->pos.x++;
    }
    else if (this->pos.y == 0 && (this->pos.x == 0 || this->pos.x == 2)) {
      this->pos.x += 2;
    }
  }

}

void Acar::addPosY(boolean up) {
  if (up) {
    if (this->pos.x == 0 && (this->pos.y == 0) ) {
      this->pos.y += 2;
    }
    else if (this->pos.x == 0 && (this->pos.y == 2 || this->pos.y == 3) ) {
      this->pos.y++;
    }
    else if (this->pos.x == 1 && (this->pos.y == 3) ) {
      this->pos.y++;
    }
    else if (this->pos.x == 2 && (this->pos.y == 0 || this->pos.y == 3)) {
      this->pos.y++;
    }
    else if (this->pos.x == 3 && (this->pos.y == 1) ) {
      this->pos.y++;
    }
    else if (this->pos.x == 3 && (this->pos.y == 2) ) {
      this->pos.y += 2;
    }
    else if (this->pos.x == 4 && (this->pos.y == 0  || this->pos.y == 2) ) {
      this->pos.y += 2;
    }
  }
  else {
    if (this->pos.x == 0 && (this->pos.y == 4 || this->pos.y == 3) ) {
      this->pos.y--;
    }
    else if (this->pos.x == 0 && (this->pos.y == 2) ) {
      this->pos.y -= 2;
    }
    else if (this->pos.x == 1 && (this->pos.y == 4) ) {
      this->pos.y--;
    }
    else if (this->pos.x == 2 && (this->pos.y == 4 || this->pos.y == 1)) {
      this->pos.y--;
    }
    else if (this->pos.x == 3 && (this->pos.y == 2) ) {
      this->pos.y--;
    }
    else if (this->pos.x == 3 && (this->pos.y == 4) ) {
      this->pos.y -= 2;
    }
    else if (this->pos.x == 4 && (this->pos.y == 4  || this->pos.y == 2) ) {
      this->pos.y -= 2;
    }
  }

}


void Acar::avancer() {
  boolean l = digitalRead(this->signalPinL);
  boolean cl = digitalRead(this->signalPincl);
  boolean cr = digitalRead(this->signalPincr);
  boolean r = digitalRead(this->signalPinR);


  if (LOW == l && LOW == cl && HIGH == cr && LOW == r) {
    correction_lente_droite();
  }
  if (LOW == l && HIGH == cl && LOW == cr && LOW == r) {
    correction_lente_gauche();
  }

  if (LOW == l && LOW == cl && LOW == cr && HIGH == r) {
    correction_rapide_droite();
  }
  if (HIGH == l && LOW == cl && LOW == cr && HIGH == r) {
    correction_rapide_gauche();
  }

  if (LOW == l && LOW == cl && LOW == cr && LOW == r)
  {
    tout_droit();
  }

  delay(50);       // wait for a second

}

void Acar::tourner_gauche() {
  this->changeDirection(Direction::left);
  Motor.stop(MOTOR2);
  Motor.stop(MOTOR1);
  delay(500);
  Motor.stop(MOTOR1);
  Motor.speed(MOTOR2, 100);
  delay(800);

}
void Acar::tourner_droite() {
  this->changeDirection(Direction::right);
  Motor.stop(MOTOR2);
  Motor.stop(MOTOR1);
  delay(500);
  Motor.stop(MOTOR2);
  Motor.speed(MOTOR1, 100);
  delay(800);
}
void Acar::correction_lente_droite() {
  Motor.speed(MOTOR1, 60);
  Motor.speed(MOTOR2, -60);
}
void Acar::correction_lente_gauche() {
  Motor.speed(MOTOR1, -60);
  Motor.speed(MOTOR2, 60);
}

void Acar::correction_rapide_gauche() {
  Motor.stop(MOTOR1);
  Motor.speed(MOTOR2, 100);
}

void Acar::correction_rapide_droite() {
  Motor.stop(MOTOR2);
  Motor.speed(MOTOR1, 100);
}

void Acar::tout_droit() {
  Motor.speed(MOTOR1, 50);
  Motor.speed(MOTOR2, 50);



}





