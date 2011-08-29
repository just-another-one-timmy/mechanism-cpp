//TODO!
// Сохранение признаков у всех групп!

#include "XMLSaver.h"

CompManager  *XMLSaver::cm;
GroupManager *XMLSaver::gm;

void XMLSaver::SetManagers(CompManager *c, GroupManager *g)
{
    cm = c;
    gm = g;
}

void XMLSaver::Save(string filename)
{
    TiXmlDocument doc;
    TiXmlElement *mech = new TiXmlElement("Mechanism");
    doc.LinkEndChild(mech);

    mech->SetDoubleAttribute("step_size", gm->GetStepSize());
    mech->SetDoubleAttribute("min", gm->GetMinGC());
    mech->SetDoubleAttribute("max", gm->GetMaxGC());

    string js = gm->GetJump()?"yes":"no";
    mech->SetAttribute("jump",js);

    map<string, Segment*> segments = cm->GetSegments();
    map<string, KPair*> kpairs = cm->GetKPairs();
    for (map<string, Segment *>::iterator i = segments.begin(); i != segments.end(); i++)
    {
        SaveSegment(i->second, mech);
    }

    TiXmlElement *kse = new TiXmlElement("KPairs");
    for (map<string, KPair *>::iterator i = kpairs.begin(); i != kpairs.end(); i++)
    {
        SaveKPair(i->second, kse);
    }

    mech->LinkEndChild(kse);


    TiXmlElement *gr = new TiXmlElement("Groups");
    gr->SetAttribute("need_analyze","no");

    list <Group*> groups = gm->groups;
    for (list <Group*>::iterator i = groups.begin(); i != groups.end(); i++)
    {
        Group *g = *i;
        SaveGroup(g, gr);
    }

    mech->LinkEndChild(gr);
    doc.SaveFile(filename);
}

void XMLSaver::SaveSegment(Segment *s, TiXmlElement *m)
{
    TiXmlElement *se = new TiXmlElement("Segment");
    se->SetAttribute("name", s->name);
    se->SetDoubleAttribute("mass", s->mass);
    se->SetDoubleAttribute("rot_inertia", s->rot_inertia);

    for (list <Connector *>::iterator i = s->connectors.begin(); i != s->connectors.end(); i++)
    {
        Connector *c = *i;
        if (c != s->polus)
            SaveConnector(c, se);
    }

    m->LinkEndChild(se);
}

void XMLSaver::SaveConnector(Connector *c, TiXmlElement *se)
{
    TiXmlElement *ce;
    CONNECTOR_TYPE ct = c->Type();
    switch (ct)
    {
        case CONNECTOR_TYPE_SLIDING:
        {
            ce = new TiXmlElement("ConnectorSliding");
            ConnectorSliding *cs = (ConnectorSliding *)c;
            ce->SetAttribute("name", cs->name);
            ce->SetDoubleAttribute("ro", cs->ro);
            ce->SetDoubleAttribute("phi", cs->phi);
            ce->SetDoubleAttribute("alpha", cs->alpha);
            break;
        }
        case CONNECTOR_TYPE_TURN:
        {
            ce = new TiXmlElement("ConnectorTurn");
            ConnectorTurn *ct = (ConnectorTurn *)c;
            ce->SetAttribute("name", ct->name);
            ce->SetDoubleAttribute("ro", ct->ro);
            ce->SetDoubleAttribute("phi", ct->phi);
            break;
        }
    }
    se->LinkEndChild(ce);
}

void XMLSaver::SaveKPair(KPair *k, TiXmlElement *kse)
{
    TiXmlElement *ke;
    KPAIR_TYPE kpt = k->Type();
    switch(kpt)
    {
        case KPAIR_TYPE_SLIDING:
        {
            ke = new TiXmlElement("KPSliding");
            KPSliding *ks = (KPSliding *)k;
            ke->SetAttribute("name", ks->name);
            ke->SetAttribute("c1_name", ks->GetC1()->name);
            ke->SetAttribute("c2_name", ks->GetC2()->name);
            break;
        }
        case KPAIR_TYPE_TURN:
        {
            ke = new TiXmlElement("KPTurn");
            KPTurn *kt = (KPTurn *)k;
            ke->SetAttribute("name", kt->name);
            ke->SetAttribute("c1_name", kt->GetC1()->name);
            ke->SetAttribute("c2_name", kt->GetC2()->name);
            break;
        }
    }
    kse->LinkEndChild(ke);
}

