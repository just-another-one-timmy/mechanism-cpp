#include<Mechan.h>

static double Mechan::GetRM(CompManager *cm);//reduced moment
{
    double RM;
    for (map<string, Segment *>::iterator i = segments.begin(); i!=segments.end(); i++)
    {
        Segment *s = i->second;
        for (list<Force *>::iterator f = s->forces.begin(); f!=s->forces.end(); f++)
        {
            Force  *Fi = *f;

            if(!Fi->IsCalculatedt())
                throw "Mechan::GetRM ##1";
            if(!Fi->IsCalculatedx())
                throw "Mechan::GetRM ##2";
            if(!Fi->IsCalculatedy())
                throw "Mechan::GetRM ##2";


            double T=Fi->GetForcet()
            double Fx=Fi->GetForcex();
            double Fy=Fi->GetForcey();
            double phi_=s->turn.phi.GetTF1();
            double xK_=Fi->linear->x.GetTF1();
            double yK_=Fi->linear->y.GetTF1();


            RM+=(Fx*xK_+Fy*yK_+M*phi_);

        }

    }
    return RM;
}

static double Mechan::GetEMoI(CompManager *cm);             //equivalent moment of inertia
{
    double m,I,phi_,xS_,yS_,EMoI=0;
    for (map<string, Segment *>::iterator i = segments.begin(); i!=segments.end(); i++)
    {
        Segment *s = i->second;
        m=s->mass;
        I=s->rot_inertia;
        phi_=s->turn.phi.GetTF1();
        xS_=s->cmass->x.GetTF1();
        yS_=s->cmass->y.GetTF1();

        EMoF+=m*(sqr(xS_)+sqr(yS_))+I*sqr(phi_);

    }

return EMoF;
}

static double Mechan::GetEMoI_(CompManager *cm);
{
    double m,I,phi_,phi__,xS_,xS__,yS_,yS__,EMoI_=0;
    for (map<string, Segment *>::iterator i = segments.begin(); i!=segments.end(); i++)
    {
        Segment *s = i->second;
        m=s->mass;
        I=s->rot_inertia;
        phi_=s->turn.phi.GetTF1();
        phi_=s->turn.phi.GetTF2();

        xS_=s->cmass->x.GetTF1();
        yS_=s->cmass->y.GetTF1();

        xS__=s->cmass->x.GetTF2();
        yS__=s->cmass->y.GetTF2();

        EMoF_+=m*(xS_*xS__+yS_*yS__)+I*phi_*phi__;

    }

return 2*EMoF_;

}
