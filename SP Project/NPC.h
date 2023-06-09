#pragma once
#include "Entity.h"
//#include "DialogueState.h"
struct NPC :
	public Entity
{
	using::Entity::Entity;
private:
	Vector2f  curr_movement = { 0.f, 0.f }, dist = { 0, 0 };
	bool will_move = 0, in_dialogue = 0;
	float motion_delay = 4, move_speed = 100, switch_delay = 0, motion_cd = 0;
	dialogue* npc_dialogues = nullptr, single_dialogue[1] = {}, * curr_dialogue = nullptr;
	short dialogues_num, curr_dialogue_num = 0, prev_tile_x = -1, prev_tile_y = -1;

	//private functions
	void player_collision_check();
	bool collide_with_player(Vector2f);

public:
	~NPC();
	void updatePos();
	bool legal_direction(Vector2f, short, short);
	void set_type(short);
	void set_dialogue(dialogue*, short);
	void start_dialogue(dialogue*, short);
	void type_behaviour();
	void path_follow(short , short , short , short , short , short );
	void update_looks();
	void update();
};