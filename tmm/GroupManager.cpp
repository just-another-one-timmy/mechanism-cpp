#include "GroupManager.h"

GroupManager::GroupManager(CompManager *cm)
{
    this->cm = cm;
    mingc = 0;
    maxgc = 0;
    jump = true;
    move_forward = true;
}

void GroupManager::AddFirstGroupByName(string KPName, string SegmentName1, string SegmentName2)
{
    map<string, Segment*> segments = cm->GetSegments();
    map<string, KPair*> kpairs = cm->GetKPairs();
    Segment *S1  = segments.find(SegmentName1)->second;
    Segment *S2  = segments.find(SegmentName2)->second;
    KPair *firstK = kpairs.find(KPName)->second;

    groups.push_back(GroupBuilder::CreateGroup("("+S1->name+","+S2->name+")",firstK, S1, S2));

    AddBlackEdge(firstK);
    AddBlackVertex(S1);
    AddBlackVertex(S2);
}

void GroupManager::AddGround(string GroundName)
{
    map<string, Segment*> segments = cm->GetSegments();
    Segment *groundS = segments.find(GroundName)->second;
    AddBlackVertex(groundS);
}

void GroupManager::Analyze()
{
    map<string, Segment*> segments = cm->GetSegments();
    map<string, KPair*> kpairs = cm->GetKPairs();

    int edges_count = kpairs.size();
    int vertexes_count = segments.size();
    while (black_vertexes.size() != vertexes_count  &&  black_edges.size() != edges_count)
    {
        vector <Segment *> path;
        for (set <Segment *>::iterator i = black_vertexes.begin(); i!=black_vertexes.end(); i++)
        {
            Segment *s = *i;
            path.push_back(s);
            FindPath(path, 2);
            path.pop_back();
        }
    }
}

void GroupManager::AddBlackEdge(KPair *K)
{
    black_edges.insert(K);
}

void GroupManager::AddBlackVertex(Segment *s)
{
    black_vertexes.insert(s);
}

void GroupManager::BuildEdgesSets()
{
    map<string, KPair*> kpairs = cm->GetKPairs();

    for (map<string, KPair *>::iterator i = kpairs.begin(); i != kpairs.end(); i++)
    {
        KPair *k = i->second;
        Segment *s1, *s2;
        s1 = k->GetC1()->s;
        s2 = k->GetC2()->s;
        edges[s1].insert(k);
        edges[s2].insert(k);
    }
}

void GroupManager::FindPath(vector <Segment *> path, int len)
{
    if (len==-1)
    {
        ProcessPath(path);
        return;
    }
    Segment *s = path.back();

    map<string, Segment*> segments = cm->GetSegments();

    bool find_black = (len == 0); // последняя вершина - черная
    for (map <string, Segment *>::iterator i = segments.begin(); i != segments.end(); i++)
        {
            Segment *next_s = i->second;
            bool in_path = find(path.begin(), path.end(), next_s) != path.end();
            if (!in_path &&                                                       // вершина не встречалась еще
                ((black_vertexes.find(next_s)!=black_vertexes.end())              // и имеет нужный
                                                                    ==find_black) // цвет
            )
            {

                if (common_edges(s, next_s).size()!=0)
                {
                    // пока что считаю, что у вершин могут быть неск. соединяющих их ребер
                    // в нормальном же механизме common_edges.size()<=1 (не мультиграф)
                    path.push_back(next_s);
                    FindPath(path, len-1);
                    path.pop_back();
                }
            }
        }
}

void GroupManager::ProcessPath(vector <Segment *> path)
{
    int len = path.size();
    KPair *k[len-1];
    for (int i=1; i<len; i++)
    {
        set <KPair *> ce = common_edges(path[i], path[i-1]);
        KPair *ke = *(ce.begin());
        k[i-1] = ke;
        black_edges.insert(k[i-1]);
        black_vertexes.insert(path[i-1]);
    }
    black_vertexes.insert(path[len-1]);

    switch (len)
    {
        case 4: AddSecondGroup(k[0], k[1], k[2], path[1], path[2]); break;
        default: throw("Не могу обработать группу");
    }
}

