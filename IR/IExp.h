#pragma once

#include "IRTree.h"

class IExp {
public:
	//std::string id="";
	virtual ~IExp() {}
	virtual void print(/*IRTree& tree*/) const= 0;
	std::string label;
};