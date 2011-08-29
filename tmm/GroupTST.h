#ifndef GROUPTST_H_INCLUDED
#define GROUPTST_H_INCLUDED

#include "Group2.h"

/**
@brief класс группы Ассура 2-го класса 3-го вида
*/

class GroupTST:public Group2 //Assur Group Second class TST
{
    private:
        double h1,h2;
        TurnTF AC,beta;
        ConnectorTurn *s1cA;
        ConnectorSliding *s1cB;
        ConnectorSliding *s2cB;
        ConnectorTurn *s2cC;
        double lac,lac_,lac__;
        double b,b_,b__;


    public:
        /**
        @brief конструктор группы
        @param K1 Указатель на первую КП
        @param K2 Указатель на вторую КП
        @param K3 Указатель на третью КП
        @param s1 указатель на первое звено
        @param s2 указатель на второе звено
        */
        GroupTST(KPTurn *K1,KPSliding *K2,KPTurn *K3,Segment *s1, Segment *s2);

        /**
        @brief Указатель на КПВ A
        */
        KPTurn * A;

        /**
        @brief Указатель на КПП B
        */
        KPSliding * B;

        /**
        @brief Указатель на КПВ C
        */
        KPTurn * C;
        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return Тип группы (т.е. GROUP_TYPE_TST)
        */
        GROUP_TYPE Type();
        friend void PrintGroupTSTInfo(GroupTST *g, bool extended, int level);

};

#endif // GROUPTST_H_INCLUDED
