#include "GroupSTS.h"

GroupSTS::GroupSTS(KPSliding *K1,KPTurn *K2,KPSliding *K3,Segment *s1_, Segment *s2_)
{
    A = K1;
    B = K2;
    C = K3;
    s1 = s1_;
    s2 = s2_;


    ConnectorSliding *cs1,*cs2;
    cs1=(ConnectorSliding*)A->GetC1();
    cs2=(ConnectorSliding*)A->GetC2();

    if (cs1->s == s1)
    {
        s1cA = cs1;
        s0cA = cs2;
    }
    else
        if (cs2->s == s1)
        {
            s1cA = cs2;
            s0cA = cs1;
        }
        else throw "GroupSTS: KPair A not connected to s1";


    ConnectorTurn *ct1,*ct2;

    ct1=(ConnectorTurn*)B->GetC1();
    ct2=(ConnectorTurn*)B->GetC2();
    if (ct1->s == s1)
        s1cB = ct1;
    else
        if (ct2->s == s1)
            s1cB = ct2;
        else throw "GroupSTS: KPair B not connected to s1";

    if (ct1->s == s2)
        s2cB = ct1;
    else
        if (ct2->s == s2)
            s2cB = ct2;
        else throw "GroupSTS: KPair B not connected to s2";

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
        else throw "GroupSTS: KPair C not connected to s2";


    h1=GetHeight(s1cB,s1cA);
    h2=GetHeight(s2cB,s2cC);

}

GROUP_TYPE GroupSTS::Type()
{
    return GROUP_TYPE_STS;
}

void GroupSTS::CalcTF0()
{

    if (!s0cA->turn->phi.IsCalculatedTF0())
        throw "GroupSTS: s0cA->turn->phi not calculated";
    if (!s0cC->turn->phi.IsCalculatedTF0())
        throw "GroupSTS: s0cC->turn->phi not calculated";

    if (!s0cA->linear0.x.IsCalculatedTF0())
        throw "GroupSTS: s0cA->linear0.x not calculated";
    if (!s0cA->linear0.y.IsCalculatedTF0())
        throw "GroupSTS: s0cA->linear0.y not calculated";


    if (!s0cC->linear0.x.IsCalculatedTF0())
        throw "GroupSTS: s0cC->linear0.x not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF0())
        throw "GroupSTS: s0cC->linear0.y not calculated";


    double phiN=s0cA->turn->phi.GetTF0();
    double phiM=s0cC->turn->phi.GetTF0();
    double xN=s0cA->linear0.x.GetTF0();
    double yN=s0cA->linear0.y.GetTF0();
    double xM=s0cC->linear0.x.GetTF0();
    double yM=s0cC->linear0.y.GetTF0();
    double xB,yB;

    if ((fabs(cos(phiN))<epsilon)
            &&(fabs(cos(phiM))<epsilon)) // obe vertical
        throw "GroupSTS: both external axis are vertical and parallel";

    if (fabs(cos(phiN))>epsilon)    // tan != inf  not vertical
        tgN=tan(phiN);
    if (fabs(cos(phiM))>epsilon)    // tan != inf  not vertical
        tgM=tan(phiM);

    if (fabs(cos(phiN))<epsilon)     // tan == inf  vertical
    {
        xB=xN-h1;
        yB=h2/cos(phiM)  +tgM*xB
                           +yM-tgM*xM;
    }
    else
        if (fabs(cos(phiM))<epsilon)    // tan == inf  vertical
        {
            xB=xM-h2;
            yB=h1/cos(phiN)    +tgN*xB
                               +yN-tgN*xN;
        }
        else
            if (fabs(tgM-tgN)>epsilon)
            {

                xB=(h1/cos(phiN)-h2/cos(phiM)-
                                    tgN*xN+tgM*xM
                                    +yN -yM)/
                                   (tgM-tgN);

                yB=tgN*xB-tgN*xN+yN+h1/cos(phiN);
            }
            else  //  палки параллельны
                throw "GroupSTS: external axis are parallel";

    B->linear.x.SetTF0(xB);
    B->linear.y.SetTF0(yB);

    s1->turn.phi.SetTF0(phiN-s1cA->alpha);
    s2->turn.phi.SetTF0(phiM-s2cC->alpha);

    CalcTF0Segment(s1,s1cB);
    CalcTF0Segment(s2,s2cB);

}

