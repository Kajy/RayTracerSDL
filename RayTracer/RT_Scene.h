#include "RT.h"

class RT_Scene
{
public:
	RT_Scene();
	~RT_Scene();

	void	setCamera(float x, float y, float z);
	void	addObjectOnScene(RT_Object *obj);
	float	checkCollisionAll(RT_Vector3df *vect, RT_Vector3df *camera);

	RT_Vector3df	*getCamera();

private:
	RT_Vector3df				*_camera;
	std::vector<RT_Object *>	_objects;
};