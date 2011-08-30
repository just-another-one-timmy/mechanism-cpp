#ifndef LINEARTF_H_INCLUDED
#define LINEARTF_H_INCLUDED

#include "TF.h"

/**
    @brief ��������� ��� �������� �������� ��
    @details ������ ��0, ��1 � ��2 ��� ���� ���������
*/

struct LinearTF
{
    public:
        /**
        @brief ������ �� �� ��������
        */
        TF x;

        /**
        @brief ������ �� �� ��������
        */
        TF y;

        /**
        @brief ������� ������� ����������
        */
        void UnsetCalculated()
        {x.UnsetCalculated();
         y.UnsetCalculated();};
};

#endif // LINEARTF_H_INCLUDED
