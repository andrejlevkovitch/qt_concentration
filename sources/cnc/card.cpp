// card.cpp

#include "card.hpp"
#include <QtWidgets>

Card::Card(const QString &str) : QPushButton{}, image_{str} {
  ::QPalette palette;
  palette.setColor(::QPalette::Button, Qt::blue);
  setPalette(palette);
  setIconSize(size());
  setFixedSize(size());
  setCheckable(true);
}

void Card::setValue() { setIcon(image_); }

void Card::clrValue() { setIcon(default_image()); }

const ::QPixmap &Card::value() const { return image_; }

const ::QPixmap &Card::default_image() {
  static const QPixmap retval{":/void"};
  return retval;
}

const QSize &Card::size() {
  static const QSize retval{50, 50};
  return retval;
}
