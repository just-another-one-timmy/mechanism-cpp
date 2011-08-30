#ifndef KPAIR_H_INCLUDED
#define KPAIR_H_INCLUDED

#include "Connector.h"

/**
@brief ���� ��
@details
 KPAIR_TYPE_SLIDING - ��������������
 KPAIR_TYPE_TURN - ������������
*/

enum KPAIR_TYPE {KPAIR_TYPE_SLIDING, KPAIR_TYPE_TURN};

/**
@brief ����� ��� �������� ��
@details �� ��������� ��� �����.
*/

class KPair
{
public:
    /**
    @brief ���� ������� ������
    */
    Force *R1;

    /**
    @brief ���� ������� ������
    */
    Force *R2;

    LinearTF linear;

    /**
    @brief ��� ��
    */
    string name;

    /**
    @return ��� ��
    */
    virtual KPAIR_TYPE Type()=0;

    /**
    @return ������ ���������
    */
    virtual Connector * GetC1()=0;

    /**
    @return ������ ���������
    */
    virtual Connector * GetC2()=0;
};

/**
@brief ����� ���
*/
class KPSliding: public KPair
{
public:

    /**
    @brief ������ ���������
    */
    ConnectorSliding *c1;

    /**
    @brief ������ ���������
    */
    ConnectorSliding *c2;

    /**
    @brief �� ����� ������� ���
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
    @brief �� ����� ������� ���
    @param name ���
    @param c1  ��������� �� ���������
    @param c2  ��������� �� ���������
    */
    KPSliding(string name, ConnectorSliding *c1, ConnectorSliding *c2);
};

/**
@brief ����� ���
*/
class KPTurn: public KPair
{
public:
    /**
    @brief ������ ���������
    */
    ConnectorTurn *c1;

    /**
    @brief ������ ���������
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
    @brief �����������
    @param name ���
    @param c1  ��������� �� ���������
    @param c2  ��������� �� ���������
    */
     KPTurn(string name, ConnectorTurn *c1, ConnectorTurn *c2);
};

#endif // KPAIR_H_INCLUDED
