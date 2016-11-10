#include "RT.h"

RT_Scene::RT_Scene()
{
	_camera = new RT_Vector3df(0, 0, 0);
}

RT_Scene::~RT_Scene()
{
}

void	RT_Scene::setCamera(float x, float y, float z)
{
	_camera->setValue(x, y, z);
}

void	RT_Scene::addObjectOnScene(RT_Object *obj)
{
	_objects.push_back(obj);
}

RT_Vector3df *RT_Scene::getCamera()
{
	return (_camera);
}

float		RT_Scene::checkCollisionAll(RT_Vector3df *vect, RT_Vector3df *camera)
{
	float k = -1;
	float tmp;

	for (auto i(_objects.begin()); i != _objects.end(); ++i) {
		tmp = (*i)->checkCollision(vect, camera);
		if (tmp > 0 && k == -1) {
			k = tmp;
		}
		if (tmp > 0 && tmp < k) {
			k = tmp;
		}
	}
	return (k);
}