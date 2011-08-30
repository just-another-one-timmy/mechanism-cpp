#ifndef TURNTF_H_INCLUDED
#define TURNTF_H_INCLUDED

#include "TF.h"

/**
    @brief ��������� ��� �������� ������� ��
    @details ������ ��0, ��1 � ��2
*/
struct TurnTF
{
    public:

        /**
        @brief ������ ������� ��
        */
        TF phi;

        /**
        @brief ������� ������� ����������
        */
        void UnsetCalculated()
        {phi.UnsetCalculated();};
};

#endif // TURNTF_H_INCLUDED
