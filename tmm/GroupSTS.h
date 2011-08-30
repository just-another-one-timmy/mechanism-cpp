#ifndef GHOUPSTS_H_INCLUDED
#define GHOUPSTS_H_INCLUDED

#include "Group2.h"
/**
@brief ����� ������ ������ 2-�� ������ 4-�� ����
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
        @brief ����������� ������
        @param K1 ��������� �� ������ ��
        @param K2 ��������� �� ������ ��
        @param K3 ��������� �� ������ ��
        @param s1 ��������� �� ������ �����
        @param s2 ��������� �� ������ �����
        */
        GroupSTS(KPSliding *K1,KPTurn *K2,KPSliding *K3,Segment *s1_, Segment *s2_);

        /**
        @brief ��������� �� ��� A
        */
        KPSliding * A;

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
        @return ��� ������ (�.�. GROUP_TYPE_STS)
        */
        GROUP_TYPE Type();
        friend void PrintGroupSTSInfo(GroupSTS *g, bool extended, int level);

};




#endif // GHOUPSTS_H_INCLUDED
