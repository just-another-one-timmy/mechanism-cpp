#include <cmath>
#include <sstream>
using namespace std;

#include <SFML/graphics.hpp>

#include "tmm/CompManager.h"
#include "tmm/GroupBuilder.h"
#include "tmm/SFMLVizualizer.h"
#include "tmm/Mechan.h"
#include "tmm/XMLLoader.h"
#include "tmm/XMLSaver.h"

void ProcessAppEvents(sf::RenderWindow &App, sf::View &v, GroupManager &gm);
void PrintDebugInfo(CompManager &cm, GroupManager &gm);
void PrepareFont(sf::Font &MyFont);
void AddHelpText(sf::RenderWindow &v, sf::Font &f, GroupManager &gm);
void BuildMechanism(CompManager &cm);

//* работает х-во
int step_per_second = 250;
double step_time = 1.0/step_per_second;

//*
enum STEP_MODE{SM_HARD_STEPS_CNT=0, SM_FREE_STEPS_CNT};
STEP_MODE step_mode = SM_FREE_STEPS_CNT;

const char *res_path = "resources/";
const char *font_name = "lucon.ttf";

void BuildMechanism(CompManager &cm, GroupManager &gm)
{
    XMLLoader::SetManagers(&cm, &gm);
    XMLSaver::SetManagers(&cm, &gm);

    bool i_want_load_this = false;
    string mname = "invars";

    if (i_want_load_this)
        XMLLoader::Load("xmls\\"+mname+".xml");
    else
    {
    cm.AddSegment("Ground", 10000, 0);

    cm.AddConnectorSlidingD("s0c1","Ground",0.0,-0.150, pi/2);
    cm.AddConnectorTurnD("s0c2", "Ground", 0.20,0.10);
    cm.AddConnectorTurnD("s0c3", "Ground", 0.20,0.10);

    cm.AddSegment("s1");
    cm.AddConnectorTurnD("s1c2", "s1", 0.0,0.0);
    cm.AddConnectorSliding("s1c1","s1",0.0,0.0, 0);
    cm.AddConnectorSliding("s1c3","s1",0.0,0.0, pi/2);
    cm.AddConnectorTurnD("s1c4", "s1", 0.0,0.0);

    cm.AddSegment("s2");
    cm.AddConnectorTurn("s2c1", "s2", 0, 0.0);
    cm.AddConnectorTurn("s2c2", "s2", 0.3, 0.0);
    cm.AddConnectorTurn("s2c3", "s2", 0.3, 0.0);


    cm.AddSegment("s3");
    cm.AddConnectorTurn("s3c1", "s3", 0, 0.0);
    cm.AddConnectorTurn("s3c2", "s3", 0.3, 0.0);


    cm.AddSegment("s4");
    cm.AddConnectorTurn("s4c1", "s4", 0, 0);
    cm.AddConnectorTurn("s4c2", "s4", 0.3, 0);
    cm.AddConnectorTurn("s4c3", "s4", 0.3, 0);


    cm.AddSegment("s5");
    cm.AddConnectorTurn("s5c1", "s5", 0.0, 0);
    cm.AddConnectorTurn("s5c2", "s5", 0.3, 0);

    cm.AddSegment("s6");
    cm.AddConnectorTurn("s6c1", "s6", 0, 0);
    cm.AddConnectorSliding("s6c2", "s6", 0, 0, 0);

    cm.AddSegment("s7");
    cm.AddConnectorTurn("s7c1", "s7", 0, 0);
    cm.AddConnectorSliding("s7c2", "s7", 0, 0, 0);
    cm.AddConnectorSliding("s7c3", "s7", 0, 0, 0);

    cm.AddSegment("s8");
    cm.AddConnectorTurn("s8c1", "s8", 0, 0);
    cm.AddConnectorSliding("s8c2", "s8", 0, 0, 0);

    cm.AddSegment("s9");
    cm.AddConnectorTurn("s9c1", "s9", 0, 0);
    cm.AddConnectorSliding("s9c2", "s9", 0, 0, 0);


    cm.AddKPSliding("O", "s0c1", "s1c1");
    cm.AddKPTurn("A", "s1c2", "s2c1");
    cm.AddKPTurn("B", "s2c2", "s3c1");
    cm.AddKPTurn("S", "s3c2", "s0c2");

    cm.AddKPTurn("E", "s1c4", "s4c1");
    cm.AddKPTurn("D", "s4c2", "s5c1");
    cm.AddKPTurn("C", "s5c2", "s0c3");

    cm.AddKPSliding("G", "s6c2", "s7c2");
    cm.AddKPTurn("F", "s2c3", "s6c1");
    cm.AddKPTurn("H", "s4c3", "s7c1");

    cm.AddKPSliding("L", "s1c3", "s9c2");
    cm.AddKPTurn("M", "s9c1", "s8c1");
    cm.AddKPSliding("N", "s8c2", "s7c3");
    gm.SetStepSize(0.005);
    gm.SetMinGC(0);
    gm.SetMaxGC(6.28);
    gm.SetJump(true);
    gm.BuildEdgesSets();
    gm.AddFirstGroupByName("O", "Ground", "s1");
    gm.Analyze();

        XMLSaver::Save("xmls\\"+mname+".xml");
    }
}

