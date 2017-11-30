#ifndef GLOBAL_ELEMENT_HANDLER_H
#define GLOBAL_ELEMENT_HANDLER_H

#include <mutex>

// Esta classe serve para manipulação de variáveis globais
template <typename type>
class GlobalElementHandler
{
	public:

		void set(type element_);
		type get(void);

	private:
		
		type element;		
		std::mutex elementMutex;
};

#endif
