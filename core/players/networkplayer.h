#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#include "core/gameplay.h"
#include "core/players/virtualplayer.h"

#include <QObject>
#include <QUdpSocket>

/// \brief 网络玩家。
class NetworkPlayer : public VirtualPlayer
{
  Q_OBJECT

public:
  /// \brief 构造函数。
  /// \param name 名字。
  /// \param parent 父控件。
  explicit NetworkPlayer(QString name, QObject *parent = nullptr);
  ~NetworkPlayer() override;

  /// \brief 设置游戏
  void setGame(GamePlay *game) { m_game = game; }

  void connectToHost(const QHostAddress &addr, quint16 port) { m_socket.connectToHost(addr, port); }

  QHostAddress localAddress() { return m_socket.localAddress(); }
  quint16 localPort() { return m_socket.localPort(); }

public slots:
  /// \brief 通知网络玩家下子。
  ///
  /// 网络玩家在这里将向网络上的玩家发送下子信息，然后等待网络上传回的下子步骤，最终完成下子。
  ///
  /// \param game 当前游戏中的棋盘。
  /// \param playerColor 玩家的颜色。
  virtual void slotNextMove(const GamePlay::CheckerBoard &game,
                            GamePlay::PlayerColor playerColor) override;

  /// \brief 处理接收到的消息。
  void readPendingDatagrams();

private:
  void processRecievedDatagram(const QNetworkDatagram &datagram);

private:
  GamePlay *m_game;
  QUdpSocket m_socket;
};

#endif // NETWORKPLAYER_H
