
#include <Player.h>
#include <QDebug>
#include <QKeyEvent>
#include <Bullet.h>
#include <Enemy.h>
#include <Bloque.h>
#include <BloqueDestructible.h>
#include <Bomb.h>
#include <QDebug>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    bulletsound = new QMediaPlayer();
    bulletoutput = new QAudioOutput();  // Crear la salida de audio
    bulletsound->setAudioOutput(bulletoutput);
    bulletsound->setSource(QUrl("qrc:/sounds/080884_bullet-hit-39872.mp3"));
    // Cargar la hoja de sprites
    spriteSheet = QPixmap(":/images/spites.png");

    // Recortar un sprite para cada dirección (ajusta según tu sprite sheet real)
    frameDown  = spriteSheet.copy(  48,  0, 16, 16);  // mirando abajo
    frameLeft  = spriteSheet.copy( 0,  0, 16, 16);  // mirando izquierda
    frameRight = spriteSheet.copy( 0,  16, 16, 16);  // mirando derecha
    frameUp    = spriteSheet.copy( 48,  16, 16, 16);  // mirando arriba

    // Mostrar la imagen inicial (mirando abajo)
    setPixmap(frameDown.scaled(48, 48));


}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        lastDirection = Left;
        if (pos().x() > 48){
            setPos(x() - 8, y());
            setPixmap(frameLeft.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible) || typeid(*items[i]) == typeid(Bomb)) {
                chocoConBloque = true;
                break;
            }
        }

        if (chocoConBloque) {
            setPos(x() + 8, y());  // Deshacer movimiento
        } else {
            setPixmap(frameLeft.scaled(48, 48));

        }
    }


    else if (event->key() == Qt::Key_Right) {
        lastDirection = Right;
        if (pos().x() < 720){
            setPos(x() + 8, y());
            setPixmap(frameLeft.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible) || typeid(*items[i]) == typeid(Bomb)) {
                chocoConBloque = true;
                break;
            }
        }
        if (chocoConBloque) {
            setPos(x() - 8, y());  // Deshacer movimiento
        } else {
            setPixmap(frameRight.scaled(48, 48));  // Solo si sí se movió

        }
    }

    else if (event->key() == Qt::Key_Up){
        lastDirection = Up;
        if (pos().y() > 48){
            setPos(x(), y() - 8);
            setPixmap(frameUp.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible) || typeid(*items[i]) == typeid(Bomb)) {
                chocoConBloque = true;
                break;
            }
        }

        if (chocoConBloque) {
            setPos(x(), y() + 8);  // Deshacer
        } else {
            setPixmap(frameUp.scaled(48, 48));

        }
    }
    else if (event->key() == Qt::Key_Down){
        lastDirection = Down;
        if (pos().y() < 576){
            setPos(x(), y() + 8);
            setPixmap(frameDown.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible) || typeid(*items[i]) == typeid(Bomb)) {
                chocoConBloque = true;
                break;
            }
        }
        if (chocoConBloque) {
            setPos(x(), y() - 8);  // Deshacer
        } else {
            setPixmap(frameDown.scaled(48, 48));

        }
    }



    else if (event->key() == Qt::Key_Space) {
        // 1) Calcula la posición de la bomba según lastDirection:
        int bx = x(), by = y();
        const int W = 48, H = 48;

        switch (lastDirection) {
        case Player::Left:
            bx = x() - W;
            by = y();
            break;
        case Player::Right:
            bx = x() + W;
            by = y();
            break;
        case Player::Up:
            bx = x();
            by = y() - H;
            break;
        case Player::Down:
            bx = x();
            by = y() + H;
            break;
        }

        // 2) Calcula sólo el punto central del casillero
        QPointF centerPoint(bx + W/2.0, by + H/2.0);

        // 3) Pide el ítem que hay justo ahí
        QGraphicsItem *item = scene()->itemAt(centerPoint, QTransform());

        // 4) Si no es un Bloque ni un BloqueDestructible, planta la bomba
        if (!dynamic_cast<Bloque*>(item) && !dynamic_cast<BloqueDestructible*>(item)) {
            Bomb* bomba = new Bomb(bx, by);
            if (bulletsound->playbackState() == QMediaPlayer::PlayingState)
                bulletsound->setPosition(0);
            else
                bulletsound->play();
        }
    }
}


void Player::spawn()
{
    //Crear un enemigo
    Enemy *enemy =new Enemy();
    scene() -> addItem(enemy);
}
