/*
 * DFSprite.cpp
 *
 *  Created on: 21.02.2013.
 *      Author: idjukic
 */

#include "DFSprite.h"

#include <string.h>
#include <stdlib.h>

DFSprite::DFSprite()
{
	// TODO Auto-generated constructor stub

}

DFSprite::~DFSprite()
{
	// TODO Auto-generated destructor stub
}


bool DFSprite::parseSpriteFile(const char* filename)
{
	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
		return false;
	XMLElement *imgElem = doc.FirstChildElement("img");
	if (imgElem)
	{
		imageName = "";
		char *pch = strrchr(filename, '/');
		if (pch)
			imageName.append(filename, pch - filename + 1);
		imageName.append(imgElem->Attribute("name"));
		imageWidth = atoi(imgElem->Attribute("w"));
		imageHeight = atoi(imgElem->Attribute("h"));
		XMLElement *defElem = imgElem->FirstChildElement("definitions");
		if (defElem)
		{
			XMLElement *rootDir = defElem->FirstChildElement("dir");
			if (rootDir)
			{
				const char *rootDirName = rootDir->Attribute("name");
				parseSpriteElements(rootDir, rootDirName);
			}
		}
	}
	return true;
}

bool DFSprite::parseAnimFile(const char* filename)
{
	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
		return false;
	XMLElement *animsElem = doc.FirstChildElement("animations");
	if (animsElem)
	{
		char *pch = strrchr(filename, '/');
		std::string spriteSheet;
		if (pch)
			spriteSheet.append(filename, pch - filename + 1);
		spriteSheet.append(animsElem->Attribute("spriteSheet"));
		if (parseSpriteFile(spriteSheet.c_str()) == false)
			return false;
		//parse animations
		XMLElement *animElem = animsElem->FirstChildElement("anim");
		while (animElem)
		{
			int animIndex = animations.size();
			animations.push_back(Animation());
			animations[animIndex].index = animIndex;
			animations[animIndex].name = animElem->Attribute("name");
			animations[animIndex].loops = atoi(animElem->Attribute("loops"));
			//parse cells
			XMLElement *cellElem = animElem->FirstChildElement("cell");
			while (cellElem)
			{
				int cellIndex = animations[animIndex].cells.size();
				animations[animIndex].cells.push_back(Cell());
				animations[animIndex].cells[cellIndex].index = cellIndex;
				animations[animIndex].cells[cellIndex].delay = atoi(cellElem->Attribute("delay"));
				// TODO: handle 'index' cell attribute ?
				//parse sprites
				XMLElement *sprElem = cellElem->FirstChildElement("spr");
				while (sprElem)
				{
					int sprIndex = animations[animIndex].cells[cellIndex].sprites.size();
					const char *sprName = sprElem->Attribute("name");
					animations[animIndex].cells[cellIndex].sprites.push_back(Sprite());
					animations[animIndex].cells[cellIndex].sprites[sprIndex].frame = getFrameByName(sprName);
					animations[animIndex].cells[cellIndex].sprites[sprIndex].x = atoi(sprElem->Attribute("x"));
					animations[animIndex].cells[cellIndex].sprites[sprIndex].y = atoi(sprElem->Attribute("y"));
					animations[animIndex].cells[cellIndex].sprites[sprIndex].z = atoi(sprElem->Attribute("z"));
					animations[animIndex].cells[cellIndex].sprites[sprIndex].angle =
							sprElem->Attribute("angle") ? atoi(sprElem->Attribute("angle")) : 0;
					animations[animIndex].cells[cellIndex].sprites[sprIndex].flipV =
							sprElem->Attribute("flipV") ? atoi(sprElem->Attribute("flipV")) : 0;
					animations[animIndex].cells[cellIndex].sprites[sprIndex].flipH =
							sprElem->Attribute("flipH") ? atoi(sprElem->Attribute("flipH")) : 0;
					printf("[GLSprite] SPR: %s\n", sprName);
					sprElem = sprElem->NextSiblingElement("spr");
				}
				cellElem = cellElem->NextSiblingElement("cell");
			}
			animElem = animElem->NextSiblingElement("anim");
		}
	}
	return true;
}

DFSprite::Frame* DFSprite::getFrameByName(const char* name)
{
	for (int i = 0; i < frames.size(); i++)
	{
		if (frames[i].name == name)
			return &(frames[i]);
	}
	return NULL;
}

DFSprite::Frame* DFSprite::getFrameByIndex(int index)
{
	return &(frames[index]);
}

DFSprite::Animation* DFSprite::getAnimationByName(const char* name)
{
	for (int i = 0; i < animations.size(); i++)
	{
		if (frames[i].name == name)
			return &(animations[i]);
	}
	return NULL;
}

DFSprite::Animation* DFSprite::getAnimationByIndex(int index)
{
	return &(animations[index]);
}

void DFSprite::parseSpriteElements(XMLElement* dirElem, std::string dirFullName)
{
	XMLElement *sprElem = dirElem->FirstChildElement("spr");
	while (sprElem)
	{
		const char *sprName = sprElem->Attribute("name");
		if (sprName)
		{
			DFSprite::Frame frame;
			frame.index = frames.size();
			frame.name = dirFullName + sprName;
			frame.x = atoi(sprElem->Attribute("x"));
			frame.y = atoi(sprElem->Attribute("y"));
			frame.w = atoi(sprElem->Attribute("w"));
			frame.h = atoi(sprElem->Attribute("h"));
			frames.push_back(frame);
			printf("[GLSprite] FRAME: %s\n", frame.name.c_str());
		}
		sprElem = sprElem->NextSiblingElement("spr");
	}
	// dir recursion
	XMLElement *nextDir = dirElem->FirstChildElement("dir");
	while (nextDir)
	{
		const char *nextDirName = nextDir->Attribute("name");
		if (nextDirName)
		{
			std::string nextName = dirFullName;
			nextName.append(nextDirName);
			nextName.append("/");
			parseSpriteElements(nextDir, nextName);
		}
		nextDir = nextDir->NextSiblingElement("dir");
	}
}

