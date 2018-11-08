#include "checkerboardwidget.h"

#include "ui/checkerboard/boardlayout.h"
#include "ui/checkerboard/boardgird.h"
#include "core/gameplay.h"

CheckerBoardWidget::CheckerBoardWidget(QWidget *parent)
    : QWidget(parent)
{
    BoardLayout *layout = new BoardLayout(this);
    for (int row = 0; row < GamePlay::kBoardRows; ++row)
    {
        for (int col = 0; col < GamePlay::kBoardColumns; ++col)
        {
            layout->addWidget(new BoardGird({row, col}), row, col);
        }
    }

    setLayout(layout);
}

void CheckerBoardWidget::setCheckerBoard(const GamePlay::CheckerBoard &board)
{

}
