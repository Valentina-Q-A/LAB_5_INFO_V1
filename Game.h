#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <Player.h>
#include <Score.h>
#include <Health.h>

// QPixmap para edicion
//Qimage solo para imagenes
//QGraphicsPixmapItem, QPixmap, Qimage

class Game:public QGraphicsView{
public:
    Game(QWidget * parent=0);
    QGraphicsScene *scene;
    Player *player;
    Score * score;
    Health * health;
};

#endif // GAME_H
