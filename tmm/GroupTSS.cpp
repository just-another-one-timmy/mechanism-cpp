#include "GroupTSS.h"

GroupTSS::GroupTSS(KPair *K1,KPair *K2,KPair *K3,Segment *s1_, Segment *s2_)
{
    A = (KPTurn*)K1;
    B = (KPSliding*)K2;
    C = (KPSliding*)K3;
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
        else throw "GroupTSS: KPair A not connected to s1";

    ConnectorSliding *cs1,*cs2;

    cs1=(ConnectorSliding*)B->GetC1();
    cs2=(ConnectorSliding*)B->GetC2();
    if (cs1->s == s1)
        s1cB = cs1;
    else
        if (cs2->s == s1)
            s1cB = cs2;
        else throw "GroupTSS: KPair B not connected to s1";

    if (cs1->s == s2)
        s2cB = cs1;
    else
        if (cs2->s == s2)
            s2cB = cs2;
        else throw "GroupTSS: KPair B not connected to s2";


    cs1=(ConnectorSliding*)C->GetC1();
    cs2=(ConnectorSliding*)C->GetC2();

    if (cs1->s == s2)
    {
        s2cC = cs1;
        s0cC = cs2;
    }
    else
        if (cs2->s == s2)
        {
            s2cC = cs2;
            s0cC = cs1;
        }
        else throw "GroupTTS: KPair C not connected to s2";


    alfa=GetAngleSS(s2cB,s2cC);
    h=GetHeight(s1cA,s1cB);

// вычисляем полярные координаты точки К
// - пересечение двух SlidingConnectors
    roK=0;
    phiK=0;
}

GROUP_TYPE GroupTSS::Type()
{
    return GROUP_TYPE_TSS;
}


void GroupTSS::CalcTF0()
{

    if (!s1cA->linear->x.IsCalculatedTF0())
        throw "GroupTSS: s1cA->linear->x not calculated";
    if (!s1cA->linear->y.IsCalculatedTF0())
        throw "GroupTSS: s1cA->linear->y not calculated";

    if (!s0cC->turn->phi.IsCalculatedTF0())
        throw "GroupTSS: s0cC->turn->phi not calculated";
    if (!s0cC->linear0.x.IsCalculatedTF0())
        throw "GroupTSS: s0cC->linear0.x not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF0())
        throw "GroupTSS: s0cC->linear0.y not calculated";


    double xA=s1cA->linear->x.GetTF0();
    double yA=s1cA->linear->y.GetTF0();


    double phiN=s0cC->turn->phi.GetTF0();
    double xN=s0cC->linear0.x.GetTF0();
    double yN=s0cC->linear0.y.GetTF0();

    double phi2 = phiN-s2cC->alpha;
    s2->turn.phi.SetTF0(phi2-s2cC->alpha);
    s1->turn.phi.SetTF0(phi2+s2cB->alpha-s1cB->alpha);
    CalcTF0Segment(s1,s1cA);


    double phiM=s2cB->turn->phi.GetTF0();
    double xM=s2cB->linear0.x.GetTF0();
    double yM=s2cB->linear0.y.GetTF0();


    if ((fabs(cos(phiN))<epsilon)
            &&(fabs(cos(phiM))<epsilon)) // obe vertical
        throw "GroupTSS: both external axis are vertical and parallel";

    if (fabs(cos(phiN))>epsilon)    // tan != inf  not vertical
        tgN=tan(phiN);
    if (fabs(cos(phiM))>epsilon)    // tan != inf  not vertical
        tgM=tan(phiM);

    if (fabs(cos(phiN))<epsilon)     // tan == inf  vertical
    {
        xK=xN;
         throw "GroupTSS: CalcTF0() ##1"; // не знаю формулу :(

    }
    else
        if (fabs(cos(phiM))<epsilon)    // tan == inf  vertical
        {
            xK=xA+h;
            yK=yN+(xK-xN)*tgN;
        }
        else
            if (fabs(tgM-tgN)>epsilon)
            {
                xK=(xM*tgM-xN*tgN+
                    yN-yM)/
                   (tgM-tgN);
                yK=(yN+xK*tgN-xN*tgN);
            }
            else  //  палки параллельны
                throw "GroupTSS: external axis are parallel";

    s2->polus->linear->x.SetTF0(xK-roK*cos(phi2+phiK));  //
    s2->polus->linear->y.SetTF0(yK-roK*sin(phi2+phiK)); //

    CalcTF0Segment(s2,s2->polus);
}

