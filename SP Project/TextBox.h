#pragma once
#include"State.h"

#include"Global.h"
using namespace globalvar;

using namespace sf;
using namespace std;
struct TextBox {

private:
	string* target_string = nullptr;
	int character_limit = 25;
	Vector2f position = { 0, 0 };
	float scale = 1, bound_y = 0, delay = 0, box_x_bound = 0, text_x_bound = 0, limit = 100000, transparency = 255;
	string input_string = "", placeholder = "", clipboard = "", pw_string = "", *display_string = &input_string;
	bool isActive = 0, selected = 0, cursor = 0, mode = 0, *submit_bool = nullptr;
	Text inputted_text, placeholder_text;
	Sprite box;
	SoundBuffer keypress_buff, enterpress_buff;
	Sound keypress, enterpress;



public:

	TextBox();

	void setTargetString(string& target_string);

	void setTexture(Texture& box_texture);

	void setColor(Color color);

	void setFont(Font font);

	void setPosition(const Vector2f new_position);

	void setLimit(float);

	void setScale(const float new_scale);

	void setPlaceholderText(const string placeholder);

	void text_poll(Event event);

	void initializeTextBox(std::string& targ_string, Texture& texture, const string placeholder = "Write Here", Vector2f pos = { 0.0, 0.0 }, float scale = 1, bool mode = 0, bool* submit_bool = nullptr);

	void drawTextBox(RenderWindow* window);

	bool empty();

	void setMode(bool mode);              //0 = text, 1 = password
	
	void setSubmitBool(bool* submit_bool);

	void save_text();

	void submit();

	void update();

};