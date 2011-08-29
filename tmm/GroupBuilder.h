#ifndef GROUPBUILDER_H_INCLUDED
#define GROUPBUILDER_H_INCLUDED

#include "GroupT.h"
#include "GroupS.h"
#include "GroupSTS.h"
#include "GroupTSS.h"
#include "GroupTST.h"
#include "GroupTTS.h"
#include "GroupTTT.h"
/**
@brief Класс для удобного создания групп Ассура
*/
class GroupBuilder
{
    public:
        // G1
        /**
        @brief Создает группу Ассура первого класса
        @details Создает группу Ассура первого класса, при этом определяется тип переданной кинеметической пары
        */
        static Group * CreateGroup(string, KPair *,     Segment *, Segment *);
        // S
        static Group * CreateGroup(KPSliding *, Segment *, Segment *);
        // T
        static Group * CreateGroup(KPTurn    *, Segment *, Segment *);
        // G2
        static Group * CreateGroup(string, KPair *,     KPair *,     KPair *,     Segment *, Segment *);
        // STS
        static Group * CreateGroup(KPSliding *, KPTurn *,    KPSliding *, Segment *, Segment *);
        // TSS, SST
        static Group * CreateGroup(KPTurn *,    KPSliding *, KPSliding *, Segment *, Segment *);
        static Group * CreateGroup(KPSliding *, KPSliding *, KPTurn *,    Segment *, Segment *);
        // TST
        static Group * CreateGroup(KPTurn *,    KPSliding *, KPTurn *,    Segment *, Segment *);
        // TTS, STT
        static Group * CreateGroup(KPTurn *,    KPTurn *,    KPSliding *, Segment *, Segment *);
        static Group * CreateGroup(KPSliding *, KPTurn *,    KPTurn *,    Segment *, Segment *);
        // TTT
        static Group * CreateGroup(KPTurn *,    KPTurn *,    KPTurn *,    Segment *, Segment *);
};

#endif // GROUPBUILDER_H_INCLUDED
