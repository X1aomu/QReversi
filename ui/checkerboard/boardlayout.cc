#include "boardlayout.h"

#include <QGridLayout>

BoardLayout::BoardLayout(QWidget *parent)
    : QGridLayout(parent)
{
    setSpacing(0);
}

BoardLayout::~BoardLayout()
{

}
