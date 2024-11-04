#include "MapEditor.h"

MapEditor::MapEditor(Grid& grid, Map& map): grid(grid) , map(map) {
	this->selectedTileType = 0;
	this->mapFilePath = "";
    sf::Font temp;
    if (!temp.loadFromFile("Font/game_font.ttf"))
    {
        cerr << "Font can't be loaded" << endl;
    }

    this->font = temp;
    this->SelectedTexture.setSize(sf::Vector2f(32, 32));
    
}

void MapEditor::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            this->selectedTileType = 1;
            cout << "Selected tile type changed to: " << selectedTileType << endl;
        }
        else if(event.key.code == sf::Keyboard::Num2)
        {
            this->selectedTileType = 2;
            cout << "Selected tile type changed to: " << selectedTileType << endl;

        }
        else if (event.key.code == sf::Keyboard::Num3)
        {
            this->selectedTileType = 3;
            cout << "Selected tile type changed to: " << selectedTileType << endl;

        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            // Get mouse position in the window
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int row = mousePos.y / grid.getTileSize();
            int col = (mousePos.x - grid.getTileSize()) / grid.getTileSize();
            cout << "Mouse position: " << mousePos.x << " " << mousePos.y << endl;
            cout << "Index: " << grid.getTileIndex(row, col) << endl;

            // Ensure row and col are within grid bounds
            if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
                paintTile(row, col, selectedTileType);  // Paint the tile with the selected type
                cout << "Painting tile at (" << row << ", " << col << ") with type " << selectedTileType << endl;
            }
        }
    }
}

/*
void MapEditor::paintTile(int row, int col, int tileType)
{
	int index = grid.getTileIndex(row, col);
	int maxIndex = grid.getTileIndex(grid.getRows(), grid.getCols());
	if (index >= 0 && index < maxIndex) {
        map.tiles[index].setType(tileType);
        selectedTileType = tileType;
		
	}
}
*/
void MapEditor::paintTile(int row, int col, int tileType) {
    map.setTileType(row, col, tileType);
    cout << "Tested" << endl;
}


void MapEditor::saveMapToFile(const string& filePath)
{
    json jsonObject;
    jsonObject["rows"] = grid.getRows();
	jsonObject["cols"] = grid.getCols();
	jsonObject["tileSize"] = grid.getTileSize();

    for (int i = 0; i < grid.getRows(); i++)
    {
        for (int j = 0; j < grid.getCols(); j++)
        {
            int index = grid.getTileIndex(i, j);
            jsonObject["tiles"].push_back(map.tiles[index].getType());

        }
    }

    std::ofstream file(filePath);
    if (file.is_open()) {
        file << jsonObject.dump(4);
        file.close();
    }
    else {
        std::cerr << "Failed to save map to " << filePath << std::endl;
    }

}

void MapEditor::loadMapFromFile(const string& filePath)
{
}

void MapEditor::setSelectedTileType(int type)
{
	selectedTileType = type;
}

void MapEditor::drawUI(sf::RenderWindow& window)
{
    // Draw text
    sf::Text text;
    text.setFont(font); // Assuming font is a member of MapEditor and loaded in the constructor
    text.setString("Selected tile:");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(5, 360);
    window.draw(text);

    // UI Textures for tile selection
    std::map<int, std::string> UI_texture = {
       {0, "textures/grass.png"},
       {1, "textures/rock.png"},
       {2, "textures/foilage.png"}
    };

    sf::Texture selectedTextureFile;
    if (selectedTextureFile.loadFromFile(UI_texture[this->selectedTileType-1])) {
        SelectedTexture.setTexture(&selectedTextureFile);
        SelectedTexture.setPosition(150, 362);
        window.draw(SelectedTexture);
    }

	// ------------------ SIDE BAR ------------------------

    std::vector<sf::RectangleShape> textures_UI_box;
    textures_UI_box.resize(UI_texture.size());
    sf::RectangleShape UI_element(sf::Vector2f(32, 32));

    text.setCharacterSize(20);
    

    // Iterate through each texture and assign it to a box
    for (size_t i = 0; i < textures_UI_box.size(); i++) {
        textures_UI_box[i].setSize(sf::Vector2f(32, 32));
        textures_UI_box[i].setPosition(350, 322 + i * 34); // Increment y-position by 32 for each box
		text.setPosition(335, 322 + i * 34);
		text.setString(to_string(i + 1)); // Display tile number in text
        window.draw(text);

        sf::Texture texture;
        if (texture.loadFromFile(UI_texture[i])) {
            textures_UI_box[i].setTexture(&texture);
        }
        else {
            std::cerr << "Error loading texture: " << UI_texture[i] << std::endl;
        }

        // Draw each texture box
        window.draw(textures_UI_box[i]);
    }
}

void MapEditor::draw(sf::RenderWindow& window) {
    // Draw the map's tiles
    map.draw(window);

    //Draw a highlight rectangle over the tile at the mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int row = mousePos.y / grid.getTileSize();
    int col = (mousePos.x - grid.getTileSize()) / grid.getTileSize();

    if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
        sf::RectangleShape highlight(sf::Vector2f(grid.getTileSize(), grid.getTileSize()));
        highlight.setPosition(grid.getTilePosition(row, col));
        highlight.setFillColor(sf::Color(255, 255, 255, 50));  // Semi-transparent highlight
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setOutlineThickness(2.0f);
        window.draw(highlight);
    }
	drawUI(window);
}

