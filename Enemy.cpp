// Enemy.cpp
#include "Enemy.h"
#include "Game.h"
#include "Bloque.h"
#include "BloqueDestructible.h"
#include "Bomb.h"
#include <QTimer>
#include <stdlib.h>
#include <time.h>
#include <QGraphicsScene>
#include <QPixmap>

extern Game *game;

static bool seeded = false;

Enemy::Enemy() {
    // Semilla rand()
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }

    // Sprite desde sprites.png en (112,48)
    QPixmap sheet(":/images/spites.png");
    QPixmap sprite = sheet.copy(112, 48, 16, 16).scaled(TILE, TILE);
    setPixmap(sprite);

    // Elegir celda libre aleatoria
    QRectF area = game->scene->sceneRect();
    int cols = static_cast<int>(area.width()) / TILE;
    int rows = static_cast<int>(area.height()) / TILE;
    int col, row;
    do {
        col = rand() % cols;
        row = rand() % rows;
    } while (!game->scene->items(QRectF(col * TILE, row * TILE, TILE, TILE)).isEmpty());
    setPos(col * TILE, row * TILE);

    // Añadir a escena
    game->scene->addItem(this);

    // Timer de movimiento aleatorio
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::mover);
    timer->start(150 + rand() % 200);
}

void Enemy::mover() {
    // Dirección aleatoria: 0=izq,1=der,2=arriba,3=abajo
    int dir = rand() % 4;
    int dx = 0, dy = 0;
    switch (dir) {
    case 0: dx = -TILE; break;
    case 1: dx =  TILE; break;
    case 2: dy = -TILE; break;
    case 3: dy =  TILE; break;
    }

    qreal nx = x() + dx;
    qreal ny = y() + dy;
    QRectF area = game->scene->sceneRect();

    // Validar que la nueva posición quede dentro de los límites visibles
    QRectF bounds = area.adjusted(0, 0, -TILE, -TILE);
    if (!bounds.contains(nx, ny))
        return;

    // Verificar colisión con bloques, destructibles y bombas
    QList<QGraphicsItem*> items = game->scene->items(QRectF(nx, ny, TILE, TILE));
    for (int i = 0; i < items.size(); ++i) {
        if ( typeid(*items[i]) == typeid(Bloque)
            || typeid(*items[i]) == typeid(BloqueDestructible)
            || typeid(*items[i]) == typeid(Bomb) )
        {
            return;  // obstáculo, no moverse
        }
    }

    // Mover si está libre
    setPos(nx, ny);
}
