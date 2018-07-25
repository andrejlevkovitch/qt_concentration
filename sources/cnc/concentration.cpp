// concentration.cpp

#include "concentration.hpp"
#include "card.hpp"
#include <QtWidgets>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <thread>
#include <vector>

Concentration::Concentration()
    : ::QWidget{}, first_card_{nullptr}, second_card_{nullptr} {
  ::QGridLayout *layout = new QGridLayout;
  layout->setSpacing(0);
  layout->setContentsMargins(0, 0, 0, 0);
  ::QStack<::QString> coloda{pack()};
  if (!coloda.empty()) {
    int n = ::sqrt(coloda.size());
    for (int i{}; i < n; ++i) {
      for (int j{}; j < n; ++j) {
        layout->addWidget(create_card(coloda.pop()), i, j);
      }
    }
    int i{};
    while (!coloda.empty()) {
      layout->addWidget(create_card(coloda.pop()), n, i);
      ++i;
    }
  }
  setLayout(layout);
}

std::chrono::milliseconds Concentration::WAITING_TIME() {
  static const std::chrono::milliseconds retval{800};
  return retval;
}

Card *Concentration::create_card(const QString &str) const {
  Card *button = new Card{str};
  connect(button, SIGNAL(released()), SLOT(slot_compare()));
  connect(button, SIGNAL(pressed()), SLOT(slot_change()));
  return button;
}

::QStack<::QString> Concentration::pack() const {
  ::QStack<::QString> retvalue;
  std::vector<::QString> pack{
      ":/cherry", ":/cat",   ":/smile", ":/horse",    ":/brain",  ":/pokemon",
      ":/bird",   ":/nerpa", ":/mario", ":/dinozaur", ":/sheet",  ":/tree",
      ":/potato", ":/cloud", ":/skull", ":/batman",   ":/pumkin", ":/spider"};
  for (int i = pack.size() - 1; i >= 0; --i) {
    pack.push_back(pack[i]);
  }
  std::random_device rd;
  std::default_random_engine gen{rd()};
  for (int i = pack.size() - 1; i > -1; --i) {
    std::uniform_int_distribution<int> dist{0, i};
    ::swap(pack[dist(gen)], pack[i]);
    retvalue.push(pack[i]);
  }

  return retvalue;
}

void Concentration::slot_change() {
  if (!first_card_) {
    first_card_ = reinterpret_cast<Card *>(sender());
    first_card_->setValue();
  } else if (first_card_ != reinterpret_cast<Card *>(sender())) {
    second_card_ = reinterpret_cast<Card *>(sender());
    second_card_->setValue();
  } else {
    first_card_->setChecked(false);
  }
}

void Concentration::slot_compare() {
  if (first_card_ && second_card_) {
    if (first_card_->value() != second_card_->value()) {
      std::this_thread::sleep_for(WAITING_TIME());
      first_card_->setChecked(false);
      second_card_->setChecked(false);
      first_card_->clrValue();
      second_card_->clrValue();
    } else {
      first_card_->setEnabled(false);
      second_card_->setEnabled(false);
    }
    first_card_ = nullptr;
    second_card_ = nullptr;
  }
  return;
}
