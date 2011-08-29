#include "KPair.h"

KPAIR_TYPE KPTurn::Type()
{
    return KPAIR_TYPE_TURN;
}

KPAIR_TYPE KPSliding::Type()
{
    return KPAIR_TYPE_SLIDING;
}

KPSliding::KPSliding(string _name, ConnectorSliding *_c1, ConnectorSliding *_c2)
{
    name = _name;
    c1 = _c1;
    c2 = _c2;

    // Reaction name = Active segment's name + self segment's name
    R1 = new Force("R_"+c2->s->name + "_" + c1->s->name, FORCE_TYPE_REACTION, c1);
    R1->linear = &linear;
    R1->turn = &angle;

    R2 = new Force("R_"+c1->s->name + "_" + c2->s->name, FORCE_TYPE_REACTION, c2);
    R2->linear = &linear;
    R2->turn = &angle;

    c1->turn = &angle;
    c2->turn = &angle;
}

KPTurn::KPTurn(string _name, ConnectorTurn *_c1, ConnectorTurn *_c2)
{
    name = _name;
    c1 = _c1;
    c2 = _c2;
    R1 = new Force("R_"+c2->s->name + "_" + c1->s->name, FORCE_TYPE_REACTION, c1);
    R1->linear = &linear;

    R2 = new Force("R_"+c1->s->name + "_" + c2->s->name, FORCE_TYPE_REACTION, c2);
    R2->linear = &linear;

    c1->linear = &linear;
    c2->linear = &linear;
}

KPSliding::~KPSliding()
{
    c1->s->forces.remove(R1);
    c2->s->forces.remove(R2);
    delete R1;
    delete R2;
}

KPTurn::~KPTurn()
{
    c1->s->forces.remove(R1);
    c2->s->forces.remove(R2);
    delete R1;
    delete R2;
}
