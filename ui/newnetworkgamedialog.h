#ifndef NEWNETWORKGAMEDIALOG_H
#define NEWNETWORKGAMEDIALOG_H

#include <QDialog>

#include "core/battle.h"

namespace Ui
{
class NewNetworkGameDialog;
}

class NewNetworkGameDialog : public QDialog
{
  Q_OBJECT

public:
  explicit NewNetworkGameDialog(QWidget *parent = nullptr);
  ~NewNetworkGameDialog();

  /// \brief 设置对战。
  void setBattle(Battle *battle) { m_battle = battle; }

private slots:
  void on_buttonBox_accepted();

private:
  Ui::NewNetworkGameDialog *ui;

  Battle *m_battle;
  std::shared_ptr<NetworkPlayer> m_networkPlayer;
};

#endif // NEWNETWORKGAMEDIALOG_H
