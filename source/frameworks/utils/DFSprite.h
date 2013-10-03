/*
 * DFSprite.h
 *
 *  Created on: 21.02.2013.
 *      Author: idjukic
 */

#ifndef DFSPRITE_H_
#define DFSPRITE_H_

#include <string>
#include <vector>

#include <TinyXML/tinyxml2.h>
using namespace tinyxml2;

class DFSprite
{
public:
	struct Frame
	{
		int index;
		std::string name;
		int x;
		int y;
		int w;
		int h;
	};

	struct Sprite
	{
		Frame *frame;
		int x;
		int y;
		int z;
		int angle;
		int flipV;
		int flipH;
	};

	struct Cell
	{
		int index;
		int delay;
		std::vector<Sprite> sprites;
	};

	struct Animation
	{
		int index;
		int loops;
		std::string name;
		std::vector<Cell> cells;
	};

public:
	DFSprite();
	virtual ~DFSprite();

	bool parseSpriteFile(const char *filename);
	bool parseAnimFile(const char *filename);

	Frame *getFrameByName(const char *name);
	Frame *getFrameByIndex(int index);
	Animation *getAnimationByName(const char *name);
	Animation *getAnimationByIndex(int index);

private:
	void parseSpriteElements(XMLElement *dirElem, std::string dirFullName);

public:
	std::string fileName;
	std::string imageName;
	int imageWidth;
	int imageHeight;
	std::vector<Frame> frames;
	std::vector<Animation> animations;
};

#endif /* DFSPRITE_H_ */
