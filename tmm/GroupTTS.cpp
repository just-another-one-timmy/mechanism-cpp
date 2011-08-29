#include "GroupTTS.h"

GroupTTS::GroupTTS(KPTurn *K1,KPTurn *K2,KPSliding *K3,Segment *s1_, Segment *s2_)
{
    A = K1;
    B = K2;
    C = K3;
    s1 = s1_;
    s2 = s2_;

    // NC=s0cC->turn->phi);

    ConnectorTurn *ct1,*ct2;
    ct1=(ConnectorTurn*)A->GetC1();
    ct2=(ConnectorTurn*)A->GetC2();
    if (ct1->s == s1)
        s1cA = ct1;
    else
        if (ct2->s == s1)
            s1cA = ct2;
        else throw "GroupTTS: KPair A not connected to s1";
    ct1=(ConnectorTurn*)B->GetC1();
    ct2=(ConnectorTurn*)B->GetC2();
    if (ct1->s == s1)
        s1cB = ct1;
    else
        if (ct2->s == s1)
            s1cB = ct2;
        else throw "GroupTTS: KPair B not connected to s1";

    if (ct1->s == s2)
        s2cB = ct1;
    else
        if (ct2->s == s2)
            s2cB = ct2;
        else throw "GroupTTS: KPair B not connected to s2";
    ConnectorSliding *cs1,*cs2;
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



    lab=GetDist(s1cA,s1cB);
    h=GetHeight(s2cB,s2cC);
    // h=0;
    j1=1;
}

GROUP_TYPE GroupTTS::Type()
{
    return GROUP_TYPE_TTS;
}

void GroupTTS::CalcTF0()
{
    double b1,r1,r2,q0,p;


    if (!s0cC->turn->phi.IsCalculatedTF0())
        throw "GroupTTS: s0cC->turn->phi not calculated";
    if (!s0cC->linear0.x.IsCalculatedTF0())
        throw "GroupTTS: s0cC->linear0.x not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF0())
        throw "GroupTTS: s0cC->linear0.y not calculated";

    if (!s1cA->linear->x.IsCalculatedTF0())
        throw "GroupTTS: s1cA->linear->x not calculated";
    if (!s1cA->linear->y.IsCalculatedTF0())
        throw "GroupTTS: s1cA->linear->y not calculated";

    double phiN=s0cC->turn->phi.GetTF0();
    double xN=s0cC->linear0.x.GetTF0();
    double yN=s0cC->linear0.y.GetTF0();

    double xA=A->linear.x.GetTF0();
    double yA=A->linear.y.GetTF0();

    double xB;
    double yB;

    if (fabs(cos(phiN))<epsilon) // if axis vertical
    {
        xB=(xN-h);
        b1=sqr(lab)-sqr(xB-xA);
        if (b1<0.0)  // Cbopku HET
            throw "GroupTTS: b1<0 ";
        yB=(yA+(double)j1*sqrt(b1));
    }
    else
    {
        tg=tan(phiN);
        yN0.SetTF0(yN+h/cos(phiN));
        r1=lab-tg*xN+yN0.GetTF0()-yA;
        r2=lab+tg*xN-yN0.GetTF0()+yA;

        p=0.5*(2.0*xA-r1*tg+r2*tg);
        q0=sqr(xA)-r1*r2;
        b1=sqr(p)-q0/sqr(cos(phiN));

        if (b1<0.0)  // Cbopku HET
            throw "GroupTTS: b1<0 ";

        xB=((p+j1*sqrt(b1))*sqr(cos(phiN)));
        yB=(tg*(xB-xN)+yN0.GetTF0());
    }
    B->linear.x.SetTF0(xB);
    B->linear.y.SetTF0(yB);

    tang.SetTF0(tg);
    AB.phi.SetTF0(atan2(-yB+yA,
                        -xB+xA));
    s1->turn.phi.SetTF0(AB.phi.GetTF0()-GetAngleTT(s1cB,s1cA));
    s2->turn.phi.SetTF0(phiN-s2cC->alpha);
    CalcTF0Segment(s1,s1cA);
    CalcTF0Segment(s2,s2cB);
}

