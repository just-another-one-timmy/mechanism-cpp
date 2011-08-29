#include "GroupTTT.h"

GROUP_TYPE GroupTTT::Type()
{
    return GROUP_TYPE_TTT;
}

GroupTTT::GroupTTT(KPTurn *K1,KPTurn *K2,KPTurn *K3,Segment *s1_, Segment *s2_)
{
    A = K1;
    B = K2;
    C = K3;
    s1 = s1_;
    s2 = s2_;

    j1=1;   // 1 or -1
//if ((s1->name=="s4")||(s2->name=="s4")) j=-1;

    ConnectorTurn *ct1,*ct2;
    ct1=(ConnectorTurn*)A->GetC1();
    ct2=(ConnectorTurn*)A->GetC2();
    if (ct1->s == s1)
        s1cA = ct1;
    else
        if (ct2->s == s1)
            s1cA = ct2;
        else throw "GroupTTT: KPair A not connected to s1";

    ct1=(ConnectorTurn*)B->GetC1();
    ct2=(ConnectorTurn*)B->GetC2();
    if (ct1->s == s1)
        s1cB = ct1;
    else
        if (ct2->s == s1)
            s1cB = ct2;
        else throw "GroupTTT: KPair B not connected to s1";

    if (ct1->s == s2)
        s2cB = ct1;
    else
        if (ct2->s == s2)
            s2cB = ct2;
        else throw "GroupTTT: KPair B not connected to s2";
    ct1=(ConnectorTurn*)C->GetC1();
    ct2=(ConnectorTurn*)C->GetC2();

    if (ct1->s == s2)
        s2cC = ct1;
    else
        if (ct2->s == s2)
            s2cC = ct2;
        else throw "GroupTTT: KPair C not connected to s2";

    lab=GetDist(s1cA,s1cB);
    lcb=GetDist(s2cC,s2cB);
}


void GroupTTT::CalcTF0()
{
    cout << "Hello from TTT!" << endl;
    double lac,b1,beta,alfa;

    if(!s1cA->linear->x.IsCalculatedTF0())
        throw "GroupTTT: s1cA->linear->x not calculated";
    if(!s1cA->linear->y.IsCalculatedTF0())
        throw "GroupTTT: s1cA->linear->y not calculated";

    if(!s2cC->linear->x.IsCalculatedTF0())
        throw "GroupTTT: s2cC->linear->x not calculated";
    if(!s2cC->linear->y.IsCalculatedTF0())
        throw "GroupTTT: s2cC->linear->y not calculated";

    double xA=A->linear.x.GetTF0();
    double yA=A->linear.y.GetTF0();
    double xC=C->linear.x.GetTF0();
    double yC=C->linear.y.GetTF0();



    lac=sqrt(sqr(xA-xC)+sqr(yA-yC));
    b1=(sqr(lab)+sqr(lac)-sqr(lcb))
        /(2.0*lab*lac);  //cos beta
    if (fabs(b1)<=1.0)   //  Cbopku HET

        beta=acos(b1); //beta=atan2(sqrt(1-b1*b1),b1);
    else
        throw "GroupTTT: fabs (cos( beta))  > 1";
// Cbopku HET
    alfa=atan2(yC-yA,xC-xA);
    AB.phi.SetTF0(alfa+(double)j1*beta);
    CB.phi.SetTF0(atan2(lab*sin(AB.phi.GetTF0())-yC+yA,
                        lab*cos(AB.phi.GetTF0())-xC+xA));

    s1->turn.phi.SetTF0(AB.phi.GetTF0()-GetAngleTT(s1cA,s1cB));
    s2->turn.phi.SetTF0(CB.phi.GetTF0()-GetAngleTT(s2cC,s2cB));

    CalcTF0Segment(s1,s1cA);
    CalcTF0Segment(s2,s2cC);
}

