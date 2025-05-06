#ifndef __Panel__
#define __Panel__

/**
* base class for panels
*/
class Panel
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
};

#endif // !__Panel__
