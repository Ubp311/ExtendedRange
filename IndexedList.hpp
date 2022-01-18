#include    <iostream>


using namespace std;

template<typename T>
struct indexBox
{
    size_t  index;
    T*  valsPtr;
    indexBox*   next;
};


template<typename T>
class IndexedList
{
private:
    indexBox<T>    *headPtr, *currentPtr;
    size_t  size;
    size_t  currentColumnCapacity;
    size_t  rowSize;
public:
    MiniIndexedList()
    {
        headPtr = nullptr;
        currentPtr = nullptr;
        size = 0;
        currentColumnCapacity = 1;
        rowSize = 0;
    };
    MiniIndexedList(size_t size)
    {
        currentColumnCapacity = size;
        rowSize++;

        headPtr = new indexBox<T>();
        headPtr->valsPtr = new T[size]();
    };
    MiniIndexedList(const MiniIndexedList& _var)
    {
        indexBox<T>* tempIndexBox = new indexBox<T>();
		
		currentPtr = headPtr = nullptr;
		_var.currentPtr = _var.headPtr;
		size = 0;
		currentColumnCapacity = 1;
		rowSize = 0;

		if (_var.headPtr != nullptr)
		{
			currentPtr = headPtr = new indexBox<T>();
			currentPtr->valsPtr = new T[currentColumnCapacity];
			*currentPtr->valsPtr = *_var.currentPtr->valsPtr;
			currentPtr->index = _var.currentPtr->index;
			_var.currentPtr = _var.currentPtr->next;
			currentColumnCapacity <<= 1;
		}
		while (_var.currentPtr != nullptr)
		{
			currentPtr->next = new indexBox<T>();
			currentPtr = currentPtr->next;
			currentPtr->valsPtr = new T[currentColumnCapacity];
			currentPtr->index = _var.currentPtr->index;
			copy(_var.currentPtr->valsPtr, _var.currentPtr->valsPtr + currentColumnCapacity, currentPtr->valsPtr);
			_var.currentPtr = _var.currentPtr->next;
			currentColumnCapacity <<= 1;
        }
    };
    ~MiniIndexedList() 
	{
		indexBox<T>* tempCurrentPtr = nullptr;
		currentPtr = headPtr;

		while (currentPtr != nullptr)
		{
			tempCurrentPtr = currentPtr;
			currentPtr = currentPtr->next;
			delete[]	tempCurrentPtr->valsPtr;
			delete	tempCurrentPtr;
		}
	};
    inline size_t	getSize()
	{
		return	size;
	};
    inline void  pushBack(const T&& _var)
    {
        if(size)
    };
};