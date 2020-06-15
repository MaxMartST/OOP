#pragma once
#include "../task_1_figures/ICanvas.h"
#include <string>
#include <vector>

class CMockedCanvas : public ICanvas
{
public:
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
	std::vector<std::string> GetFigureElements() const;

private:
	std::vector<std::string> m_figureElements;
};
