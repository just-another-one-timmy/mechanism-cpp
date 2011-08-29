#include "XMLLoader.h"

CompManager  *XMLLoader::cm;
GroupManager *XMLLoader::gm;

void XMLLoader::Load(string filename)
{
    //TiXmlDocument *d = new TiXmlDocument(filename);
    TiXmlDocument doc(filename);
    TiXmlDocument *d = &doc;
    bool loadOk = d->LoadFile();
    if (loadOk)
    {
        cout << "xml successful loaded" << endl;
        cout << "Analyzing doc" << endl;
        AnalyzeDoc(d);
    }
    else
        cout << "Error while loading xml file [" << filename << "]" << endl;
}

void XMLLoader::SetManagers(CompManager *c, GroupManager *g)
{
    cm = c;
    gm = g;
}

void XMLLoader::AnalyzeDoc(TiXmlNode *node)
{
    TiXmlNode *c = node->FirstChild();
    AnalyzeNode(c);
    // ” узла сейчас может быть только один ребенок, иначе xml-документ имеет несколько
    // корневых элементов, а поэтому до сюда управление дойти не могло (TinyXml возвращал бы ошибку)
}

void XMLLoader::AnalyzeNode(TiXmlNode *node)
{
    int t = NodeNameToType(node->Value());
    switch (t)
    {
        case NT_MECHANISM: AnalyzeMechanism(node); break;
        case NT_SEGMENT: AnalyzeSegment(node); break;
        case NT_KPAIRS: AnalyzeKPairs(node); break;
        case NT_GROUPS: AnalyzeGroups(node); break;
        default: cout << "Unknown node " << node->Value() << endl;
    }
}

NODE_TYPE XMLLoader::NodeNameToType(string name)
{
    if (name=="Mechanism") return NT_MECHANISM;
    if (name=="Segment") return NT_SEGMENT;
    if (name=="KPairs") return NT_KPAIRS;
    if (name=="Groups") return NT_GROUPS;
    return NT_UNKNOWN;
}

void XMLLoader::AnalyzeMechanism(TiXmlNode *node)
{
    TiXmlNode *child;
    // здесь можно считывать еще какие-то параметры
    // например, им€ механизма <Mechanism name="Ўагоход „ебышева">
    // и т.д.

    // опа-па. “еперь это помогло и можно считать step_size!
    SetMechanismAttributes(node);

    for (child = node->FirstChild(); child != NULL; child = child->NextSibling())
        AnalyzeNode(child);
}

void XMLLoader::AnalyzeSegment(TiXmlNode *node)
{
    bool mass_found=false, rot_inertia_found=false, name_found=false;
    double mass, rot_inertia;
    string name;

    TiXmlAttribute *attr = node->ToElement()->FirstAttribute();
    while (attr != NULL)
    {
        string aname = attr->Name();
        string avalue = attr->Value();
        double dval;
        if (aname=="name")
        {
            name_found = true;
            name = avalue;
        }
        else if (aname=="mass")
        {
            mass_found = true;
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
                mass = dval;
            else cout << "Error! SetSegmentAttribute, name=mass, value=???" << endl;
        }
        else if (aname=="rot_inertia")
        {
            rot_inertia_found = true;
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
                rot_inertia = dval;
            else cout << "Error! SetSegmentAttribute, name=rot_inertia, value=???" << endl;
        }
        attr = attr->Next();
    }

    if (!name_found)
        cout << "segment's name not found!" << endl;
    else
    {
        if(mass_found)
        {
            if (rot_inertia_found)
                cm->AddSegment(name, mass, rot_inertia);
            else
                cm->AddSegment(name, mass);
        }
        else cm->AddSegment(name);
        cout << "segment added! (name: "<<name<<")" << endl;
    }

    // —ейчас будем добавл€ть коннекторы
    TiXmlNode *child = node->FirstChild();
    while (child != NULL)
    {
        AnalyzeConnector(child, name);
        child = child->NextSibling();
    }
}

void XMLLoader::AnalyzeKPairs(TiXmlNode *node)
{    // —ейчас будем добавл€ть кинематические пары
    TiXmlNode *child = node->FirstChild();
    while (child != NULL)
    {
        AnalyzeKPair(child);
        child = child->NextSibling();
    }
}

void XMLLoader::AnalyzeGroups(TiXmlNode *node)
{
    TiXmlElement *elem = node->ToElement();

    bool need_analyze=true;
    TiXmlAttribute *attr = elem->FirstAttribute();
    while (attr)
    {
        string aname = attr->Name();
        string aval  = attr->Value();
        if (aname == "need_analyze")
        {
            if (aval=="yes") need_analyze = true;
            if (aval=="no") need_analyze = false;
        }
        attr = attr->Next();
    }

    TiXmlNode *child = node->FirstChild();

    while (child)
    {
        AnalyzeGroup(child->ToElement());
        child = child->NextSibling();
    }

    if (need_analyze)
    {
        gm->BuildEdgesSets();
        gm->Analyze();
    }
}

