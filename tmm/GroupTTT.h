#ifndef GROUPTTT_H_INCLUDED
#define GROUPTTT_H_INCLUDED

#include "Group2.h"

/**
@brief класс группы Ассура 2-го класса 1-го вида
*/

class GroupTTT:public Group2 //Assur Group Second class TTT
{
    private:
        double lab,lcb;
        TurnTF AB,CB;
        ConnectorTurn *s1cA,*s1cB;
        ConnectorTurn *s2cB,*s2cC;
    public:
        /**
        @brief конструктор группы
        @param K1 Указатель на первую КП
        @param K2 Указатель на вторую КП
        @param K3 Указатель на третью КП
        @param s1 указатель на первое звено
        @param s2 указатель на второе звено
        */

        GroupTTT(KPTurn *K1,KPTurn *K2,KPTurn *K3,Segment *s1, Segment *s2);
        /**
        @brief Указатель на КПВ A
        */
        KPTurn * A;

        /**
        @brief Указатель на КПВ B
        */
        KPTurn * B;

        /**
        @brief Указатель на КПВ C
        */
        KPTurn * C;
        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return Тип группы (т.е. GROUP_TYPE_TTT)
        */
        GROUP_TYPE Type();

        friend void PrintGroupTTTInfo(GroupTTT *g, bool extended, int level);
};


#endif // GROUPTTT_H_INCLUDED
