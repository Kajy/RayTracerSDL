class RT_Vector
{
public:
	RT_Vector(int x, int y, int z) :
		_x(x),
		_y(y),
		_z(z)
	{};
	~RT_Vector() {};
	void	setValue(int x, int y, int z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

public:
	int	_x;
	int _y;
	int	_z;
};