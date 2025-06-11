// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy();

public slots:
    void mover();

private:
    QTimer *timer;
    static constexpr int TILE = 48;
};

#endif // ENEMY_H
