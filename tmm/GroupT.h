#ifndef GROUPT_H_INCLUDED
#define GROUPT_H_INCLUDED

#include "Group1.h"

class GroupT:public Group1 // Assur Group First class Crank
{
    private:
        ConnectorTurn *s0cO,*s1cO;
    public:

        /**
        @brief ��� ������ ������� ������
        */
        KPTurn * O;

        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @brief ����������� ����� ������ 1-�� ������ � ���
        @param K ��������� �� ���
        @param s0 ��������� �� �����
        @param s1 ��������� �� ������
        */
        GroupT(KPTurn *K,Segment *s0,Segment *s1);

        /**
        @return ��� ������ (�.�. GROUP_TYPE_S)
        */
        GROUP_TYPE Type();

};


#endif // GROUPT_H_INCLUDED
