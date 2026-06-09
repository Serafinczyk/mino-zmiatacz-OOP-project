#include "MSSFMLView.h"

MSSFMLView::MSSFMLView(MinesweeperBoard& _b) : board(_b){
    boardHeight = board.getBoardHeight();
    boardWidth = board.getBoardWidth();
}

const void MSSFMLView::display(const bool& _debug) {
    sf::Vector2u startSize(boardWidth * 50, boardHeight * 50);
    if (startSize.x>1600) {
        startSize.x = 1600;
    }
    if (startSize.y > 1000) {
        startSize.y = 1000;
    }
    sf::RenderWindow window(sf::VideoMode(startSize), "SAPER");
    windowSize = window.getSize();
    window.setFramerateLimit(60);

   

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if(event->is<sf::Event::Resized>())
                windowSize = window.getSize();
        }

        window.clear();
        Scene s = createScene();
        renderFieldsDebug(s);
        renderFlags(s);
        drawScene(window,s);
        window.display();
    }
}

MSSFMLView::Scene MSSFMLView::createScene() {
	Scene scene;
    scene.textures.loadFromFile("textures.png");

    //Loading flag texture
    scene.flag.loadFromImage(scene.textures, false, sf::IntRect({ 600, 0 }, { 50, 50 }));

    //Loading textures of covered fields
    scene.coveredFields[0].loadFromImage(scene.textures, false, sf::IntRect({ 0, 0 }, { 50, 50 }));
    scene.coveredFields[1].loadFromImage(scene.textures, false, sf::IntRect({ 50, 0 }, { 50, 50 }));
    scene.coveredFields[2].loadFromImage(scene.textures, false, sf::IntRect({ 650, 0 }, { 50, 50 }));

    for (int i = 0; i < 10; ++i) {
        scene.unCoveredFields[i].loadFromImage(scene.textures, false, sf::IntRect({ 100+(i*50), 0}, {50, 50}));
    }
    return scene;
}

const void MSSFMLView::renderFields(Scene& _s) {
    for (int row = 0; row < boardHeight; ++row) {
        std::vector<std::pair<bool, sf::Sprite>>rowV;
        for (int col = 0; col < boardWidth; ++col) {
            std::pair<bool, sf::Sprite> field = { false, sf::Sprite(_s.coveredFields[(row + col) % 2]) }; //bool for faster update (true if revealed), calculations for chessboard pattern
            sf::Vector2f pos(static_cast<float>(col*50), static_cast<float>(row*50));
            field.second.setPosition(pos);
            rowV.push_back(field);
        }
        _s.fields.push_back(rowV);
    } 
}

const void MSSFMLView::renderFieldsDebug(Scene& _s) {
    for (int row = 0; row < boardHeight; ++row) {
        std::vector<std::pair<bool, sf::Sprite>>rowV;
        for (int col = 0; col < boardWidth; ++col) {
            int textureNum = (row + col) % 2;
            if (row==col || row == 0 || col == 0) {
                textureNum = 2;
            }
            std::pair<bool, sf::Sprite> field = { false, sf::Sprite(_s.coveredFields[textureNum]) }; //bool for faster update (true if revealed), calculations for chessboard pattern
            sf::Vector2f pos(static_cast<float>(col * 50), static_cast<float>(row * 50));
            field.second.setPosition(pos);
            rowV.push_back(field);
        }
        _s.fields.push_back(rowV);
    }
}

const void MSSFMLView::renderFlags(Scene& _s) {
    for (int row = 0; row < boardHeight; ++row) {
        std::vector<sf::Sprite>rowV;
        for (int col = 0; col < boardWidth; ++col) {
            sf::Sprite flag(_s.flag);
            sf::Vector2f pos(static_cast<float>(col * 50), static_cast<float>(row * 50));
            flag.setPosition(pos);
            flag.setColor(sf::Color(255, 255, 255, 0));
            rowV.push_back(flag);
        }
        _s.flags.push_back(rowV);
    }
}

const void MSSFMLView::updateScene(Scene& _s) {
    for (int row = 0; row < boardHeight; ++row) {
        for (int col = 0; col < boardWidth; ++col) {
            bool hasFlag = board.hasFlag(row, col);
            _s.flags[row][col].setColor(sf::Color(255, 255, 255, hasFlag*255));

            //For updating field we will use std pair bool value, because changing texture takes a lot more time
            bool isRevealed = board.isRevealed(row, col);
            int minesNum = board.countMines(row,col);
            if (isRevealed && !_s.fields[row][col].first) {
                _s.fields[row][col].first = true; //already updated and won't change until the end of game
                char fieldState = board.getFieldInfo(row,col);
                if (fieldState == 'x') {
                    _s.fields[row][col].second.setTexture(_s.unCoveredFields[9]); //Mine
                }
                else if (fieldState == ' ') {
                    _s.fields[row][col].second.setTexture(_s.unCoveredFields[0]); //Empty
                }
                else{
                    int code = fieldState - '0';
                    if(code>0 && code<9) _s.fields[row][col].second.setTexture(_s.unCoveredFields[code]); //0-8 num
                }
            }
        }
    }
}

void MSSFMLView::drawScene(sf::RenderWindow& _window, Scene& _s) {
    for (int row = 0; row < boardHeight; ++row) {
        for (int col = 0; col < boardWidth; ++col) {
            _window.draw(_s.fields[row][col].second);
            _window.draw(_s.flags[row][col]);
        }
    }
}
