#include "NotificationState.h"
void NotificationState::render_strings()
{
	y_pos = notification_BG.getPosition().y;
	text_y = y_pos + 60 * (scale * .8) / 2.0;
	
	float i = (notification_lines / 2.0 - 2) * -1, dis = (92 / notification_lines) * scale*.9 ;
	text.setFillColor(Color::Black);
	for (int j = 0; j < notification_lines - 3; j++, i++) {
		draw_text(notification_strings[j], text_x, text_y + i * dis, (3 + 55 / notification_lines) * scale);
	}

}
void NotificationState::update_velocity()
{
	float pos_y = notification_BG.getPosition().y;
	if (pos_y >= win_y - 60 * scale || notification_delay>3)
		velocity.y += speed * dt * scale;
	else {
		notification_delay += dt;
		velocity.y = 0;
	}
	
	notification_BG.move(velocity);

	if (pos_y > win_y )
	{
		delete states->at(NotificationID);
		states->erase(NotificationID);
	}

}
NotificationState::NotificationState()
{
	scale = min(window->getSize().x / 350.0, window->getSize().y / 350.0);
	if (window->getSize().x > 1280) scale *= 0.75;
	initial_textures("notification");
	notification_BG.setTexture(*textures[0]);
	notification_BG.setOrigin(145,0);
	x_pos = window->getSize().x, y_pos = window->getSize().y;
	notification_BG.setPosition(x_pos, y_pos);
	velocity = { 0,(float) - 0.75 * scale};
}

NotificationState::~NotificationState()
{
}


void NotificationState::pollevent()
{
	prev(prev(states->end()))->second->pollevent();
}

void NotificationState::update()
{

	if (prev_win != window->getSize()) {
		prev_win = window->getSize();
		y_pos /= scale;
		win_x = window->getSize().x, win_y = window->getSize().y;
		if (win_x / 350.0 < win_y / 350.0) scale = win_x / 350.0;
		else scale = win_y / 350.0;
		if (win_x > 1280) scale *= 0.75;
		notification_BG.setScale(scale*.8, scale*.8);
		x_pos = win_x-10*scale;
		y_pos *= scale;
		text_x = x_pos - 145 * (scale*.8) / 2.0;
		text_y = y_pos + 60 * (scale*.8) / 2.0;
		notification_BG.setPosition(x_pos, y_pos);
	}
	prev(prev(states->end()))->second->update();
	update_velocity();
	//don't put anything after//
}

void NotificationState::render()
{
	
	window->draw(notification_BG);
	render_strings();
}