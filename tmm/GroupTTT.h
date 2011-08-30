#ifndef GROUPTTT_H_INCLUDED
#define GROUPTTT_H_INCLUDED

#include "Group2.h"

/**
@brief ����� ������ ������ 2-�� ������ 1-�� ����
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
        @brief ����������� ������
        @param K1 ��������� �� ������ ��
        @param K2 ��������� �� ������ ��
        @param K3 ��������� �� ������ ��
        @param s1 ��������� �� ������ �����
        @param s2 ��������� �� ������ �����
        */

        GroupTTT(KPTurn *K1,KPTurn *K2,KPTurn *K3,Segment *s1, Segment *s2);
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
        KPTurn * C;
        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return ��� ������ (�.�. GROUP_TYPE_TTT)
        */
        GROUP_TYPE Type();

        friend void PrintGroupTTTInfo(GroupTTT *g, bool extended, int level);
};


#endif // GROUPTTT_H_INCLUDED
