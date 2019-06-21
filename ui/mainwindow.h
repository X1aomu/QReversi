#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core/battle.h"
#include "core/gameplay.h"
#include "core/players/virtualplayer.h"
#include "ui/checkerboard/checkerboardwidget.h"
#include "ui/newgamedialog.h"

#include <QMainWindow>

/// \brief 主窗体。
///
/// 程序主窗体，初始化和放置用户界面控件。
///
/// 主窗体是连接其他组件的桥梁。
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  /// \brief 以交互方式开始一个新游戏。
  ///
  /// 这个函数将弹出一个对话框，让用户选择游戏设置以开始新游戏。
  void startNewGame();
  /// \brief 以交互方式结束当前游戏。
  ///
  /// 这个函数将弹出一个对话框，询问用户是否结束游戏。
  void stopGame();
  /// \brief 游戏结束后显示胜方信息。
  ///
  /// 这个函数弹出一个对话框并显示出胜利方，其中包含一些必要的信息，比如胜者的昵称等。
  void showWinnerInfo(GamePlay::PlayerColor winner);
  /// \brief 更新状态栏。
  void battleChangedHandler();

private:
  // 游戏
  Battle *m_battle;
  // 棋盘
  CheckerBoardWidget *m_checkerBoardWidget;
  // 菜单栏组件
  QMenu *m_gameMenu;
  QAction *m_startGame;
  QAction *m_stopGame;
  QAction *m_exitGame;

  NewGameDialog *m_newGameDialog;

  void initMenuBar();
  void initSignalsAndSlots();
};

#endif // MAINWINDOW_H
