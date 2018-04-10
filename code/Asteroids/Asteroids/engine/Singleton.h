#pragma once
template < class T> class Singleton
{
public:
		static T* Get() 
		{
			static T* m_pInstance;

			if (!m_pInstance)
			{
				m_pInstance = new T;
			}

			return m_pInstance;
	}
protected:
	Singleton() {}
	~Singleton() {}
private:
	Singleton(Singleton const&) {}
};