void GroupSTS::CalcTF1()
{

    if (!s0cA->turn->phi.IsCalculatedTF1())
        throw "GroupSTS: s0cA->turn->phi_ not calculated";
    if (!s0cC->turn->phi.IsCalculatedTF1())
        throw "GroupSTS: s0cC->turn->phi_ not calculated";

    if (!s0cA->linear0.x.IsCalculatedTF1())
        throw "GroupSTS: s0cA->linear0.x_ not calculated";
    if (!s0cA->linear0.y.IsCalculatedTF1())
        throw "GroupSTS: s0cA->linear0.y_ not calculated";


    if (!s0cC->linear0.x.IsCalculatedTF1())
        throw "GroupSTS: s0cC->linear0.x_ not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF1())
        throw "GroupSTS: s0cC->linear0.y_ not calculated";


    double phiN=s0cA->turn->phi.GetTF0();
    double phiM=s0cC->turn->phi.GetTF0();

    double phiN_=s0cA->turn->phi.GetTF1();
    double phiM_=s0cC->turn->phi.GetTF1();

    double xB=B->linear.x.GetTF0();
    double yB=B->linear.y.GetTF0();


    double xN=s0cA->linear0.x.GetTF0();
    double yN=s0cA->linear0.y.GetTF0();
    double xM=s0cC->linear0.x.GetTF0();
    double yM=s0cC->linear0.y.GetTF0();

    double xN_=s0cA->linear0.x.GetTF1();
    double yN_=s0cA->linear0.y.GetTF1();
    double xM_=s0cC->linear0.x.GetTF1();
    double yM_=s0cC->linear0.y.GetTF1();


    double tgN_,tgM_;
    double xB_,yB_;

    if (fabs(cos(phiN))<epsilon)     // tan == inf  vertical
    {
        xB_=xN_;
        //  yB_=->linear.y.SetTF0(h2/cos(phiM)
        //                   +tgM*B->linear.x.GetTF0()
        //      +yM-tgM*xM);
        throw "GroupSTS: CalcTF1() ##1"; // не знаю формулу :(
    }
    else
        if (fabs(cos(phiM))<epsilon)    // tan == inf  vertical
        {
            xB_=xM_;
            // yB_=->linear.y.SetTF0(h1/cos(phiN)
            //                   +tgN*B->linear.x.GetTF0()
            //                  +yN-tgN*xN);
            throw "GroupSTS: CalcTF1() ##2";  //незнаю формулы. :(
        }
        else
            if (fabs(tgM-tgN)>epsilon)
            {

                tgN_=phiN_/sqr(cos(phiN));
                tgM_=phiM_/sqr(cos(phiM));


                xB_=((h2*tgM*tgM_*cos(phiM))-
                     h1*tgN*tgN*cos(phiN)+
                     tgN_*xN+tgN*xN_-
                     tgM_*xM-tgM*xM_+
                     yM_-yN_-xB*(tgN_-tgM_))/
                    (tgN-tgM);

                yB_=tgM_*xB+tgM*xB_+
                    yM_-tgM_*xM-
                    tgM*xM_+h2*tgM*tgM_*cos(phiM);
            }
            else  //  палки параллельны
                throw "GroupSTS: external axis are parallel";

    B->linear.x.SetTF1(xB_);
    B->linear.y.SetTF1(yB_);

    s1->turn.phi.SetTF1(phiN_);
    s2->turn.phi.SetTF1(phiM_);

    CalcTF1Segment(s1,s1cB);
    CalcTF1Segment(s2,s2cB);

}

