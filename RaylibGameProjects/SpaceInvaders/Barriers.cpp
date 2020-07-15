#include "Barriers.h"

Barriers::Barriers()
{
}

Barriers::Barriers(Rectangle BarrierRec)
{
	m_barrierRec = BarrierRec;
}

Barriers::~Barriers()
{

}

void Barriers::DrawBarriers()
{
	DrawRectangle(m_barrierRec.x, m_barrierRec.y, m_barrierRec.width, m_barrierRec.height, Color(GREEN));
}