void GroupTTS::CalcTF1()
{

    if (!s0cC->turn->phi.IsCalculatedTF1())
        throw "GroupTTS: s0cC->turn->phi_ not calculated";
    if (!s0cC->linear0.x.IsCalculatedTF1())
        throw "GroupTTS: s0cC->linear0.x_ not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF1())
        throw "GroupTTS: s0cC->linear0.y_ not calculated";

    if (!s1cA->linear->x.IsCalculatedTF1())
        throw "GroupTTS: s1cA->linear->x_ not calculated";
    if (!s1cA->linear->y.IsCalculatedTF1())
        throw "GroupTTS: s1cA->linear->y_ not calculated";

    //  double

    double phiN=s0cC->turn->phi.GetTF0();
    double phiN_=s0cC->turn->phi.GetTF1();

    double xN=s0cC->linear0.x.GetTF0();


    double xN_=s0cC->linear0.x.GetTF1();
    double yN_=s0cC->linear0.y.GetTF1();

    double xA_=A->linear.x.GetTF1();
    double yA_=A->linear.y.GetTF1();

    double xA=A->linear.x.GetTF0();
    double yA=A->linear.y.GetTF0();

    double xB=B->linear.x.GetTF0();
    double yB=B->linear.y.GetTF0();

    double xB_,yB_;

    if (fabs(cos(phiN))<epsilon) // if axis vertical
    {
        xB_=xN_;
        yB_=yA_-(xB-xA)*
            (xB_-xA_)/
            (yB-yA);
    }
    else
    {
        tg_=(phiN_/sqr(cos(phiN)));

        yN0.SetTF1(yN_+h*sin(phiN)/
                   sqr(cos(phiN))*phiN_);
        xB_=((xA_*(xB-xA)+yA_*(yB-yA)-
              (tg_*xB-tg_*xN-tg*xN_+
               yN0.GetTF1())*
              (yB -yA))/
             ((xB-xA)+ tg*(yB-yA)));
        yB_=((xA_*(xB-xA)+
              yA_*(yB-yA)-
              xB_*(xB-xA))/
             (yB-yA));
    }
    B->linear.x.SetTF1(xB_);
    B->linear.y.SetTF1(yB_);

    if (fabs(xA-xB)<epsilon)
    {
        AB.phi.SetTF1((xB_-xA_)/
                      (lab*sin(AB.phi.GetTF0())));
    }
    else
    {
        AB.phi.SetTF1((yA_-yB_)/
                      (lab*cos(AB.phi.GetTF0())));
    }

    tang.SetTF1(tg_);
    s1->turn.phi.SetTF1(AB.phi.GetTF1());
    s2->turn.phi.SetTF1(phiN_);

    CalcTF1Segment(s1,s1cA);
    CalcTF1Segment(s2,s2cB);
}

