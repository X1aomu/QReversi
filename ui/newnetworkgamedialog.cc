#include "newnetworkgamedialog.h"
#include "ui_newnetworkgamedialog.h"

#include "core/players/networkplayer.h"

NewNetworkGameDialog::NewNetworkGameDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::NewNetworkGameDialog),
    m_networkPlayer(new NetworkPlayer("远程玩家", this))
{
  ui->setupUi(this);

  QString localAddress = m_networkPlayer->localAddress().toString();
  QString localPort = QString::number(m_networkPlayer->localPort());
  ui->localAddressLbel->setText(localAddress);
  ui->localPortLabel->setText(localPort);
}

NewNetworkGameDialog::~NewNetworkGameDialog()
{
  delete ui;
}

void NewNetworkGameDialog::on_buttonBox_accepted()
{
  if (m_battle == nullptr) return;

  QHostAddress remoteAddress;
  if (!remoteAddress.setAddress(ui->remoteAddressLineEdit->text()))
  {
    qDebug() << "远程地址错误";
  }
  quint16 remotePort = ui->remotePortLineEdit->text().toUInt();
  // 设置远程地址和端口
  m_networkPlayer->connectToHost(remoteAddress, remotePort);

  Battle::PlayerColor localPlayerColor;
  if (ui->localPlayerColorComboBox->currentText() == "黑子")
    localPlayerColor = Battle::PlayerColor::Black;
  else
    localPlayerColor = Battle::PlayerColor::White;
  QString localPlayerName = ui->localPlayerNameLineEdit->text();

  m_battle->startNewNetworkBattle(localPlayerColor, m_networkPlayer, localPlayerName);
}
