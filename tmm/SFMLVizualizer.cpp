#include "SFMLVizualizer.h"
#include <SFML/Graphics.hpp>

SFMLVizualizer::SFMLVizualizer(CompManager *c, sf::RenderWindow *w)
{
    this->c = c;
    this->w = w;

    h = w->GetHeight();
    we = w->GetWidth();
    sc0 = 350;
    sc1 = 350;
    sc2 = 350;
    scf = 0.02;

    tf1_color = 0xFFAABB;
    tf2_color = 0xBBFFAA;
}

void SFMLVizualizer::Draw()
{
    map <string, Segment*> segments = c->GetSegments();
    for (map<string, Segment *>::iterator i = segments.begin(); i!=segments.end(); i++)
    {
        Segment *s = i->second;

        double pol_x = s->polus->linear->x.GetTF0();
        double pol_y = s->polus->linear->y.GetTF0();
        pol_x*=sc0;  pol_y*=sc0;

        //cout << "Assuming polus coordinates are: " << pol_x << "  " << pol_y << endl;
        for (list<Connector *>::iterator j = s->connectors.begin(); j!=s->connectors.end(); j++)
        {
            Connector *c = *j;
            switch (c->Type())
            {
                case CONNECTOR_TYPE_TURN:
                {
                    ConnectorTurn *ct = (ConnectorTurn *)c;
                    if (!ct->linear->x.IsCalculatedTF0())
                        cout <<"X not calcul" << ct->name << endl;
                    if (!ct->linear->y.IsCalculatedTF0())
                        cout <<"Y not calcul" << ct->name << endl;

                    double x = ct->linear->x.GetTF0();
                    double y = ct->linear->y.GetTF0();
                    x*=sc0; y*=sc0;

                    sf::Shape circle = sf::Shape::Circle(x, h-y,2, sf::Color::Red, 2, sf::Color::Red);
                    circle.EnableFill(false);
                    w->Draw(circle);
                    if (s->name!="Ground")
                        w->Draw(sf::Shape::Line(pol_x, h-pol_y, x, h-y, 2, sf::Color::White));


                    //  vector TF1
                    try
                    {
                        double x1 = ct->linear->x.GetTF1();
                        double y1 = ct->linear->y.GetTF1();
                        x1*=sc1; y1*=sc1;
                        //w->Draw(sf::Shape::Line(x, h-y, x+x1, h-(y+y1), 1, (ct->name=="s3c1")?sf::Color::Green:sf::Color::Yellow));
                        DrawArrow(x, h-y, x+x1, h-(y+y1), tf1_color);
                    }
                    catch (const char *s) { cout << s << endl; };

                    //  vector TF2
                    try
                    {
                        double x2 = ct->linear->x.GetTF2();
                        double y2 = ct->linear->y.GetTF2();
                        x2*=sc2; y2*=sc2;
                        //w->Draw(sf::Shape::Line(x, h-y, x+x2, h-(y+y2), 1, sf::Color::Cyan));
                        DrawArrow(x, h-y, x+x2, h-(y+y2), tf2_color);
                    }
                    catch (const char *s) { cout << s << endl; };

                    break;
                }

                case CONNECTOR_TYPE_SLIDING:
                {
                    ConnectorSliding *cs = (ConnectorSliding *)c;
                    double x = cs->linear0.x.GetTF0();
                    double y = cs->linear0.y.GetTF0();
                    x*=sc0; y*=sc0;

                    double phi = cs->turn->phi.GetTF0();
                    double len = 50;
                    double delta_x = len*cos(phi);
                    double delta_y = len*sin(phi);
                    w->Draw(sf::Shape::Line(x-delta_x, h-(y-delta_y), x+delta_x, h-(y+delta_y), 1, sf::Color::Green));

                    double rh = 10, rw = 16;
                    double x1 = x - rw/2, x2 = x + rw/2;
                    double y1 = y + rh/2, y2 = y - rh/2;
                    sf::Shape rect = sf::Shape::Rectangle(-rw/2,-rh/2,+rw/2,+rh/2,sf::Color::Blue, 2, sf::Color::Blue);
                    //cout << rect.GetPosition().x << " <-- x " << endl;
                    //cout << rect.GetPosition().y << " <-- y " << endl;
                    rect.Rotate(phi*180/pi);
                    rect.SetPosition(x, h-y);
                    rect.EnableFill(false);
                    w->Draw(rect);
                    //cout << rect.GetPosition().x << " <-- new x " << endl;
                    //cout << rect.GetPosition().y << " <-- new y " << endl;
                    if (s->name!="Ground")// *
                         w->Draw(sf::Shape::Line(pol_x, h-pol_y, x, h-y, 1, sf::Color::Blue));

                    //  vector TF1
                    try
                    {
                        double x1 = cs->linear0.x.GetTF1();
                        double y1 = cs->linear0.y.GetTF1();
                        x1*=sc1; y1*=sc1;
                        //w->Draw(sf::Shape::Line(x, h-y, x+x1, h-(y+y1), 1, sf::Color::Yellow));
                        DrawArrow(x, h-y, x+x1, h-(y+y1), tf1_color);
                    }
                    catch (const char *s) { cout << s << endl; };

                    //  vector TF2
                    try
                    {
                            double x2 = cs->linear0.x.GetTF2();
                            double y2 = cs->linear0.y.GetTF2();
                            x2*=sc2; y2*=sc2;
                            //w->Draw(sf::Shape::Line(x, h-y, x+x2, h-(y+y2), 1, sf::Color::Cyan));
                            DrawArrow(x, h-y, x+x2, h-(y+y2), tf2_color);
                    }
                    catch (const char *s) { cout << s << endl; };

                    break;
                }
                default: cout << "o_O" << endl;
            }
        }

   /*    w->Draw(sf::Shape::Circle(pol_x, h-pol_y, 5, sf::Color::Blue));
       double phi=s->turn.phi.GetTF0();
       w->Draw(sf::Shape::Line(pol_x, h-pol_y, pol_x+cos(phi)*100, h-(pol_y+sin(phi)*100), 1, sf::Color::Blue));
*/
 //if (s->name!="s3")
// continue;
/*
 for (list<Force *>::iterator j = s->forces.begin(); j!=s->forces.end(); j++)
        {
            Force *f = *j;
  try
            {

            double x = f->linear->x.GetTF0();
            double y = f->linear->y.GetTF0();
        x*=sc0;y*=sc0;

            double fx = f->GetForcex();
            double fy = f->GetForcey();

if (!f->IsCalculatedx())
cout << "fuck!!!" << endl;;
            fx*=scf; fy*=scf;

            w->Draw(sf::Shape::Line(x, h-y, x+fx, h-(y+fy), 2, sf::Color::Magenta));
              }
            catch (const char *s) { cout << s << endl; };

        }
*/

    }

}

