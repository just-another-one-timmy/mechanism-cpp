#ifndef GROUPTSS_H_INCLUDED
#define GROUPTSS_H_INCLUDED

#include "Group2.h"
/**
@brief класс группы Ассура 2-го класса 5-го вида
*/

class GroupTSS:public Group2 //Assur Group Second class STS
{
    private:
        double h,alfa;
        double tgN,tgM;
        double tgN_,tgM_;
        double tgN__,tgM__;
        ConnectorTurn *s1cA;
        ConnectorSliding *s1cB,*s2cB;
        ConnectorSliding *s2cC,*s0cC;
        double xK,yK,xK_,yK_,xK__,yK__;
        LinearTF K;
        double roK,phiK;

    public:
        /**
        @brief конструктор группы
        @param K1 Указатель на первую КП
        @param K2 Указатель на вторую КП
        @param K3 Указатель на третью КП
        @param s1 указатель на первое звено
        @param s2 указатель на второе звено
        */
        GroupTSS(KPair *K1,KPair *K2,KPair *K3,Segment *s1, Segment *s2);

        /**
        @brief Указатель на КПВ A
        */
        KPTurn * A;

        /**
        @brief Указатель на КПП B
        */
        KPSliding * B;

        /**
        @brief Указатель на КПП C
        */
        KPSliding * C;

        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return Тип группы (т.е. GROUP_TYPE_TSS)
        */
        GROUP_TYPE Type();

        friend void PrintGroupTSSInfo(GroupTSS *g, bool extended, int level);

};


#endif // GROUPTSS_H_INCLUDED
