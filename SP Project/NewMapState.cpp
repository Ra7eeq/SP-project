#include "NewMapState.h"
#define sliderconst 100.0

void NewMapState::update_arrow()
{
	back_arrow.setPosition(x - 35 * scale, y - 35 * scale);
	if (back_arrow.getGlobalBounds().contains(window->mapPixelToCoords(Mouse::getPosition(*window)))) {
		back_arrow.setTextureRect(IntRect(22, 0, 22, 21));
		back_arrow.setScale(scale * 0.4, scale * 0.4);
		if (Mouse::isButtonPressed(Mouse::Left) && back_arrow.getGlobalBounds().contains(clicked_on)) {
			arrow_pressed = 1;
			back_arrow.setTextureRect(IntRect(44, 0, 22, 21));
			back_arrow.setScale(scale * 0.36, scale * 0.36);
		}
		else {
			if (arrow_pressed) {
				arrow_pressed = 0;
				states->erase(NewMapID);
				pins.erase("");
				destruct = 1;
				return;
			}
		}
	}
	else {
		arrow_pressed = 0;
		back_arrow.setTextureRect(IntRect(0, 0, 22, 21));
		back_arrow.setScale(scale * 0.4, scale * 0.4);
	}
}

void NewMapState::update_slider(slider_info* sliders, int target)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {

			tip.setScale(scale / 2.3, scale / 2.3);
			tip.setTextureRect(tipsleft[sliders[target].color]);
			tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
			tip.setPosition(x + sliders[target].x * (scale / 2.3), y + sliders[target].y * scale);
			if (tip.getGlobalBounds().contains(clicked_on))
				sliders[target].presssed = 1;


			tip.setScale(sliderconst / 18 * (scale / 2.3), (scale / 2.3));
			tip.setTextureRect(mids[3]);
			tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
			tip.setPosition(x + (sliders[target].x + 9) * (scale / 2.3), y + sliders[target].y * scale);
			if (tip.getGlobalBounds().contains(clicked_on))
				sliders[target].presssed = 1;


			tip.setScale(scale / 2.3, scale / 2.3);
			tip.setTextureRect(tipsright[3]);
			tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
			tip.setPosition(x + (sliders[target].x + 9 + sliderconst) * (scale / 2.3), y + sliders[target].y * scale);
			if (tip.getGlobalBounds().contains(clicked_on))
				sliders[target].presssed = 1;
		}
		else
			sliders[target].presssed = 0;
	if (sliders[target].presssed) {
		float initpos = x + (sliders[target].x + 9) * (scale / 2.3), mxlen = sliderconst * (scale / 2.3), stepsize = mxlen / sliders[target].mx;
		if (mouse_pos.x < initpos) sliders[target].tipx = initpos;
		else if (mouse_pos.x > initpos + mxlen) sliders[target].tipx = initpos + mxlen;
		else
		{
			sliders[target].tipx = initpos + (sliders[target].mx - round((initpos + mxlen - mouse_pos.x) / stepsize)) * stepsize;
		}

		*sliders[target].linker = round(((sliders[target].tipx - x) / (scale / 2.3) - sliders[target].x - 9) / sliderconst * sliders[target].mx) + 2;
		sliders[target].midscale = (sliders[target].tipx - initpos) / (18 * (scale / 2.3));
	}
}

