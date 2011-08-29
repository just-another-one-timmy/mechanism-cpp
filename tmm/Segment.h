#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

#include <list>
#include <string>
using namespace std;

#include "Force.h"
class Force;

#include "Connector.h"

struct Connector;
struct ConnectorTurn;

/**
@brief звено

*/

class Segment
{
    public:
    /**
    @brief список коннекторов
    */
        list <Connector *> connectors;
    /**
    @brief список сил
    */
        list <Force *> forces;

    /**
    @brief коннектор в центре масс звена
    @details к этому коннектору нужно подсоединять силы гравитации и инерции
    */
        ConnectorTurn *cmass;

    /**
    @brief коннектор - полюс системы координат звена
    @details используется при расчетах, как опорная точка
    добавляется автоматически
    */
         ConnectorTurn *polus;

    /**
    @brief имя звена
    @details глобальное имя звена, идентификатор
    */
        string name;

    /**
    @brief масса
    @details необязательна в расчетах ПФ , но необходима для силового расчета
    */
        double mass;

    /**
    @brief момент инерции
    @details необязательный в расчетах ПФ , но необходим для силового расчета
    */
        double rot_inertia;

    /**
    @brief наклон звена
    @details наклон оси звена по отношению к глобальной системе координат
    */
        TurnTF turn;

        Segment();
        ~Segment();
};

#endif // SEGMENT_H_INCLUDED
