#include "Group.h"

#include <cmath>
double Group::GetDist(ConnectorTurn *c1,ConnectorTurn *c2)
{
    return sqrtl(sqr(c1->ro)+sqr(c2->ro)-2.0*(c1->ro)*(c2->ro)*cos((c1->phi)-(c2->phi)));
}
/*
double Group::GetHeight(ConnectorTurn *c1,ConnectorSliding *c2)
{
    double x=c1->ro*cos(c1->phi);
    double y=c1->ro*sin(c1->phi);

    double x0=c2->ro*cos(c2->phi);
    double y0=c2->ro*sin(c2->phi);

    double A=sin(c2->alpha);
    double B=cos(c2->alpha);

    return (A*(x-x0)+B*(y-y0));
}
*/

double Group::PointLineDistance(double x1, double y1, double A, double B, double C)
{
    double res;
    double num = abs(A*x1 + B*y1 + C);
    double denum = sqrt(A*A + B*B);
    res = num/denum;
    if (C<0)
        res = -res;
    return res;
}

double Group::PointLineDistanceP(double ro1, double phi1, double ro2, double phi2, double alpha)
{
    double x1 = ro1*cos(phi1);
    double y1 = ro1*sin(phi1);
    double x2 = ro2*cos(phi2);
    double y2 = ro2*sin(phi2);

    double A = tan(alpha);
    double B = -1;
    double C = y2 - x2*tan(alpha);

    double res = PointLineDistance(x1,y1,A,B,C);
    return res;
}

double Group::GetHeight(ConnectorTurn *c1, ConnectorSliding *c2)
{
    double res = PointLineDistanceP(c1->ro, c1->phi, c2->ro, c2->phi, c2->alpha);
    return res;
}

double Group::GetAngleSS(ConnectorSliding *c1,ConnectorSliding *c2)
{
    return (c1->alpha)-(c2->alpha);
}

double Group::GetAngleTT(ConnectorTurn *c1,ConnectorTurn *c2)
{
    double x1=c1->ro*cos(c1->phi);
    double y1=c1->ro*sin(c1->phi);
    double x2=c2->ro*cos(c2->phi);
    double y2=c2->ro*sin(c2->phi);

    return atan2(y2-y1,x2-x1);
}

void Group::CalcTF()
{
    CalcTF0();
    CalcTF1();
    CalcTF2();
}

void Group::CalcTF0Segment(Segment *s,ConnectorTurn *c)
{

    if (!s->turn.phi.IsCalculatedTF0())
    {
        throw "CaltTF0Segment: Segment.turn  not calculated";
    }

        double x = c->linear->x.GetTF0();
        double y = c->linear->y.GetTF0();
        double ro= c->ro;
        double phi0 = s->turn.phi.GetTF0();
        double phi = c->phi;

    if (!s->polus->linear->x.IsCalculatedTF0())
    {
        // Calculating TF0 of polus
        s->polus->linear->x.SetTF0(x-ro*cos(phi0+phi));  //
    }
    if (!s->polus->linear->y.IsCalculatedTF0())
    {
        // Calculating TF0 of polus
        s->polus->linear->y.SetTF0(y-ro*sin(phi0+phi)); //
    }

    double pol_x=s->polus->linear->x.GetTF0();
    double pol_y=s->polus->linear->y.GetTF0();


    for (list<Connector*>::iterator i = s->connectors.begin(); i!=s->connectors.end(); i++)
    {

        Connector *c_ = *i;
        switch (c_->Type())
        {
            case CONNECTOR_TYPE_SLIDING:
            {
                ConnectorSliding *cs = (ConnectorSliding*)c_;

                double ro=cs->ro;
                double phi=cs->phi;


                if (!cs->linear0.x.IsCalculatedTF0())
                {
                    cs->linear0.x.SetTF0(pol_x+ro*cos(phi0+phi));
                }
                if (!cs->linear0.y.IsCalculatedTF0())
                {
                    cs->linear0.y.SetTF0(pol_y+ro*sin(phi0+phi));
                }
                if (cs->turn == NULL)
                    throw "CaltTF0Segment: ConnectorSliding don't have TurnTF";
                //if (!cs->turn->phi.IsCalculatedTF0())
                {
                      double phi0 = s->turn.phi.GetTF0();

                    cs->turn->phi.SetTF0(phi0+cs->alpha);
                }
                break;
            }

            case CONNECTOR_TYPE_TURN:
            {
                ConnectorTurn *ct = (ConnectorTurn*)c_;
                if (ct->linear == NULL)
                {
                    string msg_err = "CalcTF0Segment: ConnectorTurn ["+ct->name+"] don't have LinearTF!";
                    throw msg_err.c_str();
                }

                    double ro=ct->ro;
                    double phi=ct->phi;

                if(!ct->linear->x.IsCalculatedTF0())
                {

                    ct->linear->x.SetTF0(pol_x+ro*cos(phi0+phi));
                }
                if (!ct->linear->y.IsCalculatedTF0())
                {
                    ct->linear->y.SetTF0(pol_y+ro*sin(phi0+phi));
                }
                break;
            }
        default:
            throw ("CalcTF0Segment  Type of Connector o_0 ");
        }
    }



}

