#include "StdAfx.h"
#include "WXZEvent.h"


Event::Event()
{
	id_ = 0;
	name_ = L"";
}

Event::	Event(const Event & rhs)
{
	id_ = rhs.id_;
	name_ = rhs.name_;
}

Event::~Event()
{

}
//////////////////////////////////////////////////////////////////////////
