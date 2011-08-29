#ifndef FORCE_H_INCLUDED
#define FORCE_H_INCLUDED

#include <string>
using namespace std;

#include "TurnTF.h"
#include "LinearTF.h"
#include "Segment.h"
class Segment;
#include "Connector.h"
class Connector;

/**
@brief Типы сил
@details
FORCE_TYPE_GRAVITY, - гравитационные силы
FORCE_TYPE_INERTION, - фиктивные силы инерции
FORCE_TYPE_REACTION, - силы реакций в КП
FORCE_TYPE_TECHNO - силы технологического сопросивления
*/

enum FORCE_TYPE {FORCE_TYPE_GRAVITY, FORCE_TYPE_INERTION, FORCE_TYPE_REACTION, FORCE_TYPE_TECHNO};


class Force
{
    private:
        FORCE_TYPE ftype;
        string name;

        double fx;
        double fy;
        double torque;
        bool calculatedx;
        bool calculatedy;
        bool calculatedt;

        Connector *c;
    public:

    /**
    @brief вращение точки, к которой приложена сила
    */
          TurnTF *turn;     //Transfer function of angle

    /**
    @brief линейное перемещение точки, к которой приложена сила
    */
        LinearTF *linear; //Transfer function of point


       /**
        @brief устанавливает силу

        @param Fx проекция вектора силы на Ох
        @param Fy проекция вектора силы на Оy
        @param Torque момент
        */
        void SetForce(double Fx, double Fy, double Torque);

        /**
        @return проекцию силы на Ох
        */
        double GetForcex();

        /**
        @return проекцию силы на Оу
        */
        double GetForcey();

        /**
        @return момент
        */
        double GetForcet();

        /**
        @return true , если посчитана проекция силы на Ох
        */
        bool IsCalculatedx();

        /**
        @return true , если посчитана проекция силы на Оy
        */
        bool IsCalculatedy();

        /**
        @return true , если посчитан момент
        */
        bool IsCalculatedt();

        /**
        @return тип силы
        */
        FORCE_TYPE Type();


        /**
        @return имя силы
        */
        string GetName();

        /**
        @return коннектор, к которому присоединена сила
        */
        Connector * GetConnector();

        /**
        @brief конструктор силы
        @param name имя силы
        @param type тип силы
        @param c указатель на коннектор
        */
        Force(string name, FORCE_TYPE type, Connector *c);

        /**
        @brief метод для обнуления вычисления значений
        */
        void UnsetCalculated();

};

#endif // FORCE_H_INCLUDED