void Group::CalcTF1Segment(Segment *s,ConnectorTurn *c)
{

    if (!s->turn.phi.IsCalculatedTF1())
    {
        throw "CaltTF1Segment: Segment.turn  not calculated";
    }

        double x1 = c->linear->x.GetTF1();
        double y1 = c->linear->y.GetTF1();
        double ro= c->ro;
        double phi01 = s->turn.phi.GetTF1();
        double phi0 = s->turn.phi.GetTF0();

        double phi = c->phi;

 //   if (!s->polus->linear->x.IsCalculatedTF1())
    {
        // Calculating TF1 of polus
        //xa1:=xs1+las*sin(fiab+alfas)*fiab1;
        s->polus->linear->x.SetTF1(x1+ro*sin(phi0+phi)*phi01);  //
    }
  //  if (!s->polus->linear->y.IsCalculatedTF1())
    {
        // Calculating TF1 of polus
        //ya1:=ys1-las*cos(fiab+alfas)*fiab1;
        s->polus->linear->y.SetTF1(y1-ro*cos(phi0+phi)*phi01); //
    }

    double pol_x1=s->polus->linear->x.GetTF1();
    double pol_y1=s->polus->linear->y.GetTF1();


    for (list<Connector*>::iterator i = s->connectors.begin(); i!=s->connectors.end(); i++)
    {

        Connector *c_ = *i;
        switch (c_->Type())
        {
            case CONNECTOR_TYPE_SLIDING:
            {
                ConnectorSliding *cs = (ConnectorSliding*)c_;

                double ro=cs->ro;
                double phi=cs->phi;


                if (!cs->linear0.x.IsCalculatedTF1())
                {
                    cs->linear0.x.SetTF1(pol_x1-ro*sin(phi0+phi)*phi01);
                }
                if (!cs->linear0.y.IsCalculatedTF1())
                {
                    cs->linear0.y.SetTF1(pol_y1+ro*cos(phi0+phi)*phi01);
                }
                if (cs->turn == NULL)
                    throw "CaltTF0Segment: ConnectorSliding don't have TurnTF";
                if (!cs->turn->phi.IsCalculatedTF1())
                {

                    cs->turn->phi.SetTF1(phi01);
                }
                break;
            }

            case CONNECTOR_TYPE_TURN:
            {
                ConnectorTurn *ct = (ConnectorTurn*)c_;
                if (ct->linear == NULL)
                    throw "CaltTF0Segment: ConnectorTurn don't have LinearTF";

                    double ro=ct->ro;
                    double phi=ct->phi;

     //           if(!ct->linear->x.IsCalculatedTF1())
                {

                    ct->linear->x.SetTF1(pol_x1-ro*sin(phi0+phi)*phi01);

               //  xs1:=xa1-las*sin(fiab+alfas)*fiab1;

                }
       //         if (!ct->linear->y.IsCalculatedTF1())
                {
                    ct->linear->y.SetTF1(pol_y1+ro*cos(phi0+phi)*phi01);
                //  ys1:=ya1+las*cos(fiab+alfas)*fiab1;

                }
                break;
            }
        default:
            throw ("CalcTF1Segment  Type of Connector o_0 ");
        }
    }

/*
  xs1:=xa1-las*sin(fiab+alfas)*fiab1;
  ys1:=ya1+las*cos(fiab+alfas)*fiab1;

*/
}

