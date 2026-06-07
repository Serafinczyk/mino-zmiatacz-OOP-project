#include "MSSFMLView.h"

MSSFMLView::MSSFMLView(MinesweeperBoard& _b) : board(_b){

}

const void MSSFMLView::display(const bool& _debug) {
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

MSSFMLView::Scene MSSFMLView::createScene() {
	Scene scene;
	return scene;
}

const void MSSFMLView::updateScene(Scene& _s) {

}
const void MSSFMLView::updateSceneDebug(Scene& _s) {

}