void XMLLoader::AnalyzeConnector(TiXmlNode *node, string segment_name)
{
    if (!node) return;

    string name;
    double ro, phi, x, y, alpha;
    bool name_found=false, ro_found=false, phi_found=false, x_found=false, y_found=false, alpha_found=false;

    TiXmlAttribute *attr = node->ToElement()->FirstAttribute();
    while (attr != NULL)
    {
        string aname = attr->Name();
        string avalue = attr->Value();
        double dval;
        if (aname=="name")
        {
            name_found = true;
            name = avalue;
        }
        else if (aname=="ro")
        {
            ro_found = true;
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
                ro = dval;
            else cout << "Error! AnalyzeConnector, ro=???" << endl;
        }
        else if (aname=="phi")
        {
            phi_found = true;
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
                phi = dval;
            else cout << "Error! AnalyzeConnector, phi=???" << endl;

        }
        else if (aname=="x")
        {
            x_found = true;
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
                x = dval;
            else cout << "Error! AnalyzeConnector, x=???" << endl;
        }
        else if (aname=="y")
        {
            y_found = true;
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
                y = dval;
            else cout << "Error! AnalyzeConnector, y=???" << endl;
        }
        else if (aname=="alpha")
        {
            alpha_found = true;
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
                alpha = dval;
            else cout << "Error! AnalyzeConnector, alpha=???" << endl;
        }
        attr = attr->Next();
    }

    string val = node->Value();
    if (val=="ConnectorTurn")
        ProcessConnectorTurn(name, segment_name, ro, phi, ro_found, phi_found);
    else if (val=="ConnectorTurnD")
        ProcessConnectorTurnD(name, segment_name, x, y, x_found, y_found);
    else if (val=="ConnectorSliding")
        ProcessConnectorSliding(name, segment_name, ro, phi, alpha, ro_found, phi_found, alpha_found);
    else if (val=="ConnectorSlidingD")
        ProcessConnectorSlidingD(name, segment_name, x, y, alpha, x_found, y_found, alpha_found);
    else cout << "AnalyzeConnector: unknown type" << endl;
}

void XMLLoader::AnalyzeKPair(TiXmlNode* node)
{
    string name, c1name, c2name;
    bool name_found=false, c1name_found=false, c2name_found=false;

    TiXmlAttribute *attr = node->ToElement()->FirstAttribute();
    while (attr != NULL)
    {
        string aname = attr->Name();
        string avalue = attr->Value();
        if (aname=="name")
        {
            name_found = true;
            name = avalue;
        }
        else if (aname=="c1_name")
        {
            c1name_found = true;
            c1name = avalue;
        }
        else if (aname=="c2_name")
        {
            c2name_found = true;
            c2name = avalue;
        }
        attr = attr->Next();
    }

    if (!name_found)
        cout << "KPName not found!" << endl;
    if (!c1name_found)
        cout << "c1_name not found!" << endl;
    if (!c2name_found)
        cout << "c2_name not found!" << endl;

    if (name_found && c1name_found && c2name_found)
    {
        string val = node->Value();
        if (val=="KPTurn")
            cm->AddKPTurn(name, c1name, c2name);
        if (val=="KPSliding")
            cm->AddKPSliding(name, c1name, c2name);
    }
}

void XMLLoader::ProcessConnectorTurn(string name, string segment_name, double ro, double phi, bool ro_found, bool phi_found)
{
    if (!ro_found || !phi_found)
    {
        cout << "ProcessConnectorTurn: not all arguments found" << endl;
        return;
    }
    if (name.length()>2 && name[name.length()-2]=='c' && name[name.length()-1]=='S')
        cm->AddCMass(segment_name, ro, phi);
    else
        cm->AddConnectorTurn(name, segment_name, ro, phi);
}

void XMLLoader::ProcessConnectorTurnD(string name, string segment_name, double x, double y, bool x_found, bool y_found)
{
    if (!x_found || !y_found)
    {
        cout << "ProcessConnectorTurnD: not all arguments found" << endl;
        return;
    }
    cm->AddConnectorTurnD(name, segment_name, x, y);
}

void XMLLoader::ProcessConnectorSliding(string name, string segment_name, double ro, double phi, double alpha, bool ro_found, bool phi_found, bool alpha_found)
{
    if (!ro_found || !phi_found || !alpha_found)
    {
        cout << "ProcessConnectorSliding: not all arguments found" << endl;
        return;
    }
    cm->AddConnectorSliding(name, segment_name, ro, phi, alpha);
}

void XMLLoader::ProcessConnectorSlidingD(string name, string segment_name, double x, double y, double alpha, bool x_found, bool y_found, bool alpha_found)
{
    if (!x_found || !y_found || !alpha_found)
    {
        cout << "ProcessConnectorSlidingD: not all arguments found" << endl;
        return;
    }
    cm->AddConnectorSlidingD(name, segment_name, x, y, alpha);
}

