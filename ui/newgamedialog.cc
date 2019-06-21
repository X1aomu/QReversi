#include "newgamedialog.h"
#include "ui_newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewGameDialog)
{
  ui->setupUi(this);
  setWindowTitle("New Game");
  setModal(true);
}

NewGameDialog::~NewGameDialog()
{
  delete ui;
}

void NewGameDialog::on_buttonBox_accepted()
{
  if (m_battle == nullptr) return;
  QString name1 = "黑方";
  QString name2 = "白方";
  if (!ui->lineEdit_name_1->text().isEmpty())
  {
    name1 = ui->lineEdit_name_1->text();
  }
  if (!ui->lineEdit_name_2->text().isEmpty())
  {
    name2 = ui->lineEdit_name_2->text();
  }
  Battle::PlayerType player1Type;
  Battle::PlayerType player2Type;
  if (ui->comboBox_playerType_1->currentText() == "电脑")
    player1Type = Battle::Ai;
  else
    player1Type = Battle::Human;
  if (ui->comboBox_playerType_2->currentText() == "电脑")
    player2Type = Battle::Ai;
  else
    player2Type = Battle::Human;

  m_battle->startNewBattle(player1Type, player2Type, name1, name2);
}
