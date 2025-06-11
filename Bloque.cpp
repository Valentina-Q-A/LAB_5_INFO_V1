#include <Bloque.h>
#include <QPixmap>

Bloque::Bloque(int posx, int posy) : QObject(), QGraphicsPixmapItem() {
    // Posicionar el bloque en la escena
    setPos(posx, posy);

    // Cargar la hoja de sprites
    QPixmap spriteSheet(":/images/spites.png");

    // Recortar el sprite en la posición (48, 64) de tamaño 16x16
    QPixmap bloqueSprite = spriteSheet.copy(48, 48, 16, 16);

    // Aplicarlo al bloque (escalar si deseas que se vea más grande)
    setPixmap(bloqueSprite.scaled(48, 48));  // o sin scaled() si quieres tamaño 16x16
    //setPen(Qt::NoPen);  // Elimina el borde negro

}
