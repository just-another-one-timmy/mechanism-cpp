#include "GroupTST.h"

GroupTST::GroupTST(KPTurn *K1,KPSliding *K2,KPTurn *K3,Segment *s1_, Segment *s2_)
{
    A = K1;
    B = K2;
    C = K3;
    s1 = s1_;
    s2 = s2_;

    ConnectorTurn *ct1,*ct2;
    ct1=(ConnectorTurn*)A->GetC1();
    ct2=(ConnectorTurn*)A->GetC2();
    if (ct1->s == s1)
        s1cA = ct1;
    else
        if (ct2->s == s1)
            s1cA = ct2;
        else throw "GroupTST: KPair A not connected to s1";

    ConnectorSliding *cs1,*cs2;
    cs1=(ConnectorSliding*)B->GetC1();
    cs2=(ConnectorSliding*)B->GetC2();
    if (cs1->s == s1)
        s1cB = cs1;
    else
        if (cs2->s == s1)
            s1cB = cs2;
        else throw "GroupTST: KPair B not connected to s1";

    if (cs1->s == s2)
        s2cB = cs1;
    else
        if (cs2->s == s2)
            s2cB = cs2;
        else throw "GroupTST: KPair B not connected to s2";
    ct1=(ConnectorTurn*)C->GetC1();
    ct2=(ConnectorTurn*)C->GetC2();

    if (ct1->s == s2)
    {
        s2cC = ct1;

    }
    else
        if (ct2->s == s2)
        {
            s2cC = ct2;
        }
        else throw "GroupTTS: KPair C not connected to s2";

    h1=-GetHeight(s1cA,s1cB);
    h2=GetHeight(s2cC,s2cB);
  //  if (h1<0) h1 = -h1;
  //  if (h2<0) h2 = -h2;
}

GROUP_TYPE GroupTST::Type()
{
    return GROUP_TYPE_TST;
}

void GroupTST::CalcTF0()
{

    if(!s1cA->linear->x.IsCalculatedTF0())
        throw "GroupTST: s1cA->linear->x not calculated";
    if(!s1cA->linear->y.IsCalculatedTF0())
        throw "GroupTST: s1cA->linear->y not calculated";

    if(!s2cC->linear->x.IsCalculatedTF0())
        throw "GroupTST: s2cC->linear->x not calculated";
    if(!s2cC->linear->y.IsCalculatedTF0())
        throw "GroupTST: s2cC->linear->y not calculated";

    double sin_b;
    double xA=s1cA->linear->x.GetTF0();
    double yA=s1cA->linear->y.GetTF0();
    double xC=s2cC->linear->x.GetTF0();
    double yC=s2cC->linear->y.GetTF0();

    lac=sqrt(sqr(xA-xC)+sqr(yA-yC));
    sin_b=(h1+h2)/lac; // sin beta
    b=asin(sin_b); // ##
    AC.phi.SetTF0(atan2(yA-yC,xA-xC));
    B->angle.phi.SetTF0(AC.phi.GetTF0()-b);

    s1->turn.phi.SetTF0(B->angle.phi.GetTF0()-s1cB->alpha);
    s2->turn.phi.SetTF0(B->angle.phi.GetTF0()-s2cB->alpha);
    CalcTF0Segment(s1,s1cA);
    CalcTF0Segment(s2,s2cC);
}

void GroupTST::CalcTF1()
{
    if(!s1cA->linear->x.IsCalculatedTF1())
        throw "GroupTST: s1cA->linear->x_ not calculated";
    if(!s1cA->linear->y.IsCalculatedTF1())
        throw "GroupTST: s1cA->linear->y_ not calculated";

    if(!s2cC->linear->x.IsCalculatedTF1())
        throw "GroupTST: s2cC->linear->x_ not calculated";
    if(!s2cC->linear->y.IsCalculatedTF1())
        throw "GroupTST: s2cC->linear->y_ not calculated";

    double xA=s1cA->linear->x.GetTF0();
    double yA=s1cA->linear->y.GetTF0();
    double xC=s2cC->linear->x.GetTF0();
    double yC=s2cC->linear->y.GetTF0();


    double xA_=A->linear.x.GetTF1();
    double yA_=A->linear.y.GetTF1();

    double xC_=C->linear.x.GetTF1();
    double yC_=C->linear.y.GetTF1();



    lac_=((xA-xC)*(xA_-xC_)
         +(yA-yC)*(yA_-yC_))/lac;
        b_=-lac_/lac*tan(b);
        AC.phi.SetTF1(((yA_-yC_)-(xA_-xC_)*tan(AC.phi.GetTF0()))
                    *sqr(cos(AC.phi.GetTF0()))
                    /(xA-xC));          // ##9
        B->angle.phi.SetTF1(AC.phi.GetTF1()-b_);

    s1->turn.phi.SetTF1(B->angle.phi.GetTF1());
    s2->turn.phi.SetTF1(B->angle.phi.GetTF1());
    CalcTF1Segment(s1,s1cA);
    CalcTF1Segment(s2,s2cC);
}

void GroupTST::CalcTF2()
{
    if(!s1cA->linear->x.IsCalculatedTF2())
        throw "GroupTST: s1cA->linear->x__ not calculated";
    if(!s1cA->linear->y.IsCalculatedTF2())
        throw "GroupTST: s1cA->linear->y__ not calculated";

    if(!s2cC->linear->x.IsCalculatedTF2())
        throw "GroupTST: s2cC->linear->x__ not calculated";
    if(!s2cC->linear->y.IsCalculatedTF2())
        throw "GroupTST: s2cC->linear->y__ not calculated";


    double xA__=A->linear.x.GetTF2();
    double yA__=A->linear.y.GetTF2();
    double xC__=C->linear.x.GetTF2();
    double yC__=C->linear.y.GetTF2();

    double xA_=A->linear.x.GetTF1();
    double yA_=A->linear.y.GetTF1();
    double xC_=C->linear.x.GetTF1();
    double yC_=C->linear.y.GetTF1();

    double xA=A->linear.x.GetTF0();
    double yA=A->linear.y.GetTF0();
    double xC=C->linear.x.GetTF0();
    double yC=C->linear.y.GetTF0();



        lac__=(sqr(xA_-xC_)+(xA-xC)*(xA__-xC__)+
        sqr(yA_-yC_)+(yA-yC)*(yA__-yC__)-sqr(lac_))/lac;

        b__=(sqr(b_)*lac*sin(b)-2.0*b_*lac_*cos(b)-lac__*
                            sin(b))/lac/cos(b);                   //##8
        AC.phi.SetTF2(((yA__-yC__)*sqr(cos(AC.phi.GetTF0()))-
                    (yA_-yC_)*sin(2.0*AC.phi.GetTF0())*AC.phi.GetTF1()-
                AC.phi.GetTF1()*(xA_-xC_)-
                cos(2.0*AC.phi.GetTF0())*AC.phi.GetTF1()*(xA_-xC_)-
                0.5*sin(2.0*AC.phi.GetTF0())*(xA__-xC__))/(xA-xC)); //##7
        B->angle.phi.SetTF2(AC.phi.GetTF2()-b__);


    s1->turn.phi.SetTF2(B->angle.phi.GetTF2());
    s2->turn.phi.SetTF2(B->angle.phi.GetTF2());
    CalcTF2Segment(s1,s1cA);
    CalcTF2Segment(s2,s2cC);
}


void GroupTST::CalcReaction()
{

}
