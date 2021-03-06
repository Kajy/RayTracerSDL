#include "RT_Scene.h"

RT::Scene::Scene()
{
}

RT::Scene::~Scene()
{
}

void	RT::Scene::setCamera(float x, float y, float z)
{
	_camera.setValue(x, y, z);
}

void	RT::Scene::addObjectOnScene(RT::Object *obj)
{
	_objects.push_back(obj);
}

void	RT::Scene::addLightOnScene(float x, float y, float z, uint32_t color)
{
	RT::Light *new_light = new RT::Light(x, y, z, color);
	_lights.push_back(new_light);
}

void	RT::Scene::addLightOnScene(float x, float y, float z, uint32_t color, float diffuse)
{
	RT::Light *new_light = new RT::Light(x, y, z, color, diffuse);
	_lights.push_back(new_light);
}

RT::Vector3df const  &RT::Scene::getCamera() const
{
	return (_camera);
}

RT::Intersec		RT::Scene::checkCollisionAll(float x, float y) const
{
	float		k = -1;
	float		tmp = -1;
	uint32_t	tmp_color = 0;
	RT::Intersec inter;
	RT::Vector3df vect(0, 0, 0);
	RT::Object		*obj = NULL;

	for (auto const &i : _objects) {
		vect.setValue(FOV - this->getCamera()._x - i->getPos()._x, ((RES_X / 2) - x) - this->getCamera()._y - i->getPos()._y, ((RES_Y / 2) - y) - this->getCamera()._z - i->getPos()._z);
		vect.normalize();
		tmp = i->checkCollision(this->getCamera(), vect);
		if ((tmp > 0 && k == -1) || (tmp > 0 && tmp < k)) {
			k = tmp;
			i->calcNormale(&vect, k, this->getCamera(), &inter);
			tmp_color = i->getColor();
			obj = i;
		}
	}
	if (k != -1) {
		inter.setDist(k);
		//obj->calcNormale(&vect, k, this->getCamera(), &inter);
		inter.setColor(tmp_color);
		inter.setColor(this->checkShadows(inter, this->checkLights(inter), obj));
	}
	return (inter);
}

uint32_t		RT::Scene::checkLights(RT::Intersec const &inter) const
{
	float			cos_light = 0, cos_reflect = 0;
	float			spec = 0;
	RT::Vector3df	vect_light;
	RT::Color		FinalColor(COLOR_BACKGROUND), ColorTmp;

	uint32_t tmp_color = inter.getColor();
	for (auto const &i : _lights) {
		vect_light.setValue(i->getPos()._x - inter.getInter()._x, i->getPos()._y - inter.getInter()._y, i->getPos()._z - inter.getInter()._z);
		vect_light.normalize();
		cos_light = MAX(0, (inter.getNormale()._x * vect_light._x) + (inter.getNormale()._y * vect_light._y) + (inter.getNormale()._z * vect_light._z));
		cos_reflect = MAX(0, (inter.getReflect()._x * vect_light._x) + (inter.getReflect()._y * vect_light._y) + (inter.getReflect()._z * vect_light._z));
		ColorTmp.tranformColorWithLightsCoef(tmp_color, *i, cos_light, pow(cos_reflect, 48));
		FinalColor.addColor(ColorTmp.getR(), ColorTmp.getG(), ColorTmp.getB());
	}
	FinalColor.divColor((float)(_lights.size()));
	return (FinalColor.getColor());
}

uint32_t	RT::Scene::checkShadows(RT::Intersec const &inter, uint32_t color, RT::Object *obj) const
{
	RT::Vector3df vect;
	uint32_t nb_inter = _lights.size();
	float tmp = -1;
	RT::Color	FinalColorShadow(color);
	bool stop = false;

	for (auto const &i : _lights) {
		stop = false;
		vect.setValue(i->getPos()._x - inter.getInter()._x, i->getPos()._y - inter.getInter()._y, i->getPos()._z - inter.getInter()._z);
		for (auto const &i : _objects) {
			if (i != obj) {
				tmp = i->checkCollision(inter.getInter(), vect);
				if (tmp > 0 && tmp < 1 && stop == false) {
					nb_inter--;
					stop = true;
				}
			}
		}
	}
	FinalColorShadow.mulColor((float)(nb_inter / _lights.size()));
	return (FinalColorShadow.getColor());
}