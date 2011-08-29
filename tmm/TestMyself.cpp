#include "TestMyself.h"
void PrintSegmentInfo(Segment *s, bool extended, int level)
{
    string fmt = string(level+1,'\t');
    cout << "." << string(level,'\t') << "Testing segment" << endl;
    cout << fmt << "Name: " << s->name <<endl;
    if (!extended) return;
    cout << fmt << "Connectors count: " << s->connectors.size() << endl;

    int k = 0;
    for (list<Connector*>::iterator i = s->connectors.begin(); i!=s->connectors.end(); i++)
    {
        Connector* c = *i;
        cout << endl << fmt << "Connector #" << k << endl;
        PrintConnectorInfo(c, false, level+1);
        k++;
    }

    cout << fmt << "Center of mass: " << endl;
    PrintConnectorInfo(s->cmass, false, level+1);

    cout << fmt << "Forces count: " << s->forces.size() << endl;

    k = 0;
    for (list<Force*>::iterator i = s->forces.begin(); i!=s->forces.end(); i++)
    {
        Force *f = *i;
        cout  << endl << fmt << "Force #" << k << endl;
        PrintForceInfo(f, false, level+1);
        k++;
    }
}

void PrintConnectorInfo(Connector *c, bool extended, int level)
{
    string fmt = string(level+1, '\t');
    cout << "." << string(level,'\t') << "Testing connector" << endl;
    if (c!=NULL)
    {
        cout << fmt << "Name: " << c->name << endl;
        if (!extended) return;
        cout << fmt << "Parent's name: " << c->s->name << endl;
        cout << fmt << "Ro = " << c->ro << endl;
        cout << fmt << "Phi = " << c->phi << endl;

        string ctype;
        switch (c->Type())
        {
            case CONNECTOR_TYPE_SLIDING:
            {
                ctype = "CONNECTOR_TYPE_SLIDING";
                cout << fmt << "Alpha = " << ((ConnectorSliding*)c)->alpha << endl;
                break;
            }
            case CONNECTOR_TYPE_TURN: ctype = "CONNECTOR_TYPE_TURN"; break;
            default: ctype = "CONNECTOR_TYPE_UNKNOWN";
        }
        cout << fmt << "Type: " << ctype << endl;
    }
    else cout << fmt << "NULL POINTER!" << endl;
}

void PrintForceInfo(Force *f, bool extended, int level)
{
    string fmt(level+1, '\t');
    cout << "." << string(level,'\t') << "Testing force" << endl;
    cout << fmt << "Force's name: " << f->GetName() << endl;
    if (!extended) return;
    //
    //
    //
}

void PrintKPTurnInfo(KPTurn *K, bool extended, int level)
{
    string fmt(level+1, '\t');
    cout << fmt << "Type: " << "KPAIR_TYPE_TURN" << endl;
    cout << fmt << "Connectors: " << endl;
    cout << fmt << "c1: " << endl;
    PrintConnectorInfo(K->GetC1(), level+1);
    cout << fmt << "c2: " << endl;
    PrintConnectorInfo(K->GetC2(), level+1);
}

void PrintKPSlidingInfo(KPSliding *K, bool extended, int level)
{
    string fmt(level+1, '\t');
    cout << fmt << "Type: " << "KPAIR_TYPE_SLIDING" << endl;
    cout << fmt << "Connectors: " << endl;
    cout << fmt << "c1: " << endl;
    PrintConnectorInfo(K->GetC1(), level+1);
    cout << fmt << "c2: " << endl;
    PrintConnectorInfo(K->GetC1(), level+1);
}

void PrintKPInfo(KPair *K, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << "." << string(level,'\t') << "Testing KPair" << endl;
    cout << fmt << "Name: " << K->name << endl;
    if (!extended) return;
    string kptype;
    switch (K->Type())
    {
        case KPAIR_TYPE_TURN:    PrintKPTurnInfo   ((KPTurn *)K,    false, level);   break;
        case KPAIR_TYPE_SLIDING: PrintKPSlidingInfo((KPSliding *)K, false, level); break;
    }
}

