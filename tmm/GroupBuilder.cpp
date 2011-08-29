#include "GroupBuilder.h"

Group * GroupBuilder::CreateGroup(KPSliding *K, Segment *s1, Segment *s2)
{
    GroupS *g = new GroupS(K, s1, s2);
    return g;
}

Group * GroupBuilder::CreateGroup(KPTurn    *K, Segment *s1, Segment *s2)
{
    GroupT *g = new GroupT(K, s1, s2);
    return g;
}

Group * GroupBuilder::CreateGroup(KPSliding *K1, KPTurn *K2,    KPSliding *K3, Segment *s1, Segment *s2)
{
    GroupSTS *g = new GroupSTS(K1,K2,K3,s1,s2);
    return g;
}

Group * GroupBuilder::CreateGroup(KPTurn *K1,    KPSliding *K2, KPSliding *K3, Segment *s1, Segment *s2)
{
    GroupTSS *g = new GroupTSS(K1,K2,K3,s1,s2);
    return g;
}

Group * GroupBuilder::CreateGroup(KPSliding *K1, KPSliding *K2, KPTurn *K3,    Segment *s1, Segment *s2)
{
    GroupTSS *g = new GroupTSS(K3,K2,K1,s2,s1);
    return g;
}

Group * GroupBuilder::CreateGroup(KPTurn *K1,    KPSliding *K2, KPTurn *K3,    Segment *s1, Segment *s2)
{
    GroupTST *g = new GroupTST(K1,K2,K3,s1,s2);
    return g;
}

Group * GroupBuilder::CreateGroup(KPTurn *K1,    KPTurn *K2,    KPSliding *K3, Segment *s1, Segment *s2)
{
    GroupTTS *g = new GroupTTS(K1,K2,K3,s1,s2);
    return g;
}

Group * GroupBuilder::CreateGroup(KPSliding *K1, KPTurn *K2,    KPTurn *K3,    Segment *s1, Segment *s2)
{
    GroupTTS *g = new GroupTTS(K3,K2,K1,s2,s1);
    return g;
}

Group * GroupBuilder::CreateGroup(KPTurn *K1,    KPTurn *K2,    KPTurn *K3,    Segment *s1, Segment *s2)
{
    GroupTTT *g = new GroupTTT(K1,K2,K3,s1,s2);
    return g;
}

Group * GroupBuilder::CreateGroup(string name, KPair *K, Segment *s1, Segment *s2)
{
    KPAIR_TYPE kt = K->Type();
    Group *g;
    if (kt == KPAIR_TYPE_SLIDING)
        g = CreateGroup((KPSliding *)K, s1, s2);
    else if (kt == KPAIR_TYPE_TURN)
        g = CreateGroup((KPTurn *)K,    s1, s2);
    g->name = name;
    return g;
}

Group * GroupBuilder::CreateGroup(string name, KPair *K1, KPair *K2, KPair *K3, Segment *s1, Segment *s2)
{
    KPAIR_TYPE kt1, kt2, kt3;
    kt1 = K1->Type();
    kt2 = K2->Type();
    kt3 = K3->Type();
    Group *g;
    // STS
    if      (kt1==KPAIR_TYPE_SLIDING && kt2==KPAIR_TYPE_TURN    && kt3==KPAIR_TYPE_SLIDING)
        g = CreateGroup((KPSliding *)K1, (KPTurn *)K2,    (KPSliding *)K3, s1, s2);
    // TSS
    else if (kt1==KPAIR_TYPE_TURN    && kt2==KPAIR_TYPE_SLIDING && kt3==KPAIR_TYPE_SLIDING)
        g = CreateGroup((KPTurn *)K1,    (KPSliding *)K2, (KPSliding *)K3, s1, s2);
    // SST
    else if (kt1==KPAIR_TYPE_SLIDING && kt2==KPAIR_TYPE_SLIDING && kt3==KPAIR_TYPE_TURN   )
        g = CreateGroup((KPSliding *)K1, (KPSliding *)K2, (KPTurn *)K3,    s1, s2);
    // TST
    else if (kt1==KPAIR_TYPE_TURN    && kt2==KPAIR_TYPE_SLIDING && kt3==KPAIR_TYPE_TURN   )
        g = CreateGroup((KPTurn *)K1,    (KPSliding *)K2, (KPTurn *)K3,    s1, s2);
    // TTS
    else if (kt1==KPAIR_TYPE_TURN    && kt2==KPAIR_TYPE_TURN    && kt3==KPAIR_TYPE_SLIDING)
        g = CreateGroup((KPTurn *)K1,    (KPTurn *)K2,    (KPSliding *)K3, s1, s2);
    // STT
    else if (kt1==KPAIR_TYPE_SLIDING && kt2==KPAIR_TYPE_TURN    && kt3==KPAIR_TYPE_TURN   )
        g = CreateGroup((KPSliding *)K1, (KPTurn *)K2,    (KPTurn *)K3,    s1, s2);
    // TTT
    else if (kt1==KPAIR_TYPE_TURN    && kt2==KPAIR_TYPE_TURN    && kt3==KPAIR_TYPE_TURN   )
        g = CreateGroup((KPTurn *)K1,    (KPTurn *)K2,    (KPTurn *)K3,    s1, s2);

    g->name = name;
    return g;
}