int main()
{

    //freopen("output.txt","w",stdout);
    CompManager cm;
    GroupManager gm(&cm);


    BuildMechanism(cm, gm);
    PrintCompManagerInfo(&cm);
    PrintGroupsInfo(gm);

    sf::RenderWindow App(sf::VideoMode(800, 600),
                         string("Vizualization").c_str());
                         //sf::Style::Fullscreen);
    SFMLVizualizer viz(&cm, &App);

    sf::View v = App.GetView();
    v.Move(-650,300);
    v.Zoom(1.3);
    App.SetView(v);
    sf::Vector2f v2f = v.GetHalfSize();
    //App.SetSize(v2f.x*2, v2f.y*2);

    sf::Clock clock, clock1;
    sf::Font MyFont;
    PrepareFont(MyFont);

    // Start game loop
    int steps = 0;
    while (App.IsOpened())
    {
        gm.CalcNextStep();

        ProcessAppEvents(App, v, gm);
        if (!App.IsOpened())
            return 0;

        App.Clear();
        viz.Draw();
        AddHelpText(App, MyFont, gm);

        App.Display();

        if (step_mode == SM_HARD_STEPS_CNT)
            if (clock.GetElapsedTime() >= step_time)
            {
                gm.MakeStep();
                steps++;
                clock.Reset();
            }
        if (step_mode == SM_FREE_STEPS_CNT)
        {
          gm.MakeStep();
          steps++;
        }
        if (clock1.GetElapsedTime() >= 1)
        {
            step_per_second = steps;
            step_time = 1.0/step_per_second;
            steps = 0;
            clock1.Reset();
        }
    }
    return EXIT_SUCCESS;
}

