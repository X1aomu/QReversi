#ifndef CHECKERBOARDWIDGET_H
#define CHECKERBOARDWIDGET_H

#include "core/gameplay.h"

#include <QObject>
#include <QWidget>

/// \brief 棋盘显示控件。
///
/// 这个界面控件用来显示棋盘。
class CheckerBoardWidget : public QWidget
{
    Q_OBJECT

public:
    /// \brief 构造函数。
    explicit CheckerBoardWidget(QWidget *parent = nullptr);

    /// \brief 设置棋盘。
    ///
    /// 这个函数用来设置棋盘控件上显示的棋盘。
    ///
    /// \param board 棋盘。
    void setCheckerBoard(const GamePlay::CheckerBoard& board);

signals:
    /// \brief 发出下子信号。
    /// \param position 下子位置。
    void sigMoved(GamePlay::Position position);
};

#endif // CHECKERBOARDWIDGET_H
