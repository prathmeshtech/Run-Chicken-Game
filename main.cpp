#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;
using namespace std;

struct point
{ int x,y;};

int main()
{
    srand(time(0));

    //SFML Window Initialization:

    RenderWindow app(VideoMode(400, 533), "Run Chicken!");
    app.setFramerateLimit(60);

    //This code loads textures from image files ("background.png", "branch.png", and "duck.png") and creates sprites for each texture.
    Texture t1,t2,t3;
    t1.loadFromFile("images/bg.jpg");
    t2.loadFromFile("images/branch.png");
    t3.loadFromFile("images/chicken.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    // This code initializes an array of 20 point structures/array of objects type, representing the platforms. The x and y coordinates of each platform are initialized with random values.
    point plat[20];

    for (int i=0;i<10;i++)
    {
       plat[i].x=rand()%400;
       plat[i].y=rand()%533;
    }


    //These variables represent the player's position (x and y), the initial height of the jump (h), and the velocity components (dx and dy).
    int x=100,y=100,h=200;
    float dx=0,dy=0;
    int countframes = 0;
    int score = 0;

    // Main game loop that continuously runs until the window is closed.
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        //These lines handle player controls (left and right arrow keys) and simulate simple physics for the player's jump.
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            x += 3;
            /*cout << "Moved Right" << countframes++ << endl;*/
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            x -= 3;
        }

        dy+=0.2;
        y = y+dy;

        //Condition where chicken falls if doesnt land on branch.
        if (y > 500) {
            cout << "Chicken got cooked !!! Biryani Ready"<<endl<<endl;

            cout << "Your Score: " << score << endl;
            break;
        }

        if (y<h)
        for (int i=0;i<10;i++)
        {
            y=h;
            plat[i].y = plat[i].y - dy;

            if (plat[i].y > 533)
            {
                plat[i].y=0; 
                plat[i].x=rand()%400;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            if ((x + 50 > plat[i].x) &&
                (x + 20 < plat[i].x + 68) &&
                (y + 70 > plat[i].y) &&
                (y + 70 < plat[i].y + 14) &&
                (dy > 0))
            {
                // this indicates jump when collision
                dy = -10;
                score++;
            }
        }

        sPers.setPosition(x,y);

        app.draw(sBackground);
        app.draw(sPers);
        for (int i=0;i<10;i++)
        {
            sPlat.setPosition(plat[i].x,plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }

    return 0;
}
