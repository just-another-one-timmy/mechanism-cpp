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
@brief �����

*/

class Segment
{
    public:
    /**
    @brief ������ �����������
    */
        list <Connector *> connectors;
    /**
    @brief ������ ���
    */
        list <Force *> forces;

    /**
    @brief ��������� � ������ ���� �����
    @details � ����� ���������� ����� ������������ ���� ���������� � �������
    */
        ConnectorTurn *cmass;

    /**
    @brief ��������� - ����� ������� ��������� �����
    @details ������������ ��� ��������, ��� ������� �����
    ����������� �������������
    */
         ConnectorTurn *polus;

    /**
    @brief ��� �����
    @details ���������� ��� �����, �������������
    */
        string name;

    /**
    @brief �����
    @details ������������� � �������� �� , �� ���������� ��� �������� �������
    */
        double mass;

    /**
    @brief ������ �������
    @details �������������� � �������� �� , �� ��������� ��� �������� �������
    */
        double rot_inertia;

    /**
    @brief ������ �����
    @details ������ ��� ����� �� ��������� � ���������� ������� ���������
    */
        TurnTF turn;

        Segment();
        ~Segment();
};

#endif // SEGMENT_H_INCLUDED