void Group::CalcTF2Segment(Segment *s,ConnectorTurn *c)
{


    if (!s->turn.phi.IsCalculatedTF2())
    {
        throw "CaltTF2Segment: Segment.turn  not calculated";
    }

        double x2 = c->linear->x.GetTF2();
        double y2 = c->linear->y.GetTF2();
        double ro= c->ro;
        double phi0 = s->turn.phi.GetTF0();
        double phi01 = s->turn.phi.GetTF1();
        double phi02 = s->turn.phi.GetTF2();

        double phi = c->phi;

    if (!s->polus->linear->x.IsCalculatedTF2())
    {
        // Calculating TF2 of polus
        //  xa2:=xs2+las*cos(fiab+alfas)*sqr(fiab1)+las*sin(fiab+alfas)*fiab2;
        s->polus->linear->x.SetTF2(x2+ro*cos(phi0+phi)*sqr(phi01)+
                                      ro*sin(phi0+phi)*phi02);  //
    }
    if (!s->polus->linear->y.IsCalculatedTF2())
    {
        // Calculating TF2 of polus
        //ya2:=ys2+las*sin(fiab+alfas)*sqr(fiab1)-las*cos(fiab+alfas)*fiab2;

        s->polus->linear->y.SetTF2(y2+ro*sin(phi0+phi)*sqr(phi01)-
                                      ro*cos(phi0+phi)*phi02); //
    }

    double pol_x2=s->polus->linear->x.GetTF2();
    double pol_y2=s->polus->linear->y.GetTF2();


    for (list<Connector*>::iterator i = s->connectors.begin(); i!=s->connectors.end(); i++)
    {

        Connector *c_ = *i;
        switch (c_->Type())
        {
            case CONNECTOR_TYPE_SLIDING:
            {
                ConnectorSliding *cs = (ConnectorSliding*)c_;

                double ro=cs->ro;
                double phi=cs->phi;


                if (!cs->linear0.x.IsCalculatedTF2())
                {
                    cs->linear0.x.SetTF2(pol_x2-ro*cos(phi0+phi)*sqr(phi01)-ro*sin(phi0+phi)*phi02);
                }
                if (!cs->linear0.y.IsCalculatedTF2())
                {
                    cs->linear0.y.SetTF2(pol_y2-ro*sin(phi0+phi)*sqr(phi01)+ro*cos(phi0+phi)*phi02);
                }
                if (cs->turn == NULL)
                    throw "CaltTF2Segment: ConnectorSliding don't have TurnTF";
                if (!cs->turn->phi.IsCalculatedTF2())
                {

                    cs->turn->phi.SetTF2(phi02);
                }
                break;
            }

            case CONNECTOR_TYPE_TURN:
            {
                ConnectorTurn *ct = (ConnectorTurn*)c_;
                if (ct->linear == NULL)
                    throw "CaltTF0Segment: ConnectorTurn don't have LinearTF";

                    double ro=ct->ro;
                    double phi=ct->phi;

           //     if(!ct->linear->x.IsCalculatedTF2())
                {
                //    xs2:=xa2-las*cos(fiab+alfas)*sqr(fiab1)-las*sin(fiab+alfas)*fiab2;
                    ct->linear->x.SetTF2(pol_x2-ro*cos(phi0+phi)*sqr(phi01)-ro*sin(phi0+phi)*phi02);
                }
           //     if (!ct->linear->y.IsCalculatedTF2())
                {
        //          ys2:=ya2-las*sin(fiab+alfas)*sqr(fiab1)+las*cos(fiab+alfas)*fiab2;
                    ct->linear->y.SetTF2(pol_y2-ro*sin(phi0+phi)*sqr(phi01)+ro*cos(phi0+phi)*phi02);
                }
                break;
            }
        default:
            throw ("CalcTF0Segment  Type of Connector o_0 ");
        }
    }



/*


    xs2:=xa2-las*cos(fiab+alfas)*sqr(fiab1)-las*sin(fiab+alfas)*fiab2;
          ys2:=ya2-las*sin(fiab+alfas)*sqr(fiab1)+las*cos(fiab+alfas)*fiab2;


*/
}