void GroupTTT::CalcTF1()
{
    if(!s1cA->linear->x.IsCalculatedTF1())
        throw "GroupTTT: s1cA->linear->x_ not calculated";
    if(!s1cA->linear->y.IsCalculatedTF1())
        throw "GroupTTT: s1cA->linear->y_ not calculated";

    if(!s2cC->linear->x.IsCalculatedTF1())
        throw "GroupTTT: s2cC->linear->x_ not calculated";
    if(!s2cC->linear->y.IsCalculatedTF1())
        throw "GroupTTT: s2cC->linear->y_ not calculated";

    double xA_=A->linear.x.GetTF1();
    double yA_=A->linear.y.GetTF1();

    double xC_=C->linear.x.GetTF1();
    double yC_=C->linear.y.GetTF1();

    double phiAB=AB.phi.GetTF0();
    double phiCB=CB.phi.GetTF0();

    if (fabs(phiAB-phiCB)<epsilon)
    {

            double xA__=A->linear.x.GetTF2();
            double yA__=A->linear.y.GetTF2();


            double c1=xA_*sin(phiAB)-
                        yA_*cos(phiAB);
            double b10=xA__*cos(phiAB)+
                        yA__*sin(phiAB);
            CB.phi.SetTF1((-c1*(lcb/lab)-j1*sqrt(c1*c1*sqr(lcb/lab)-lcb*(lcb/lab-1)*
                         (c1*c1/lab-b10)))/lcb/(lcb/lab-1));
            AB.phi.SetTF1((sqr(CB.phi.GetTF1())*lcb+b10)/
                            (CB.phi.GetTF1()*lcb+c1));

    }
      else
      {
          AB.phi.SetTF1(((xA_-xC_)*cos(phiCB)+
                         (yA_-yC_)*sin(phiCB))/
                        (lab*sin(phiAB-phiCB)));
          CB.phi.SetTF1(((xA_-xC_)*cos(phiAB)+
                         (yA_-yC_)*sin(phiAB))/
                        (lcb*sin(phiAB-phiCB)));
      }

      s1->turn.phi.SetTF1(AB.phi.GetTF1());
      s2->turn.phi.SetTF1(CB.phi.GetTF1());
      CalcTF1Segment(s1,s1cA);
      CalcTF1Segment(s2,s2cC);

}

void GroupTTT::CalcTF2()
{
    if(!s1cA->linear->x.IsCalculatedTF2())
        throw "GroupTTT: s1cA->linear->x__ not calculated";
    if(!s1cA->linear->y.IsCalculatedTF2())
        throw "GroupTTT: s1cA->linear->y__ not calculated";

    if(!s2cC->linear->x.IsCalculatedTF2())
        throw "GroupTTT: s2cC->linear->x__ not calculated";
    if(!s2cC->linear->y.IsCalculatedTF2())
        throw "GroupTTT: s2cC->linear->y__ not calculated";


    double xA__=A->linear.x.GetTF2();
    double yA__=A->linear.y.GetTF2();
    double xC__=C->linear.x.GetTF2();
    double yC__=C->linear.y.GetTF2();

    double xA_=A->linear.x.GetTF1();
    double yA_=A->linear.y.GetTF1();
    double xC_=C->linear.x.GetTF1();
    double yC_=C->linear.y.GetTF1();


    double phiAB=AB.phi.GetTF0();
    double phiCB=CB.phi.GetTF0();

    double phiAB_=AB.phi.GetTF1();
    double phiCB_=CB.phi.GetTF1();

    if (fabs(phiAB-phiCB)<epsilon)
    {
      /*   надо доделать. формулы не знаю...
           иначе возможна ошибка приделении на 0
*/
       throw "GroupTTT: CalcTF2() ##1";

    }
    else
    {
        AB.phi.SetTF2(((xA__-xC__)*cos(phiCB)+
                   (yA__-yC__)*sin(phiCB)-
                   (xA_ -xC_ )*sin(phiCB)*phiCB_+
                   (yA_ -yC_ )*cos(phiCB)*phiCB_-
                lab*cos(phiAB-phiCB)*phiAB_*
                (phiAB_-phiCB_))/
                (lab*sin(phiAB-phiCB)));
        CB.phi.SetTF2(((xA__-xC__)*cos(phiAB)+
                   (yA__-yC__)*sin(phiAB)-
                   (xA_ -xC_ )*sin(phiAB)*phiAB_+
                   (xA_ -xC_ )*cos(phiAB)*phiAB_-
                lcb*cos(phiAB-phiCB)*phiCB_*
                (phiAB_-phiCB))/
                (lcb*sin(phiAB-phiCB)));
    }
    s1->turn.phi.SetTF2(AB.phi.GetTF2());
    s2->turn.phi.SetTF2(CB.phi.GetTF2());
    CalcTF2Segment(s1,s1cA);
    CalcTF2Segment(s2,s2cC);

}

