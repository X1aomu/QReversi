#include "boardgrid.h"

#include <QtDebug>

BoardGrid::BoardGrid(GamePlay::Position position, GamePlay::PlayerColor role, QWidget *parent)
    : QPushButton(parent),
      m_position(position),
      m_color(role)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(64, 64));
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet(":hover { background-color: grey; }");
    // 连接信号
    connect(this, &QPushButton::clicked, this, &BoardGrid::slotOnClicked);
}

BoardGrid::~BoardGrid()
{

}

void BoardGrid::setStoneColor(GamePlay::PlayerColor role)
{
    m_color = role;
    switch (role) {
    case GamePlay::Black:
        setStyleSheet("background-color:black;");
        //setText("B");
        break;
    case GamePlay::White:
        setStyleSheet("background-color:white;");
        //setText("W");
        break;
    case GamePlay::Unknown:
        setStyleSheet("QPushButton {background-color: #a7690a;} :hover { background-color: grey; }");
        break;
    }
}

void BoardGrid::slotOnClicked()
{
    qDebug()<<"clicked:" + QString::number(m_position.row) + "," + m_position.col;
    emit sigMoved(m_position);
}
