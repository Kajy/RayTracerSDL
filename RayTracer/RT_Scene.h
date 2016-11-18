#include "RT.h"

class RT_Scene
{
public:
	RT_Scene();
	~RT_Scene();

	void			setCamera(float x, float y, float z);
	void			addObjectOnScene(RT_Object *obj);
	void			addLightOnScene(float x, float y, float z, uint32_t color);

	RT_Intersec		*checkCollisionAll(float x, float y);
	void			checkLights(RT_Intersec *inter);


	RT_Vector3df	*getCamera();

private:
	RT_Vector3df				*_camera;
	std::vector<RT_Object *>	_objects;
	std::vector<RT_Light *>		_lights;
};