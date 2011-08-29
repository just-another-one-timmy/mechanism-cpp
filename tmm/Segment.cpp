#include "Segment.h"

Segment::~Segment()
{
    for (list<Force *>::iterator i = forces.begin(); i!=forces.end(); i++)
    {
        Force f = *(*i);
        delete *i;
    }
    for (list<Connector *>::iterator i = connectors.begin(); i!=connectors.end(); i++)
    {
        Connector *c = *i;
        delete c;
    }
}

Segment::Segment()
{
    this->cmass = NULL;
    this->polus = NULL;
}
