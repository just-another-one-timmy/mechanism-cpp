#ifndef SFMLVIZUALIZER_H_INCLUDED
#define SFMLVIZUALIZER_H_INCLUDED

#include "Vizualizer.h"
#include <SFML/Graphics.hpp>

class SFMLVizualizer: public Vizualizer
{
    private:
        sf::RenderWindow *w;

    public:
        virtual void Draw();
        void DrawArrow(int x1, int y1, int x2, int y2, int color);
        SFMLVizualizer(CompManager *c, sf::RenderWindow *w);
};

#endif // SFMLVIZUALIZER_H_INCLUDED
