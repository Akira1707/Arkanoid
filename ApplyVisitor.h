#pragma once
#include "BonusVisitor.h"

class ApplyVisitor : public BonusVisitor{
public:
    void visit(BonusChangePaddle & bonus, Paddle & sPaddle, Ball & sBall) override;
    void visit(BonusChangeSpeed& bonus, Paddle& sPaddle, Ball& sBall) override;
    void visit(BonusChangeAdhesion& bonus, Paddle& sPaddle, Ball& sBall) override;
    void visit(BonusFilmyPaddle& bonus, Paddle& sPaddle, Ball& sBall) override;
    void visit(BonusChangeTrajectory& bonus, Paddle& sPaddle, Ball& sBall) override;
};
