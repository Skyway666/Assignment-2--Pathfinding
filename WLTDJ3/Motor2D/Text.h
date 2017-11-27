#pragma once
#include "Ui_element.h"

class Text : public Ui_element
{
public:
	Text(int x, int y, const char* _string);
	~Text();
	void Draw();
private:

	SDL_Texture* graphic;
};

