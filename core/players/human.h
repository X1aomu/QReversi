#ifndef HUMAN_H
#define HUMAN_H

#include "core/players/virtualplayer.h"
#include "core/gameplay.h"

#include <QObject>

/// \brief 人类玩家。
class Human : public VirtualPlayer
{
    Q_OBJECT

public:
    using VirtualPlayer::VirtualPlayer;

public slots:
    /// \brief 通知人类玩家下子。
    ///
    /// 注：人类玩家（这个类）在这个方法里不需要做下子决策，实际决策由真人决定，它只需要按真人的指示落子就可以了。
    ///
    /// 这个槽被触发后将会触发 #sigHelpMe() 信号。
    ///
    /// \param game 无实际用途。
    /// \param playerColor 无实际用途。
    void slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor) override;
    /// \brief 告诉这个这个玩家往哪里下子。
    /// \param position 下棋位置。
    void slotMoveTo(GamePlay::Position position);

signals:
    /// \brief 寻求帮助信号。
    ///
    /// 轮到人类玩家下子时，这个类自己并不知道下一步棋该怎么下，要让外界帮助它。
    void sigHelpMe();
};
#endif // HUMAN_H
