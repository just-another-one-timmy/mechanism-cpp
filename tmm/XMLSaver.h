#ifndef XMLSAVER_H_INCLUDED
#define XMLSAVER_H_INCLUDED

#include <string>
using namespace std;

#include "..\tinyxml\tinyxml.h"

#include "CompManager.h"
#include "GroupManager.h"
/**
@brief ����� ��� ���������� ��������� � ���� xml
@details ����� ����� ��������� ����� XMLLoader ����� ��������� �������� �� ������������ �����.
����� �������� �����������.
*/
class XMLSaver
{
    private:
        static CompManager *cm;
        static GroupManager *gm;
        static void SaveSegment(Segment *s, TiXmlElement *m);
        static void SaveConnector(Connector *c, TiXmlElement *se);
        static void SaveKPair(KPair *k, TiXmlElement *kse);
        static void SaveGroup(Group *g, TiXmlElement *gre);

        static void SaveGroupS(GroupS* g, TiXmlElement *gre);
        static void SaveGroupT(GroupT* g, TiXmlElement *gre);
        static void SaveGroupSTS(GroupSTS* g, TiXmlElement *gre);
        static void SaveGroupTSS(GroupTSS* g, TiXmlElement *gre);
        static void SaveGroupTST(GroupTST* g, TiXmlElement *gre);
        static void SaveGroupTTS(GroupTTS* g, TiXmlElement *gre);
        static void SaveGroupTTT(GroupTTT* g, TiXmlElement *gre);
    public:
        /**
        @brief ���������� ���������
        @details ������������� ��������� �� �������� ����������� � �������� �����, ������� � ���������� ��������.
        @param c, g ��������� �� ���������
        @bug ������������� ������� ����� ���� ��������. � ���������, ��� ����������� �������� � ������������� �����.
             ������� ������� - �������� �� ������������ ������ XMLSaver, �� �������� �������� �����������.
        @bug ��� ��������, ��������� �� CompManager *c � g->cm
        */
        static void SetManagers(CompManager *c, GroupManager *g);
        /**
        @brief ��������� �������� � ����
        @details ��������� ������� cm � ���� (���������� � �������, ��, �����������), � ����� gm (���������� � �������)
        @param filename ��� �����, � ������� ����� �������� ��������.
        @bug ���� ��� ��� ����������� ���������� NULL ������ ����������, ����� ������ �� �����������. � ��� ������ ����?
        */
        static void Save(string filename);
};

#endif // XMLSAVER_H_INCLUDED
