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
@brief ���� ���
@details
FORCE_TYPE_GRAVITY, - �������������� ����
FORCE_TYPE_INERTION, - ��������� ���� �������
FORCE_TYPE_REACTION, - ���� ������� � ��
FORCE_TYPE_TECHNO - ���� ���������������� �������������
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
    @brief �������� �����, � ������� ��������� ����
    */
          TurnTF *turn;     //Transfer function of angle

    /**
    @brief �������� ����������� �����, � ������� ��������� ����
    */
        LinearTF *linear; //Transfer function of point


       /**
        @brief ������������� ����

        @param Fx �������� ������� ���� �� ��
        @param Fy �������� ������� ���� �� �y
        @param Torque ������
        */
        void SetForce(double Fx, double Fy, double Torque);

        /**
        @return �������� ���� �� ��
        */
        double GetForcex();

        /**
        @return �������� ���� �� ��
        */
        double GetForcey();

        /**
        @return ������
        */
        double GetForcet();

        /**
        @return true , ���� ��������� �������� ���� �� ��
        */
        bool IsCalculatedx();

        /**
        @return true , ���� ��������� �������� ���� �� �y
        */
        bool IsCalculatedy();

        /**
        @return true , ���� �������� ������
        */
        bool IsCalculatedt();

        /**
        @return ��� ����
        */
        FORCE_TYPE Type();


        /**
        @return ��� ����
        */
        string GetName();

        /**
        @return ���������, � �������� ������������ ����
        */
        Connector * GetConnector();

        /**
        @brief ����������� ����
        @param name ��� ����
        @param type ��� ����
        @param c ��������� �� ���������
        */
        Force(string name, FORCE_TYPE type, Connector *c);

        /**
        @brief ����� ��� ��������� ���������� ��������
        */
        void UnsetCalculated();

};

#endif // FORCE_H_INCLUDED
