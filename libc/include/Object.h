//
//	Objective Foundation Class
//
#ifndef	_SYSTEM_OBJECT_H_
#define	_SYSTEM_OBJECT_H_
#include <sys/types.h>

//typedef unsigned long int size_t;

namespace System {

	class	Object;

	class	Object {
	public:
		void*	operator new(size_t);
		void	operator delete(void*);
		void*	operator new[](size_t);
		void	operator delete[](void*);
		inline			Object(){}
		inline	virtual	~Object(){}	
	};


}

#endif
