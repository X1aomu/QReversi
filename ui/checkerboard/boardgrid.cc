#include "boardgrid.h"

#include <QPainter>
#include <QBrush>
#include <QEvent>

BoardGrid::BoardGrid(GamePlay::Position position, GamePlay::PlayerColor role, QWidget *parent)
    : QPushButton(parent),
      m_position(position),
      m_playerColor(role)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(kGridSize, kGridSize));
    setMaximumSize(QSize(kGridSize, kGridSize));
    setFocusPolicy(Qt::NoFocus);
    // 连接信号
    connect(this, &QPushButton::clicked, this, &BoardGrid::slotOnClicked);
}

BoardGrid::~BoardGrid()
{

}

void BoardGrid::setStoneColor(GamePlay::PlayerColor role)
{
    m_playerColor = role;
    update();
}

void BoardGrid::slotOnClicked()
{
    emit sigMoved(m_position);
}

void BoardGrid::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    static QColor background(0xa7, 0x69, 0x0a, 169);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制背景和边框
    brush.setColor(background);
    painter.setBrush(brush);
    painter.drawRect(0, 0, kGridSize, kGridSize);

    // 画棋子
    switch (m_playerColor) {
    case GamePlay::Black:
        brush.setColor(Qt::black);
        painter.setBrush(brush);
        painter.drawEllipse(kGridSize / 2 - kStoneRadius, kGridSize / 2 - kStoneRadius, kStoneRadius * 2, kStoneRadius * 2);
        break;
    case GamePlay::White:
        brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawEllipse(kGridSize / 2 - kStoneRadius, kGridSize / 2 - kStoneRadius, kStoneRadius * 2, kStoneRadius * 2);
        break;
    case GamePlay::Unknown:
        break;
    }

    // 鼠标悬停加深颜色
    if (m_hovered)
    {
        QColor color(0, 0, 0, 127);
        brush.setColor(color);
        painter.setBrush(brush);
        painter.drawRect(0, 0, kGridSize, kGridSize);
    }
}

bool BoardGrid::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::HoverEnter:
        m_hovered = true;
        update();
        return true;
    case QEvent::HoverLeave:
        m_hovered = false;
        update();
        return true;
    default:
        return QWidget::event(event);
    }
}
