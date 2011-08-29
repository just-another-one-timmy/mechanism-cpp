#ifndef XMLLOADER_H_INCLUDED
#define XMLLOADER_H_INCLUDED

#include <string>
using namespace std;

#include "..\tinyxml\tinyxml.h"

#include "CompManager.h"
#include "GroupManager.h"

enum NODE_TYPE {NT_MECHANISM, NT_SEGMENT, NT_KPAIRS, NT_GROUPS, NT_UNKNOWN};
/**
@brief Класс для загрузки механизмов из xml-файлов.
@details При этом для парсинга xml-файла используется библиотека TinyXML.
*/
class XMLLoader
{
    private:
        static CompManager *cm;
        static GroupManager *gm;
        static void AnalyzeElem(TiXmlElement *elem);
        static void AnalyzeNode(TiXmlNode *node);
        static void AnalyzeDoc(TiXmlNode *doc);
        static NODE_TYPE NodeNameToType(string name);

        static void AnalyzeMechanism(TiXmlNode *node);
        static void AnalyzeSegment(TiXmlNode *node);
        static void AnalyzeKPairs(TiXmlNode *node);
        static void AnalyzeKPair(TiXmlNode *node);
        static void AnalyzeGroups(TiXmlNode *node);

        static void AnalyzeConnector(TiXmlNode *node, string segment_name);
        static void AnalyzeGroup(TiXmlElement *elem);

        static void ProcessConnectorTurn(string name, string segment_name, double ro, double phi, bool ro_found, bool phi_found);
        static void ProcessConnectorTurnD(string name, string segment_name, double x, double y, bool x_found, bool y_found);
        static void ProcessConnectorSliding(string name, string segment_name, double ro, double phi, double alpha, bool ro_found, bool phi_found, bool alpha_found);
        static void ProcessConnectorSlidingD(string name, string segment_name, double x, double y, double alpha, bool x_found, bool y_found, bool alpha_found);

        static void ProcessGroup1(TiXmlElement *elem);
        static void ProcessGroup2(TiXmlElement *elem);

        static void SetMechanismAttributes(TiXmlNode *node);
    public:
        /**
        @brief Загружает механизм из файла с именем filename
        @details При этом вызывая нужные методы менеджера компонентов *c и менеджера групп *g
        @param filename Имя загружаемого xml-файла
        */
        static void Load(string filename);
        /**
        @brief Устанавливает указатели на менеджер компонентов и менеджер групп
        @details Это необходимо для последующей загрузки механизма в эти объекты
        @param c Указатель на менеджер компонентов
        @param g Указатель на менеджер групп
        */
        static void SetManagers(CompManager *c, GroupManager *g);
};

#endif // XMLLOADER_H_INCLUDED