void RotatePoint(double &x, double &y, double ox, double oy, double alpha)
{
    double xn, yn;
    xn = ox + (x-ox)*cos(alpha) - (y-oy)*sin(alpha);
    yn = oy + (x-ox)*sin(alpha) + (y-oy)*cos(alpha);
    x = xn;
    y = yn;
}

void DecreaseVector(double x1, double y1, double &x_n1, double &y_n1)
{
    double dx = (x_n1 - x1)*0.9;
    double dy = (y_n1 - y1)*0.9;
    x_n1 = x1 + dx;
    y_n1 = y1 + dy;
}

void SFMLVizualizer::DrawArrow(int x1, int y1, int x2, int y2, int icolor)
{
    int red, green, blue;
    blue = icolor%255;
    icolor/=255;
    green = icolor%255;
    icolor/=255;
    red = icolor;
    sf::Color color = sf::Color(red, green, blue);

    int line_width = 1;
    w->Draw(sf::Shape::Line(x1, y1, x2, y2, line_width, color));

    double x_n1, y_n1, x_n2, y_n2;
    x_n1 = x_n2 = x2;
    y_n1 = y_n2 = y2;

    RotatePoint(x_n1, y_n1, x1, y1, pi/48);
    RotatePoint(x_n2, y_n2, x1, y1, -pi/48);
    DecreaseVector(x1, y1, x_n1, y_n1);
    DecreaseVector(x1, y1, x_n2, y_n2);


    w->Draw(sf::Shape::Line(x_n1, y_n1, x2, y2, line_width, color));
    w->Draw(sf::Shape::Line(x_n2, y_n2, x2, y2, line_width, color));
}
