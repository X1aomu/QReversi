#include "human.h"

void Human::slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor)
{
  Q_UNUSED(game);
  Q_UNUSED(playerColor);
  emit sigHelpMe();
}

void Human::slotMoveTo(GamePlay::Position position)
{
  emit sigMoved(position);
}
