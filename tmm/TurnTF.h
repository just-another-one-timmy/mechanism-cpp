#ifndef TURNTF_H_INCLUDED
#define TURNTF_H_INCLUDED

#include "TF.h"

/**
    @brief Структура для хранения угловых ПФ
    @details хранит ПФ0, ПФ1 и ПФ2
*/
struct TurnTF
{
    public:

        /**
        @brief хранит угловые ПФ
        */
        TF phi;

        /**
        @brief Убирает признак вычисления
        */
        void UnsetCalculated()
        {phi.UnsetCalculated();};
};

#endif // TURNTF_H_INCLUDED