void GroupTSS::CalcTF1()
{

    if (!s1cA->linear->x.IsCalculatedTF0())
        throw "GroupTSS: s1cA->linear->x not calculated";
    if (!s1cA->linear->y.IsCalculatedTF0())
        throw "GroupTSS: s1cA->linear->y not calculated";

    if (!s0cC->turn->phi.IsCalculatedTF0())
        throw "GroupTSS: s0cC->turn->phi not calculated";
    if (!s0cC->linear0.x.IsCalculatedTF0())
        throw "GroupTSS: s0cC->linear0.x not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF0())
        throw "GroupTSS: s0cC->linear0.y not calculated";


    double xA=s1cA->linear->x.GetTF0();
    double yA=s1cA->linear->y.GetTF0();


    double phiN=s0cC->turn->phi.GetTF0();
    double xN=s0cC->linear0.x.GetTF0();
    double yN=s0cC->linear0.y.GetTF0();

    double phi2 = phiN-s2cC->alpha;
    s2->turn.phi.SetTF0(phi2-s2cC->alpha);
    s1->turn.phi.SetTF0(phi2+s2cB->alpha-s1cB->alpha);
    CalcTF0Segment(s1,s1cA);


    double phiM=s2cB->turn->phi.GetTF0();
    double xM=s2cB->linear0.x.GetTF0();
    double yM=s2cB->linear0.y.GetTF0();


    if ((fabs(cos(phiN))<epsilon)
            &&(fabs(cos(phiM))<epsilon)) // obe vertical
        throw "GroupTSS: both external axis are vertical and parallel";

    if (fabs(cos(phiN))>epsilon)    // tan != inf  not vertical
        tgN=tan(phiN);
    if (fabs(cos(phiM))>epsilon)    // tan != inf  not vertical
        tgM=tan(phiM);

    if (fabs(cos(phiN))<epsilon)     // tan == inf  vertical
    {
         throw "GroupTSS: CalcTF1() ##2"; // не знаю формулу :(

    }
    else
        if (fabs(cos(phiM))<epsilon)    // tan == inf  vertical
        {
         throw "GroupTSS: CalcTF1() ##3"; // не знаю формулу :(

        }
        else
            if (fabs(tgM-tgN)>epsilon)
            {
               /* xK_=(xM*tgM-xN*tgN+
                    yN-yM)/
                   (tgM-tgN);
                yK_=(yN+xK*tgN-xN*tgN);
          */  }
            else  //  палки параллельны
                throw "GroupTSS: external axis are parallel";

    s2->polus->linear->x.SetTF1(xK_-roK*cos(phi2+phiK));  //
    s2->polus->linear->y.SetTF1(yK_-roK*sin(phi2+phiK)); //  // формулы взять из CalcTF1Segment

    CalcTF1Segment(s2,s2->polus);

    /*
    xc1pr:=xa1-h*sin(fiac)*fin1;
         yc1pr:=ya1+h*cos(fiac)*fin1;
         km1:=fin1/sqr(cos(fim));
         kn1:=fin1/sqr(cos(fin));
         xk1:=(-yc1pr+yn1-xk*(km1-kn1)+xc1pr*km-xn1*kn+xc*km1-xn*kn1)/(km-kn);
         yk1:=yn1+xk1*kn+xk*kn1-xn1*kn-xn*kn1;

    */
}

void GroupTSS::CalcTF2()
{
    /*
    xc2pr:=xa2-h*cos(fiac)*sqr(fin1)-h*sin(fiac)*fin2;
         yc2pr:=ya2-h*sin(fiac)*sqr(fin1)+h*cos(fiac)*fin2;
         km2:=(fin2*sqr(cos(fim))+sqr(fin1)*sin(2.0*fim))/sqr(sqr(cos(fim)));
         kn2:=(fin2*sqr(cos(fin))+sqr(fin1)*sin(2.0*fin))/sqr(sqr(cos(fin)));
    xk2:=(-yc2pr+yn2-2.0*xk1*(km1-kn1)-xk*(km2-kn2)+xc2pr*km-xn2*kn+
                    2.0*xc1pr*km1-2.0*xn1*kn1+xc*km2-xn*kn2)/(km-kn);
         yk2:=yn2+xk2*kn+2.0*xk1*kn1+xk*kn2-xn2*kn-2.0*xn1*kn1-xn*kn2;
    */
}


void GroupTSS::CalcReaction()
{

}
