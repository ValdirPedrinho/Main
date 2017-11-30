#include "GlobalElementHandler.h"

template <typename type> void GlobalElementHandler<type>::set(type element_)
{
	elementMutex.lock();
	element = element_;
	elementMutex.unlock();
}

template <typename type> type GlobalElementHandler<type>::get(void)
{
	return element;
}
