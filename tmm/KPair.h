#ifndef KPAIR_H_INCLUDED
#define KPAIR_H_INCLUDED

#include "Connector.h"

/**
@brief Типы КП
@details
 KPAIR_TYPE_SLIDING - поступательная
 KPAIR_TYPE_TURN - вращательная
*/

enum KPAIR_TYPE {KPAIR_TYPE_SLIDING, KPAIR_TYPE_TURN};

/**
@brief класс для описания КП
@details КП соединяет два звена.
*/

class KPair
{
public:
    /**
    @brief сила реакции первая
    */
    Force *R1;

    /**
    @brief сила реакции вторая
    */
    Force *R2;

    LinearTF linear;

    /**
    @brief имя КП
    */
    string name;

    /**
    @return тип КП
    */
    virtual KPAIR_TYPE Type()=0;

    /**
    @return первый коннектор
    */
    virtual Connector * GetC1()=0;

    /**
    @return второй коннектор
    */
    virtual Connector * GetC2()=0;
};

/**
@brief класс КПП
*/
class KPSliding: public KPair
{
public:

    /**
    @brief первый коннектор
    */
    ConnectorSliding *c1;

    /**
    @brief второй коннектор
    */
    ConnectorSliding *c2;

    /**
    @brief ПФ угола наклона оси
    */
    TurnTF angle;

    virtual KPAIR_TYPE Type();
    virtual ~KPSliding();
    virtual Connector * GetC1()
    {
        return c1;
    };
    virtual Connector * GetC2()
    {
        return c2;
    };
    /**
    @brief ПФ угола наклона оси
    @param name имя
    @param c1  указатель на коннектор
    @param c2  указатель на коннектор
    */
    KPSliding(string name, ConnectorSliding *c1, ConnectorSliding *c2);
};

/**
@brief класс КПВ
*/
class KPTurn: public KPair
{
public:
    /**
    @brief первый коннектор
    */
    ConnectorTurn *c1;

    /**
    @brief второй коннектор
    */
    ConnectorTurn *c2;

    virtual KPAIR_TYPE Type();
    virtual ~KPTurn();
    virtual Connector * GetC1()
    {
        return c1;
    };
    virtual Connector * GetC2()
    {
        return c2;
    };

    /**
    @brief конструктор
    @param name имя
    @param c1  указатель на коннектор
    @param c2  указатель на коннектор
    */
     KPTurn(string name, ConnectorTurn *c1, ConnectorTurn *c2);
};

#endif // KPAIR_H_INCLUDED
