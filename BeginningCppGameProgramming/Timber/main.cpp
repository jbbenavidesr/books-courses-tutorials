#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(1360, 768);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
    View view(sf::FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    Clock clock;

    // Set up background
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Set up tree
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");

    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Set up bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");

    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeActive = false;
    float beeSpeed = 0.0f;

    // Set up clouds
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    while (window.isOpen())
    {
        /*
        *******************************************
        Handle the players input
        *******************************************
        */
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        *******************************************
        Update the scene
        *******************************************
        */

        // Measure time
        Time dt = clock.restart();

        // Setup the bee
        if (!beeActive)
        {
            // Set the speed of the bee
            srand((int)time(0) * 10);
            beeSpeed = (rand() % 200) + 200;

            // Set the height of the bee
            srand((int)time(0) * 10);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        }
        else
        {
            // Move the bee
            spriteBee.setPosition(
                spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
                spriteBee.getPosition().y);

            // Has the bee reached the right hand edge of the screen?
            if (spriteBee.getPosition().x < -100)
            {
                beeActive = false;
            }
        }

        // Manage the clouds
        // Cloud 1
        if (!cloud1Active)
        {
            // Set the speed of the cloud
            srand((int)time(0) * 10);
            cloud1Speed = (rand() % 200);

            // Set the height of the cloud
            srand((int)time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);
            cloud1Active = true;
        }
        else
        {
            spriteCloud1.setPosition(
                spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
                spriteCloud1.getPosition().y);

            // Has the cloud reached the right hand edge of the screen?
            if (spriteCloud1.getPosition().x > 1920)
            {
                cloud1Active = false;
            }
        }

        // Cloud 2
        if (!cloud2Active)
        {
            // Set the speed of the cloud
            srand((int)time(0) * 20);
            cloud2Speed = (rand() % 200);

            // Set the height of the cloud
            srand((int)time(0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition(-200, height);
            cloud2Active = true;
        }
        else
        {
            spriteCloud2.setPosition(
                spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()),
                spriteCloud2.getPosition().y);

            // Has the cloud reached the right hand edge of the screen?
            if (spriteCloud2.getPosition().x > 1920)
            {
                cloud2Active = false;
            }
        }

        // Cloud 3
        if (!cloud3Active)
        {
            // Set the speed of the cloud
            srand((int)time(0) * 30);
            cloud3Speed = (rand() % 200);

            // Set the height of the cloud
            srand((int)time(0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition(-200, height);
            cloud3Active = true;
        }
        else
        {
            spriteCloud3.setPosition(
                spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
                spriteCloud3.getPosition().y);

            // Has the cloud reached the right hand edge of the screen?
            if (spriteCloud3.getPosition().x > 1920)
            {
                cloud3Active = false;
            }
        }

        /*
        *******************************************
        Draw the scene
        *******************************************
        */
        // Clear everything from the last frame
        window.clear();
        // Draw our game scene here
        window.draw(spriteBackground);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteTree);
        window.draw(spriteBee);

        // Show everything we just drew
        window.display();
    }

    return 0;
}