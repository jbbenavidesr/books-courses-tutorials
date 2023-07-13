#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(1360, 768);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
    View view(sf::FloatRect(0, 0, 1920, 1080));
    window.setView(view);

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