void GroupSTS::CalcTF2()
{


    if (!s0cA->turn->phi.IsCalculatedTF2())
        throw "GroupSTS: s0cA->turn->phi__ not calculated";
    if (!s0cC->turn->phi.IsCalculatedTF2())
        throw "GroupSTS: s0cC->turn->phi__ not calculated";

    if (!s0cA->linear0.x.IsCalculatedTF2())
        throw "GroupSTS: s0cA->linear0.x__ not calculated";
    if (!s0cA->linear0.y.IsCalculatedTF2())
        throw "GroupSTS: s0cA->linear0.y__ not calculated";


    if (!s0cC->linear0.x.IsCalculatedTF2())
        throw "GroupSTS: s0cC->linear0.x__ not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF2())
        throw "GroupSTS: s0cC->linear0.y__ not calculated";


    double phiN=s0cA->turn->phi.GetTF0();
    double phiM=s0cC->turn->phi.GetTF0();

    double phiN_=s0cA->turn->phi.GetTF1();
    double phiM_=s0cC->turn->phi.GetTF1();


    double phiN__=s0cA->turn->phi.GetTF2();
    double phiM__=s0cC->turn->phi.GetTF2();

    double xB=B->linear.x.GetTF0();
    double yB=B->linear.y.GetTF0();

    double xB_=B->linear.x.GetTF1();
    double yB_=B->linear.y.GetTF1();


    double xN=s0cA->linear0.x.GetTF0();
    double yN=s0cA->linear0.y.GetTF0();
    double xM=s0cC->linear0.x.GetTF0();
    double yM=s0cC->linear0.y.GetTF0();

    double xN_=s0cA->linear0.x.GetTF1();
    double yN_=s0cA->linear0.y.GetTF1();
    double xM_=s0cC->linear0.x.GetTF1();
    double yM_=s0cC->linear0.y.GetTF1();

    double xN__=s0cA->linear0.x.GetTF2();
    double yN__=s0cA->linear0.y.GetTF2();
    double xM__=s0cC->linear0.x.GetTF2();
    double yM__=s0cC->linear0.y.GetTF2();


    double xB__,yB__;

    if (fabs(cos(phiN))<epsilon)     // tan == inf  vertical
    {
        xB__=xN__;
        //  yB_=->linear.y.SetTF0(h2/cos(phiM)
        //                   +tgM*B->linear.x.GetTF0()
        //      +yM-tgM*xM);
        throw "GroupSTS: CalcTF2() ##4"; // не знаю формулу :(
    }
    else
        if (fabs(cos(phiM))<epsilon)    // tan == inf  vertical
        {
            xB__=xM__;
            // yB_=->linear.y.SetTF0(h1/cos(phiN)
            //                   +tgN*B->linear.x.GetTF0()
            //                  +yN-tgN*xN);
            throw "GroupSTS: CalcTF2() ##5";  //незнаю формулы. :(
        }
        else
            if (fabs(tgM-tgN)>epsilon)
            {

                double r1,r2;



                tgM__=(phiM__+tgM_*sin(2.0*phiM)*phiM_)/
                                       sqr(cos(phiM));
                tgN__=(phiN__+tgN_*sin(2.0*phiN)*phiN_)/
                                       sqr(cos(phiN));

                r1=((tgM_/cos(phiM))-sqr(tgM)*tgM_*cos(phiM))*cos(phiM);
                r2=((tgN_/cos(phiN))-sqr(tgN)*tgN_*cos(phiN))*cos(phiN);
// я на осонове формул методы вывел намного проще формулы.


                xB__=(-2.0*xB_*(tgN_-tgM_)-xB*(tgN__-tgM__)+
                      h2*r1*tgM_+h2*tgM*tgM__*cos(phiM)-
                      h1*r2*tgN_-h1*tgN*tgN__*cos(phiN)+
                    tgN__*xN+2.0*tgN_*xN_+tgN*xN__-
                    tgM__*xM-2.0*tgM_*xM_-tgM*xM__+
                    xM__-xN__)/(tgN-tgM);

                yB__=tgM__*xB+2.0*tgM_*xB_+tgM*xB__+yM__-
                     tgM__*xM-2.0*tgM_*xM_-tgM*xM__+
                            h2*r1*tgM_+
                            h2*tgM*tgM__*cos(phiM);



            }
            else  //  палки параллельны
                throw "GroupSTS: external axis are parallel";

    B->linear.x.SetTF2(xB__);
    B->linear.y.SetTF2(yB__);

    s1->turn.phi.SetTF2(phiN__);
    s2->turn.phi.SetTF2(phiM__);

    CalcTF2Segment(s1,s1cB);
    CalcTF2Segment(s2,s2cB);

}


void GroupSTS::CalcReaction()
{

}