void GroupTTT::CalcReaction()
{

double SumTorque1=0;

for (list<Force *>::iterator f = s1->forces.begin(); f!=s1->forces.end(); f++)
    {
        Force  *Fi = *f;
        double T=0;
        double Fx=0;
        double Fy=0;
        if(Fi->IsCalculatedt())
            T=Fi->GetForcet();
        if(Fi->IsCalculatedx())
            Fx=Fi->GetForcex();
        if(Fi->IsCalculatedy())
            Fy=Fi->GetForcey();

        double leverx = -Fi->linear->x.GetTF0()+A->linear.x.GetTF0();
        double levery = -Fi->linear->y.GetTF0()+A->linear.y.GetTF0();

        SumTorque1+=T+Fx*leverx-Fy*levery;
    }

double SumTorque2=0;

/*
   dd:=(yb[i]-ya[i])*(xb[i]-xc[i])+(yb[i]-yc[i])*(xa[i]-xb[i]);
        dd1:=-k3*(xb[i]-xc[i])+k4*(xa[i]-xb[i]);
        dd2:=k4*(ya[i]-yb[i])+k3*(yb[i]-yc[i]);

*/

for (list<Force *>::iterator f = s2->forces.begin(); f!=s2->forces.end(); f++)
    {
        Force  *Fi = *f;
        double T=0;
        double Fx=0;
        double Fy=0;
        if(Fi->IsCalculatedt())
            T=Fi->GetForcet();
        if(Fi->IsCalculatedx())
            Fx=Fi->GetForcex();
        if(Fi->IsCalculatedy())
            Fy=Fi->GetForcey();
        double leverx = -Fi->linear->x.GetTF0()+C->linear.x.GetTF0();
        double levery = -Fi->linear->y.GetTF0()+C->linear.y.GetTF0();


            SumTorque2+=T+Fx*leverx-Fy*levery;
    }

/*
   dd:=(yb[i]-ya[i])*(xb[i]-xc[i])+(yb[i]-yc[i])*(xa[i]-xb[i]);
        dd1:=-k3*(xb[i]-xc[i])+k4*(xa[i]-xb[i]);
        dd2:=k4*(ya[i]-yb[i])+k3*(yb[i]-yc[i]);

*/

double leverxAB = A->linear.x.GetTF0()-B->linear.x.GetTF0();
double leveryAB = A->linear.y.GetTF0()-B->linear.y.GetTF0();

double leverxCB = C->linear.x.GetTF0()-B->linear.x.GetTF0();
double leveryCB = C->linear.y.GetTF0()-B->linear.y.GetTF0();

double d=leveryAB*leverxCB-leverxAB*leveryCB;
double d1=SumTorque1*leverxCB+SumTorque2*leverxAB;
double d2=SumTorque2*leveryAB+SumTorque1*leveryCB;

double R21x=d1/d;
double R21y=d2/d;

B->R1->SetForce(R21x,R21y,0);
B->R2->SetForce(-R21x,-R21y,0);

double SumFx1=0;
double SumFy1=0;

for (list<Force *>::iterator f = s1->forces.begin(); f!=s1->forces.end(); f++)
    {
        Force  *Fi = *f;
        if(Fi->IsCalculatedx())
            SumFx1+=Fi->GetForcex();
        if(Fi->IsCalculatedy())
            SumFy1+=Fi->GetForcey();
    }

double RAx=-SumFx1;
double RAy=-SumFy1;


A->R1->SetForce(RAx,RAy,0);
A->R2->SetForce(-RAx,-RAy,0);

double SumFx2=0;
double SumFy2=0;

for (list<Force *>::iterator f = s2->forces.begin(); f!=s2->forces.end(); f++)
    {
        Force  *x = *f;
        if(x->IsCalculatedx())
            SumFx2+=x->GetForcex();
        if(x->IsCalculatedy())
            SumFy2+=x->GetForcey();
    }

double RCx=-SumFx2;
double RCy=-SumFy2;

C->R2->SetForce(RCx,RCy,0);
C->R1->SetForce(-RCx,-RCy,0);

}
