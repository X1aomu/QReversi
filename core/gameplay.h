#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>

#include <array>


/// \brief 黑白棋游戏玩法类，定义了游戏核心的对外接口。
///
/// 这个类定义了游戏角色、棋盘、棋盘位置和玩法。
///
/// 通过该类可以进行创建一局新游戏，在棋盘上下子等操作。
///
/// 每一次下子后会发出下子方改变信号（发生一方连续下子时可能并没有实际改变）。
/// 游戏结束时会发出游戏结束信号。
///
/// 根据黑白棋规则，每局新游戏都是黑方先下。
class GamePlay : public QObject
{
    Q_OBJECT

public:
    static const int kBoardRows = 8; ///< 棋盘行数。
    static const int kBoardColumns = 8; ///< 棋盘列数。

    /// \brief 下子方颜色。
    enum PlayerColor {
        Black, ///< 黑方
        White, ///< 白方
        Unknown ///< 未知
    };
    /// \brief 棋盘上的位置。
    struct Position {
        int row; ///< 行
        int col; ///< 列
    };
    /// \brief 棋盘。
    using CheckerBoard = std::array<std::array<PlayerColor, kBoardColumns>, kBoardRows>;

    /// \brief 构造函数。
    explicit GamePlay(QObject *parent);

    /// \brief 判断一个位置能否下子。
    /// \param position 下子位置。
    /// \return 是否可以下子。
    bool isMoveable(Position position) const;
    /// \brief 获取当前棋盘。
    /// \return 当前棋盘。
    CheckerBoard getCheckerBoard() const;
    /// \brief 获取当前下子方。
    /// \return 当前下子方。
    PlayerColor getCurrentPlayerColor() const;

public slots:
    /// \brief 开始一局新游戏。
    void slotStartNewGame();
    /// \brief 下子。
    ///
    /// 注：在一个位置下子时不需要指明下子方，下子方在每一次下子时都是确定的。
    ///
    /// \param position 下子位置。
    void slotMove(Position position);

signals:
    /// \brief 棋盘改变信号。
    ///
    /// 当棋盘发生变化时发出该信号。当开始一局游戏或发生有效下子时会发出此信号。
    ///
    /// \param currentBoard 改变后的棋盘。
    void sigCheckerBoardChanged(CheckerBoard *currentBoard);
    /// \brief 下子方改变信号。
    /// \param playerColor 当前下子方，游戏未开始或结束时为 Unknown。
    void sigPlayerChanged(PlayerColor playerColor);
    /// \brief 游戏结束倍号。
    /// \param playerColor 胜方，平局为 Unknown。
    void sigGameOver(PlayerColor playerColor);
};

#endif // GAMEMODEL_H
