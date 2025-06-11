#include <BloqueDestructible.h>
#include <QPixmap>
#include <stdlib.h> //rand() numero muy grande

BloqueDestructible::BloqueDestructible(int posx, int posy) : QObject(), QGraphicsPixmapItem() {
    // Posicionar el bloque en la escena
    setPos(posx, posy);

    // Cargar la hoja de sprites
    QPixmap spriteSheet(":/images/spites.png");

    // Recortar el sprite en la posición (48, 64) de tamaño 16x16
    QPixmap BloqueDestructibleSprite = spriteSheet.copy(64, 48, 16, 16);

    // Aplicarlo al bloque (escalar si deseas que se vea más grande)
    setPixmap(BloqueDestructibleSprite.scaled(48, 48));  // o sin scaled() si quieres tamaño 16x16
    //setPen(Qt::NoPen);  // Elimina el borde negro
    setZValue(0);  // Por debajo de la explosión

    /*qDebug() << "[DEBUG] Bloque destructible creado en:" << pos()
             << " Bounding rect:" << sceneBoundingRect();*/


}
