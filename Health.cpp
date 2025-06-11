
#include <Health.h>
#include <QGraphicsItem>
#include <QFont>

Health::Health(QGraphicsItem * parent):QGraphicsTextItem(parent){
    //inicializar el score en 0
    health=5;
    //Dibujar el texto
    setPlainText(QString("Health: ")+QString::number(health)); //Score: 0
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::decrease()
{
    if (health>0){
        health--;
        setPlainText(QString("Health: ")+QString::number(health)); //Actualiza la informacion de la vida
    }
}

int Health::getHealth()
{
    return health;
}
