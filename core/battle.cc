#include "battle.h"

#include "core/players/human.h"
#include "core/players/ai.h"

Battle::Battle(QObject *parent)
    : QObject(parent),
    m_gamePlay(this),
    m_playerBlack(nullptr),
    m_playerWhile(nullptr)
{
    connect(&m_gamePlay, &GamePlay::sigCheckerBoardChanged, this, &Battle::gamePlayCheckerBoardChangedHandler);
    connect(&m_gamePlay, &GamePlay::sigPlayerChanged, this, &Battle::gamePlayPlayerChangedHandler);
    connect(&m_gamePlay, &GamePlay::sigGameOver, this, &Battle::gamePlayGameOverHandler);
}

Battle::~Battle()
{
    cleanup();
}

bool Battle::isBattleRunning()
{
    return m_gamePlay.isRunning();
}

Battle::PlayerColor Battle::currentPlayerColor()
{
    return m_gamePlay.getCurrentPlayerColor();
}

VirtualPlayer *Battle::getPlayer(Battle::PlayerColor playerColor)
{
    if (playerColor == PlayerColor::Black)
    {
        return m_playerBlack;
    }
    if (playerColor == PlayerColor::White)
    {
        return m_playerWhile;
    }
    return nullptr;
}

void Battle::startNewBattle(Battle::PlayerType blackPlayerType, Battle::PlayerType whitePlayerType, QString blackPlayerName, QString whitePlayerName)
{
    cleanup();

    switch (blackPlayerType) {
    case Human:
        m_playerBlack = new class Human(blackPlayerName, this);
        break;
    case Ai:
        m_playerBlack = new class Ai(blackPlayerName, this);
        break;
    }
    switch (whitePlayerType) {
    case Human:
        m_playerWhile = new class Human(whitePlayerName, this);
        break;
    case Ai:
        m_playerWhile = new class Ai(whitePlayerName, this);
        break;
    }

    // 连接信号
    connect(m_playerBlack, &VirtualPlayer::sigMoved, &m_gamePlay, &GamePlay::slotMove);
    connect(m_playerWhile, &VirtualPlayer::sigMoved, &m_gamePlay, &GamePlay::slotMove);

    m_gamePlay.slotStartNewGame();
    emit sigBattleStarted();
}

void Battle::endBattle()
{
    cleanup();
    emit sigChanged();
}

void Battle::slotHumanMove(GamePlay::Position position)
{
    VirtualPlayer* playerToMove = m_gamePlay.getCurrentPlayerColor() == PlayerColor::Black ? m_playerBlack : m_playerWhile;
    if (class Human* humanPlayer = dynamic_cast<class Human*>(playerToMove))
    {
        humanPlayer->slotMoveTo(position);
    }
}

void Battle::cleanup()
{
    delete m_playerBlack;
    delete m_playerWhile;
    m_playerBlack = nullptr;
    m_playerWhile = nullptr;
}

void Battle::gamePlayCheckerBoardChangedHandler(GamePlay::CheckerBoard currentBoard)
{
    emit sigCheckerBoardChanged(currentBoard);
    emit sigChanged();
}

void Battle::gamePlayPlayerChangedHandler(Battle::PlayerColor playerColor)
{
    // 通知玩家下子
    if (playerColor == PlayerColor::Black)
    {
        m_playerBlack->slotNextMove(m_gamePlay.getCheckerBoard(), playerColor);
    }
    else
    {
        m_playerWhile->slotNextMove(m_gamePlay.getCheckerBoard(), playerColor);
    }
    emit sigPlayerChanged(playerColor);
    emit sigChanged();
}

void Battle::gamePlayGameOverHandler(Battle::PlayerColor winner)
{
    emit sigBattleEnded(winner);
    emit sigChanged();
}

