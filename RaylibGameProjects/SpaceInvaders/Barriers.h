#pragma once
#include"raylib.h"
class Barriers
{
public:
	Barriers();
	Barriers(Rectangle BarrierRec);
	Rectangle m_barrierRec;
	~Barriers();
	void DrawBarriers();
};

