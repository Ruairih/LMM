#ifndef WRAPPER_H
#define WRAPPER_H

template<class T>
class Wrapper
{
public:
	Wrapper(int = 0)
	{
		DataPtr =0;
	}

	Wrapper(const T& inner)
	{
		DataPtr = inner.clone();
	}

	~Wrapper()
	{
		if(DataPtr!=0)
		{
			delete DataPtr;
		}
	}

	Wrapper& operator=(const Wrapper<T>& original)
	{
		if( this!= &original)
		{
			if(DataPtr!=0)
			{
				delete DataPtr;
				DataPtr = original.DataPtr !=0 ? original.DataPtr->clone() : 0;	
			}
		}

		return *this;
	}

	Wrapper(const Wrapper<T>& original)
	{
		if(original.DataPtr !=0)
		{
			DataPtr = original.DataPtr->clone();
		}
		else
		{
			DataPtr=0;
		}
	}

	T& operator*()
	{
		return *DataPtr;
	}
	
	const T& operator*() const
	{
		return *DataPtr;
	}

	T* operator->()
	{
		return DataPtr;
	}

	const T* const operator->() const
	{
		return DataPtr;
	}

private:
	T* DataPtr;
};





#endif