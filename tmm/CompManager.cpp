#include "CompManager.h"

using namespace std;

CompManager::~CompManager()
{
    for (map<string, Segment *>::iterator i = segments.begin(); i!=segments.end(); i++)
    {
        Segment *s = i->second;
        for (list<Connector *>::iterator c = s->connectors.begin(); c!=s->connectors.end(); c++)
        {
            Connector *x = *c;
            connectors.erase(x->name);
        }
        delete i->second;
    }
    for (map<string, Connector *>::iterator i = connectors.begin(); i!=connectors.end(); i++)
    {
        delete i->second;
    }
    for (map<string, KPair *>::iterator i = kpairs.begin(); i!=kpairs.end(); i++)
    {
        delete i->second;
    }
    segments.clear();
    connectors.clear();
    kpairs.clear();
    forces.clear();
}

Segment * CompManager::AddSegment(string name, double mass, double rot_inertia)
{
    Segment *s = new Segment;
    s->name = name;
    s->mass = mass;
    s->rot_inertia = rot_inertia;

    segments[name] = s;

    s->polus = (ConnectorTurn *)AddConnectorTurn(name+"cP", name, 0, 0);

    LinearTF *linearTF = new LinearTF;
    s->polus->linear = linearTF;
    return s;
}

Segment * CompManager::GetSegment(string name)
{
    map <string, Segment *>::iterator i = segments.find(name);
    return i->second;
}

void CompManager::DelSegment(string name)
{
    map <string, Segment *>::iterator i = segments.find(name);
    Segment *s = i->second;

    for (list<Connector *>::iterator c = s->connectors.begin(); c!=s->connectors.end(); i++)
    {
        Connector *x = *c;
        connectors.erase(x->name);
    }

    delete s;
    segments.erase(i);
}

KPair * CompManager::GetKPair(string name)
{
    map <string, KPair *>::iterator i = kpairs.find(name);
    return i->second;
}

void CompManager::DelKPair(string name)
{
    map <string, KPair *>::iterator i = kpairs.find(name);
    delete i->second;
    kpairs.erase(i);
}

Connector * CompManager::AddConnectorTurn(string name, string segment_name, double ro, double phi)
{
    Connector *c = new ConnectorTurn;
    c->name = name;

    Segment       *s = segments.find(segment_name)->second;
    // добавляем коннектор в список нужного звена
    s->connectors.push_back(c);

    connectors.insert(pair<string, Connector *>(name, c));

    c->s = s;
    c->ro = ro;
    c->phi = phi;
    return c;
}

Connector * CompManager::AddConnectorTurnD(string name, string segment_name, double x, double y)
{
    double ro, phi;
    ro=sqrt(sqr(x)+sqr(y));
    phi=atan2(y,x);
    return AddConnectorTurn(name, segment_name, ro, phi);
}


Connector * CompManager::AddConnectorSliding(string name, string segment_name, double ro, double phi, double alpha)
{
    ConnectorSliding *c = new ConnectorSliding;
    c->name = name;
    Segment          *s = segments.find(segment_name)->second;
    s->connectors.push_back(c);

    connectors.insert(pair<string, Connector *>(name, c));

    c->s = s;
    c->ro = ro;
    c->phi = phi;
    c->alpha = alpha;

    TurnTF *turnTF = new TurnTF;
    c->turn = turnTF;
    return c;
}

Connector * CompManager::AddConnectorSlidingD(string name, string segment_name, double x, double y, double alpha)
{
    double ro,phi;
    ro=sqrt(sqr(x)+sqr(y));
    phi=atan2(y,x);
    return AddConnectorSliding(name, segment_name, ro, phi,alpha);
}

Connector * CompManager::GetConnector(string name)
{
    map <string, Connector *>::iterator i = connectors.find(name);
    Connector *c = i->second;
    return c;
}

void CompManager::DelConnector(string name)
{
    map <string, Connector *>::iterator i = connectors.find(name);
    Connector *c = i->second;
    Segment   *s = c->s;

    //удаляем коннектор из списка нужного звена
    s->connectors.remove(c);
    //удаляем коннектор из списка менеджера
    connectors.erase(i);
    //освобождаем память
    delete c;
}

KPair * CompManager::AddKPTurn(string name, string c1name, string c2name)
{
    map <string, Connector *>::iterator i1, i2;
    i1 = connectors.find(c1name);
    i2 = connectors.find(c2name);


    if ( (i1->second)->Type() != CONNECTOR_TYPE_TURN )
    {
        throw "AddKPTurn: i1->second->Type() != CONNECTOR_TYPE_TURN";
    }

    if ( (i2->second)->Type() != CONNECTOR_TYPE_TURN )
    {
        throw "AddKPTurn: i2->second->Type() != CONNECTOR_TYPE_TURN";
    }

    ConnectorTurn *c1 = (ConnectorTurn *) i1->second;
    ConnectorTurn *c2 = (ConnectorTurn *) i2->second;

    KPair *K = new KPTurn(name, c1, c2);
    kpairs.insert(pair<string, KPair *>(name, K));
    forces.insert(pair<string, Force *>(K->R1->GetName(), K->R1));
    forces.insert(pair<string, Force *>(K->R2->GetName(), K->R2));

    return K;
}

