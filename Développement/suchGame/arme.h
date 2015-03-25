#ifndef ARME_H
#define ARME_H

class QGraphicsPixmapItem;

class Arme : public QGraphicsPixmapItem
{
    public:
        Arme();
        int get_atq() const;
        int get_def() const;
        int get_portee() const;
        void set_atq(int atq);
        void set_def(int def);
        void set_portee(int portee);

    protected:
        int _atq;
        int _def;
        int _portee;

};

#endif // ARME  _H
