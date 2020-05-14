#pragma once
#include "IShape.h"
#include "ISolidShape.h"
#include <boost/noncopyable.hpp>

class CCommandHandler : boost::noncopyable
{
public:
	CCommandHandler(std::istream& input, std::ostream& output);
	void HandleCommand();
	void PrintShapeWithMinPerimetr(); 
	void PrintShapeWithMaxArea(); 

private:
	void CreateLineSegment(std::istream& args);
	void CreateTriangle(std::istream& args); 
	void CreateRectangle(std::istream& args);
	void CreateCircle(std::istream& args); 

	typedef std::map<std::string, std::function<void(std::istream& args)>> ActionMap;

	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
	std::vector<std::unique_ptr<IShape>> m_shapeList;
};