void PrintCompManagerInfo(CompManager *cm, int level)
{
    string fmt(level+1,'\t');
    cout << "." << string(level,'\t') << "Testing CompManager" << endl;

    int k;

    cout << fmt << "Segments   count: " << cm->segments.size()   << endl;
    cout << fmt << "Kpairs     count: " << cm->kpairs.size()     << endl;
    cout << fmt << "Connectors count: " << cm->connectors.size() << endl;

    cout << endl;
    cout << fmt << "Testing segments: " << endl;
    k=0;
    for (map <string, Segment *>::iterator i = cm->segments.begin(); i!=cm->segments.end(); i++)
    {
        cout << fmt << "Segment #" << k << endl;
        PrintSegmentInfo(i->second, false, level+1);
        k++;
    }

    cout << endl;
    cout << fmt << "Testing KPairs: " << endl;
    k=0;
    for (map <string, KPair *>::iterator i = cm->kpairs.begin(); i!=cm->kpairs.end(); i++)
    {
        cout  << fmt << "KPair #" << k << endl;
        PrintKPInfo(i->second, false, level+1);
        k++;
    }

    cout << endl;
    cout << fmt << "Testing connectors: " << endl;
    k=0;
    for (map <string, Connector *>::iterator i = cm->connectors.begin(); i!=cm->connectors.end(); i++)
    {
        cout << fmt << "Connector #" << k << endl;
        PrintConnectorInfo(i->second, false, level+1);
        k++;
    }
}

void PrintGroupSInfo(GroupS *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << fmt << "Formula: " << "S" << endl;
    if (!extended) return;
    cout << fmt << "KPair: " << endl;
    PrintKPInfo(((GroupS *)g)->O, false, level+1);
}

void PrintGroupTInfo(GroupT *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << fmt << "Formula: " << "T" << endl;
    if (!extended) return;
    cout << fmt << "KPair: " << endl;
    PrintKPInfo(((GroupT *)g)->O, false, level+1);
}


void PrintGroup1Info(Group1 *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    switch (g->Type())
    {
        case GROUP_TYPE_S: PrintGroupSInfo((GroupS *)g, extended, level); break;
        case GROUP_TYPE_T: PrintGroupTInfo((GroupT *)g, extended, level); break;
        default: ;
    }
    cout << fmt << "Segment#0: " << endl;
    PrintSegmentInfo(g->s0, false, level+1);
    cout << fmt << "Segment#0: " << endl;
    PrintSegmentInfo(g->s1, false, level+1);
}

void PrintGroupSTSInfo(GroupSTS *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << fmt << "Formula: " << "STS" << endl;
    if (!extended) return;
     cout << fmt << "h1=" << g->h1 << endl;
    cout << fmt << "h2=" << g->h2 << endl;

    cout << fmt << "Connector s0cA " << endl;
    PrintConnectorInfo(g->s0cA, level+1);

    cout << fmt << "Connector s1cA " << endl;
    PrintConnectorInfo(g->s1cA, level+1);
    cout << fmt << "Connector s1cB " << endl;
    PrintConnectorInfo(g->s1cB, level+1);
    cout << fmt << "Connector s2cB " << endl;
    PrintConnectorInfo(g->s2cB, level+1);
    cout << fmt << "Connector s2cC " << endl;
    PrintConnectorInfo(g->s2cC, level+1);

    cout << fmt << "Connector s0cC " << endl;
    PrintConnectorInfo(g->s0cC, level+1);


    cout << fmt << "KPair #0: " << endl;
    PrintKPInfo(g->A, false, level+1);
    cout << fmt << "KPair #1: " << endl;
    PrintKPInfo(g->B, false, level+1);
    cout << fmt << "KPair #2: " << endl;
    PrintKPInfo(g->C, false, level+1);
}

void PrintGroupTSSInfo(GroupTSS *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << fmt << "Formula: " << "TSS" << endl;
    if (!extended) return;

       cout << fmt << "h=" << g->h << endl;
    cout << fmt << "alfa=" << g->alfa<< endl;


    cout << fmt << "Connector s1cA " << endl;
    PrintConnectorInfo(g->s1cA, level+1);
    cout << fmt << "Connector s1cB " << endl;
    PrintConnectorInfo(g->s1cB, level+1);
    cout << fmt << "Connector s2cB " << endl;
    PrintConnectorInfo(g->s2cB, level+1);
    cout << fmt << "Connector s2cC " << endl;
    PrintConnectorInfo(g->s2cC, level+1);
    cout << fmt << "Connector s0cC " << endl;
    PrintConnectorInfo(g->s0cC, level+1);

    cout << fmt << "KPair #0: " << endl;
    PrintKPInfo(g->A, false, level+1);
    cout << fmt << "KPair #1: " << endl;
    PrintKPInfo(g->B, false, level+1);
    cout << fmt << "KPair #2: " << endl;
    PrintKPInfo(g->C, false, level+1);
}

