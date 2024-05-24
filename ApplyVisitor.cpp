#include "ApplyVisitor.h"
#include "BonusChangePaddle.h"
#include "BonusChangeSpeed.h"
#include "BonusChangeAdhesion.h"
#include "BonusFilmyPaddle.h"
#include "BonusChangeTrajectory.h"

void ApplyVisitor::visit(BonusChangePaddle& bonus, Paddle& sPaddle, Ball& sBall) {
    bonus.Apply(sPaddle, sBall);
}

void ApplyVisitor::visit(BonusChangeSpeed& bonus, Paddle& sPaddle, Ball& sBall) {
    bonus.Apply(sPaddle, sBall);
}

void ApplyVisitor::visit(BonusChangeAdhesion& bonus, Paddle& sPaddle, Ball& sBall) {
    bonus.Apply(sPaddle, sBall);
}

void ApplyVisitor::visit(BonusFilmyPaddle& bonus, Paddle& sPaddle, Ball& sBall) {
    bonus.Apply(sPaddle, sBall);
}

void ApplyVisitor::visit(BonusChangeTrajectory& bonus, Paddle& sPaddle, Ball& sBall) {
    bonus.Apply(sPaddle, sBall);
}
