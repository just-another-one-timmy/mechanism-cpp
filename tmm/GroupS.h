#ifndef GROUPS_H_INCLUDED
#define GROUPS_H_INCLUDED

#include "Group1.h"
/**
@brief ����� ����� ������ 1-�� ������ � ���
@details �������� � ���� �����(����), ��� , ������
*/


class GroupS:public Group1 // Assur Group First class Slider
{
    private:
        ConnectorSliding *s0cO,*s1cO;

    public:
        /**
        @brief ��� ������ ������� ������
        */
        KPSliding * O;

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
        GroupS(KPSliding *K,Segment *s0, Segment *s1);

        /**
        @return ��� ������ (�.�. GROUP_TYPE_S)
        */
        GROUP_TYPE Type();
};

#endif // GROUPS_H_INCLUDED
