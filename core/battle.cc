#include "battle.h"

Battle::Battle(QObject *parent)
    : QObject(parent)
{

}

bool Battle::isBattleRunning()
{

}

Battle::PlayerColor Battle::currentPlayer()
{

}

VirtualPlayer *Battle::getPlayer(Battle::PlayerColor playerColor)
{

}

void Battle::startNewBattle(Battle::PlayerType blackPlayerType, Battle::PlayerType whitePlayerType, QString blackPlayerName, QString whitePlayerName)
{

}

void Battle::endBattle()
{

}

void Battle::slotHumanMove(GamePlay::Position position)
{

}

