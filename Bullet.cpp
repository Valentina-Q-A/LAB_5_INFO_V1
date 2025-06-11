// Bullet.cpp
#include "Bullet.h"
#include "Game.h"
#include "Enemy.h"
#include "BloqueDestructible.h"
#include "Player.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QPixmap>

extern Game* game;

Bullet::Bullet(int posx, int posy) {
    QPixmap spriteSheet(":/images/spites.png");
    int paso = 48;

    struct Parte { QString name; int offsetX, offsetY, sx, sy; };
    Parte datos[9] = {
        {"center",   0,     0,    112,  96},
        {"up-mid",   0,    -paso, 112,  80},
        {"up-end",   0,  -2*paso, 112,  64},
        {"down-mid", 0,     paso, 112, 112},
        {"down-end", 0,   2*paso, 112, 128},
        {"left-mid", -paso,  0,     96,  96},
        {"left-end", -2*paso,0,     80,  96},
        {"right-mid",paso,   0,    128,  96},
        {"right-end",2*paso,0,    144,  96}
    };

    // Crear sprites de la explosión
    for (auto &d : datos) {
        QPixmap sprite = spriteSheet.copy(d.sx, d.sy, 16, 16);
        auto *parte = new QGraphicsPixmapItem(sprite);
        parte->setOffset(0, 0);
        parte->setScale(3.0);  // 16 * 3 = 48px
        parte->setZValue(1);
        parte->setPos(posx + d.offsetX, posy + d.offsetY);
        game->scene->addItem(parte);
        partesExplosion.append(parte);
    }

    // Temporizador para activar la detección cada 50ms
    activationTimer = new QTimer(this);
    connect(activationTimer, &QTimer::timeout, this, &Bullet::activate);
    activationTimer->start(50);
}

void Bullet::activate() {
    bool collided = false;

    // Revisar colisiones para cada parte de la explosión
    for (auto *parte : partesExplosion) {
        auto col = parte->collidingItems();
        for (auto *item : col) {
            if (auto *e = dynamic_cast<Enemy*>(item)) {
                game->score->increase();
                game->scene->removeItem(e);
                delete e;
                collided = true;
            } else if (auto *b = dynamic_cast<BloqueDestructible*>(item)) {
                game->scene->removeItem(b);
                delete b;
                collided = true;
            } else if (auto *p = dynamic_cast<Player*>(item)) {
                game->health->decrease();
                collided = true;
            }
        }
    }

    // Si hubo colisión, detener timer y eliminar explosión
    if (collided) {
        activationTimer->stop();
        eliminate();
    }
}

void Bullet::eliminate() {
    // Quitar sprites de la escena y liberar memoria
    for (auto *parte : partesExplosion) {
        game->scene->removeItem(parte);
        delete parte;
    }
    partesExplosion.clear();

    // Autodestrucción
    delete this;
}
