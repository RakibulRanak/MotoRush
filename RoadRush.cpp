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

int score = 0, highscore;
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

void Help(RenderWindow &Window)
{
    while(Window.isOpen())
    {
        Font _score, s;
        _score.loadFromFile("SHOWG.TTF");
        s.loadFromFile("ALGER.TTF");
        string s1="You  have  to  save  the  car. ";
        string s2="Use Right key to move the bike at right. ";
        string s3="Use Left key to move the bike at left. ";
        string s4="Use Up key to speed up the bike.";
        string s5="' Use Esc key to return Main Menu.'";
        Text t1(s1, _score, 40), t2(s2, _score, 40), t3(s3, _score, 40), t4(s4, _score, 40), t5(s5, s, 30);
        (s1, _score, 40);
        t1.setString(s1);
        t2.setString(s2);
        t3.setString(s3);
        t4.setString(s4);
        t5.setString(s5);

        t1.setPosition(130, 200);
        t2.setPosition(130,255);
        t3.setPosition(130,310);
        t4.setPosition(130,365);
        t5.setPosition(200,500);
        Window.draw(t1);
        Window.draw(t2);
        Window.draw(t3);
        Window.draw(t4);
        Window.draw(t5);
        Window.display();
        Window.clear();

        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            return;
        }
    }
}

void Highscore(RenderWindow &Window)
{

    while(Window.isOpen())
    {
        freopen("score.dat","r",stdin);
        cin>>highscore;
        Font _score;
        _score.loadFromFile("SHOWG.TTF");

        char arr[100];
        sprintf(arr," High Score :  %d",highscore);
        Text t_(arr, _score, 50);
        t_.setPosition(350, 350);
        Window.draw(t_);
        Window.display();
        Window.clear();

        if(Keyboard::isKeyPressed(Keyboard::Space))
        {
            return;
        }

    }
}