set <KPair *> GroupManager::common_edges(Segment *s1, Segment *s2)
{
    set <KPair *> edges1, edges2;
    set <KPair *> edges3;

    if (edges.find(s1) != edges.end())
        edges1 = edges[s1];
    if (edges.find(s2) != edges.end())
        edges2 = edges[s2];

    /*
    cout << "Edges 1: " << endl;
    for (set <KPair *>::iterator i = edges1.begin(); i!=edges1.end(); i++)
    {
        KPair *k = *i;
        cout << k->name << endl;
    }
    cout << "Edges 2: " << endl;
    for (set <KPair *>::iterator i = edges2.begin(); i!=edges2.end(); i++)
    {
        KPair *k = *i;
        cout << k->name << endl;
    }
    */

    set_intersection(edges1.begin(), edges1.end(),
                     edges2.begin(), edges2.end(),
                     inserter(edges3, edges3.begin()));

    /*
    cout << "Common edges: " << endl;
    for (set <KPair *>::iterator i = edges3.begin(); i!=edges3.end(); i++)
    {
        KPair *k = *i;
        cout << k->name << endl;
    }
    */

    return edges3;
}

void GroupManager::AddSecondGroup(KPair *k1, KPair *k2, KPair *k3, Segment *s1, Segment *s2)
{
    /*
    cout << "Now creating group " << endl;
    cout << "k1: " << k1->name << endl;
    cout << "s1: " << s1->name << endl;
    cout << "k2: " << k2->name << endl;
    cout << "s2: " << s2->name << endl;
    cout << "k3: " << k3->name << endl;
    */
    Group *g = GroupBuilder::CreateGroup("("+s1->name+","+s2->name+")",k1,k2,k3,s1,s2);
    groups.push_back(g);
}


void GroupManager::CalcNextStep()
{
    for (list<Group *>::iterator i = groups.begin(); i != groups.end(); i++)
    {
        Group *g = *i;
        try
        {
            cout << g->name << endl;
            g->CalcTF0();
        }
        catch (const char *s) { cout << s << endl; };
        }
    cout << "----------------" << endl;
    for (list<Group *>::iterator i = groups.begin(); i != groups.end(); i++)
    {
        Group *g = *i;
        try
        {
            g->CalcTF1();
        }
        catch (const char *s) { cout << s << endl; };
    }
    for (list<Group *>::iterator i = groups.begin(); i != groups.end(); i++)
    {
        Group *g = *i;
        try
        {
            g->CalcTF2();
        }
        catch (const char *s) { cout << s << endl; };
    }
/*  for (list<Group *>::reverse_iterator i = gm.groups.rbegin(); i != gm.groups.rend(); i++)
    {
        Group *g = *i;
        try
        {
            //cout << g->name << endl;
            g->CalcReaction();
        }
        catch (const char *s) { cout << s << endl; };
    }*/
}

void GroupManager::SetStepSize(double s)
{
    if (s<0) s=-s;
    step_size = s;
}

double GroupManager::GetStepSize()
{
    return step_size;
}

void GroupManager::MakeStep()
{
    GroupT *g = (GroupT *)groups.front();
    double gc = g->GC;
    if (move_forward)
        gc += step_size;
    else
        gc -= step_size;
    cm->UnsetCalculated();
    if (move_forward && gc>maxgc)
    {
        if (jump)
            gc = mingc;
        else
            move_forward = false;
    }
    else if (!move_forward && gc<mingc)
    {
        move_forward = true;
    }
    g->GC = gc;
}

void GroupManager::AddSecondGroupByName(string KP1Name, string KP2Name, string KP3Name, string SegmentName1, string SegmentName2, signed char mj1, signed char mj2)
{
    map<string, Segment*> segments = cm->GetSegments();
    map<string, KPair*> kpairs = cm->GetKPairs();
    Segment *S1  = segments.find(SegmentName1)->second;
    Segment *S2  = segments.find(SegmentName2)->second;
    KPair *K1 = kpairs.find(KP1Name)->second;
    KPair *K2 = kpairs.find(KP2Name)->second;
    KPair *K3 = kpairs.find(KP3Name)->second;
    string gname = "("+S1->name+","+S2->name+")";
    Group2 *g = (Group2 *)GroupBuilder::CreateGroup(gname,K1, K2, K3, S1, S2);
    groups.push_back(g);
    g->Setj1(mj1);
    g->Setj2(mj2);
}

void GroupManager::SetMaxGC(double x)
{
    maxgc = x;
}

void GroupManager::SetMinGC(double x)
{
    mingc = x;
}

double GroupManager::GetMaxGC()
{
    return maxgc;
}

double GroupManager::GetMinGC()
{
    return mingc;
}
void GroupManager::SetJump(bool x)
{
    jump = x;
}
bool GroupManager::GetJump()
{
    return jump;
}