void XMLLoader::AnalyzeGroup(TiXmlElement *elem)
{
    if (elem==NULL) return;
    string tp = elem->Value();
    if (tp=="Group1")
        ProcessGroup1(elem);
    if (tp=="Group2")
        ProcessGroup2(elem);
}

void XMLLoader::ProcessGroup1(TiXmlElement *elem)
{
    string kp_name, s1_name, s2_name;
    bool kp_name_found=false, s1_name_found=false, s2_name_found=false;

    TiXmlAttribute *attr = elem->FirstAttribute();
    while (attr != NULL)
    {
        string aname = attr->Name();
        string avalue = attr->Value();
        if (aname=="kp_name")
        {
            kp_name_found = true;
            kp_name = avalue;
        }
        else if (aname=="s1_name")
        {
            s1_name_found = true;
            s1_name = avalue;
        }
        else if (aname=="s2_name")
        {
            s2_name_found = true;
            s2_name = avalue;
        }
        attr = attr->Next();
    }

    if (!kp_name_found)
        cout << "kp_name not found!" << endl;
    if (!s1_name_found)
        cout << "s1_name not found!" << endl;
    if (!s2_name_found)
        cout << "s2_name not found!" << endl;

    if (kp_name_found && s1_name_found && s2_name_found)
        gm->AddFirstGroupByName(kp_name, s1_name, s2_name);
}


void XMLLoader::ProcessGroup2(TiXmlElement *elem)
{
    string kp1_name, kp2_name, kp3_name, s1_name, s2_name, sign1, sign2;
    bool kp1_name_found=false, kp2_name_found=false, kp3_name_found=false, s1_name_found=false, s2_name_found=false, sign1_found=false, sign2_found=false;
    signed char mj1;
    signed char mj2;

    TiXmlAttribute *attr = elem->FirstAttribute();
    int ival;
    while (attr != NULL)
    {
        string aname = attr->Name();
        string avalue = attr->Value();
        if (aname=="kp1_name")
        {
            kp1_name_found = true;
            kp1_name = avalue;
        }
        else if (aname=="kp2_name")
        {
            kp2_name_found = true;
            kp2_name = avalue;
        }
        else if (aname=="kp3_name")
        {
            kp3_name_found = true;
            kp3_name = avalue;
        }
        else if (aname=="s1_name")
        {
            s1_name_found = true;
            s1_name = avalue;
        }
        else if (aname=="s2_name")
        {
            s2_name_found = true;
            s2_name = avalue;
        }
        else if (aname == "sign1")
        {
            if (attr->QueryIntValue(&ival)==TIXML_SUCCESS)
               mj1 = ival;
            else cout << "Error! ProcessGroup2, sign1=???" << endl;
            sign1_found = true;
        }
        else if (aname == "sign2")
        {
            if (attr->QueryIntValue(&ival)==TIXML_SUCCESS)
               mj2 = ival;
            else cout << "Error! ProcessGroup2, sign1=???" << endl;
            sign2_found = true;
        }
        attr = attr->Next();
    }

    if (!kp1_name_found)
        cout << "kp1_name not found!" << endl;
    if (!kp2_name_found)
        cout << "kp2_name not found!" << endl;
    if (!kp3_name_found)
        cout << "kp3_name not found!" << endl;
    if (!s1_name_found)
        cout << "s1_name not found!" << endl;
    if (!s2_name_found)
        cout << "s2_name not found!" << endl;

    if (kp1_name_found && kp2_name_found && kp3_name_found && s1_name_found && s2_name_found)
    {
        if (sign2_found)
            gm->AddSecondGroupByName(kp1_name, kp2_name, kp3_name, s1_name, s2_name, mj1, mj2);
        else
        {
            if (sign1_found)
                gm->AddSecondGroupByName(kp1_name, kp2_name, kp3_name, s1_name, s2_name, mj1);
            else
                gm->AddSecondGroupByName(kp1_name, kp2_name, kp3_name, s1_name, s2_name);
        }
    }
}

void XMLLoader::SetMechanismAttributes(TiXmlNode *node)
{
    TiXmlAttribute *attr = node->ToElement()->FirstAttribute();
    double dval;
    while (attr != NULL)
    {
        string aname = attr->Name();
        string aval   = attr->Value();

        if (aname == "step_size")
        {
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
               gm->SetStepSize(dval);
            else cout << "Error! SetMechanismAttributes, step_size=???" << endl;
        }
        else if (aname == "min")
        {
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
               gm->SetMinGC(dval);
            else cout << "Error! SetMechanismAttributes, min=???" << endl;
        }
        else if (aname == "max")
        {
            if (attr->QueryDoubleValue(&dval)==TIXML_SUCCESS)
               gm->SetMaxGC(dval);
            else cout << "Error! SetMechanismAttributes, max=???" << endl;
        }
        else if (aname == "jump")
        {
            if (aval == "yes")
                gm->SetJump(true);
            else if (aval == "no")
                gm->SetJump(false);
            else cout << "Error! SetMechanismAttributes, jump=???" << endl;
        }
        attr = attr->Next();
    }
}
