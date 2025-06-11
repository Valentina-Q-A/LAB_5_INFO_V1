#include <Score.h>
#include <QGraphicsItem>
#include <QFont>

Score::Score(QGraphicsItem * parent):QGraphicsTextItem(parent){
    //inicializar el score en 0
    score=0;
    //Dibujar el texto
    setPlainText(QString("Score: ")+QString::number(score)); //Score: 0
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16)); //tipo de letra y tamaño
}

void Score::increase()
{
    score++;
    setPlainText(QString("Score: ")+QString::number(score));
}

int Score::getScore()
{
    return score;
}
