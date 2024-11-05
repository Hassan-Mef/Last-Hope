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
    this->SelectedTexture.setSize(sf::Vector2f(64, 64));
    this->saveButton = sf::RectangleShape(sf::Vector2f(120, 60));
    
}

void MapEditor::handleInput(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) {
            this->selectedTileType = 1;
            cout << "Selected tile type changed to: " << selectedTileType << endl;
        }
        else if(event.key.code == sf::Keyboard::Num2) {
            this->selectedTileType = 2;
            cout << "Selected tile type changed to: " << selectedTileType << endl;
        }
        else if (event.key.code == sf::Keyboard::Num3) {
            this->selectedTileType = 3;
            cout << "Selected tile type changed to: " << selectedTileType << endl;
        }
    }

     
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int row = mousePos.y / grid.getTileSize();
            int col = (mousePos.x - grid.getTileSize()) / grid.getTileSize();

            int mouseX = mousePos.x;
            int mouseY = mousePos.y;
            // ---------- Save Button -----------------------
            sf::Vector2f buttonCorrd = this->get_saveButtonCoord();
            if (mouseX >= buttonCorrd.x && mouseX < buttonCorrd.x+120 && mouseY >= buttonCorrd.y && mouseY < buttonCorrd.y+60) {  // Adjusted for 64x64 scale
                cout << "Saved File" << endl;
                saveMapToFile("MapData/map_1.json");
            }

            if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
                paintTile(row, col, selectedTileType);
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

void MapEditor::drawUI(sf::RenderWindow& window) {
    sf::Text text;
    text.setFont(font);
    text.setString("Selected tile:");
    text.setCharacterSize(32);  // Larger font size for better visibility with 64x64 scaling
    text.setFillColor(sf::Color::White);
    text.setPosition(10, 660);  // Adjusted for new scaling // bb
    window.draw(text);

    std::map<int, std::string> UI_texture = {
       {0, "assets/textures/bg.png"},
        {1, "assets/textures/grass.png"},
        {2, "assets/textures/rock.png"},
        {3, "assets/textures/foilage.png"}
    };

    sf::Texture selectedTextureFile;
    if (selectedTextureFile.loadFromFile(UI_texture[this->selectedTileType ])) {
        SelectedTexture.setTexture(&selectedTextureFile);
        SelectedTexture.setPosition(180, 660);  // Adjusted for new scaling
        window.draw(SelectedTexture);
    }

    // Save button with adjusted position
    
    saveButton.setPosition(460, 660);  // Adjusted position
    saveButton.setFillColor(sf::Color::Green);
    text.setPosition(470, 670);
    text.setString("Save");
    window.draw(saveButton);
    window.draw(text);

    // Adjusted positions for the sidebar UI texture boxes
    std::vector<sf::RectangleShape> textures_UI_box;
    textures_UI_box.resize(UI_texture.size());
    sf::RectangleShape UI_element(sf::Vector2f(64, 64));

    text.setCharacterSize(28);  // Adjusted for visibility with scaling
    for (size_t i = 0; i < textures_UI_box.size(); i++) {
        textures_UI_box[i].setSize(sf::Vector2f(64, 64));  // 64x64 for UI texture boxes
        textures_UI_box[i].setPosition(880, 0 + i * 66);  // Adjusted position for 64x64 scaling
        text.setPosition(860, 0 + i * 66);
        text.setString(to_string(i));
        window.draw(text);

        sf::Texture texture;
        if (texture.loadFromFile(UI_texture[i])) {
            textures_UI_box[i].setTexture(&texture);
        }

        window.draw(textures_UI_box[i]);
    }
}

void MapEditor::draw(sf::RenderWindow& window) {
    map.draw(window);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int row = mousePos.y / grid.getTileSize();
    int col = (mousePos.x - grid.getTileSize()) / grid.getTileSize();

    if (row >= 0 && row < grid.getRows() && col >= 0 && col < grid.getCols()) {
        sf::RectangleShape highlight(sf::Vector2f(grid.getTileSize(), grid.getTileSize()));
        highlight.setPosition(grid.getTilePosition(row, col));
        highlight.setFillColor(sf::Color(255, 255, 255, 50));
        highlight.setOutlineColor(sf::Color::Yellow);
        highlight.setOutlineThickness(2.0f);
        window.draw(highlight);
    }
    drawUI(window);
}