KPair * CompManager::AddKPSliding(string name, string c1name, string c2name)
{
    map <string, Connector *>::iterator i1 = connectors.find(c1name);
    map <string, Connector *>::iterator i2 = connectors.find(c2name);

    if ( (i1->second)->Type() != CONNECTOR_TYPE_SLIDING )
    {
        throw "AddKPSliding: i1->second->Type() != CONNECTOR_TYPE_SLIDING";
    }
    ConnectorSliding *c1 = (ConnectorSliding *) i1->second;

    if ( (i2->second)->Type() != CONNECTOR_TYPE_SLIDING )
    {
        throw "AddKPSliding: i2->second->Type() != CONNECTOR_TYPE_SLIDING";
    }
    ConnectorSliding *c2 = (ConnectorSliding *) i2->second;

    KPair *K = new KPSliding(name, c1, c2);
    kpairs.insert(pair<string, KPair *>(name, K));
    forces.insert(pair<string, Force *>(K->R1->GetName(), K->R1));
    forces.insert(pair<string, Force *>(K->R2->GetName(), K->R2));

    return K;
}

Connector * CompManager::AddCMass(string seg_name, double ro, double phi)
{
    // CHANGE
    string cname = seg_name + "cS";
    Connector *c = AddConnectorTurn(cname, seg_name, ro, phi);
    GetSegment(seg_name)->cmass = (ConnectorTurn*)c;

    LinearTF * linearTF = new LinearTF;
    ((ConnectorTurn*)c)->linear = linearTF;

    ConnectorTurn* ct;
    ct = (ConnectorTurn *)c;
    float grav=-9.81;
    Force *f = new Force("G_" + seg_name, FORCE_TYPE_GRAVITY, ct);
    f->SetForce(0,grav*GetSegment(seg_name)->mass,0);
    forces.insert(pair<string, Force *>("G_" + seg_name, f));
    f->linear = ct->linear;

    return c;
}

Force * CompManager::AddTechnoForce(string name, string con_name, double fx, double fy, double torque)
{
    Connector *c = GetConnector(con_name);
    ConnectorTurn *ct;
    if (c->Type() != CONNECTOR_TYPE_TURN)
    {
        throw ("Force * CompManager::AddTechnoForce: c->Type() != CONNECTOR_TYPE_TURN");
    }
    ct = (ConnectorTurn *)c;

    Force *f = new Force(name, FORCE_TYPE_TECHNO, ct);
    f->SetForce(fx,fy,torque);
    forces.insert(pair<string, Force *>(name, f));

    Segment   *s = ct->s;

    f->linear = ct->linear;
    f->turn   = &(s->turn);

    return f;
}

Force * CompManager::GetForce(string name)
{
    map<string, Force *>::iterator i = forces.find(name);
    return i->second;
}

void CompManager::DelTechnoForce(string name)
{
    map<string, Force *>::iterator i = forces.find(name);

    Force *f = i->second;
    Segment *s = f->GetConnector()->s;
    s->forces.remove(f);

    forces.erase(i);
    delete f;
}

void CompManager::UnsetCalculated()
{
    for (map<string, Connector *>::iterator i = connectors.begin(); i!=connectors.end(); i++)
    {
        Connector *c = i->second;
        switch (c->Type())
        {
            case CONNECTOR_TYPE_SLIDING:
            {
                ConnectorSliding *cs = (ConnectorSliding *)c;
                cs->linear0.UnsetCalculated();
                cs->turn->UnsetCalculated();
                break;
            }
            case CONNECTOR_TYPE_TURN:
            {
                ConnectorTurn *ct = (ConnectorTurn *)c;
                ct->linear->UnsetCalculated();
                break;
            }
        }
    }
for (map<string, Segment *>::iterator i = segments.begin(); i!=segments.end(); i++)
    {
        Segment *s = i->second;
        for (list<Force *>::iterator f = s->forces.begin(); f!=s->forces.end(); f++)
        {
            Force  *x = *f;
            x->UnsetCalculated();
        }

    }
}

const map<string, Segment *> CompManager::GetSegments()
{
    return segments;
}

const map<string, KPair*> CompManager::GetKPairs()
{
    return kpairs;
}
/*
bool CompManager::LoadXml(string filename)
{
    TiXmlDocument *doc = new TiXmlDocument(filename.c_str());
    bool LoadOkay = doc->LoadFile();
    if (!LoadOkay)
        return false;
    RecAnalyze(doc);
    delete doc;
}

void CompManager::ProcessXmlElem(TiXmlElement* pElem)
{
	if ( !pElem) return;

	TiXmlAttribute* pAttrib=pElem->FirstAttribute();
	int i=0;
	int ival;
	double dval;
	printf("\n");
	while (pAttrib)
	{
		printf( "%s: value=[%s]", pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
		printf( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	return;
}

void CompManager::RecAnalyze(TiXmlNode *pParent)
{
    if (!pParent)
        return;
    if (pParent->Type() == TiXmlNode::TINYXML_ELEMENT)
    {
        ProcessXmlElem(pParent->ToElement());
    }
    for (TiXmlNode *pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
    {
        RecAnalyze(pChild);
    }
}
*/
CompManager::CompManager()
{
}
