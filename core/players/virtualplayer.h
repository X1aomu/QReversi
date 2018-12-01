#ifndef REALPLAYER_H
#define REALPLAYER_H

#include "core/gameplay.h"

#include <QObject>

/// \brief 虚拟玩家。
///
/// 这个类表示一个抽象的玩家，包含了一个玩家的基本操作。
/// 这是一个纯虚类，子类必须实现下棋决策的方法。
///
/// 例子：该类的子类可以是一个人类玩家、电脑玩家或网络上的玩家等。
class VirtualPlayer : public QObject
{
    Q_OBJECT

public:
    /// \brief 构造函数。
    /// \param name 名字。
    /// \param parent 父控件。
    explicit VirtualPlayer(QString name, QObject *parent = nullptr);

    /// \brief 获取名字。
    /// \return 玩家的名字。
    QString getName() { return m_name; }

public slots:
    /// \brief 通知玩家下子。
    ///
    /// 在这里实现下棋决策。
    ///
    /// \param game 当前游戏中的棋盘。
    /// \param playerColor 玩家的颜色。
    virtual void slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor) = 0;

signals:
    /// \brief 完成下子信号。
    /// \param position 下子位置。
    void sigMoved(GamePlay::Position position);

private:
    QString m_name;
};

#endif // REALPLAYER_H
