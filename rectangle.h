#include <memory>
class Rectangle;
using RectanglePtr = std::shared_ptr<Rectangle>;

#ifndef Rectangle_H
#define Rectangle_H

#include "shape.h"

class Rectangle : public Shape {
	unsigned int m_vao;
protected:
	Rectangle();
public:
	static RectanglePtr Make();
	virtual ~Rectangle();
	virtual void Draw(StatePtr st);
};
#endif