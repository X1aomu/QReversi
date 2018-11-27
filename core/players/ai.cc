#include "ai.h"

#include <ctime>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

#include "core/gameplay.h"

#include <QtDebug>


void Ai::slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor)
{
    Q_UNUSED(game);
    if (m_game == nullptr)
        return;

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

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
        return;

    std::random_device r;
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<size_t> randomDist(0, availPositions.size() - 1);

    emit sigMoved(availPositions.at(randomDist(randomEngine)));
}
