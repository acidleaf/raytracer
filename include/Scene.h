#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include "Primitive.h"

class Scene {
protected:
	std::vector<Primitive*> _primitives;
	
public:
	bool init();
	void release();
	
	void addPrimitive(Primitive* p);
	
	std::vector<Primitive*>& getPrimitives() { return _primitives; }
};


#endif