#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <iostream>

template<typename T> class CSingleton
{
public:

    /*
      Cette fonction retourne l'unique instance de l'objet
    */
    static T* getInstance(void)
    {
        if(singleton==0)
	    {
            singleton = new T;
	    }
        return singleton;
    }

    /*
      Cette fonction tue l'unique instance de l'objet
    */
    static void clear()
    {
        if(singleton!=0)
	    {
		delete singleton ;
		singleton=0;
	    }
    }


    //un couple d'accesseur / mutateur
    int getValue()
    {
        return  value;
    }

    void setValue(int val)
    {
	value=val;
    }

protected:

    int value;

    CSingleton() : value(0)
    {
        std::cout<<"Singleton crée"<<std::endl;
    }

    virtual ~CSingleton()
    {
        std::cout<<"Singleton détruit"<<std::endl;
    }

    static T *singleton;
};

template <typename T> T* CSingleton<T>::singleton = 0;

#endif
