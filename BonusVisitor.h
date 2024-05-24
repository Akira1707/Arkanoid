#pragma once

#include "Paddle.h"
#include "Ball.h"

class BonusChangePaddle;
class BonusChangeSpeed;
class BonusChangeAdhesion;
class BonusFilmyPaddle;
class BonusChangeTrajectory;

class BonusVisitor {
public:
    virtual ~BonusVisitor() = default;

    virtual void visit(BonusChangePaddle& bonus, Paddle& sPaddle, Ball& sBall) = 0;
    virtual void visit(BonusChangeSpeed& bonus, Paddle& sPaddle, Ball& sBall) = 0;
    virtual void visit(BonusChangeAdhesion& bonus, Paddle& sPaddle, Ball& sBall) = 0;
    virtual void visit(BonusFilmyPaddle& bonus, Paddle& sPaddle, Ball& sBall) = 0;
    virtual void visit(BonusChangeTrajectory& bonus, Paddle& sPaddle, Ball& sBall) = 0;
};





