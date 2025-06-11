#include <QApplication>
#include <Game.h>

/* Requisitos
- Conocimientos básico en C++ (punteros, manejo de memoria y POO)
- Conocimientos básicos en Widgets

Temas:
Paso 1
- QGraphicsScene (mapa, mundo)
- QGraphicsItem -> QGraphicsRectItem
- QGraphisView
Paso 2
- Eventos (keyPressEvent(), QkeyEvent)
- sistema de propagación de eventos
- Qdebug
Paso 3
-QTimer
- Señales (signals) y slots (funcion connect)
- QObject QOBJECT macro
Paso 4
-Parents
-QGraphicsTesxtItem, setPlainText(),setFont(),setDefaultTextcolor()
*/

Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game=new Game();
    game -> show();

    return a.exec();
}
