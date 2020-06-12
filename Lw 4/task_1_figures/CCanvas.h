#pragma once

#include <SFML/Graphics.hpp>
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	explicit CCanvas(sf::RenderTarget& window);
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
	//std::vector<std::string> GetDrawingHistory(); 

private:
	sf::RenderTarget& m_window;
	std::vector<std::string> m_drawingHistory;
};
