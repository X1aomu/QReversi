#ifndef BOARDLAYOUT_H
#define BOARDLAYOUT_H

#include <QGridLayout>
#include <QObject>

/// \brief 棋盘布局。
///
/// 这个类控制棋盘显示控件上的布局。
class BoardLayout : public QGridLayout
{
  Q_OBJECT

public:
  explicit BoardLayout(QWidget *parent);
  ~BoardLayout();
};

#endif // BOARDLAYOUT_H