void NewMapState::render_slider(int target)
{
	//background

	tip.setScale(sliderconst / 18 * (scale / 2.3), (scale / 2.3));
	tip.setTextureRect(mids[3]);
	tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
	tip.setPosition(x + (sliders[target].x + 9) * (scale / 2.3), y + sliders[target].y * scale);
	window->draw(tip);

	tip.setScale(scale / 2.3, scale / 2.3);
	tip.setTextureRect(tipsright[3]);
	tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
	tip.setPosition(x + (sliders[target].x + 9 + sliderconst) * (scale / 2.3), y + sliders[target].y * scale);
	window->draw(tip);

	//foreground

	tip.setScale(scale / 2.3, scale / 2.3);
	tip.setTextureRect(tipsleft[sliders[target].color]);
	tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
	tip.setPosition(x + sliders[target].x * (scale / 2.3), y + sliders[target].y * scale);
	window->draw(tip);

	tip.setScale(sliders[target].midscale * (scale / 2.3), (scale / 2.3));
	tip.setTextureRect(mids[sliders[target].color]);
	tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
	tip.setPosition(x + (sliders[target].x + 9) * (scale / 2.3), y + sliders[target].y * scale);
	window->draw(tip);

	tip.setScale(scale / 2.3, scale / 2.3);
	tip.setTextureRect(tipsright[sliders[target].color]);
	tip.setOrigin(tip.getLocalBounds().left, tip.getLocalBounds().top + tip.getLocalBounds().height / 2.0);
	tip.setPosition(sliders[target].tipx, y + sliders[target].y * scale);

	window->draw(tip);

	slider_text.setCharacterSize(8 * scale);
	slider_text.setString(sliders[target].name);
	slider_text.setPosition(x + (sliders[target].x - 15) * (scale / 2.3), y + (sliders[target].y - 5.5) * scale);
	window->draw(slider_text);

	slider_text.setCharacterSize(8 * scale);
	if (sliders[target].text_type == 0)
		slider_text.setString(to_string(*sliders[target].linker));
	else if (sliders[target].text_type == 1)
		slider_text.setString(to_string(*sliders[target].linker) + "%");
	else
		slider_text.setString(sliders[target].txt[*sliders[target].linker]);
	slider_text.setPosition(x + (sliders[target].x + 9 + sliderconst + 15) * (scale / 2.3), y + (sliders[target].y - 5.5) * scale);
	window->draw(slider_text);

}

NewMapState::NewMapState()
{
	initial_textures("newmap");
	bg.setTexture(*textures[0]);
	bg.setOrigin(100 / 2, 100 / 2);

	tint.setSize({ 1920, 1080 });
	tint.setFillColor(Color(0, 0, 0, 154));

	back_arrow.setTexture(*textures[1]);
	back_arrow.setTextureRect(IntRect(0, 0, 22, 21));
	back_arrow.setOrigin(22 / 2, 21 / 2);

	slider_text.setFont(font);
	slider_text.setCharacterSize(50);
	slider_text.setFillColor(Color::Black);

	tip.setTexture(*textures[4]);

	txt_box.initializeTextBox(map_name, *textures[2], "Enter Map name");

}

NewMapState::~NewMapState()
{

}


void NewMapState::update()
{
	mouse_pos = window->mapPixelToCoords(Mouse::getPosition(*window));

	if (prev_win != window->getSize()) {
		prev_win = window->getSize();
		win_x = window->getSize().x, win_y = window->getSize().y;
		x = win_x / 2, y = win_y / 2;
		if (win_x / 150.0 < win_y / 150.0) scale = win_x / 150.0;
		else scale = win_y / 150.0;
		///////////////////////////////////
		tint.setSize({ win_x, win_y });

		bg.setPosition(x, y);
		bg.setScale(scale, scale);

		txt_box.setPosition({ x - 10, y - 20 * scale});
		txt_box.setScale(scale*0.2);
	}

	update_arrow();
	if (destruct)
		return;

	txt_box.update();

	for (int i = 0; i < 2; i++)
		update_slider(sliders, i);
}


void NewMapState::render()
{
	window->draw(tint);
	window->draw(bg);


	window->draw(back_arrow);

	for (int i = 0; i < 2; i++)
		render_slider(i);

	txt_box.drawTextBox(window);
}

void NewMapState::pollevent()
{
	while (window->pollEvent(event)) {
		switch (event.type) {
		case Event::Closed:
			window->close(); break;
		case Event::KeyPressed:
			switch (event.key.code) {
			case Keyboard::Escape:
				states->erase(NewMapID); pins.erase(""); return; break;
			case Keyboard::F3:
				fps_active = !fps_active; break;
			case Keyboard::F11:
				fullscreen = !fullscreen;
				game.update_window();
				break;
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