#include "battle.h"

#include "core/players/human.h"
#include "core/players/ai.h"

Battle::Battle(QObject *parent)
    : QObject(parent),
    m_gamePlay(this),
    m_blackAiPlayer(std::make_shared<class Ai>("", this)),
    m_whiteAiPlayer(std::make_shared<class Ai>("", this)),
    m_playerBlack(nullptr),
    m_playerWhile(nullptr)
{
    connect(&m_gamePlay, &GamePlay::sigCheckerBoardChanged, this, &Battle::gamePlayCheckerBoardChangedHandler);
    connect(&m_gamePlay, &GamePlay::sigPlayerChanged, this, &Battle::gamePlayPlayerChangedHandler);
    connect(&m_gamePlay, &GamePlay::sigGameOver, this, &Battle::gamePlayGameOverHandler);
}

Battle::~Battle()
{

}

bool Battle::isBattleRunning()
{
    return m_gamePlay.isRunning();
}

Battle::PlayerColor Battle::currentPlayerColor()
{
    return m_gamePlay.getCurrentPlayerColor();
}

std::shared_ptr<VirtualPlayer> Battle::getPlayer(Battle::PlayerColor playerColor)
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
    endBattle();

    switch (blackPlayerType) {
    case Human:
        m_playerBlack = std::make_shared<class Human>(blackPlayerName, this);
        break;
    case Ai:
        m_playerBlack = m_blackAiPlayer;
        m_playerBlack->setName(blackPlayerName);
        dynamic_cast<class Ai&>(*m_playerBlack).setGame(&m_gamePlay);
        break;
    }
    switch (whitePlayerType) {
    case Human:
        m_playerWhile = std::make_shared<class Human>(whitePlayerName, this);
        break;
    case Ai:
        m_playerWhile = m_whiteAiPlayer;
        m_playerWhile->setName(whitePlayerName);
        dynamic_cast<class Ai&>(*m_playerWhile).setGame(&m_gamePlay);
        break;
    }

    // 连接信号
    connect(m_playerBlack.get(), &VirtualPlayer::sigMoved, &m_gamePlay, &GamePlay::slotMove);
    connect(m_playerWhile.get(), &VirtualPlayer::sigMoved, &m_gamePlay, &GamePlay::slotMove);

    m_gamePlay.slotStartNewGame();
    emit sigBattleStarted();
    emit sigChanged();
}

void Battle::endBattle()
{
    m_gamePlay.reset();
    emit sigChanged();
}

void Battle::slotHumanMove(GamePlay::Position position)
{
    auto playerToMove = m_gamePlay.getCurrentPlayerColor() == PlayerColor::Black ? m_playerBlack : m_playerWhile;
    if (class Human* humanPlayer = dynamic_cast<class Human*>(playerToMove.get()))
    {
        humanPlayer->slotMoveTo(position);
    }
}

void Battle::gamePlayCheckerBoardChangedHandler(GamePlay::CheckerBoard currentBoard)
{
    emit sigCheckerBoardChanged(currentBoard);
    emit sigChanged();
}

void Battle::gamePlayPlayerChangedHandler(Battle::PlayerColor playerColor)
{
    emit sigPlayerChanged(playerColor);
    emit sigChanged();
    // 通知玩家下子
    if (playerColor == PlayerColor::Black)
    {
        m_playerBlack->slotNextMove(m_gamePlay.getCheckerBoard(), playerColor);
    }
    else
    {
        m_playerWhile->slotNextMove(m_gamePlay.getCheckerBoard(), playerColor);
    }
}

void Battle::gamePlayGameOverHandler(Battle::PlayerColor winner)
{
    emit sigBattleEnded(winner);
    emit sigChanged();
}

