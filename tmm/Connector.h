#ifndef CONNECTOR_H_INCLUDED
#define CONNECTOR_H_INCLUDED

#include "LinearTF.h"
#include "TurnTF.h"

#include "Segment.h"
class Segment;

/**
@brief ���� ����������
*/
enum CONNECTOR_TYPE {CONNECTOR_TYPE_SLIDING, CONNECTOR_TYPE_TURN};

    /**
        @brief ���������
        @details ��������� ������ ��� ������������� �� � �����
    */

struct Connector
{
    public:

        /**
        @brief �����, �� ������� ��������� ���������
        */
        Segment *s;

        /**
        @brief ���������� ���������� � �������� �������
        @details ���������� ���������� � �������� ������� ���������,
        ��������� �� ������, �� ������� ��������� ���������
        */
        double ro;
        double phi;

        /**
        @brief ���������� ��� ����������
        @details ��������� ��� ����������: ������������ , ��������������
        */
        virtual CONNECTOR_TYPE Type()=0;

        /**
        @brief ��� ����������
        @details ���������� ��� ����������
        @todo ArcSin: �������� ������� ��������� ����� � ����������,
         ��� ����������� ������������ ���������� ���������
        */
        string name;

};

/**
        @brief �������������� ���������
        @details ��������  ��������� ������ ������ � ��������
        ������ ��� ������������� ��� � �����
*/

struct ConnectorSliding: public Connector
{
    public:

        /**
        @brief �� ��������� �����
        */
        LinearTF linear0;

        /**
        @brief �� ���� �������
        */
        TurnTF *turn;

        /**
        @brief ���� ������� � ������� ��������� �����-�������
        */
        double alpha;

        /**
        @brief ���������� ��� ����������
        */
        virtual CONNECTOR_TYPE Type();
};

/**
        @brief ������������ ���������
        @details �������� ��������� ������
        ������ ��� ������������� ��� � �����
*/

struct ConnectorTurn: public Connector
{
    public:

        /**
        @brief �� ������������� ����������
        */
        LinearTF *linear;

        /**
        @brief ���������� ��� ����������
        */
        virtual CONNECTOR_TYPE Type();
};

#endif // CONNECTOR_H_INCLUDED
