#ifndef GROUPTST_H_INCLUDED
#define GROUPTST_H_INCLUDED

#include "Group2.h"

/**
@brief ����� ������ ������ 2-�� ������ 3-�� ����
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
        @brief ����������� ������
        @param K1 ��������� �� ������ ��
        @param K2 ��������� �� ������ ��
        @param K3 ��������� �� ������ ��
        @param s1 ��������� �� ������ �����
        @param s2 ��������� �� ������ �����
        */
        GroupTST(KPTurn *K1,KPSliding *K2,KPTurn *K3,Segment *s1, Segment *s2);

        /**
        @brief ��������� �� ��� A
        */
        KPTurn * A;

        /**
        @brief ��������� �� ��� B
        */
        KPSliding * B;

        /**
        @brief ��������� �� ��� C
        */
        KPTurn * C;
        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return ��� ������ (�.�. GROUP_TYPE_TST)
        */
        GROUP_TYPE Type();
        friend void PrintGroupTSTInfo(GroupTST *g, bool extended, int level);

};

#endif // GROUPTST_H_INCLUDED
