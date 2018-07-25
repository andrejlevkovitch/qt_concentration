// main.cpp

#include <QApplication>

#include "concentration.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Concentration game;

  game.setMaximumSize(0, 0);
  game.show();

  return app.exec();
}
