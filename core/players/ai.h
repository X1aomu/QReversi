#ifndef AI_H
#define AI_H

#include "core/players/virtualplayer.h"

#include <QObject>

/// \brief 电脑玩家。
class Ai : public VirtualPlayer
{
    Q_OBJECT

public:
    using VirtualPlayer::VirtualPlayer;

public slots:
    /// \brief 通知电脑玩家下子。
    ///
    /// 电脑玩家在这里实现下下一步棋的决策。
    ///
    /// \param game 当前游戏中的棋盘。
    /// \param playerColor 玩家的颜色。
    void slotNextMove(const GamePlay::CheckerBoard &game, GamePlay::PlayerColor playerColor) override;
};

#endif // AI_H
