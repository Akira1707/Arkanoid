#pragma once
#include "Bonus.h"

class BonusChangePaddle;
class BonusChangeSpeed;
class BonusChangeAdhesion;
class BonusFilmyPaddle;
class BonusChangeTrajectory;

class BonusVisitor {
public:
    void visit(BonusChangePaddle& bonus, Paddle& sPaddle, Ball& sBall);
    void visit(BonusChangeSpeed& bonus, Paddle& sPaddle, Ball& sBall);
    void visit(BonusChangeAdhesion& bonus, Paddle& sPaddle, Ball& sBall);
    void visit(BonusFilmyPaddle& bonus, Paddle& sPaddle, Ball& sBall);
    void visit(BonusChangeTrajectory& bonus, Paddle& sPaddle, Ball& sBall);
};



