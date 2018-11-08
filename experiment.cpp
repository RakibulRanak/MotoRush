#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<SFML/Audio.hpp>
using namespace std;
using namespace sf;

int width = 1024;
int height = 768;
int roadw = 1000;
int segl = 100;
float camd = 0.80;
bool first = true, second = false, third = false;

struct Line
{
    float x=0, y=0, z;///3d center of line
    float X, Y, W;///screen coordinate
    float scale;

    //Line(){x = y = z = 0;}

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

    Music gamemusic;
    gamemusic.openFromFile("carsong.ogg");
    gamemusic.setVolume(100);
    gamemusic.play();
    gamemusic.setLoop(true);

    Texture texture1, texture2, t, t2, t3, t4, t5, t6, t7, t8, t9;
    Sprite sprite, sprite1, s, bluecar, greencar, jeep, bluecar2, greencar2, sclbus, redbus, redcar;
    t9.loadFromFile("redcar.png");
    redcar.setTexture(t9);
    t8.loadFromFile("red bus.png");
    redbus.setTexture(t8);
    t7.loadFromFile("school bus.png");
    sclbus.setTexture(t7);
    t5.loadFromFile("bluecar2.png");
    bluecar2.setTexture(t5);
    t6.loadFromFile("greenCar2.png");
    greencar2.setTexture(t6);
    t4.loadFromFile("jeep1.png");
    jeep.setTexture(t4);
    t3.loadFromFile("ran.png");
    greencar.setTexture(t3);
    t2.loadFromFile("ranak.png");
    bluecar.setTexture(t2);

    texture1.loadFromFile("hondafinal.png");
    texture2.loadFromFile("architecture-buildings-city-164583.png");
    t.loadFromFile("1503170393_preview_Spinningcoin--1q4q6x1q9s4t6y9p50.gif");
    s.setTexture(t);

    s.setScale(0.1f, 0.1f);
    sprite1.setTexture(texture2);
    sprite.setTexture(texture1);
    sprite.setPosition(440,610);
    sprite.setScale(0.25f, 0.25f);
    sprite1.setScale(0.3f, 0.16f);
    sprite1.setPosition(-100,0);

    Font font;
    font.loadFromFile("ALGER.TTF");
    string sentence = "collied with the coin";
    Text text(sentence, font, 60);
    text.setColor(Color::Green);
    text.setString(sentence);
    text.setPosition(400,450);


    vector<Line> lines;
    for(int i=0; i<10000; i++)
    {
        Line line;
        line.z = i * segl;
        lines.push_back(line);
    }
    int pos = 0;
    int playerx = 440;
    int b = 400, d= 400, counter = 0 ;
    float scaleblue = 0.0000001, a = 530, c = 500, scalegreen = 0.001, scalejeep = 0.1,  f = 490;
    float scaleblue2 = 0.1, scalegreen2 = 0.0000001, g = 480, scalesclbus = 0.00001, schoolx = 540 ;
    float scaleredx = 0.005, scaleredcar = 0.008;
    while(Window.isOpen())
    {


        Event e;
        while(Window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                Window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Right)){
                if(playerx < 765)
                playerx += 5;
        }
        if(Keyboard::isKeyPressed(Keyboard::Left )){
                if(playerx > 150)
                playerx -= 5;
        }
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            pos += 80, b += 3,scaleblue+=0.007,scalegreen+=0.004, scalejeep += 0.006, scalegreen2 += 0.007, scaleblue2 += 0.007 ;
            a+=0.8;
            c-=2.8;
            f -= 0.3;
            g -= 2.2;
            scalesclbus += 0.0025;
            scaleredx += 0.0002;
            scaleredcar += 0.0019;
             schoolx -= 2.2;
        }
        pos += 50;
        b += 3;
        if(b > 600)
            d += 3;

        sprite.setPosition(playerx, 610);

        int startpos = pos/segl;
        /// draw road
        for(int n=startpos; n<startpos+300; n++)
        {
            Line &l = lines[n];
            l.project(0, 1500, pos);

            Color grass = (n/3)%2?Color(0, 0, 0):Color(0, 0, 0);
            Color rumble = (n/3)%2?Color(0, 0, 0):Color::Yellow;
            Color road = (n/3)%2?Color(105, 105, 105):Color(107, 107,107);
            Color div = (n/5)%2?Color::White:Color(107, 107, 107);
            Line p = lines[n-1];///previous line

            drawquad(Window, grass, 0, p.Y, width, 0, l.Y, width);
            drawquad(Window, rumble, p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2);
            drawquad(Window, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
            drawquad(Window, div,p.X, p.Y, p.W*0.1, l.X, l.Y, l.W*0.1 );

        }

        bluecar.setScale(scaleblue,scaleblue);
        greencar.setScale(scalegreen, scalegreen);
        jeep.setScale(scalejeep, scalejeep);
        bluecar2.setScale(scaleblue2, scaleblue2);
        greencar2.setScale(scalegreen2, scalegreen2);
        sclbus.setScale(scalesclbus, scalesclbus);
        redbus.setScale(scaleredx, scaleredx);
        redcar.setScale(scaleredcar, scaleredcar);
        //if((b >=650 && b<=690)&& (playerx >= 290 && playerx < 450))
        // Window.draw(text);
        bluecar.setPosition(a, b);
        greencar.setPosition(c, b);
        jeep.setPosition(f, b);
        bluecar2.setPosition(g, b);
        greencar2.setPosition(a, b);
        sclbus.setPosition(schoolx, b-180);
        redbus.setPosition(f, b-200);
        redcar.setPosition(f, b-240);

        s.setPosition(550, b);
        //Window.draw(s);
        if(first)
        {
            Window.draw(bluecar);
            Window.draw(greencar);
            Window.draw(redbus);
        }
        if(second)
        {
            Window.draw(jeep);
            Window.draw(sclbus);


        }

        if(third)
        {
            Window.draw(bluecar2);
            Window.draw(greencar2);
            Window.draw(redcar);

        }

        Window.draw(sprite1);
        Window.draw(sprite);
        Window.display();



        a+=0.8;
        c-=2.8;
        f -= 0.3;
        g -= 2.2;
        schoolx -= 2.2;

        if( b >= 1000)
        {
            a=530;
            c=500;
            f = 490;
            g = 480;
            schoolx = 540;
        }

        scaleblue+=0.007;
        scalegreen+=0.004;
        scalejeep += 0.006;
        scalegreen2 += 0.007;
        scaleblue2 += 0.007;
        scalesclbus += 0.0025;
        scaleredx += 0.0002;
        scaleredcar += 0.0019;

        if( b >= 1000)
        {
            counter += 1;
            scaleblue = 0.0000001;
            scalegreen =  0.001;
            scalejeep = 0.1;
            scalegreen2 = 0.0000001;
            scaleblue2 = 0.1;
            scalesclbus = 0.0001;
            scaleredx = 0.005;
            scaleredcar = 0.008;

            if(counter % 3 == 1)
            {
                first = false;
                second = true;
                third = false;
            }
            else if(counter % 3 == 2)
            {
                first = true;
                second = false;
                third = false;
            }
            else if(counter % 3 == 0)
            {
                third = true;
                first = false;
                second = false;
            }
        }
        if(b > 1000)
            b=400;
        if(d > 1000)
            d = 400;
    }
}



