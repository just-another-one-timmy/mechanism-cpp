#ifndef GROUPS_H_INCLUDED
#define GROUPS_H_INCLUDED

#include "Group1.h"
/**
@brief класс групп Ассура 1-го класса с КПП
@details включает в себя землю(рама), КПП , ползун
*/


class GroupS:public Group1 // Assur Group First class Slider
{
    private:
        ConnectorSliding *s0cO,*s1cO;

    public:
        /**
        @brief КПП группы первого класса
        */
        KPSliding * O;

        virtual void CalcTF0();
        virtual void CalcTF1();
        virtual void CalcTF2();
        virtual void CalcReaction();

        /**
        @brief конструктор групп Ассура 1-го класса с КПП
        @param K указатель на КПП
        @param s0 указатель на землю
        @param s1 указатель на ползун
        */
        GroupS(KPSliding *K,Segment *s0, Segment *s1);

        /**
        @return Тип группы (т.е. GROUP_TYPE_S)
        */
        GROUP_TYPE Type();
};

#endif // GROUPS_H_INCLUDED
