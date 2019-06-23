#include "mainwindow.h"

#include "ui/checkerboard/checkerboardwidget.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent),
    m_battle(new Battle(this)),
    m_checkerBoardWidget(new CheckerBoardWidget(this)),
    m_gameMenu(menuBar()->addMenu("游戏")),
    m_startGame(new QAction("开始新游戏", this)),
    m_startNetworkGame(new QAction("开始网络游戏", this)),
    m_stopGame(new QAction("结束游戏", this)),
    m_exitGame(new QAction("退出", this)),
    m_newGameDialog(new NewGameDialog(this)),
    m_newNetworkGameDialog(new NewNetworkGameDialog(this))
{
  // 中心控件
  setCentralWidget(m_checkerBoardWidget);

  initMenuBar();
  initSignalsAndSlots();

  m_newGameDialog->setBattle(m_battle);
  m_newNetworkGameDialog->setBattle(m_battle);

  m_battle->endBattle(); // 首次重置
}

MainWindow::~MainWindow()
{
}

void MainWindow::initMenuBar()
{
  // 游戏菜单
  m_gameMenu->addAction(m_startGame);
  m_gameMenu->addAction(m_startNetworkGame);
  m_gameMenu->addAction(m_stopGame);
  m_gameMenu->addSeparator();
  m_gameMenu->addAction(m_exitGame);
}

void MainWindow::initSignalsAndSlots()
{
  // menu actions
  connect(m_exitGame, &QAction::triggered, this, []() { QApplication::quit(); });
  connect(m_startGame, &QAction::triggered, this, &MainWindow::startNewGame);
  connect(m_startNetworkGame, &QAction::triggered, this, &MainWindow::startNewNetworkGame);
  connect(m_stopGame, &QAction::triggered, this, &MainWindow::stopGame);

  // battle and checkerboardwidget
  connect(m_battle, &Battle::sigCheckerBoardChanged, m_checkerBoardWidget,
          &CheckerBoardWidget::setCheckerBoard);
  connect(m_checkerBoardWidget, &CheckerBoardWidget::sigMoved, m_battle, &Battle::slotHumanMove);

  // battle and mainwindow
  connect(m_battle, &Battle::sigBattleEnded, this, &MainWindow::showWinnerInfo);
  connect(m_battle, &Battle::sigChanged, this, &MainWindow::battleChangedHandler);
}

void MainWindow::startNewGame()
{
  m_newGameDialog->show();
}

void MainWindow::startNewNetworkGame()
{
  m_newNetworkGameDialog->show();
}

void MainWindow::stopGame()
{
  m_battle->endBattle();
}

void MainWindow::showWinnerInfo(GamePlay::PlayerColor winner)
{
  QMessageBox *mb = new QMessageBox(this);
  mb->setAttribute(Qt::WA_DeleteOnClose, true);
  mb->setWindowTitle(" ");
  if (winner == GamePlay::Unknown)
    mb->setText("平局！");
  else
    mb->setText(m_battle->getPlayer(winner)->getName() + " 胜利！");
  mb->show();
}

void MainWindow::battleChangedHandler()
{
  if (m_battle->isBattleRunning())
  {
    m_startGame->setEnabled(false);
    m_stopGame->setEnabled(true);
    QString currentPlayerName = m_battle->getPlayer(m_battle->currentPlayerColor())->getName();
    statusBar()->showMessage("请 " + currentPlayerName + " 下子", 0);
  }
  else
  {
    m_startGame->setEnabled(true);
    m_stopGame->setEnabled(false);
    statusBar()->showMessage("开始一场新游戏", 0);
  }
}
