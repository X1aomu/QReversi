#ifndef PIECEGIRD_H
#define PIECEGIRD_H

#include "core/gameplay.h"

#include <QPushButton>

/// \brief 棋盘格子。
///
/// 每个棋盘格子都有它的位置和归属方（黑、白或未知），
/// 点击一个棋盘格子可以在它所处的位置下子。
class BoardGrid : public QPushButton
{
    Q_OBJECT

public:
    /// \brief 构造函数。
    /// \param position 该格子的位置。
    /// \param stoneColor 该格子上的棋子颜色。
    /// \param parent 父控件
    BoardGrid(GamePlay::Position position, GamePlay::PlayerColor stoneColor = GamePlay::PlayerColor::Unknown, QWidget *parent = nullptr);
    ~BoardGrid();

    /// \brief 更改格子上的棋子颜色。
    /// \param stoneColor 棋子颜色。
    void setStoneColor(GamePlay::PlayerColor stoneColor);

public slots:
    /// \brief 点击格子被触发的事件。
    void slotOnClicked();

signals:
    /// \brief 发出下子信号。
    /// \param position 下子位置。
    void sigMoved(GamePlay::Position position);

private:
    GamePlay::Position m_position;
    GamePlay::PlayerColor m_color;
};

#endif // PIECEGIRD_H
