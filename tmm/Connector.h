#ifndef CONNECTOR_H_INCLUDED
#define CONNECTOR_H_INCLUDED

#include "LinearTF.h"
#include "TurnTF.h"

#include "Segment.h"
class Segment;

/**
@brief “ипы коннектора
*/
enum CONNECTOR_TYPE {CONNECTOR_TYPE_SLIDING, CONNECTOR_TYPE_TURN};

    /**
        @brief коннектор
        @details коннектор служит дл€ присоединени€  ѕ к звену
    */

struct Connector
{
    public:

        /**
        @brief «вено, на котором находитс€ коннектор
        */
        Segment *s;

        /**
        @brief координаты коннектора в пол€рной системе
        @details координаты коннектора в пол€рной системе координат,
        св€занной со звеном, на котором находитс€ коннектор
        */
        double ro;
        double phi;

        /**
        @brief ¬озвращает тип коннектора
        @details ¬озвращет тип коннектора: вращательный , поступательный
        */
        virtual CONNECTOR_TYPE Type()=0;

        /**
        @brief им€ коннектора
        @details глобальное им€ коннектора
        @todo ArcSin: предлага сделать локальные имена и глобальные,
         дл€ возможности клонировани€ одинаковых сегментов
        */
        string name;

};

/**
        @brief поступательный коннектор
        @details задаетс€  начальной точкой точкой и наклоном
        служит дл€ присоединени€  ѕѕ к звену
*/

struct ConnectorSliding: public Connector
{
    public:

        /**
        @brief ѕ‘ начальной точки
        */
        LinearTF linear0;

        /**
        @brief ѕ‘ угла наклона
        */
        TurnTF *turn;

        /**
        @brief угол наклона в системе координат звена-хоз€ина
        */
        double alpha;

        /**
        @brief возвращает тип коннектора
        */
        virtual CONNECTOR_TYPE Type();
};

/**
        @brief вращательный коннектор
        @details задаетс€ начальной точкой
        служит дл€ присоединени€  ѕ¬ к звену
*/

struct ConnectorTurn: public Connector
{
    public:

        /**
        @brief ѕ‘ вращательного коннектора
        */
        LinearTF *linear;

        /**
        @brief ¬озвращает тип коннектора
        */
        virtual CONNECTOR_TYPE Type();
};

#endif // CONNECTOR_H_INCLUDED
