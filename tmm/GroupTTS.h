#ifndef GROUPTTS_H_INCLUDED
#define GROUPTTS_H_INCLUDED

#include "Group2.h"
/**
@brief ����� ������ ������ 2-�� ������ 2-�� ����
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
        @brief ����������� ������
        @param K1 ��������� �� ������ ��
        @param K2 ��������� �� ������ ��
        @param K3 ��������� �� ������ ��
        @param s1 ��������� �� ������ �����
        @param s2 ��������� �� ������ �����
        */
        GroupTTS(KPTurn *K1,KPTurn *K2,KPSliding *K3,Segment *s1, Segment *s2);

        /**
        @brief ��������� �� ��� A
        */
        KPTurn * A;

        /**
        @brief ��������� �� ��� B
        */
        KPTurn * B;

        /**
        @brief ��������� �� ��� C
        */
        KPSliding * C;

        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return ��� ������ (�.�. GROUP_TYPE_TTS)
        */
        GROUP_TYPE Type();
        friend void PrintGroupTTSInfo(GroupTTS *g, bool extended, int level);
};


#endif // GROUPTTS_H_INCLUDED
