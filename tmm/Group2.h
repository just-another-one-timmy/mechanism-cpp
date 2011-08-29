#ifndef GROUP2_H_INCLUDED
#define GROUP2_H_INCLUDED

#include "Group.h"


/**
@brief Общий класс для групп Ассура 2-го класса
@details Данный класс является предком для классов
GroupTTT, GroupTTS, GroupTST, GroupSTS, GroupTSS
и определяет общие свойства групп Ассура 2-го класса
*/

class Group2:public Group //Assur Group Second class
{
    protected:
        signed char j1, j2;
    public:

        /**
        @brief Указатель на первый сегмент, входящий в группу
        */
        Segment *s1;

        /**
        @brief Указатель на второй сегмент, входящий в группу
        */
        Segment *s2;

        /**
        @return признак сборки 1
        */
        signed char Getj1();

        /**
        @brief установить признак сборки
        */
        void Setj1(signed char j1);

        /**
        @return признак сборки 2
        */
        signed char Getj2();

        /**
        @brief установить признак сборки
        */
        void Setj2(signed char j2);


        /**
        @return класс группы Ассура (т.е. 2)
        */
        int GetClass(){return 2;};
};


#endif // GROUP2_H_INCLUDED
