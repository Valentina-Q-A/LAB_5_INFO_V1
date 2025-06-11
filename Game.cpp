
#include <Game.h>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <Enemy.h>
#include <Score.h>
#include <Bloque.h>
#include <BloqueDestructible.h>
#include <Bomb.h>
#include <Health.h>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <stdlib.h> //rand() numero muy grande


Game::Game (QWidget *parent){
    // Crear un nuevo escenario
    scene = new QGraphicsScene();
    scene -> setSceneRect(0, 0,816,672);
    setBackgroundBrush(QBrush(QImage(":/images/fondo.jpg")));
    // 1) Spawnea 2 de golpe
    /*for (int i = 0; i < 2; ++i) {
        new Enemy();
        ++enemiesSpawned;
    }

    // 2) Crea el timer para uno cada 15 s
    enemySpawnTimer = new QTimer(this);
    connect(enemySpawnTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    enemySpawnTimer->start(15'000);  // 15 000 ms = 15 s*/

    setScene(scene);
    //me quita o elimina todas las barras espaciodoras que aparecen en posicion vertical u horizontal
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(816,672);

    //crear jugador
    player = new Player();
    //player -> setRect(0,0,100,100); //x,y,ancho,alto
    //player -> setPixmap(QPixmap(":/images/jugador.png")); //x,y,ancho,alto
    player -> setPos(48,96);
    player -> setFlag(QGraphicsItem::ItemIsFocusable); //objeto enfocable
    player -> setFocus();
    scene ->addItem(player);

    //crear muro
    // === BORDES DE BLOQUES ===
    int ancho = 816;
    int alto = 672;
    int tam = 48;
    // Borde superior
    for (int x = 0; x < ancho; x += tam) {
        Bloque* bloque = new Bloque(x, 48);
        scene->addItem(bloque);
    }
    // Borde inferior
    for (int x = 0; x < ancho; x += tam) {
        Bloque* bloque = new Bloque(x, alto - tam);
        scene->addItem(bloque);
    }
    // Borde izquierdo
    for (int y = tam; y < alto - tam; y += tam) {
        Bloque* bloque = new Bloque(0, y+48);
        scene->addItem(bloque);
    }
    // Borde derecho
    for (int y = tam; y < alto - tam; y += tam) {
        Bloque* bloque = new Bloque(ancho - tam, y+48);
        scene->addItem(bloque);
    }
    // === BLOQUES INTERNOS ===
    int filas = 12;
    int columnas = 16;
    // Empezar en fila 2 (fila 0 = borde, fila 1 = espacio libre debajo del HUD)
    for (int fila = 2; fila < filas - 1; fila++) {
        for (int col = 1; col < columnas - 1; col++) {
            // Solo colocar bloque en columnas impares para hacer patrón: uno sí, uno no
            if (fila % 2 == 1 && col % 2 == 1) {
                continue;  // Saltar este para que queden huecos (uno sí, uno no)
            }
            // Bloques sólidos cada dos filas y columnas (tipo patrón fijo)
            if (fila % 2 == 0 && col % 2 == 0) {
                Bloque* bloque = new Bloque(col * tam, fila * tam + 48);
                scene->addItem(bloque);
            }
        }
    }

    //crear bloques destructibles
    for (int i = 1; i < columnas - 1; i++) {
        for (int j = 2; j < filas - 1; j++) {
            if ((rand() % 100) < 30) {  // 30% probabilidad
                int x = i * 48;
                int y = j * 48;
                BloqueDestructible* bloqueDestructible = new BloqueDestructible(x, y);
                scene->addItem(bloqueDestructible);
            }
        }
    }


    //crear Score
    score =new Score();
    scene -> addItem(score);

    //crear Health
    health =new Health();
    health -> setPos(health-> x(), health->y()+ 25); //que aparezca en x=0 y en y un poquito mas abajo (25)
    scene -> addItem(health);

    //Generar enemigos de manera periodica
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),player,SLOT(spawn()));
    timer -> start(2000); // 2 seg

    //play background music
    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();  // Crear la salida de audio
    music->setAudioOutput(audioOutput);               // Vincular la salida de audio al reproductor

    // Configurar la fuente del medio correctamente
    music->setSource(QUrl("qrc:/sounds/bgroundsound.mp3"));

    music->play();

    //show();

}

/*void Game::spawnEnemy() {
    if (enemiesSpawned < MAX_ENEMIES) {
        new Enemy();
        ++enemiesSpawned;
    } else {
        // Llegaste al tope: detén el timer
        enemySpawnTimer->stop();
    }
}*/

