#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>

           class Bloque : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bloque(int posx, int posy);
};

#endif // BLOQUE_H
