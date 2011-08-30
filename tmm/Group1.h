#ifndef GROUP1_H_INCLUDED
#define GROUP1_H_INCLUDED

#include "Group.h"

/**
@brief ����� ����� ��� ����� ������ 1-�� ������
@details ������ ����� �������� ������� ��� ������� GroupT, GroupS
� ���������� ����� �������� ����� ������ 1-�� ������
*/
class Group1:public Group
{
    public:
/**
@brief ���������� ���������� (generalized coordinate)
*/
        double GC;

/**
@brief ��������� �� ������ �������, �������� � ������
*/
        Segment *s0;

/**
@brief ��������� �� ������ �������, �������� � ������
*/
        Segment *s1;

/**
@return ����� ������ ������ (�.�. 1)
*/
        int GetClass(){return 1;};
};


#endif // GROUP1_H_INCLUDED
