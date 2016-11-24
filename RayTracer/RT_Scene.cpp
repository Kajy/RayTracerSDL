#include "RT_Scene.h"

RT_Scene::RT_Scene()
{
}

RT_Scene::~RT_Scene()
{
}

void	RT_Scene::setCamera(float x, float y, float z)
{
	_camera.setValue(x, y, z);
}

void	RT_Scene::addObjectOnScene(RT_Object *obj)
{
	_objects.push_back(obj);
}

void	RT_Scene::addLightOnScene(float x, float y, float z, uint32_t color)
{
	RT_Light *new_light = new RT_Light(x, y, z, color);
	_lights.push_back(new_light);
}

RT_Vector3df const  &RT_Scene::getCamera() const
{
	return (_camera);
}

RT_Intersec		RT_Scene::checkCollisionAll(float x, float y) const
{
	float		k = -1;
	float		tmp = -1;
	uint32_t	tmp_color = 0;
	RT_Intersec inter;
	RT_Object 	*obj = NULL;
	RT_Vector3df vect(0, 0, 0);

	for (auto i(_objects.begin()); i != _objects.end(); ++i) {
		vect.setValue(FOV - this->getCamera()._x - (*i)->getPos()._x, ((RES_X / 2) - x) - this->getCamera()._y - (*i)->getPos()._y, ((RES_Y / 2) - y) - this->getCamera()._z - (*i)->getPos()._z);
		vect.normalize();
		tmp = (*i)->checkCollision(this->getCamera(), vect);
		if ((tmp > 0 && k == -1) || (tmp > 0 && tmp < k)) {
			k = tmp;
			obj = (*i);
			tmp_color = (*i)->getColor();
		}
	}
	if (k != -1 && obj != NULL) {
		inter.setDist(k);
		obj->calcNormale(&vect, k, this->getCamera(), &inter);
		inter.setColor(tmp_color);
		inter.setColor(this->checkShadows(inter, this->checkLights(inter), obj));
	}
	return (inter);
}

uint32_t		RT_Scene::checkLights(RT_Intersec const &inter) const
{
	float			cos_light = 0, tmp;
	float			spec = 0;
	RT_Vector3df	vect_light;

	uint32_t tmp_color = inter.getColor();
	float R = ((COLOR_BACKGROUND & 0xff000000) >> 24);
	float G = ((COLOR_BACKGROUND & 0x00ff0000) >> 16);
	float B = ((COLOR_BACKGROUND & 0x0000ff00) >> 8);
	for (auto i(_lights.begin()); i != _lights.end(); ++i) {
		vect_light.setValue((*i)->getPos()->_x - inter.getInter()._x, (*i)->getPos()->_y - inter.getInter()._y, (*i)->getPos()->_z - inter.getInter()._z);
		vect_light.normalize();
		cos_light = (inter.getNormale()._x * vect_light._x) + (inter.getNormale()._y * vect_light._y) + (inter.getNormale()._z * vect_light._z);
		spec = ((-inter.getReflect()._x) * vect_light._x) + ((-inter.getReflect()._y) * vect_light._y) + ((-inter.getReflect()._z) * vect_light._z);
		if (cos_light >= 0.000001) {
			R += ((tmp_color & 0xff000000) >> 24) * cos_light;// +(255 * pow(spec, 0.5));
			G += ((tmp_color & 0x00ff0000) >> 16) * cos_light;// +(255 * pow(spec, 0.5));
			B += ((tmp_color & 0x0000ff00) >> 8) * cos_light;// +(255 * pow(spec, 0.5));
		}
	}
	R /= _lights.size();
	G /= _lights.size();
	B /= _lights.size();
	return ((unsigned int)R << 24) + ((unsigned int)G << 16) + ((unsigned int)B << 8);
}

uint32_t	RT_Scene::checkShadows(RT_Intersec const &inter, uint32_t color, RT_Object *obj) const
{
	RT_Vector3df vect;
	float nb_inter = _lights.size();
	float tmp = -1;
	bool stop;

	for (auto i(_lights.begin()); i != _lights.end(); ++i) {
		stop = true;
		vect.setValue((*i)->getPos()->_x - inter.getInter()._x, (*i)->getPos()->_y - inter.getInter()._y, (*i)->getPos()->_z - inter.getInter()._z);
		//vect.normalize();
		for (auto i(_objects.begin()); i != _objects.end(); ++i) {
			if ((*i) != obj)
				tmp = (*i)->checkCollision(inter.getInter(), vect);
			if (tmp > 0 && tmp < 1 && stop == true) {
				nb_inter--;
				stop = false;
			}
		}
	}
	return ((unsigned int)(((color & 0xff000000) >> 24) * (nb_inter / _lights.size())) << 24) + ((unsigned int)(((color & 0x00ff0000) >> 16) * (nb_inter / _lights.size())) << 16) + ((unsigned int)(((color & 0x0000ff00) >> 8) * (nb_inter / _lights.size())) << 8);

}