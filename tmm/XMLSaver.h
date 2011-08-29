#ifndef XMLSAVER_H_INCLUDED
#define XMLSAVER_H_INCLUDED

#include <string>
using namespace std;

#include "..\tinyxml\tinyxml.h"

#include "CompManager.h"
#include "GroupManager.h"
/**
@brief Класс для сохранения механизма в файл xml
@details После этого используя класс XMLLoader можно загрузить механизм из сохраненного файла.
Класс является статическим.
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
        @brief Установить менеджеры
        @details Устанавливает указатели на менеджер компонентов и менеджер групп, которые и составляют механизм.
        @param c, g Указатели на менеджеры
        @bug Архитектурное решение может быть неверным. В частности, нет возможности работать в многопоточной среде.
             Вариант решения - создание не статического класса XMLSaver, но теряется удобство пользования.
        @bug Нет проверки, совпадают ли CompManager *c и g->cm
        */
        static void SetManagers(CompManager *c, GroupManager *g);
        /**
        @brief Сохраняет механизм в файл
        @details Сохраняет сначала cm в файл (информация о звеньях, КП, коннекторах), а затем gm (информация о группах)
        @param filename Имя файла, в который будет сохранен механизм.
        @bug Пока что нет возможности передавать NULL вторым параметром, чтобы группы не сохранялись. А оно вообще надо?
        */
        static void Save(string filename);
};

#endif // XMLSAVER_H_INCLUDED
