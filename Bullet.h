// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QList>

class QTimer;

class Bullet : public QObject {
    Q_OBJECT
public:
    // Constructor: crea la explosión en cruz en (posX, posY) y arranca el temporizador de colisión
    Bullet(int posX, int posY);

public slots:
    // Se llama periódicamente para detectar colisiones
    void activate();

private slots:
    // Elimina los sprites de la explosión y se autodestruye
    void eliminate();

private:
    QList<QGraphicsPixmapItem*> partesExplosion;  // Partes de la explosión
    QTimer *activationTimer;                      // Temporizador para detección periódica
};

#endif // BULLET_H
