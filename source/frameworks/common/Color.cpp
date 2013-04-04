/*
	by Ilija
*/


#include "Color.h"
#include "mymath.h"


//init common colors
Color Color::Transparent(0, 0, 0, 0);
Color Color::White(1, 1, 1);
Color Color::Black(0, 0, 0);
Color Color::Red(1, 0, 0);
Color Color::Green(0, 1, 0);
Color Color::Blue(0, 0, 1);
Color Color::Yellow(1, 1, 0);
Color Color::Gray(0.5, 0.5, 0.5);

void Color::setHexColor(unsigned int argb)
{
	int A = argb >> 24;
	int R = (argb >> 16) & 0xFF;
	int G = (argb >> 8) & 0xFF;
	int B = argb & 0xFF;
	alpha = A / 255.0f;
	red = R / 255.0f;
	green = G / 255.0f;
	blue = B / 255.0f;
};

void Color::addBrightness(int brightness)
{
	red = CLAMP(red + brightness, 0, 1);
	green = CLAMP(green + brightness, 0, 1);
	blue = CLAMP(blue + brightness, 0, 1);
}
