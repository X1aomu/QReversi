#include "ai.h"

#include <ctime>
#include <vector>
#include <random>
#include <memory>

#include <QTimer>
#include <QEventLoop>

#include "core/gameplay.h"

Ai::~Ai()
{
    // 善后，让本对象析构之前所有的 slotNextMove 执行完毕
    std::lock_guard<std::mutex> lock(m_processing);
}

void Ai::slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor)
{
    Q_UNUSED(game);
    m_processing.lock();

    if (m_game == nullptr)
    {
        m_processing.unlock();
        return;
    }

    // 设置延时，同时不失去主进程的响应
    QTimer t;
    QEventLoop eventLoop;
    t.setSingleShot(true);
    t.setTimerType(Qt::PreciseTimer);
    connect(&t, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    t.start(1000);
    eventLoop.exec();

    std::vector<GamePlay::Position> availPositions;
    for (size_t row = 0; row != GamePlay::kBoardRows; ++row)
    {
        for (size_t col = 0; col != GamePlay::kBoardColumns; ++col)
        {
            if (m_game->tryMove({row, col}, playerColor, false) > 0)
            {
                availPositions.push_back({row, col});
            }
        }
    }

    if (availPositions.empty())
    {
        m_processing.unlock();
        return;
    }

    std::mt19937 rng;
    rng.seed(time(nullptr));
    std::uniform_int_distribution<size_t> randomDist(0, availPositions.size() - 1);

    m_processing.unlock();

    emit sigMoved(availPositions.at(randomDist(rng)));
}
