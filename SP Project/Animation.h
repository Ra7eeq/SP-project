#pragma once
#include"State.h"


#include"Global.h"
using namespace globalvar;

class Animation
{
private:
	Texture animation_tex;
	Sprite animation_sprite;
	IntRect frame;
	int frame_count, current_frame = 0;
	float &map_x, &map_y;
	float delay = 0, prev_scale = 0, animation_scale = 0;
	bool loop;


public:
	//public variables:
	Vector2i pos;
	bool despawn = 0;

	//constructors / destructors
	Animation(IntRect, int, Vector2i, string, float, Color, bool, float&, float&);
	~Animation();

	//functions
	void update(float);
	void render(Shader*);
};