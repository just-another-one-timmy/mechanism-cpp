#ifndef MECHAN_H_INCLUDED
#define MECHAN_H_INCLUDED

class Mechan
{
    public:
        Mechan();

        static double GetRM(CompManager *cm);     //equivalent moment of inertia
        static double GetEMoI(CompManager *cm);
        static double GetEMoI_(CompManager *cm);
};

#endif // MECHAN_H_INCLUDED
