#pragma once
class PanAndZoom
{
public:
	PanAndZoom();
	PanAndZoom(float x, float y);
	~PanAndZoom();
	void WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY);
	void ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY);

	void SetOffSets(float fOffsetX, float fOffsetY);
	void SetStartPan(float fStartPanX, float fStartPanY);

	void PanOffsetChange(float fOffsetX, float fOffsetY);
private:
	float m_fOffsetX;
	float m_fOffsetY;

	float m_fStartPanX;
	float m_fStartPanY;
};