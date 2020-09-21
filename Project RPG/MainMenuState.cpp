#include "MainMenuState.h"


//Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Blackford.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.txt");

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
void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 250, 50,
		&this->font, "New Game", 25,
		sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70,70,70,0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS"] = new Button(100, 200, 250, 50,
		&this->font, "Settings", 25,
		sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new Button(100, 300, 250, 50,
		&this->font, "Editor", 25,
		sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new Button(100, 400, 250, 50,
		&this->font, "Quit", 25,
		sf::Color(0, 0, 0, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

//Constructors/Destructors

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
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

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.cbegin();
	for (it = this->buttons.cbegin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	//delete this->gamestate_btn;
}

//Functions
void MainMenuState::updateInput(const float & dt)
{

}

void MainMenuState::updateButtons()
{
	/*Update the all buttons here*/
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Settings

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	}

	//Quit Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->background);

	this->renderButtons(target);
}