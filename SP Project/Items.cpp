#include "Items.h"

Items::~Items()
{
}

void Items::move()
{
	if (time <= 1.0 && !interact) {
		float x_movement = velocity.x * dt, y_movement = velocity.y * dt;
		if (legal_tile({ x_movement, 0 }, current_hitbox))
			 {
			pos.x += x_movement;
		}
		if (legal_tile({ 0, y_movement }, current_hitbox)) {
			pos.y += y_movement;
		}

		velocity.x -= dt_v_x * dt;
		velocity.y -= dt_v_y * dt;
		time += dt;
	}
	
}

void Items::intersect(){
	if (time > 1.0 || interact) {
		FloatRect item_hitbox = { getRelativePos().x - 8 * entity_stats.scale_const ,getRelativePos().y - 8 * entity_stats.scale_const,16 * entity_stats.scale_const,16 * entity_stats.scale_const };
		if (item_hitbox.intersects(FloatRect(player_entity.getRelativePos().x - (player_entity.current_hitbox.x * player_entity.entity_stats.scale_const) / 2.0, player_entity.getRelativePos().y - (player_entity.current_hitbox.y * player_entity.entity_stats.scale_const) / 2.0, player_entity.current_hitbox.x * player_entity.entity_stats.scale_const, player_entity.current_hitbox.y * player_entity.entity_stats.scale_const)))
		{
			//destroys item
			despawn = 1;
		}
	}
}

void Items::update()
{
	if (game_time - despawn_timer > time_to_despawn && !persistant) {
		despawn = 1;
		return;
	}
	
	if (prev_win != window->getSize()) {

		prev_win = window->getSize();
		win_x = window->getSize().x, win_y = window->getSize().y;
		if (win_x / 540.0 < win_y / 304.5) scale = win_x / 540.0;
		else scale = win_y / 304.5;
		                //////////////////////////
		entity_sprite.setScale(scale, scale);

	}
	entity_sprite.setPosition(round(map_x * scale) + pos.x * scale, round(map_y * scale) + pos.y * scale);

	
    intersect();
	move();
}

void Items::pollevent()
{
}