void XMLSaver::SaveGroup(Group *g, TiXmlElement *gre)
{
    GROUP_TYPE gt = g->Type();
    switch (gt)
    {
        case GROUP_TYPE_S: SaveGroupS((GroupS *)g, gre); break;
        case GROUP_TYPE_T: SaveGroupT((GroupT *)g, gre); break;
        case GROUP_TYPE_STS: SaveGroupSTS((GroupSTS *)g, gre); break;
        case GROUP_TYPE_TSS: SaveGroupTSS((GroupTSS *)g, gre); break;
        case GROUP_TYPE_TST: SaveGroupTST((GroupTST *)g, gre); break;
        case GROUP_TYPE_TTS: SaveGroupTTS((GroupTTS *)g, gre); break;
        case GROUP_TYPE_TTT: SaveGroupTTT((GroupTTT *)g, gre); break;
    }
}

void XMLSaver::SaveGroupS(GroupS* g, TiXmlElement *gre)
{
    TiXmlElement *ge = new TiXmlElement("Group1");
    ge->SetAttribute("kp_name", g->O->name);
    ge->SetAttribute("s1_name", g->s0->name);
    ge->SetAttribute("s2_name", g->s1->name);
    gre->LinkEndChild(ge);
}

void XMLSaver::SaveGroupT(GroupT* g, TiXmlElement *gre)
{
    TiXmlElement *ge = new TiXmlElement("Group1");
    ge->SetAttribute("kp_name", g->O->name);
    ge->SetAttribute("s1_name", g->s0->name);
    ge->SetAttribute("s2_name", g->s1->name);
    gre->LinkEndChild(ge);
}
void XMLSaver::SaveGroupSTS(GroupSTS* g, TiXmlElement *gre)
{
    TiXmlElement *ge = new TiXmlElement("Group2");
    ge->SetAttribute("kp1_name", g->A->name);
    ge->SetAttribute("kp2_name", g->B->name);
    ge->SetAttribute("kp3_name", g->C->name);
    ge->SetAttribute("s1_name", g->s1->name);
    ge->SetAttribute("s2_name", g->s2->name);
    gre->LinkEndChild(ge);
}
void XMLSaver::SaveGroupTSS(GroupTSS* g, TiXmlElement *gre)
{
    TiXmlElement *ge = new TiXmlElement("Group2");
    ge->SetAttribute("kp1_name", g->A->name);
    ge->SetAttribute("kp2_name", g->B->name);
    ge->SetAttribute("kp3_name", g->C->name);
    ge->SetAttribute("s1_name", g->s1->name);
    ge->SetAttribute("s2_name", g->s2->name);
    gre->LinkEndChild(ge);
}
void XMLSaver::SaveGroupTST(GroupTST* g, TiXmlElement *gre)
{
    TiXmlElement *ge = new TiXmlElement("Group2");
    ge->SetAttribute("kp1_name", g->A->name);
    ge->SetAttribute("kp2_name", g->B->name);
    ge->SetAttribute("kp3_name", g->C->name);
    ge->SetAttribute("s1_name", g->s1->name);
    ge->SetAttribute("s2_name", g->s2->name);
    gre->LinkEndChild(ge);
}

void XMLSaver::SaveGroupTTS(GroupTTS* g, TiXmlElement *gre)
{
    TiXmlElement *ge = new TiXmlElement("Group2");
    ge->SetAttribute("kp1_name", g->A->name);
    ge->SetAttribute("kp2_name", g->B->name);
    ge->SetAttribute("kp3_name", g->C->name);
    ge->SetAttribute("s1_name", g->s1->name);
    ge->SetAttribute("s2_name", g->s2->name);
    ge->SetAttribute("sign1", g->Getj1());
    ge->SetAttribute("sign2", g->Getj2());
    gre->LinkEndChild(ge);
}

void XMLSaver::SaveGroupTTT(GroupTTT* g, TiXmlElement *gre)
{
    TiXmlElement *ge = new TiXmlElement("Group2");
    ge->SetAttribute("kp1_name", g->A->name);
    ge->SetAttribute("kp2_name", g->B->name);
    ge->SetAttribute("kp3_name", g->C->name);
    ge->SetAttribute("s1_name", g->s1->name);
    ge->SetAttribute("s2_name", g->s2->name);
    ge->SetAttribute("sign1", g->Getj1());
    gre->LinkEndChild(ge);
}

