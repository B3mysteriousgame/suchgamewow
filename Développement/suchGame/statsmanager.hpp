#ifndef STATSFRAME_HPP
#define STATSFRAME_HPP

#include "barre.hpp"

class QGraphicsScene;

class StatsManager
{
public:
    StatsManager(QGraphicsScene *scene);
    ~StatsManager();
    void moveBarresBy(const QPointF &dp);
    void setLargeur(const int largeur, const QString &cible);

signals:

public slots:

private:
    Barre *_vie;
    Barre *_mana;
    Barre *_ki;
    QHash<QString, Barre*> _barreDico;

    void initBarres(QGraphicsScene *scene);
};

#endif // STATSFRAME_HPP
