// concentraion.hpp

#pragma once

#include <QStack>
#include <QWidget>
#include <chrono>

class QPushButton;
class Card;

class Concentration : public QWidget {
  Q_OBJECT
public:
  static std::chrono::milliseconds WAITING_TIME();

private:
  Card *first_card_;
  Card *second_card_;

public:
  Concentration();

private:
  Card *create_card(const QString &) const;
  QStack<QString> pack() const;
public slots:
  void slot_compare();
  void slot_change();
};
