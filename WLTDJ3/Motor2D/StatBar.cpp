#include "StatBar.h"
#include "j1App.h"
#include "j1Render.h"



StatBar::StatBar(int x, int y, int w, int h, float* _variable) : Ui_element(x, y)
{
	bar = { x, y, w, h };
	variable = _variable;
	variable_starting_value = *_variable;
	bar_width_starting_value = w;
}


StatBar::~StatBar()
{
	
}

void StatBar::Update()
{
	//Update bar's position
	bar.x = position.x;
	bar.y = position.y;
	
	//Update bar's length
	bar.w = bar_width_starting_value * (*variable/variable_starting_value);

	//Update position of all linked objects to match parent
	for (int i = 0; i < linked_elements.count(); i++)
	{
		linked_elements[i]->position = position + linked_elements[i]->offset;
	}
}

void StatBar::Draw()
{
	App->render->DrawQuad(bar, 255, 0, 0, 255, true, false);
}