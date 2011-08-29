#ifndef VIZUALIZER_H_INCLUDED
#define VIZUALIZER_H_INCLUDED

#include "GroupManager.h"

class Vizualizer
{
    protected:
        bool dmode;
        CompManager *c;
    public:
        Vizualizer(CompManager *c = NULL);
        virtual void Draw()=0;
        void SetDebugMode(bool dmode);
        bool GetDebugMode();
        void SetCompManager(CompManager *c);
        int tf1_color, tf2_color;

        double sc0;
        double sc1;
        double sc2;
        double scf;

        int h;
        int we;
};

#endif // VIZUALIZER_H_INCLUDED