void PrintGroupTSTInfo(GroupTST *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << fmt << "Formula: " << "TST" << endl;
    if (!extended) return;

    cout << fmt << "h1=" << g->h1 << endl;
    cout << fmt << "h2=" << g->h2 << endl;
    cout << fmt << "Connector s1cA " << endl;
    PrintConnectorInfo(g->s1cA, level+1);
    cout << fmt << "Connector s1cB " << endl;
    PrintConnectorInfo(g->s1cB, level+1);
    cout << fmt << "Connector s2cB " << endl;
    PrintConnectorInfo(g->s2cB, level+1);
    cout << fmt << "Connector s2cC " << endl;
    PrintConnectorInfo(g->s2cC, level+1);


    cout << fmt << "KPair #0: " << endl;
    PrintKPInfo(g->A, false, level+1);
    cout << fmt << "KPair #1: " << endl;
    PrintKPInfo(g->B, false, level+1);
    cout << fmt << "KPair #2: " << endl;
    PrintKPInfo(g->C, false, level+1);
}

void PrintGroupTTSInfo(GroupTTS *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << fmt << "Formula: " << "TTS" << endl;
    if (!extended) return;

     cout << fmt << "lab=" << g->lab << endl;
    cout << fmt << "h=" << g->h << endl;
    cout << fmt << "Connector s1cA " << endl;
    PrintConnectorInfo(g->s1cA, level+1);
    cout << fmt << "Connector s1cB " << endl;
    PrintConnectorInfo(g->s1cB, level+1);
    cout << fmt << "Connector s2cB " << endl;
    PrintConnectorInfo(g->s2cB, level+1);
    cout << fmt << "Connector s2cC " << endl;
    PrintConnectorInfo(g->s2cC, level+1);
    cout << fmt << "Connector s0cC " << endl;
    PrintConnectorInfo(g->s0cC, level+1);

    cout << fmt << "KPair #0: " << endl;
    PrintKPInfo(g->A, false, level+1);
    cout << fmt << "KPair #1: " << endl;
    PrintKPInfo(g->B, false, level+1);
    cout << fmt << "KPair #2: " << endl;
    PrintKPInfo(g->C, false, level+1);
}

void PrintGroupTTTInfo(GroupTTT *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << fmt << "Formula: " << "TTT" << endl;
    if (!extended) return;

    cout << fmt << "lab=" << g->lab << endl;
    cout << fmt << "lcb=" << g->lcb << endl;
    cout << fmt << "Connector s1cA " << endl;
    PrintConnectorInfo(g->s1cA, level+1);
    cout << fmt << "Connector s1cB " << endl;
    PrintConnectorInfo(g->s1cB, level+1);
    cout << fmt << "Connector s2cB " << endl;
    PrintConnectorInfo(g->s2cB, level+1);
    cout << fmt << "Connector s2cC " << endl;
    PrintConnectorInfo(g->s2cC, level+1);


    cout << fmt << "KPair #0: " << endl;
    PrintKPInfo(g->A, false, level+1);
    cout << fmt << "KPair #1: " << endl;
    PrintKPInfo(g->B, false, level+1);
    cout << fmt << "KPair #2: " << endl;
    PrintKPInfo(g->C, false, level+1);
}

void PrintGroup2Info(Group2 *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    string formula = "";

    switch (g->Type())
    {
        case GROUP_TYPE_STS: PrintGroupSTSInfo((GroupSTS *)g, extended, level); break;
        case GROUP_TYPE_TSS: PrintGroupTSSInfo((GroupTSS *)g, extended, level); break;
        case GROUP_TYPE_TST: PrintGroupTSTInfo((GroupTST *)g, extended, level); break;
        case GROUP_TYPE_TTS: PrintGroupTTSInfo((GroupTTS *)g, extended, level); break;
        case GROUP_TYPE_TTT: PrintGroupTTTInfo((GroupTTT *)g, extended, level); break;
        default: break;
    }

    if (!extended) return;
    cout << fmt << "Segment: #0" << endl;
    PrintSegmentInfo(g->s1, false, level+1);
    cout << fmt << "Segment: #1" << endl;
    PrintSegmentInfo(g->s2, false, level+1);
}

void PrintGroupInfo(Group *g, bool extended, int level)
{
    string fmt(level+1,'\t');
    cout << "." << string(level,'\t') << "Testing group" << endl;
    cout << fmt << "Group name: " << g->name << endl;
    int cl = g->GetClass();
    cout << fmt << "Class = " << cl << endl;
    if (!extended) return;
    switch (cl)
    {
        case 1: PrintGroup1Info((Group1 *)g, extended, level); break;
        case 2: PrintGroup2Info((Group2 *)g, extended, level); break;
        default: cout << "Unkown group class!" << endl;
    }
}

void PrintGroupsInfo(GroupManager &gm)
{
    for (list<Group *>::iterator i = gm.groups.begin(); i != gm.groups.end(); i++)
    {
        Group *g = *i;
        if (g!=NULL)
        PrintGroupInfo(g,true);
    }
}
