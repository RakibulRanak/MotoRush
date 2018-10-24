#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;

int width = 1024;
int height = 768;
int roadw = 1000;
int segl = 100;
float camd = 0.80;

struct Line
{
    float x=0, y=0, z;///3d center of line
    float X, Y, W;///screen coordinate
    float scale;

    ///from world to project coordinate
    void project(int camx, int camy, int camz)
    {
        scale = 0.80 /(z - camz);
        X = (1 + scale * ( - camx)) * 512;
        Y = (1 + scale * 1500) * 384;
        W = scale * roadw * width/2;
    }
};

void drawquad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2)
{
    ConvexShape Shape(4);
    Shape.setFillColor(c);
    Shape.setPoint(0, Vector2f(x1 - w1, y1));
    Shape.setPoint(1, Vector2f(x2 - w2, y2));
    Shape.setPoint(2, Vector2f(x2 + w2, y2));
    Shape.setPoint(3, Vector2f(x1 + w1, y1));
    w.draw(Shape);
}

int main()
{
    RenderWindow Window(VideoMode(width, height),"ja issa tai");
    Window.setFramerateLimit(60);

    Texture texture1, texture2;
    Sprite sprite, sprite1;
    texture2.loadFromFile("architecture-buildings-city-164583.png");
    sprite1.setTexture(texture2);
    sprite1.setScale(0.3f, 0.16f);
    sprite1.setPosition(-100,0);

    vector<Line> lines;
    for(int i=0; i<10000; i++)
    {
        Line line;
        line.z = i * segl;
        lines.push_back(line);
    }

    while(Window.isOpen())
    {
        Event e;
        while(Window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                Window.close();
        }

        /// draw road
        for(int n=0; n<300; n++)
        {
            Line &l = lines[n];
            l.project(0, 1500,0);
            Color grass = (n/3)%2?Color(0, 0, 0):Color(0, 0, 0);
            Color rumble = (n/3)%2?Color(0, 0, 0):Color::Yellow;
            Color road = (n/3)%2?Color(107, 107, 107):Color(105, 105, 105);
            Color div = (n/5)%2?Color::White:Color(107, 107, 107);
            Line p = lines[n-1];///previous line

            drawquad(Window, grass, 0, p.Y, width, 0, l.Y, width);
            drawquad(Window, rumble, p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2);
            drawquad(Window, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
            drawquad(Window, div,p.X, p.Y, p.W*0.1, l.X, l.Y, l.W*0.1 );
        }

        Window.draw(sprite1);
         Window.draw(sprite);
        Window.display();

    }
}



