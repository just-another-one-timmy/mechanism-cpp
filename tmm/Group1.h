#ifndef GROUP1_H_INCLUDED
#define GROUP1_H_INCLUDED

#include "Group.h"

/**
@brief Общий класс для групп Ассура 1-го класса
@details Данный класс является предком для классов GroupT, GroupS
и определяет общие свойства групп Ассура 1-го класса
*/
class Group1:public Group
{
    public:
/**
@brief Обобщенная координата (generalized coordinate)
*/
        double GC;

/**
@brief Указатель на первый сегмент, входящий в группу
*/
        Segment *s0;

/**
@brief Указатель на второй сегмент, входящий в группу
*/
        Segment *s1;

/**
@return Класс группы Ассура (т.е. 1)
*/
        int GetClass(){return 1;};
};


#endif // GROUP1_H_INCLUDED
