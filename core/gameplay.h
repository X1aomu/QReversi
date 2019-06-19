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
  static const size_t kBoardRows = 8;    ///< 棋盘行数。
  static const size_t kBoardColumns = 8; ///< 棋盘列数。

  /// \brief 下子方颜色。
  enum PlayerColor
  {
    Black,  ///< 黑方
    White,  ///< 白方
    Unknown ///< 未知
  };
  /// \brief 棋盘上的位置。
  struct Position
  {
    size_t row; ///< 行
    size_t col; ///< 列
  };
  /// \brief 棋盘。
  using CheckerBoard = std::array<std::array<PlayerColor, kBoardColumns>, kBoardRows>;

  /// \brief 构造函数。
  explicit GamePlay(QObject *parent);

  /// \brief 判断一个位置能否下子。
  /// \param pos 下子位置。
  /// \return 是否可以下子。
  bool isMoveable(Position pos);

  /// \brief 获取当前棋盘。
  /// \return 当前棋盘。
  CheckerBoard getCheckerBoard();

  /// \brief 查询游戏是否正在进行中。
  /// \return 为 true 则正在进行中，为 false 则反之。
  bool isRunning();

  /// \brief 获取当前下子方。
  /// \return 当前下子方。
  PlayerColor getCurrentPlayerColor();

  /// \brief 获取最后一次的下子位置。
  /// \return 最后一次的下子位置。
  Position getLastMovePosition() { return m_lastMove; }

public slots:
  /// \brief 开始一局新游戏。
  void slotStartNewGame();
  /// \brief 下子。
  ///
  /// 注：在一个位置下子时不需要指明下子方，下子方在每一次下子时都是确定的。
  ///
  /// \param pos 下子位置。
  void slotMove(Position pos);

  /// \brief 重置。
  void reset();

signals:
  /// \brief 棋盘改变信号。
  ///
  /// 当棋盘发生变化时发出该信号。当开始一局游戏或发生有效下子时会发出此信号。
  ///
  /// \param currentBoard 改变后的棋盘。
  void sigCheckerBoardChanged(CheckerBoard currentBoard);
  /// \brief 下子方改变信号。
  /// \param playerColor 当前下子方，游戏未开始或结束时为 Unknown。
  void sigPlayerChanged(PlayerColor playerColor);
  /// \brief 游戏结束倍号。
  /// \param playerColor 胜方，平局为 Unknown。
  void sigGameOver(PlayerColor playerColor);

private:
  /// \brief 在一个位置尝试下子。
  ///
  /// 这个函数可以用来测试一个位置能否下子，它将返回假设在给定位置下子后被翻转的
  /// 对方的棋子的个数，并可以通过 \p realMove 参数来决定是否真的在棋盘上落子。
  ///
  /// \param pos 下子位置。
  /// \param playerColor 下子方的颜色。
  /// \param realMove 为 false 不实际下子，为 true 则实际下子。
  /// \return 下子方在指定位置下子后翻转对方棋子的数量。
  size_t tryMove(Position pos, PlayerColor playerColor, bool realMove);

  /// \brief 判断一方是否能下子。
  /// \param playerColor 想要下子的一方。
  /// \return 为 true 则指定的一方可以下子，为 false 则反之。
  bool playerCanMove(PlayerColor playerColor);

  PlayerColor getWinner();

private:
  CheckerBoard m_board;        ///< 目前棋盘。
  bool m_running;              ///< 游戏是否正在进行中。
  PlayerColor m_currentPlayer; ///< 目前下子玩家。
  Position m_lastMove;         ///< 最后一次的下子位置

  friend class Ai;
};

inline GamePlay::CheckerBoard GamePlay::getCheckerBoard()
{
  return m_board;
}

inline bool GamePlay::isRunning()
{
  return m_running;
}

inline GamePlay::PlayerColor GamePlay::getCurrentPlayerColor()
{
  return m_currentPlayer;
}

#endif // GAMEMODEL_H
