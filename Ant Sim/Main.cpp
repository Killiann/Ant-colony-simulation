#include <SFML/Graphics.hpp>
#include "Ant.h"
#include "MapHandler.h"
#include <iostream>

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

    //shaders
    sf::Shader shader;
    sf::RectangleShape* testShape = new sf::RectangleShape();
    testShape->setSize(sf::Vector2f(1000, 700));
    testShape->setFillColor(sf::Color::Red);
    testShape->setPosition(0, 0);
    
    std::vector<sf::Uint8>* pixels = new std::vector<sf::Uint8>(700 * 1000 * 4);       

    for (int y = 0; y < 700; y++) {
        for (int x = 0; x < 1000; x++) {
            if (y % 2 == 0) {
                pixels->at((y * 1000 + x) * 4 + 2) = 255; //blue
                pixels->at((y * 1000 + x) * 4 + 3) = 255; //alpha
            }
            else {
                pixels->at((y * 1000 + x) * 4 + 1) = 255; //blue
                pixels->at((y * 1000 + x) * 4 + 3) = 255; //alpha
            }
        }
    }

    sf::Texture* testTexture = new sf::Texture();
    testTexture->create(1000, 700);
    testTexture->update(pixels->data());

    //testShape->setTexture(*testTexture);
        
    if (!sf::Shader::isAvailable())
    {
        std::cout << "Shaders not available on device.\n";
    }
    else {
        if (!shader.loadFromFile("test.frag", sf::Shader::Fragment)) {
            std::cout << "Problem loading shader.\n";
        }
    }    

    shader.setUniform("u_resolution", sf::Vector2f(1000, 700));
    shader.setUniform("u_texture", *testTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int row = mh::Random(2, 698);
        for (int i = 0; i < 1000; i++) {
            pixels->at(((row - 1)* 1000 + i) * 4) = 255;
            pixels->at((row * 1000 + i) * 4) = 255;
            pixels->at(((row + 1) * 1000 + i) * 4) = 255;
        }

        testTexture->update(pixels->data());
        shader.setUniform("u_texture", *testTexture);

        window.clear(sf::Color(219, 214, 195));
        window.draw(*testShape, &shader);
        map.Draw(window);
        for (auto& ant : ants) {           
            ant.Update();
            ant.Draw(window);
        }                       
        window.display();
    }

    return 0;
}
