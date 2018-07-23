// card.hpp

#pragma once

#include <QWidget>
#include <qpushbutton.h>

class Card : public ::QPushButton {
  Q_OBJECT
private:
  QPixmap image_;

public:
  Card(const QString &);
  void setValue();
  void clrValue();
  const ::QPixmap &value() const;

  static const QSize &size();
  static const QPixmap &default_image();
};
