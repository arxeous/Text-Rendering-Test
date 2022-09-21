#include "PanAndZoom.h"

PanAndZoom::PanAndZoom()
	: m_fOffsetX(0), m_fOffsetY(0), m_fStartPanX(0), m_fStartPanY(0)
{
}

PanAndZoom::PanAndZoom(float x, float y)
	: m_fOffsetX(x), m_fOffsetY(y), m_fStartPanX(0), m_fStartPanY(0)
{
}

PanAndZoom::~PanAndZoom()
{
}

void PanAndZoom::WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY)
{
	nScreenX = (int)(fWorldX - m_fOffsetX);
	nScreenY = (int)(fWorldY - m_fOffsetY);
}	

void PanAndZoom::ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY)
{
	fWorldX = (float)(nScreenX + m_fOffsetX);
	fWorldY = (float)(nScreenY + m_fOffsetY);
}

void PanAndZoom::SetOffSets(float fOffsetX, float fOffsetY)
{
	m_fOffsetX = fOffsetX;
	m_fOffsetY = fOffsetY;
}

void PanAndZoom::SetStartPan(float fStartPanX, float fStartPanY)
{
	m_fStartPanX = fStartPanX;
	m_fStartPanY = fStartPanY;
}

void PanAndZoom::PanOffsetChange(float fOffsetX, float fOffsetY)
{
	m_fOffsetX -= (fOffsetX - m_fStartPanX);
	m_fOffsetY -= (fOffsetY - m_fStartPanY);
}
