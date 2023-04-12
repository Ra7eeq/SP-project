#include "PauseState.h"


void PauseState::update_buttons(RenderWindow* window)
{
	for (auto& button : buttons) {
		buttontex.setTextureRect(IntRect(0, button.pressed * 49, 190, 49));
		buttontex.setPosition(x + button.x * scale * 0.33, y + button.y * scale * 0.33);
		if (buttontex.getGlobalBounds().contains(window->mapPixelToCoords(Mouse::getPosition(*window)))) {
			if (Mouse::isButtonPressed(Mouse::Left) && buttontex.getGlobalBounds().contains(clicked_on))button.pressed = 1;
			else {
				if (button.pressed)
					button.execute = 1;
				button.pressed = 0;
			}
			button.hover = 1;
		}
		else {
			button.pressed = 0;
			button.hover = 0;
		}
	}
}

void PauseState::render_buttons(RenderWindow* window)
{
	buttontex.setScale(scale * 0.33, scale * 0.33);
	button_text.setCharacterSize(7.5 * scale);
	for (auto& button : buttons) {
		buttontex.setTextureRect(IntRect(0, button.pressed * 49, 190, 49));
		buttontex.setPosition(x + button.x * scale * 0.33, y + button.y * scale * 0.33);
		button_text.setString(button.txt);
		FloatRect bounds = button_text.getLocalBounds();
		button_text.setOrigin(bounds.width / 2.0, bounds.top + bounds.height / 2.0);
		button_text.setPosition(x + button.x * scale * 0.33, (button.pressed) ? y + button.y * scale * 0.33 + 2 * scale * 0.33 : y + button.y * scale * 0.33 - 2 * scale * 0.33);
		if (button.hover)button_text.setFillColor(Color::White);
		else button_text.setFillColor(Color::Color(226, 211, 195));
		window->draw(buttontex);
		window->draw(button_text);
	}
}

PauseState::PauseState()
{
	initial_textures("pause");

	initial_fps();

	tissue.setTexture(*textures[2]);
	tissue.setOrigin(700 / 2, 700 / 2);

	tint.setSize({ 1920, 1080 });
	tint.setFillColor(Color(0, 0, 0, 154));

	buttontex.setTexture(*textures[0]);
	buttontex.setTextureRect(IntRect(0, 0, 190, 49));
	buttontex.setOrigin(190 / 2, 49 / 2);

	button_text.setFont(font);
	buttons.push_back({ "Resume",0,-48, resume });
	buttons.push_back({ "Settings",0,16, settings });
	buttons.push_back({ "Save and Exit" ,0,80, exit });

}

PauseState::~PauseState()
{
}

void PauseState::update(float dt, RenderWindow* window, int* terminator, map<int, State*>* states)
{
	win_x = window->getSize().x, win_y = window->getSize().y;
	x = win_x / 2, y = win_y / 2;
	if (win_x / 120.0 < win_y / 120.0) scale = win_x / 120.0;
	else scale = win_y / 120.0;
	mouse_pos = Mouse::getPosition(*window);
	/////// Do Not touch;


	tint.setSize({ win_x, win_y });
	tissue.setPosition(x, y);
	tissue.setScale(scale * 0.125, scale * 0.125);

	if (resume) {
		resume = 0;
		delete states->at(PauseID);
		states->erase(PauseID);
	}
	if (settings) {
		settings = 0;
		states->insert(SettingsST);
		states->at(SettingsID)->update(dt, window, terminator, states);

		for (auto& state : *states) {
			if (state.first != SettingsID && state.first != BackgroundID && state.first != MapBuilderID && state.first != GameID) {
				delete state.second;
				states->erase(state.first);
			}
		}

	}
	if (exit) {
		exit = 0; 

		states->insert(MainMenuST);
		states->at(MainMenuID)->update(dt, window, terminator, states);

		if (states->find(BackgroundID) == states->end())
			states->insert(BackgroundST);

		for (auto& state : *states) {
			if (state.first != MainMenuID && state.first != BackgroundID) {
				delete state.second;
				states->erase(state.first);
			}
		}

	}

	update_buttons(window);

	if (fps_active)
		calc_fps(dt);
}

void PauseState::pollevent(Event event, RenderWindow* window, int* terminator, map<int, State*>* states)
{
	while (window->pollEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			window->close(); break;
		case Event::KeyPressed:
			switch (event.key.code) {
			case Keyboard::Escape:
				resume = 1; break;
			case Keyboard::F3:
				fps_active = !fps_active; break;
			}
		case Event::MouseButtonPressed:
			switch (event.mouseButton.button) {
			case Mouse::Left:
				clicked_on = window->mapPixelToCoords(Mouse::getPosition(*window));
				break;
			}
		}
	}
}

void PauseState::render(RenderWindow* window)
{
	window->draw(tint);
	window->draw(tissue);
	render_buttons(window);

	text.setFillColor(Color::Black);
	draw_text(window, "Paused", x, y - 35 * scale, 6.5 * scale);
	if (fps_active)
		window->draw(fps_text);
}
