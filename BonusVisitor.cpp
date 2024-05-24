#include "BonusVisitor.h"

void BonusVisitor::visit(BonusChangePaddle& bonus, Paddle& sPaddle, Ball& sBall) {
	bonus.Apply(sPaddle, sBall);	
}
void BonusVisitor::visit(BonusChangeSpeed& bonus, Paddle& sPaddle, Ball& sBall) {
	bonus.Apply(sPaddle, sBall);
}

void BonusVisitor::visit(BonusChangeAdhesion& bonus, Paddle& sPaddle, Ball& sBall) {
	bonus.Apply(sPaddle, sBall);
}

void BonusVisitor::visit(BonusFilmyPaddle& bonus, Paddle& sPaddle, Ball& sBall) {
	bonus.Apply(sPaddle, sBall);
}

void BonusVisitor::visit(BonusChangeTrajectory& bonus, Paddle& sPaddle, Ball& sBall) {
	bonus.Apply(sPaddle, sBall);
}
