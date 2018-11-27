#include "mainwindow.h"

#include "ui/checkerboard/checkerboardwidget.h"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_battle(new Battle(this)),
      m_checkerBoardWidget(new CheckerBoardWidget(this)),
      m_gameMenu(menuBar()->addMenu("Game")),
      m_startGame(new QAction("Start game", this)),
      m_stopGame(new QAction("Stop game", this)),
      m_exitGame(new QAction("Exit", this))
{
    // 中心控件
    setCentralWidget(m_checkerBoardWidget);

    initMenuBar();
    initSignalsAndSlots();
    //updateStatusBar();

    m_battle->startNewBattle(Battle::Human, Battle::Human, "H1", "H2");
}

MainWindow::~MainWindow()
{

}

void MainWindow::initMenuBar()
{
    // 游戏菜单
    m_gameMenu->addAction(m_startGame);
    m_gameMenu->addAction(m_stopGame);
    m_gameMenu->addSeparator();
    m_gameMenu->addAction(m_exitGame);
}

void MainWindow::initSignalsAndSlots()
{
    // menu actions
    connect(m_exitGame, &QAction::triggered, this, [](){QApplication::quit();});
    connect(m_startGame, &QAction::triggered, this, &MainWindow::startNewGame);
    connect(m_stopGame, &QAction::triggered, this, &MainWindow::stopGame);

    // battle and checkerboardwidget
    connect(m_battle, &Battle::sigCheckerBoardChanged, m_checkerBoardWidget, &CheckerBoardWidget::setCheckerBoard);
    connect(m_checkerBoardWidget, &CheckerBoardWidget::sigMoved, m_battle, &Battle::slotHumanMove);

    // battle and mainwindow
    connect(m_battle, &Battle::sigBattleEnded, this, &MainWindow::showWinnerInfo);
    connect(m_battle, &Battle::sigChanged, this, &MainWindow::updateStatusBar);
}

void MainWindow::startNewGame()
{

}

void MainWindow::stopGame()
{
    m_battle->endBattle();
}

void MainWindow::showWinnerInfo(GamePlay::PlayerColor winner)
{

}

void MainWindow::updateStatusBar()
{
    QString currentPlayerName = m_battle->getPlayer(m_battle->currentPlayerColor())->getName();
    statusBar()->showMessage("请 " + currentPlayerName + " 下子");
}
