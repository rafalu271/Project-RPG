#include "EditorState.h"

//Initializer functions
void EditorState::initVariables()
{

}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Blackford.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

//Buttons Initializations --- FOR REWORK
void EditorState::initButtons()
{

}

//Constructors/Destructors

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

	//this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	//this->background.setFillColor(sf::Color::Magenta);
}

EditorState::~EditorState()
{
	auto it = this->buttons.cbegin();
	for (it = this->buttons.cbegin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	//delete this->gamestate_btn;
}

//Functions
void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons()
{
	/*Update the all buttons here*/
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderButtons(target);
}