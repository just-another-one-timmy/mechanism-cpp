#ifndef GROUP_H_INCLUDED
#define GROUP_H_INCLUDED

#include "Segment.h"
#include "KPair.h"

#include <string>
#include <math.h>
#include <iostream>

#include <stdio.h>

const double epsilon = 1e-10;

inline double sqr(double x)
{
    return x*x;
}

#define pi 3.1415926535897932384626433832795

/**
@brief Типы групп Ассура
*/
enum GROUP_TYPE {GROUP_TYPE_S, GROUP_TYPE_T,
                 GROUP_TYPE_TTT, GROUP_TYPE_TTS, GROUP_TYPE_TST, GROUP_TYPE_STS, GROUP_TYPE_TSS};

/**
@brief Класс родитель для групп Ассура
@details ...
*/
class Group
{
    private:
        double PointLineDistance(double x1, double y1, double A, double B, double C);
        double PointLineDistanceP(double ro1, double phi1, double ro2, double phi2, double alpha);

    public:
        /**
        @brief Имя группы
        @details Именем группы считается перечисление в скобках имен звеньев группы
        */
        string name;
        /**
        @brief Вычисляет ПФ0 для группы
        @details Вычисляет передаточную функцию нулевого порядка по спечитальным формулам
        */
        virtual void CalcTF0()=0;

        /**
        @brief Вычисляет ПФ1 для группы
        @details Вычисляет передаточную функцию первого порядка (аналог скорости) по спечитальным формулам
        */
        virtual void CalcTF1()=0;

        /**
        @brief Вычисляет ПФ2 для группы
        @details Вычисляет передаточную функцию второго порядка (аналог ускорения) по спечитальным формулам
        */
        virtual void CalcTF2()=0;

        /**
        @brief Вычисляет ПФ для группы
        @details Вычисляет передаточную функцию нулевого, первого и второго порядка по спечитальным формулам
        */
        virtual void CalcTF();


        /**
        @brief Вычисляет реакции в КП
        @details Вычисляет реакции сил в кинематических парах
        */
        virtual void CalcReaction()=0;

        /**
        @brief Возвращает класс группы
        @details ...
        */
        virtual int GetClass()=0;

        /**
        @return тип группы
        @details ...
        */
        virtual GROUP_TYPE Type()=0;

        void CalcTF0Segment(Segment *s,ConnectorTurn *c);
        void CalcTF1Segment(Segment *s,ConnectorTurn *c);
        void CalcTF2Segment(Segment *s,ConnectorTurn *c);
        double GetDist(ConnectorTurn *c1,ConnectorTurn *c2);
        double GetHeight(ConnectorTurn *c1,ConnectorSliding *c2);
        double GetAngleSS(ConnectorSliding *c1,ConnectorSliding *c2);
        double GetAngleTT(ConnectorTurn *c1,ConnectorTurn *c2);


};

#endif // GROUP_H_INCLUDED
