#include "GroupS.h"

GROUP_TYPE GroupS::Type()
{
    return GROUP_TYPE_S;
}

GroupS::GroupS(KPSliding * K,Segment * s0_,Segment * s1_)
{

    O=K;
    s0=s0_;
    s1=s1_;
    ConnectorSliding *c1,*c2;
    c1=(ConnectorSliding*)O->GetC1();
    c2=(ConnectorSliding*)O->GetC2();

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

void GroupS::CalcTF0()
{
    s0->turn.phi.SetTF0(0.0);
    s0->polus->linear->x.SetTF0(0.0);
    s0->polus->linear->y.SetTF0(0.0);
    CalcTF0Segment(s0,s0->polus);


  double phi0 = s0cO->turn->phi.GetTF0()-s1cO->alpha;

    s1->turn.phi.SetTF0(phi0);

    s1cO->linear0.x.SetTF0(s0cO->linear0.x.GetTF0()
    +GC*cos(s0cO->turn->phi.GetTF0()));

    s1cO->linear0.y.SetTF0(s0cO->linear0.y.GetTF0()
    +GC*sin(s0cO->turn->phi.GetTF0()));

    s1->polus->linear->x.SetTF0(s1cO->linear0.x.GetTF0()
                                -s1cO->ro*
                                cos(phi0+s1cO->phi));  //
    s1->polus->linear->y.SetTF0(s1cO->linear0.y.GetTF0()
                                -s1cO->ro*
                                sin(phi0+s1cO->phi)); //

    CalcTF0Segment(s1,s1->polus);

//printf("xp=%f\typ=%f\n",s1->polus->linear->x.GetTF0(),s1->polus->linear->y.GetTF0());


  //  printf("x=%f\ty=%f\n",s1cO->linear0.x.GetTF0(),s1cO->linear0.y.GetTF0());

}

void GroupS::CalcTF1()
{
    s0->turn.phi.SetTF1(0.0);
    s0->polus->linear->x.SetTF1(0.0);
    s0->polus->linear->y.SetTF1(0.0);
    CalcTF1Segment(s0,s0->polus);


 //      xa_1:=cos(finr)*jp;
 //      ya_1:=sin(finr)*jp;

}

void GroupS::CalcTF2()
{
    s0->turn.phi.SetTF2(0.0);
    s0->polus->linear->x.SetTF2(0.0);
    s0->polus->linear->y.SetTF2(0.0);
    CalcTF2Segment(s0,s0->polus);

//    xa_2:=0;
//    ya_2:=0;

}


void GroupS::CalcReaction()
{

}
