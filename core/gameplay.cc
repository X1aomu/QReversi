#include "gameplay.h"

GamePlay::GamePlay(QObject *parent)
    : QObject(parent)
{
    reset();
}

bool GamePlay::isMoveable(GamePlay::Position pos)
{
    if (tryMove(pos, m_currentPlayer, false) > 0)
    {
        return true;
    }
    return false;
}

void GamePlay::slotStartNewGame()
{
    reset();
    m_running = true;
    m_currentPlayer = Black;
    emit sigCheckerBoardChanged(m_board);
    emit sigPlayerChanged(m_currentPlayer);
}

void GamePlay::slotMove(GamePlay::Position pos)
{
    if (!m_running) return;
    if (m_currentPlayer == Unknown) return;
    if (tryMove(pos, m_currentPlayer, true) > 0)
    {
        emit sigCheckerBoardChanged(m_board);
        // 判断下子方有没有改变
        PlayerColor nextPlayer = (m_currentPlayer == Black) ? White : Black;
        if (playerCanMove(nextPlayer))
        {
            m_currentPlayer = nextPlayer;
            emit sigPlayerChanged(m_currentPlayer);
            return;
        }
        if (!playerCanMove(nextPlayer) && playerCanMove(m_currentPlayer))
        {
            emit sigPlayerChanged(m_currentPlayer);
            return;
        }
        if (!playerCanMove(nextPlayer) && !playerCanMove(m_currentPlayer))
        {
            // 没有玩家能够继续下子了，游戏结束，发送信号。
            PlayerColor winner = getWinner();
            emit sigGameOver(winner);
            m_running = false;
            return;
        }
    }
}

size_t GamePlay::tryMove(GamePlay::Position pos, PlayerColor playerColor, bool realMove)
{
    std::array<std::array<int, 2>, 8> directions =
    {
        {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
            {0, 1},   {1, -1}, {1, 0},  {1, 1}
        }
    }; // 八个方向

    if (pos.row >= kBoardRows || pos.col >= kBoardColumns)
        return 0;
    if (m_board[pos.row][pos.col] != Unknown)
        return 0;

    PlayerColor self = playerColor;
    PlayerColor opponent = self == Black ? White : Black;

    size_t count = 0;

    // 遍历 8 个方向，看能否吃到对方的棋子
    for (std::array<int, 2> direction : directions)
    {
        size_t row = pos.row;
        size_t col = pos.col;
        // 按方向延伸
        row += direction[0];
        col += direction[1];
        size_t steps = 1; // 延伸的步数
        while (row < kBoardRows && col < kBoardColumns && m_board[row][col] == opponent)
        {
            row += direction[0];
            col += direction[1];
            ++steps;
        }
        // 已经到延伸的端点了

        if (steps < 2)
            continue; // 步数小于 2，中间没有对方棋子

        // 看在端点的是不是自己的棋子
        if (row < kBoardRows && col < kBoardColumns && m_board[row][col] == self)
        {
            row -= direction[0];
            col -= direction[1];
            --steps;
            // 反向延伸以翻转中间的对方的棋子
            while (steps != 0)
            {
                if (realMove)
                {
                    m_board[row][col] = self; // 翻转棋子
                }
                row -= direction[0];
                col -= direction[1];
                --steps;
                ++count; // 翻转对方的棋子数加一
            }
        }
    }

    if (count > 0 && realMove) // fuck: 这个realMove小心一定要加上
    {
        m_board[pos.row][pos.col] = self;
    }

    return count;
}

bool GamePlay::playerCanMove(GamePlay::PlayerColor playerColor)
{
    for (size_t row = 0; row != kBoardRows; ++row)
    {
        for (size_t col = 0; col != kBoardColumns; ++col)
        {
            if (tryMove({row, col}, playerColor, false) > 0)
            {
                return true;
            }
        }
    }
    return false;
}

GamePlay::PlayerColor GamePlay::getWinner()
{
    size_t numOfBlack = 0;
    size_t numOfWhite = 0;
    for (const auto& row : m_board)
    {
        for (const auto& playerColor : row)
        {
            if (playerColor == Black)
            {
                ++numOfBlack;
            }
            if (playerColor == White)
            {
                ++numOfWhite;
            }
        }
    }

    if (numOfBlack > numOfWhite)
        return Black;
    else if (numOfBlack < numOfWhite)
        return White;
    else
        return Unknown;
}

void GamePlay::reset()
{
    for(size_t i = 0; i < kBoardRows; i++)
    {
        for(size_t j = 0; j < kBoardColumns; j++)
        {
            m_board[i][j] = Unknown;
        }
    }
    m_board[3][3] = m_board[4][4] = White;
    m_board[3][4] = m_board[4][3] = Black;
    m_running = false;
    m_currentPlayer = Unknown;
    emit sigCheckerBoardChanged(m_board);
}
