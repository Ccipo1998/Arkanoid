
#pragma once

template <class T>
class Singleton
{

public:

    /*
    @brief
    Delete singleton clonation
    */
    Singleton(Singleton<T> &other) = delete;

    /*
    @brief
    Delete singleton assignment
    */
    void operator=(const Singleton<T> &) = delete;

    /*
    Getter for the unique instance of the template class
    */
    static T* GetInstance();

    ~Singleton();

private:

    Singleton(); // disabling constructor outside

    static T* Instance;

};

#pragma region DEFINITIONS

template <class T>
Singleton<T>::Singleton()
    : Instance(nullptr)
    {}

template <class T>
T* Singleton<T>::GetInstance()
{
    if (Instance == nullptr)
        Instance = new T();
        
    return Instance;
}

template <class T>
Singleton<T>::~Singleton()
{
    delete Instance;
}

// static member variables need to be defined explicitly
template <class T>
T* Singleton<T>::Instance = nullptr;

#pragma endregion DEFINITIONS
