#include "virtualplayer.h"

VirtualPlayer::VirtualPlayer(QString name, QObject *parent)
    : QObject(parent), m_name(name)
{

}

VirtualPlayer::~VirtualPlayer()
{

}
