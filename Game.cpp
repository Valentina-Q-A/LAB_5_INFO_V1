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
#include <QApplication>
#include <QMessageBox>

extern Game *game;

Game::Game (QWidget *parent): QGraphicsView(parent), enemyCount(0){
    ::game = this;
    // Crear un nuevo escenario
    scene = new QGraphicsScene();
    scene -> setSceneRect(0, 0,816,672);
    // Carga el sprite-sheet
    QPixmap sheet(":/images/spites.png");

    // Corta el tile de 16×16 que quieres usar como fondo (ajusta coordenadas)
    QPixmap bgTile = sheet.copy(0, 64, 16, 16);

    // Escálalo al tamaño de tu escena o vista
    QPixmap bgScaled = bgTile.scaled(816, 672);

    // Ponlo como brush de fondo
    setBackgroundBrush(QBrush(bgScaled));

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
    health -> setPos(health-> x()+ 175, health->y()); //que aparezca en x=0 y en y un poquito mas abajo (25)
    scene -> addItem(health);

    // --- dentro de Game::Game() ---

    // 1) Crea el texto del timer
    timerText = scene->addText("Time: 0", QFont("Arial", 28));
    timerText->setDefaultTextColor(Qt::white);
    timerText->setPos(375, 0);   // por ejemplo en la esquina superior izquierda
    timerText->setZValue(1);

    // 2) Crea un QTimer que dispare cada 1000 ms
    timerClock = new QTimer(this);
    connect(timerClock, &QTimer::timeout, this, [=]() {
        secondsElapsed++;
        int m = secondsElapsed / 60;
        int s = secondsElapsed % 60;
        timerText->setPlainText(QString("Time: %1:%2")
                                    .arg(m, 2, 10, QChar('0'))
                                    .arg(s, 2, 10, QChar('0')));
    });

    timerClock->start(1000);


    /*//Generar enemigos de manera periodica
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),player,SLOT(spawn()));
    timer -> start(2000); // 2 seg*/

    //play background music
    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();  // Crear la salida de audio
    music->setAudioOutput(audioOutput);               // Vincular la salida de audio al reproductor

    // Configurar la fuente del medio correctamente
    music->setSource(QUrl("qrc:/sounds/bgroundsound.mp3"));

    music->play();

    //show();

    // Crear 2 enemigos iniciales
    for (int i = 0; i < 2; ++i) spawnEnemy();

    // Timer para crear 1 enemigo cada 15 s
    spawnTimer = new QTimer(this);
    connect(spawnTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    spawnTimer->start(15000);

    // 3) Cada 70 000 ms (1m10s) comprobamos victory
    victoryTimer = new QTimer(this);
    connect(victoryTimer, &QTimer::timeout, this, &Game::checkVictory);
    victoryTimer->start(70000);

}

// Slot para generar un nuevo enemigo
void Game::spawnEnemy() {
    if (enemyCount >= MAX_ENEMIES) {
        // Detener el timer si ya llegamos al máximo
        spawnTimer->stop();
        return;
    }
    // Construye y añade el enemigo (el constructor de Enemy se encarga de scene->addItem)
    new Enemy();
    ++enemyCount;
}

void Game::checkVictory() {
    // Recorre la escena buscando cualquier Enemy
    bool anyEnemy = false;
    for (auto *it : scene->items()) {
        if (dynamic_cast<Enemy*>(it)) {
            anyEnemy = true;
            break;
        }
    }
    // Si no queda ninguno, victoria y fin del juego
    if (!anyEnemy) {
        victoryTimer->stop();
        QMessageBox::information(nullptr, "¡Victoria!", "Has eliminado a todos!");
        qApp->quit();
    }
    // si sí hay enemigos, no hacemos nada y el spawnTimer seguirá su curso
}

