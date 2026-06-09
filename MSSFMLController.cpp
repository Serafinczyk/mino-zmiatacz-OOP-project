#include "MSSFMLController.h"

MSSFMLController::MSSFMLController(MinesweeperBoard& _board, MSSFMLView& _view, MSCheatEngine& _cheat) : board(_board), view(_view), cheatEngine(_cheat) {
	boardHeight = board.getBoardHeight();
	boardWidth = board.getBoardWidth();
    fieldHeight = 50;
    fieldWidth = 50;
    sf::Vector2u startSize(boardWidth * 50, boardHeight * 50);
    window = sf::RenderWindow (sf::VideoMode(startSize), "SAPER");

	cheatEngine.addHintFunctions([this]() {
        const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Cross).value();
        this->window.setMouseCursor(cursor);
	}, [this]() {
        const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
        this->window.setMouseCursor(cursor);
	});
}

MSSFMLController::~MSSFMLController() {

}

void MSSFMLController::play() {
    
    windowSize = window.getSize();
    calcFieldSize();

    window.setFramerateLimit(60);
    if (board.getGameMode() == DEBUG) {
        view.display(1); //debug mode
    }
    else {
        view.display(0); //normal mode
    }

    int lastMouseRow = 0;
    int lastMouseCol = 0;
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window); //Get mouse pos
            int mouseRow = mousePosition.y / fieldHeight;
            int mouseCol = mousePosition.x / fieldWidth;

            //To ensure we wont go outside the screen
            if (mouseRow < 0) mouseRow = 0;
            if (mouseCol < 0) mouseCol = 0;
            if (mouseRow >= boardHeight) mouseRow = boardHeight - 1;
            if (mouseCol >= boardWidth) mouseCol = boardWidth - 1;

            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            // Resize 
            if (event->is<sf::Event::Resized>()) {
                windowSize = window.getSize();
                calcFieldSize();
            }

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) { //reveal field
                    board.revealField(mouseRow, mouseCol);
                }
                else if (mouseButtonPressed->button == sf::Mouse::Button::Right) { //togle flag
                    board.toggleFlag(mouseRow, mouseCol);
                }
            }

            if (mouseRow != lastMouseRow || mouseCol != lastMouseCol) { //mouse moved
                lastMouseRow = mouseRow;
                lastMouseCol = mouseCol;
                cheatEngine.spyOnTile(mouseRow, mouseCol);
            }
            
        }
        view.showScene(window);
    }
}

void MSSFMLController::calcFieldSize() {
    fieldHeight = windowSize.y / board.getBoardHeight();
    fieldWidth = windowSize.x / board.getBoardWidth();
}