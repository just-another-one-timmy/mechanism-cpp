#include "GroupT.h"


GROUP_TYPE GroupT::Type()
{
    return GROUP_TYPE_T;
}

GroupT::GroupT(KPTurn * K,Segment * s0_,Segment * s1_)
{
    O=K;
    s0=s0_;
    s1=s1_;
    ConnectorTurn *c1,*c2;
    c1=(ConnectorTurn*)O->GetC1();
    c2=(ConnectorTurn*)O->GetC2();

    if (c1->s == s1)
    {
        s0cO = c2;
        s1cO = c1;
    }
    else
        if(c2->s == s1)
        {
            s0cO = c1;
            s1cO = c2;
        }



}


void GroupT::CalcTF0()
{
    s0->turn.phi.SetTF0(0.0);
    s0->polus->linear->x.SetTF0(0.0);
    s0->polus->linear->y.SetTF0(0.0);
    CalcTF0Segment(s0,s0->polus);

    s1->turn.phi.SetTF0(GC);
    CalcTF0Segment(s1,s1cO);
}

void GroupT::CalcTF1()
{
    s0->turn.phi.SetTF1(0.0);
    s0->polus->linear->x.SetTF1(0.0);
    s0->polus->linear->y.SetTF1(0.0);
    CalcTF1Segment(s0,s0->polus);

    s1->turn.phi.SetTF1(1);
    CalcTF1Segment(s1,s1cO);

}

void GroupT::CalcTF2()
{
    s0->turn.phi.SetTF2(0.0);
    s0->polus->linear->x.SetTF2(0.0);
    s0->polus->linear->y.SetTF2(0.0);
    CalcTF2Segment(s0,s0->polus);

    s1->turn.phi.SetTF2(0);
    CalcTF2Segment(s1,s1cO);

}


void GroupT::CalcReaction()
{

double SumFx=0;
double SumFy=0;
double SumTorque=0;

for (list<Force *>::iterator f = s1->forces.begin(); f!=s1->forces.end(); f++)
    {
        Force  *x = *f;
        if(x->IsCalculatedx())
            SumFx+=x->GetForcex();
        if(x->IsCalculatedy())
            SumFy+=x->GetForcey();
        if(x->IsCalculatedt())
            SumTorque+=x->GetForcet();
    }

O->R1->SetForce(-SumFx,-SumFy,0);
O->R2->SetForce(SumFx,SumFy,0);

}
