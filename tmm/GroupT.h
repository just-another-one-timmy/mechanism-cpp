#ifndef GROUPT_H_INCLUDED
#define GROUPT_H_INCLUDED

#include "Group1.h"

class GroupT:public Group1 // Assur Group First class Crank
{
    private:
        ConnectorTurn *s0cO,*s1cO;
    public:

        /**
        @brief КПП группы первого класса
        */
        KPTurn * O;

        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @brief конструктор групп Ассура 1-го класса с КПВ
        @param K указатель на КПВ
        @param s0 указатель на землю
        @param s1 указатель на ползун
        */
        GroupT(KPTurn *K,Segment *s0,Segment *s1);

        /**
        @return Тип группы (т.е. GROUP_TYPE_S)
        */
        GROUP_TYPE Type();

};


#endif // GROUPT_H_INCLUDED
