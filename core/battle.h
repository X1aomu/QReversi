#ifndef ROUND_H
#define ROUND_H

#include <memory>

#include "core/gameplay.h"
#include "core/players/virtualplayer.h"

#include <QObject>

/// \brief 对战类，代表一局游戏。
///
/// 一场对战中有黑方和白方两个玩家，玩家可以有不同的玩家类型。
///
/// 记住，在每一次的新对战中，永远是黑方先手。
class Battle : public QObject
{
    Q_OBJECT

public:
    /// \brief 下子方颜色。
    using PlayerColor = GamePlay::PlayerColor;
    /// \brief 玩家类型。
    enum PlayerType {
        Human, ///< 玩家
        Ai ///< 电脑
    };

    /// \brief 构造函数。
    explicit Battle(QObject *parent = nullptr);
    ~Battle();

    /// \brief 是否正在对战中。
    /// \return 如果正在对战则为 true。
    bool isBattleRunning();
    /// \brief 当前下子方。
    /// \return 当前下子方。
    PlayerColor currentPlayerColor();
    /// \brief 获取对战中的玩家。
    /// \param playerColor 玩家颜色，
    ///        需为 #GamePlay::Black 或 #GamePlay::White 。
    /// \return 下子方 \p playerColor 对应的玩家。如果没有对战则为 nullptr。
    std::shared_ptr<VirtualPlayer> getPlayer(PlayerColor playerColor);

    /// \brief 开始对战。
    /// \param blackPlayerType 黑方的玩家类型。
    /// \param whitePlayerType 白方的玩家类型。
    /// \param blackPlayerName 黑方的玩家名字。
    /// \param whitePlayerName 白方的玩家名字。
    void startNewBattle(PlayerType blackPlayerType, PlayerType whitePlayerType,
                        QString blackPlayerName = "Black Player", QString whitePlayerName = "White Player");
    /// \brief 结束对战。
    ///
    /// 这个函数用于中途结束对战，不会发出 sigBattleEnded() 信号。
    void endBattle();

public slots:
    /// \brief 人类玩家下子。
    ///
    /// 接受一个人类下子的请求。
    ///
    /// 注：只有当轮到人类玩家下子时，才会发生有效下子。
    ///
    /// \param position 下子位置。
    void slotHumanMove(GamePlay::Position position);

signals:
    /// \brief 状态改变信号。
    ///
    /// 当发生任何的状态改变时发出此信号。如：开始、结束、下子方改变等。
    void sigChanged();
    /// \brief 对战开始信号。
    void sigBattleStarted();
    /// \brief 对战结束信号。
    ///
    /// 这个信号在正常结束对战时发出，
    ///
    /// \param winner 胜方，平局为 Unknown。
    void sigBattleEnded(PlayerColor winner);
    /// \brief 下子玩家改变信号。
    /// \param playerColor 当前下子方。
    void sigPlayerChanged(PlayerColor playerColor);
    /// \brief 棋盘改变信号。
    ///
    /// 当棋盘发生变化时发出该信号。当开始一局游戏或发生有效下子时会发出此信号。
    ///
    /// \param currentBoard 改变后的棋盘。
    void sigCheckerBoardChanged(GamePlay::CheckerBoard currentBoard);

private:
    GamePlay m_gamePlay;
    std::shared_ptr<VirtualPlayer> m_playerBlack;
    std::shared_ptr<VirtualPlayer> m_playerWhile;

    void gamePlayCheckerBoardChangedHandler(GamePlay::CheckerBoard currentBoard);
    void gamePlayPlayerChangedHandler(PlayerColor playerColor);
    void gamePlayGameOverHandler(PlayerColor winner);
};

#endif // ROUND_H
