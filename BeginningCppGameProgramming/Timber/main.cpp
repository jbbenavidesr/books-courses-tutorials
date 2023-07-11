#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(1360, 768);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
    View view(sf::FloatRect(0, 0, 1920, 1080));
    window.setView(view);

    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

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
        // Show everything we just drew
        window.display();
    }

    return 0;
}