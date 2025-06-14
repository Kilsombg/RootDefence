#ifndef __Creator__
#define __Creator__

#include<memory>

/**
* Base Creator class.
* 
* T is base class that created objects inherits.
*/
template <typename T>
class Creator
{
public:
	virtual std::unique_ptr<T> create() const = 0;
};

#endif // !__Creator__
