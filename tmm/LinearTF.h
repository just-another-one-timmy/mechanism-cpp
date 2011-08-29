#ifndef LINEARTF_H_INCLUDED
#define LINEARTF_H_INCLUDED

#include "TF.h"

/**
    @brief Структура для хранения линейных ПФ
    @details хранит ПФ0, ПФ1 и ПФ2 для двух координат
*/

struct LinearTF
{
    public:
        /**
        @brief хранит ПФ по абсциссе
        */
        TF x;

        /**
        @brief хранит ПФ по ординате
        */
        TF y;

        /**
        @brief Убирает признак вычисления
        */
        void UnsetCalculated()
        {x.UnsetCalculated();
         y.UnsetCalculated();};
};

#endif // LINEARTF_H_INCLUDED
