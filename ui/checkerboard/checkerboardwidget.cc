#include "checkerboardwidget.h"

#include "core/gameplay.h"
#include "ui/checkerboard/boardgrid.h"
#include "ui/checkerboard/boardlayout.h"

CheckerBoardWidget::CheckerBoardWidget(QWidget *parent) : QWidget(parent)
{
  for (size_t row = 0; row != GamePlay::kBoardRows; ++row)
  {
    for (size_t col = 0; col != GamePlay::kBoardColumns; ++col)
    {
      BoardGrid *grid = new BoardGrid({row, col});
      // 连接信号
      connect(grid, &BoardGrid::sigMoved, this, &CheckerBoardWidget::sigMoved);
      m_grids[row][col] = grid;
    }
  }
  BoardLayout *layout = new BoardLayout(this);
  for (size_t row = 0; row != GamePlay::kBoardRows; ++row)
  {
    for (size_t col = 0; col != GamePlay::kBoardColumns; ++col)
    {
      layout->addWidget(m_grids[row][col], row, col);
    }
  }

  setLayout(layout);
}

void CheckerBoardWidget::setCheckerBoard(const GamePlay::CheckerBoard &board)
{
  for (size_t row = 0; row < GamePlay::kBoardRows; ++row)
  {
    for (size_t col = 0; col < GamePlay::kBoardColumns; ++col)
    {
      m_grids[row][col]->setStoneColor(board[row][col]);
    }
  }
}