void GroupTTS::CalcTF2()
{
    if (!s0cC->turn->phi.IsCalculatedTF2())
        throw "GroupTTS: s0cC->turn->phi__ not calculated";
    if (!s0cC->linear0.x.IsCalculatedTF2())
        throw "GroupTTS: s0cC->linear0.x__ not calculated";
    if (!s0cC->linear0.y.IsCalculatedTF2())
        throw "GroupTTS: s0cC->linear0.y__ not calculated";

    if (!s1cA->linear->x.IsCalculatedTF2())
        throw "GroupTTS: s1cA->linear->x__ not calculated";
    if (!s1cA->linear->y.IsCalculatedTF2())
        throw "GroupTTS: s1cA->linear->y__ not calculated";

    double phiN=s0cC->turn->phi.GetTF0();
    double phiN_=s0cC->turn->phi.GetTF1();
    double phiN__=s0cC->turn->phi.GetTF2();

    double xN=s0cC->linear0.x.GetTF0();
    double xN_=s0cC->linear0.x.GetTF1();


    double xN__=s0cC->linear0.x.GetTF2();
    double yN__=s0cC->linear0.y.GetTF2();

    double xA__=A->linear.x.GetTF2();
    double yA__=A->linear.y.GetTF2();

    double xA=A->linear.x.GetTF0();
    double yA=A->linear.y.GetTF0();

    double xA_=A->linear.x.GetTF1();
    double yA_=A->linear.y.GetTF1();

    double xB=B->linear.x.GetTF0();
    double yB=B->linear.y.GetTF0();

    double xB_=B->linear.x.GetTF1();
    double yB_=B->linear.y.GetTF1();


    double xB__,yB__;
    {
        if (fabs(cos(phiN))<epsilon) // if axis vertical
        {

            xB__=xN__;

            yB__=(yA__*(yB-yA)-
                  sqr(yB_-yA_)-
                  sqr(xB_-xA_)-
                  (xB-xA)*
                  (xB__-xA__))/
                 (yB-yA);
        }
        else
        {
            tg__=phiN__/sqr(cos(phiN))+
                 sqr(phiN_)*
                 sin(2.0*phiN)/
                 sqr(sqr(cos(phiN)));

            yN0.SetTF2(((yN__+
                         ((cos(phiN)*sqr(phiN_)+
                           sin(phiN)*phiN__)*
                          sqr(cos(phiN)))*h+
                         sin(phiN)*sin(2.0*phiN)*
                         sqr(phiN_)))/sqr(sqr(cos(phiN))));


          xB__=(xA__*(xB-xA)+xA_*(xB_-xA_)+
                  yA__*(yB-yA)+yA_*(yB_-yA_)-
                  (tg__*xB+tg_*xB-
                   tg__*xN-2.0*tg_*xN_-
                   tg*xN__+yN0.GetTF2())*
                  (yB-yA)-
                  (tg_*xB-tg_*xN-tg*xN_+yN0.GetTF1())*
                  (yB_-yA_)- xB_*(xB_-xA_)+tg_*(yB-yA)+
                  tg*(yB_- yA_))/
                 ((xB- xA)+ tg*(yB-yA));

            yB__=(yA__*(yB-yA)-
                  sqr(yB_-yA_)-
                    sqr(xB_-xA_)-
                  (xB-xA)*
                  (xB__-xA__))/
                 (yB-yA);
        }

        B->linear.x.SetTF2(xB__);
        B->linear.y.SetTF2(yB__);
        tang.SetTF2(tg__);

        if (fabs(xA-xB)<epsilon)
        {
            // формулы из паскалевского модуля и методички различны :(
            /*AB.phi.SetTF2(((xB__-xA__)*lab*sin(AB.phi.GetTF0())-
                           (xB_-xA_)* lab*cos(AB.phi.GetTF0())*AB.phi.GetTF1())/
                          sqr(lab*sin(AB.phi.GetTF0())));
            */
            AB.phi.SetTF2((xA__-xB__)*lab*sin(AB.phi.GetTF0()));

        }
        else
        {
            /*   AB.phi.SetTF2(((yA__-yB__)*lab*cos(AB.phi.GetTF0())-
                              (yA_-yB_)*  lab*sin(AB.phi.GetTF0())
                              *AB.phi.GetTF1())/
                             sqr(lab*cos(AB.phi.GetTF0())));
*/
            AB.phi.SetTF2((yA__-yB__)*lab*cos(AB.phi.GetTF0()));
        }

    }
    s1->turn.phi.SetTF2(AB.phi.GetTF2());
    s2->turn.phi.SetTF2(s0cC->turn->phi.GetTF2());

    CalcTF2Segment(s1,s1cA);
    CalcTF2Segment(s2,s2cB);


}


void GroupTTS::CalcReaction()
{

}
