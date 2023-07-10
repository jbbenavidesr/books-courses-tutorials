#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(1360, 768);
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

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
        // Show everything we just drew
        window.display();
    }

    return 0;
}