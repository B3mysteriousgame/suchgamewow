#ifndef STRATEGIE_H
#define STRATEGIE_H

class Strategie // interface
{
    public:
        virtual ~Strategie(){}
        void executer (){ analyser(); appliquer(); }

    protected:
        virtual void analyser () = 0;
        virtual void appliquer () = 0;
};
#endif // STRATEGIE_H