void game(RenderWindow &w)
{
    RenderWindow Window(VideoMode(width, height),"MotoRush");
    Window.setFramerateLimit(60);
    srand(time(NULL));

    Music gamemusic;
    gamemusic.openFromFile("carsong.ogg");

    gamemusic.setVolume(100);
    gamemusic.play();

    gamemusic.setLoop(true);

    Texture texture1, texture2, t, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12;
    Sprite sprite, sprite1, s, bluecar, greencar, jeep, bluecar2, greencar2, sclbus, redbus, redcar, col, life, agun;
    t12.loadFromFile("agun3.png");
    agun.setTexture(t12);
    t9.loadFromFile("redcar.png");
    t11.loadFromFile("love.png");
    life.setTexture(t11);
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
    t10.loadFromFile("type_A.png");
    col.setTexture(t10);

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
    life.setScale(0.05f, 0.05f);
    agun.setScale(0.5f, 0.5f);
    int LIFE = 3;

    score = 0;


here:
    vector<Line> lines;
    for(int i=0; i<50000; i++)
    {
        Line line;
        line.z = i * segl;
        lines.push_back(line);
    }
    int pos = 0;
    int playerx = 440;
    int b = 400, d= 400 ;
    float scaleblue = 0.0000001, a = 500, c = 500, scalegreen = 0.001, scalejeep = 0.1,  f = 490;
    float scaleblue2 = 0.1, scalegreen2 = 0.0000001, g = 480, scalesclbus = 0.00001, schoolx = 540 ;
    float scaleredx = 0.00001, scaleredcar = 0.00001;
    while(Window.isOpen())
    {


        Event e;
        while(Window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                Window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            if(playerx < 730)
                playerx += 5;
        }
        if(Keyboard::isKeyPressed(Keyboard::Left ))
        {
            if(playerx > 200)
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
            scaleredx += 0.00005;
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
        if(first)
        {
            bluecar.setScale(scaleblue,scaleblue);
            greencar.setScale(scalegreen, scalegreen);
            redbus.setScale(scaleredx, scaleredx);
            bluecar.setPosition(a, b-100);
            greencar.setPosition(c, b);
            redbus.setPosition(f, b-250);
        }

        if(second)
        {
            jeep.setScale(scalejeep, scalejeep);
            sclbus.setScale(scalesclbus, scalesclbus);
            jeep.setPosition(f, b);
            sclbus.setPosition(schoolx, b-180);
        }

        if(third)
        {
            bluecar2.setScale(scaleblue2, scaleblue2);
            greencar2.setScale(scalegreen2, scalegreen2);
            redcar.setScale(scaleredcar, scaleredcar);
            bluecar2.setPosition(g, b);
            greencar2.setPosition(a, b-100);
            redcar.setPosition(f, b-240);
        }

        s.setPosition(550, b);
        //Window.draw(s);
        if(first)
        {
            if(greencar.getPosition().x + greencar.getGlobalBounds().width-50 >= sprite.getPosition().x && greencar.getPosition().x  <= sprite.getPosition().x + sprite.getGlobalBounds().width-100 )
            {
                if(greencar.getPosition().y+ greencar.getGlobalBounds().height >= sprite.getPosition().y+20 && greencar.getPosition().y <= sprite.getPosition().y + sprite.getGlobalBounds().height)
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(greencar.getPosition().x-300,greencar.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }

            }

            if(bluecar.getPosition().x + bluecar.getGlobalBounds().width-70  >= sprite.getPosition().x && bluecar.getPosition().x <= sprite.getPosition().x + sprite.getGlobalBounds().width -50 )
            {
                if(bluecar.getPosition().y+bluecar.getGlobalBounds().height-70 >= sprite.getPosition().y && bluecar.getPosition().y <= sprite.getPosition().y+sprite.getGlobalBounds().height)
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(bluecar.getPosition().x-300,bluecar.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }
            }

            if(redbus.getPosition().x + redbus.getGlobalBounds().width >= sprite.getPosition().x && redbus.getPosition().x <= sprite.getPosition().x+sprite.getGlobalBounds().width-50 )
            {
                if(redbus.getPosition().y + redbus.getGlobalBounds().height >= sprite.getPosition().y+50 && redbus.getPosition().y <= sprite.getPosition().y + sprite.getGlobalBounds().height )
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(redbus.getPosition().x-300,redbus.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }
            }
            Window.draw(bluecar);
            Window.draw(greencar);
            Window.draw(redbus);
        }
        if(second)
        {
            if(jeep.getPosition().x + jeep.getGlobalBounds().width-120 >= sprite.getPosition().x && jeep.getPosition().x <= sprite.getPosition().x + sprite.getGlobalBounds().width-60)
            {
                if(jeep.getPosition().y + jeep.getGlobalBounds().height >= sprite.getPosition().y+40 && jeep.getPosition().y <= sprite.getPosition().y + sprite.getGlobalBounds().height )
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(jeep.getPosition().x-300,jeep.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }
            }
            if(sclbus.getPosition().x + sclbus.getGlobalBounds().width -100>= sprite.getPosition().x && sclbus.getPosition().x <= sprite.getPosition().x + sprite.getGlobalBounds().width-120)
            {
                if(sclbus.getPosition().y + sclbus.getGlobalBounds().height >= sprite.getPosition().y+50 && sclbus.getPosition().y+30<= sprite.getPosition().y + sprite.getGlobalBounds().height )
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(sclbus.getPosition().x-300,sclbus.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }
            }
            Window.draw(jeep);
            Window.draw(sclbus);
        }

        if(third)
        {
            if(bluecar2.getPosition().x + bluecar2.getGlobalBounds().width-50 >= sprite.getPosition().x && bluecar2.getPosition().x <= sprite.getPosition().x + sprite.getGlobalBounds().width-90)
            {
                if(bluecar2.getPosition().y + bluecar2.getGlobalBounds().height >= sprite.getPosition().y+40 && bluecar2.getPosition().y+40 <= sprite.getPosition().y + sprite.getGlobalBounds().height)
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(bluecar2.getPosition().x-300,bluecar2.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }
            }
            if(redcar.getPosition().x + redcar.getGlobalBounds().width-50 >= sprite.getPosition().x && redcar.getPosition().x <= sprite.getPosition().x + sprite.getGlobalBounds().width -40)
            {
                if(redcar.getPosition().y + redcar.getGlobalBounds().height >= sprite.getPosition().y+50 && redcar.getPosition().y+40 <= sprite.getPosition().y + sprite.getGlobalBounds().height)
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(redcar.getPosition().x-300,redcar.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }
            }
            if(greencar2.getPosition().x + greencar2.getGlobalBounds().width -70>= sprite.getPosition().x && greencar2.getPosition().x <= sprite.getPosition().x + sprite.getGlobalBounds().width -50)
            {
                if(greencar2.getPosition().y + greencar2.getGlobalBounds().height >= sprite.getPosition().y+50 && greencar2.getPosition().y+40 <= sprite.getPosition().y + sprite.getGlobalBounds().height)
                {
                    LIFE--;
                    for(int i=0; i<5; i++)
                    {
                        Window.draw(sprite1);
                        agun.setPosition(greencar2.getPosition().x-300,greencar2.getPosition().y-300);
                        Window.draw(agun);
                        Window.display();
                    }
                    goto here;
                }
            }
            Window.draw(bluecar2);
            Window.draw(greencar2);
            Window.draw(redcar);

        }
        Window.draw(sprite1);
        Window.draw(sprite);
        if(LIFE == 3)
        {
            life.setPosition(30, 450);
            Window.draw(life);
            life.setPosition(90, 450);
            Window.draw(life);
            life.setPosition(150, 450);
            Window.draw(life);
        }

        if(LIFE == 2)
        {
            life.setPosition(30, 450);
            Window.draw(life);
            life.setPosition(90,450);
            Window.draw(life);
        }
        if(LIFE == 1)
        {
            life.setPosition(30, 450);
            Window.draw(life);
        }
        if(LIFE==0)
        {
            Window.clear(Color::Black);
            Font g_over;
            g_over.loadFromFile("SHOWG.TTF");
            Text game_over("Game Over", g_over, 50);
            game_over.setColor(Color::Red);
            game_over.setPosition(380, 350);
            Window.clear();
            for(int j=0; j<100; j++)
            {
                Text game_over("Game Over", g_over, 50+j);
                game_over.setColor(Color::Red);
                game_over.setPosition(380-j*2, 350);
                Window.draw(game_over);
                Window.display();
                Window.clear();
            }

            return;

        }

        Window.draw(life);
        if(score > highscore)
        {
            freopen("score.dat","w",stdout);
            cout<<score<<endl;
        }


        Font _score;
        _score.loadFromFile("arial.ttf");

        char arr[100];
        sprintf(arr,"SCORE : %d",score);
        Text t_(arr, _score, 30);
        t_.setPosition(700, 500);
        Window.draw(t_);

        freopen("score.dat","r",stdin);
        cin>>highscore;

        char ara[100];
        sprintf(ara," HIGH SCORE :  %d",highscore);
        Text t(ara, _score, 30);
        t.setPosition(680, 450);
        Window.draw(t);

        Window.display();

        a+=0.7;
        c-=2.8;
        f -= 0.3;
        g -= 2.2;
        schoolx -= 2.2;

        if( b >= 1000)
        {
            a=510;
            c=500;
            f = 490;
            g = 480;
            schoolx = 540;
        }

        scaleblue+=0.005;
        scalegreen+=0.004;
        scalejeep += 0.006;
        scalegreen2 += 0.005;
        scaleblue2 += 0.007;
        scalesclbus += 0.0025;
        scaleredx += 0.0003;
        scaleredcar += 0.0019;

        if(greencar.getPosition().y > 768  && greencar.getPosition().y < 770)
            score+=5;

        if(bluecar.getPosition().y > 768  && bluecar.getPosition().y < 772)
            score+=5;

        if(redbus.getPosition().y + redbus.getGlobalBounds().height> 745 && redbus.getPosition().y + redbus.getGlobalBounds().height< 750  )
            score+=5;

        if(jeep.getPosition().y > 768  && jeep.getPosition().y < 770)
            score+=5;

        if(sclbus.getPosition().y > 768  && sclbus.getPosition().y < 770)
            score+=5;

        if(greencar2.getPosition().y > 768  && greencar2.getPosition().y < 772)
            score+=5;

        if(bluecar2.getPosition().y > 768  && bluecar2.getPosition().y < 770)
            score+=5;

        if(redcar.getPosition().y > 755  && redcar.getPosition().y < 760)
            score+=5;

        if( b >= 1000)
        {
            scaleblue = 0.0000001;
            scalegreen =  0.001;
            scalejeep = 0.1;
            scalegreen2 = 0.0000001;
            scaleblue2 = 0.1;
            scalesclbus = 0.0001;
            scaleredx = 0.005;
            scaleredcar = 0.000001;

            int counter = rand()%3;
            if(counter == 1)
            {
                first = false;
                second = true;
                third = false;
            }
            else if(counter == 2)
            {
                first = true;
                second = false;
                third = false;
            }
            else if(counter == 0)
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


int main()
{
    RenderWindow window(VideoMode(1024, 768),"Game Menu");
    Texture texture;
    Sprite sprite;
    texture.loadFromFile("menu.png");
    sprite.setTexture(texture);
    sprite.setScale(0.57f,0.75f);

    Music Menu;
    Menu.openFromFile("gamemenu.ogg");
    Menu.setVolume(70);
    Menu.play();
    Menu.setLoop(true);

    bool menu = true;
    int controler = 1;


    Font font, font1;
    font.loadFromFile("SHOWG.TTF");
    string game_name = "Moto Rush";
    Text text(game_name, font,60);
    text.setColor(Color::Black);
    text.setString(game_name);
    text.setPosition(110,75);
    text.rotate(-7);

    font1.loadFromFile("SHOWG.TTF");
    string new_game = "New game";
    Text text_new(new_game, font1, 50);
    text_new.setColor(Color::White);
    text_new.setString(new_game);
    text_new.setCharacterSize(45);
    text_new.setPosition(140, 145);
    text_new.rotate(-7);

    string high_score = "High score";
    Text text_high(high_score, font1, 50);
    text_high.setColor(Color::White);
    text_high.setString(high_score);
    text_high.setCharacterSize(45);
    text_high.setPosition(145, 205);
    text_high.rotate(-7);

    string help = "Help";
    Text text_help(help, font1, 50);
    text_help.setColor(Color::White);
    text_help.setString(help);
    text_help.setCharacterSize(45);
    text_help.setPosition(150, 265);
    text_help.rotate(-7);

    string exit = "Exit";
    Text text_exit(exit, font1, 50);
    text_exit.setColor(Color::White);
    text_exit.setString(exit);
    text_exit.setCharacterSize(45);
    text_exit.setPosition(155, 325);
    text_exit.rotate(-7);


    while(window.isOpen())
    {
        Event event;
        Clock key;
        float time;
        while(window.pollEvent(event))
        {
            if(event.type== Event::Closed)
                window.close();
        }

        while (menu)
        {
            time=key.getElapsedTime().asSeconds();
            if(controler==1)
            {
                text_new.setColor(Color::Red);
                if(Keyboard::isKeyPressed(Keyboard::Down) && time>.2)
                {
                    controler = 2;
                    text_new.setColor(Color::White);
                    key.restart();
                    time=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)&&time>0.2)
                {
                    controler = 4;
                    text_new.setColor(Color::White);
                    key.restart();
                    time=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    //window.close();
                    Menu.stop();
                    game(window);
                }

            }

            if(controler ==2)
            {
                text_high.setColor(Color::Red);
                if(Keyboard::isKeyPressed(Keyboard::Down)&&time>0.2)
                {
                    controler = 3;
                    text_high.setColor(Color::White);
                    key.restart();
                    time=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)&&time>0.2)
                {
                    controler = 1;

                    text_high.setColor(Color::White);
                    key.restart();
                    time=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    //window.close();
                    Menu.stop();
                    Highscore(window);
                }

            }
            if(controler ==3)
            {
                text_help.setColor(Color::Red);
                if(Keyboard::isKeyPressed(Keyboard::Down)&&time>0.2)
                {
                    controler = 4;
                    text_help.setColor(Color::White);
                    key.restart();
                    time=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)&&time>0.2)
                {
                    controler = 2;

                    text_help.setColor(Color::White);
                    key.restart();
                    time=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    Menu.stop();
                    Help(window);
                }


            }
            if(controler ==4)
            {
                text_exit.setColor(Color::Red);
                if(Keyboard::isKeyPressed(Keyboard::Down)&&time>0.2)
                {
                    controler = 1;

                    text_exit.setColor(Color::White);
                    key.restart();
                    time=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Up)&&time>0.2)
                {
                    controler = 3;

                    text_exit.setColor(Color::White);
                    key.restart();
                    time=0;
                }

                if(Keyboard::isKeyPressed(Keyboard::Enter))
                    window.close();
            }

            window.draw(sprite);
            window.draw(text);
            window.draw(text_new);
            window.draw(text_high);
            window.draw(text_help);
            window.draw(text_exit);
            window.display();

        }

    }
}



