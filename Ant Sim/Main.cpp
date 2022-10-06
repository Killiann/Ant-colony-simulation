#include <SFML/Graphics.hpp>
#include "Ant.h"
#include "MapHandler.h"

int main()
{
    cout << "hi40" << endl;
    //app
    sf::RenderWindow window(sf::VideoMode(1000, 700), "SFML works!");    
    window.setFramerateLimit(60);
    
    //ants
    std::vector<Ant> ants;
    int antCount = 2000;            

    //map
    int pixelSize = 4;
    sf::Color caveBackground(219, 214, 195);
    MapHandler map(250, 175, pixelSize);

    //init
    for (int i = 0; i < antCount; i++) {
        Ant ant(sf::Vector2f(500, 350), map.GetData(), pixelSize);
        ants.push_back(ant);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(219, 214, 195));
        map.Draw(window);
        for (auto& ant : ants) {           
            ant.Update();
            ant.Draw(window);
        }                       
        window.display();
    }

    return 0;
}
