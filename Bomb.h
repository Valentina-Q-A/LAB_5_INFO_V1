#ifndef BOMB_H
#define BOMB_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Bomb : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    // x,y: posición donde aparece la bomba
    Bomb(int x, int y);

private slots:
    // se llamará tras 4 segundos
    void explode();
};

#endif // BOMB_H
