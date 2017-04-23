#pragma once
#include <vector>

namespace dream {	
	template<class T>
	class IManager 
	{
	protected:		
		std::vector<T*> m_objects;			// Holds pointers to T objects 
	public:
		// Clean manager objects upon destraction
		virtual ~IManager() { Clean(); }

		// Call it to initialise Manager
		virtual void Init() = 0;
		// Adds a new object to the Manager
		virtual void Add(T* object);
		// Returns a stored object
		virtual T* Get(const std::string& name) = 0;
		// Cleans the objects 
		virtual void Clean();
	};

	template<class T>
	inline void IManager<T>::Add(T * object){
		m_objects.push_back(object);
	}
	template<class T>
	inline void IManager<T>::Clean(){
		for (T* object : m_objects) delete object;
	}
}