#ifndef GROUP2_H_INCLUDED
#define GROUP2_H_INCLUDED

#include "Group.h"


/**
@brief ����� ����� ��� ����� ������ 2-�� ������
@details ������ ����� �������� ������� ��� �������
GroupTTT, GroupTTS, GroupTST, GroupSTS, GroupTSS
� ���������� ����� �������� ����� ������ 2-�� ������
*/

class Group2:public Group //Assur Group Second class
{
    protected:
        signed char j1, j2;
    public:

        /**
        @brief ��������� �� ������ �������, �������� � ������
        */
        Segment *s1;

        /**
        @brief ��������� �� ������ �������, �������� � ������
        */
        Segment *s2;

        /**
        @return ������� ������ 1
        */
        signed char Getj1();

        /**
        @brief ���������� ������� ������
        */
        void Setj1(signed char j1);

        /**
        @return ������� ������ 2
        */
        signed char Getj2();

        /**
        @brief ���������� ������� ������
        */
        void Setj2(signed char j2);


        /**
        @return ����� ������ ������ (�.�. 2)
        */
        int GetClass(){return 2;};
};


#endif // GROUP2_H_INCLUDED
