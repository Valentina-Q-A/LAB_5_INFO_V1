#include "Bomb.h"
#include "Game.h"
#include "Bullet.h"        // tu clase de explosión
#include <QTimer>
#include <QGraphicsScene>

extern Game* game;

Bomb::Bomb(int x, int y) {
    // 1) Carga el sprite de la bomba
    QPixmap sprite(":/images/spites.png");     // ajusta la ruta y el recorte si usas spriteSheet
    // por ejemplo:
    QPixmap bombImg = sprite.copy(0, 48, 16, 16);
    setPixmap(bombImg.scaled(48,48));
    setPos(x, y);  // centrar la bomba en x,y (opcional)

    // 2) Añádela a la escena
    game->scene->addItem(this);

    // 3) Fija un temporizador para la explosión a los 4000 ms
    QTimer::singleShot(4000, this, SLOT(explode()));
}

void Bomb::explode() {
    // 1) Quita el sprite de la bomba
    scene()->removeItem(this);
    delete this;  // elimina la bomba

    // 2) Crea la explosión (usando tu clase Bullet)
    //    La explosion se añade y se queda activa hasta colisionar
    //    Pasa las coordenadas donde estaba la bomba:
    Bullet* explosion = new Bullet(pos().x() + 24, pos().y() + 24);
    // NO necesitas hacer scene()->addItem(explosion)
    // pues tu constructor de Bullet ya añade sus sprites.
}
