#pragma once
#include "Hat.h"
class BaseballCap :
	public Hat
{
public:
	//BaseballCap() :Hat(10.0f, 1.5f, -0.5f, 1.0f);
	BaseballCap();
	~BaseballCap();

	virtual void launch() {
		
	}
};

