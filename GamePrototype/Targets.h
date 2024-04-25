#pragma once	
#include "pch.h"
class Texture;

class Targets
{
public:
	Targets(Point2f Loc);
	~Targets();
	void Update(float elapsedSec);
	void Draw();

private:
	Point2f m_RandomLocation{};
	Texture* m_Plebs;
	Rectf m_SourceRect{};
	Rectf m_DestRect{};

};

	