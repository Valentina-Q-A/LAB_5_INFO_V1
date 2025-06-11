#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <Player.h>
#include <Score.h>
#include <Health.h>

// QPixmap para edicion
//Qimage solo para imagenes
//QGraphicsPixmapItem, QPixmap, Qimage

class Game:public QGraphicsView{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);
    QGraphicsScene *scene;
    Player *player;
    Score * score;
    Health * health;
public slots:
    void spawnEnemy();
    void checkVictory();

private:
    QTimer *spawnTimer;
    int enemyCount = 0;
    static constexpr int MAX_ENEMIES = 20;
    QTimer *victoryTimer;

    QGraphicsTextItem *timerText;
    QTimer           *timerClock;
    int               secondsElapsed = 0;

};

#endif // GAME_H



