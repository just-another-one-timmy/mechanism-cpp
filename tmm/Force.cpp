#include "Force.h"

Force::Force(string name, FORCE_TYPE type, Connector *c)
{
    this->name = name;
    this->c = c;
    ftype = type;
    //s = c->s;
    c->s->forces.push_back(this);

    calculatedx=false;
    calculatedy=false;
    calculatedt=false;

}

string Force::GetName()
{
    return name;
}

FORCE_TYPE Force::Type()
{
    return ftype;
}

Connector * Force::GetConnector()
{
    return c;
}

void Force::SetForce(double Fx, double Fy, double Torque)
{
    fx=Fx;
    calculatedx=true;
    fy=Fy;
    calculatedy=true;
    torque=Torque;
    calculatedt=true;
}

double Force::GetForcex()
{
    if (!calculatedx)        throw "Force: GetForcex : fx not calculated";
    return fx;

}

double Force::GetForcey()
{
    if (!calculatedy) throw "Force: GetForcey : fy not calculated";
    return fy;

}

double Force::GetForcet()
{
    if (!calculatedt) throw "Force: GetForcet : torque not calculated";
    return torque;

}

bool Force::IsCalculatedx()
{
    return calculatedx;
}

bool Force::IsCalculatedy()
{
    return calculatedy;
}
bool Force::IsCalculatedt()
{
    return calculatedt;
}

void Force::UnsetCalculated()
{
    if((this->Type()==FORCE_TYPE_GRAVITY)||(this->Type()==FORCE_TYPE_TECHNO))
    return;
    calculatedx=false;
    calculatedy=false;
    calculatedt=false;
}
