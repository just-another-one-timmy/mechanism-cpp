#include "Vizualizer.h"

void Vizualizer::SetDebugMode(bool dmode)
{
    this->dmode = dmode;
}

bool Vizualizer::GetDebugMode()
{
    return this->dmode;
}

void Vizualizer::SetCompManager(CompManager *c)
{
    this->c = c;
}

Vizualizer::Vizualizer(CompManager *c)
{
    this->c = c;
    dmode = false;
}
