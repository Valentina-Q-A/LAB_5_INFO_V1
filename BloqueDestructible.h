#ifndef BLOQUEDESCTRUCTIBLE_H
#define BLOQUEDESCTRUCTIBLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

                       class BloqueDestructible : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    BloqueDestructible(int posx, int posy);
};

#endif // BLOQUEDESCTRUCTIBLE_H

