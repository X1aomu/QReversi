#include "networkplayer.h"

#include <ctime>
#include <memory>
#include <random>
#include <vector>

#include <QEventLoop>
#include <QMessageBox>
#include <QNetworkDatagram>
#include <QRandomGenerator>
#include <QTimer>

#include "core/gameplay.h"

NetworkPlayer::NetworkPlayer(QString name, QObject *parent) : VirtualPlayer(name, parent)
{
  // 绑定 udpSocket
  // Note: 使用默认随机端口会绑定失败，原因不明
  int port = QRandomGenerator::global()->bounded(10240, 65526);
  if (m_socket.bind(QHostAddress::Any, static_cast<quint16>(port)) == false)
  {
    QMessageBox msgBox;
    msgBox.setText(tr("C-C Communicating Client"));
    msgBox.setInformativeText(tr("Cannot bind to port %1.").arg(port));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    return;
  }
  // 连接 udpSocket
  connect(&m_socket, &QIODevice::readyRead, this, &NetworkPlayer::readPendingDatagrams);
}

NetworkPlayer::~NetworkPlayer()
{
}

void NetworkPlayer::slotNextMove(const GamePlay::CheckerBoard &game,
                                 GamePlay::PlayerColor playerColor)
{
  GamePlay::Position nextMove = m_game->getLastMovePosition(); // 下子位置
  QByteArray raw_data;
  QTextStream out(&raw_data, QIODevice::WriteOnly);
  QString msg;
  msg += "MOVE\n";
  msg += tr("Location: %1, %2\n").arg(nextMove.row).arg(nextMove.col);
  m_socket.writeDatagram(msg.toUtf8());
}

void NetworkPlayer::readPendingDatagrams()
{
  while (m_socket.hasPendingDatagrams())
  {
    QNetworkDatagram datagram = m_socket.receiveDatagram();
    processRecievedDatagram(datagram);
  }
}

void NetworkPlayer::processRecievedDatagram(const QNetworkDatagram &datagram)
{
  QByteArray data = datagram.data();
  QString message = QString::fromUtf8(data);
  QTextStream ss(&message, QIODevice::ReadOnly);

  QString line;
  line = ss.readLine().toLower();
  // 丢弃不合法消息
  if (line != "move")
  {
    qDebug() << "收到的不是下棋指令：" << line;
    return;
  }
  line = ss.readLine();
  QStringList kv = line.split(':');
  QStringList xy = kv[1].split(',');
  size_t x = xy[0].toUInt();
  size_t y = xy[1].toUInt();
  GamePlay::Position pos = {x, y};
  emit sigMoved(pos);
}
