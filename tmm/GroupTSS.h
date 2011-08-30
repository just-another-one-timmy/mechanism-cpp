#ifndef GROUPTSS_H_INCLUDED
#define GROUPTSS_H_INCLUDED

#include "Group2.h"
/**
@brief ����� ������ ������ 2-�� ������ 5-�� ����
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
        @brief ����������� ������
        @param K1 ��������� �� ������ ��
        @param K2 ��������� �� ������ ��
        @param K3 ��������� �� ������ ��
        @param s1 ��������� �� ������ �����
        @param s2 ��������� �� ������ �����
        */
        GroupTSS(KPair *K1,KPair *K2,KPair *K3,Segment *s1, Segment *s2);

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
        KPSliding * C;

        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @return ��� ������ (�.�. GROUP_TYPE_TSS)
        */
        GROUP_TYPE Type();

        friend void PrintGroupTSSInfo(GroupTSS *g, bool extended, int level);

};


#endif // GROUPTSS_H_INCLUDED
