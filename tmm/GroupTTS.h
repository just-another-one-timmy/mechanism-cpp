#ifndef GROUPTTS_H_INCLUDED
#define GROUPTTS_H_INCLUDED

#include "Group2.h"
/**
@brief класс группы Ассура 2-го класса 2-го вида
*/

class GroupTTS:public Group2 //Assur Group Second class TTS
{
    private:
        double lab,h;
        double tg,tg_,tg__;

        TurnTF AB,NC;
        ConnectorTurn *s1cA,*s1cB;
        ConnectorTurn *s2cB;
        ConnectorSliding *s2cC;
        ConnectorSliding *s0cC;  // extern connector
        TF yN0,tang;


    public:

                /**
        @brief конструктор группы
        @param K1 Указатель на первую КП
        @param K2 Указатель на вторую КП
        @param K3 Указатель на третью КП
        @param s1 указатель на первое звено
        @param s2 указатель на второе звено
        */
        GroupTTS(KPTurn *K1,KPTurn *K2,KPSliding *K3,Segment *s1, Segment *s2);

        /**
        @brief Указатель на КПВ A
        */
        KPTurn * A;

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
        @return Тип группы (т.е. GROUP_TYPE_TTS)
        */
        GROUP_TYPE Type();
        friend void PrintGroupTTSInfo(GroupTTS *g, bool extended, int level);
};


#endif // GROUPTTS_H_INCLUDED