void ProcessAppEvents(sf::RenderWindow &App, sf::View &v, GroupManager &gm)
{
    sf::Event Event;
    while (App.GetEvent(Event))
    {
        switch (Event.Type)
        {
            case sf::Event::Closed: App.Close(); break;
            case sf::Event::KeyPressed:
            {
                switch (Event.Key.Code)
                {
                    case sf::Key::Escape: App.Close(); break;
                    case sf::Key::Right:
                    case sf::Key::Left:
                    case sf::Key::Up:
                    case sf::Key::Down:
                    {
                        const int step = 5;
                        v = App.GetView();
                        int hor = 0, ver = 0;
                        if (Event.Key.Code == sf::Key::Left)
                            hor+=step;
                        if (Event.Key.Code == sf::Key::Right)
                            hor-=step;
                        if (Event.Key.Code == sf::Key::Up)
                            ver+=step;
                        if (Event.Key.Code == sf::Key::Down)
                            ver-=step;
                        v.Move(hor, ver);
                        App.SetView(v);
                        break;
                    }
                    case sf::Key::S:
                    case sf::Key::D:
                    {
                        //if (Event.Key.Code == sf::Key::S)
                        //    wanna_step_per_second-= wanna_step_per_second/10 - 1;
                        //if (Event.Key.Code == sf::Key::D)
                        //    wanna_step_per_second+= wanna_step_per_second/10 + 1;
                        //if (wanna_step_per_second <= 0)
                        //    step_per_second = 1;
                        //if (wanna_step_per_second >= 250)
                        //    step_per_second = 250;
                        //step_time = 1.0/wanna_step_per_second;
                        break;
                    }
                    case sf::Key::W:
                    case sf::Key::E:
                    {
                        if (Event.Key.Code == sf::Key::E)
                            gm.SetStepSize(gm.GetStepSize() + 0.005);
                        if (Event.Key.Code == sf::Key::W)
                            gm.SetStepSize(gm.GetStepSize() - 0.005);
                        break;
                    }
                    case sf::Key::Z:
                    case sf::Key::X:
                    {
                        if (Event.Key.Code == sf::Key::Z)
                            v.Zoom(1.01);
                        if (Event.Key.Code == sf::Key::X)
                            v.Zoom(1.0/1.01);
                        break;
                    }
                    case sf::Key::A:
                    {
                        step_mode = (STEP_MODE) ((int)SM_HARD_STEPS_CNT + (int)SM_FREE_STEPS_CNT - step_mode);
                        break;
                    }
                    default: break;
                }
                break;
            }
            case sf::Event::Resized:
            {
                int h = Event.Size.Height;
                int w = Event.Size.Width;
                v.SetHalfSize(w/2, h/2);
                break;
            }
            default: break;
        }
    }
}

void AddHelpText(sf::RenderWindow &App, sf::Font &f, GroupManager &gm)
{
    sf::View v = App.GetView();
    sf::Vector2f center = v.GetCenter(), half = v.GetHalfSize();

    string s;
    s = "Operations available:\n";
    s += "Move:              Left, Right, Up, Down\n";
    s += "Speed:             s (decrease), d (increase)\n";
    s += "Step size:         w (decrease), e (increase)\n";
    s += "Zoom:              z (in), x (out)\n";
    s += "Steps mode:        a (switch between modes)\n";
    s += "Quit:              Esc\n";
    sf::String text(s, f, 12);
    text.SetColor(sf::Color(128, 200, 40));
    text.Move(center.x - half.x + half.x/20, center.y - half.y + half.y/20);
    App.Draw(text);


    ostringstream step_per_second_str;
    step_per_second_str << "~" << step_per_second << "\n";
    ostringstream step_time_str;
    step_time_str << "~" << step_time << "\n";
    ostringstream framerate_str;
    framerate_str << 1.0/App.GetFrameTime() << "\n";
    ostringstream step_size_str;
    step_size_str << gm.GetStepSize() << "\n";

    s = "Steps per second: ";
    s += step_per_second_str.str() ;
    s += "Step time: ";
    s += step_time_str.str();
    s += "Framerate: ";
    s += framerate_str.str();
    s += "Step size: ";
    s += step_size_str.str();
    s += "Steps mode: ";
    switch (step_mode)
    {
        case SM_HARD_STEPS_CNT: s += "SM_HARD_STEPS_CNT\n"; break;
        case SM_FREE_STEPS_CNT: s += "SM_FREE_STEPS_CNT\n"; break;
        default: break;
    }

    sf::String inf(s.c_str(), f, 20);
    inf.SetColor(sf::Color(230, 200, 180));
    inf.Move(center.x - half.x + half.x/20, center.y + half.y - half.y/2);
    App.Draw(inf);
}

void PrepareFont(sf::Font &MyFont)
{
    MyFont.LoadFromFile(string(res_path)+string(font_name), 20);
}
