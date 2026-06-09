#include "MSSFMLController.h"

MSSFMLController::MSSFMLController(MinesweeperBoard& _board, MSSFMLView& _view, MSCheatEngine& _cheat) : board(_board), view(_view), cheatEngine(_cheat) {
	boardHeight = board.getBoardHeight();
	boardWidth = board.getBoardWidth();
	cheatEngine.addHintFunctions([]() {

	}, []() {

	});
}

MSSFMLController::~MSSFMLController() {

}

void MSSFMLController::play() {
    sf::Vector2u startSize(boardWidth * 50, boardHeight * 50);
    if (startSize.x > 1000) {
        startSize.x = 1000;
    }
    if (startSize.y > 1000) {
        startSize.y = 1000;
    }
    sf::RenderWindow window(sf::VideoMode(startSize), "SAPER");
    windowSize = window.getSize();
    window.setFramerateLimit(60);
    if (board.getGameMode() == DEBUG) {
        view.display(1); //debug mode
    }
    else {
        view.display(0); //normal mode
    }

    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            // Resize 
            if (event->is<sf::Event::Resized>())
                windowSize = window.getSize();

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window); //Get mouse pos
                int row = mousePosition.y / 50;
                int col = mousePosition.x / 50;
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) { //reveal field
                    board.revealField(row, col);
                }
                else if (mouseButtonPressed->button == sf::Mouse::Button::Right) { //togle flag
                    board.toggleFlag(row, col);
                }
            }
            
        }
        view.showScene(window);
    }
}