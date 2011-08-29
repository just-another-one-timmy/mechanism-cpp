#ifndef GHOUPSTS_H_INCLUDED
#define GHOUPSTS_H_INCLUDED

#include "Group2.h"
/**
@brief класс группы Ассура 2-го класса 4-го вида
*/

class GroupSTS:public Group2 //Assur Group Second class STS
{
    private:
        double h1,h2;
        ConnectorSliding *s1cA,*s0cA;
        ConnectorTurn *s1cB;
        ConnectorTurn *s2cB;
        ConnectorSliding *s2cC,*s0cC;

         double tgN,tgM;
         double tgN_,tgM_;
         double tgN__,tgM__;

    public:
        /**
        @brief конструктор группы
        @param K1 Указатель на первую КП
        @param K2 Указатель на вторую КП
        @param K3 Указатель на третью КП
        @param s1 указатель на первое звено
        @param s2 указатель на второе звено
        */
        GroupSTS(KPSliding *K1,KPTurn *K2,KPSliding *K3,Segment *s1_, Segment *s2_);

        /**
        @brief Указатель на КПП A
        */
        KPSliding * A;

        /**
        @brief Указатель на КПВ B
        */
        KPTurn * B;

        /**
        @brief Указатель на КПП C
        */
        KPSliding * C;

        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return Тип группы (т.е. GROUP_TYPE_STS)
        */
        GROUP_TYPE Type();
        friend void PrintGroupSTSInfo(GroupSTS *g, bool extended, int level);

};




#endif // GHOUPSTS_H_INCLUDED
