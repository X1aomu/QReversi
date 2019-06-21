#include "ai.h"

#include <ctime>
#include <memory>
#include <random>
#include <vector>

#include <QEventLoop>
#include <QTimer>

#include "core/gameplay.h"

Ai::~Ai()
{
}

void Ai::slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor)
{
  Q_UNUSED(game)

  if (m_game == nullptr) return;

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

  if (availPositions.empty()) return;

  std::mt19937 rng;
  rng.seed(time(nullptr));
  std::uniform_int_distribution<size_t> randomDist(0, availPositions.size() - 1);

  emit sigMoved(availPositions.at(randomDist(rng)));
}
