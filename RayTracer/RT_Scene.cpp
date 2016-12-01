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
		inter.setColor(/*this->checkShadows(inter, */this->checkLights(inter)/*, obj)*/);
	}
	return (inter);
}

uint32_t		RT_Scene::checkLights(RT_Intersec const &inter) const
{
	float			cos_light = 0, cos_reflect = 0;
	float			spec = 0;
	RT_Vector3df	vect_light;
	RT_Color		FinalColor(COLOR_BACKGROUND), ColorTmp;
	float			R_tmp, G_tmp, B_tmp;

	uint32_t tmp_color = inter.getColor();
	for (auto const &i : _lights) {
		vect_light.setValue(i->getPos()._x - inter.getInter()._x, i->getPos()._y - inter.getInter()._y, i->getPos()._z - inter.getInter()._z);
		vect_light.normalize();
		cos_light = MAX(0, (inter.getNormale()._x * vect_light._x) + (inter.getNormale()._y * vect_light._y) + (inter.getNormale()._z * vect_light._z));
		cos_reflect = MAX(0, (inter.getReflect()._x * vect_light._x) + (inter.getReflect()._y * vect_light._y) + (inter.getReflect()._z * vect_light._z));
		ColorTmp.tranformColorWithLightsCoef(tmp_color, i->getColor(), cos_light, pow(cos_reflect, 48));
		FinalColor.addColor(ColorTmp.getR(), ColorTmp.getG(), ColorTmp.getB());
	}
	FinalColor.divColor(_lights.size());
	return (FinalColor.getColor());
}

uint32_t	RT_Scene::checkShadows(RT_Intersec const &inter, uint32_t color, RT_Object *obj) const
{
	RT_Vector3df vect;
	float nb_inter = _lights.size();
	float tmp = -1;
	RT_Color	FinalColorShadow(color);
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
	FinalColorShadow.mulColor(nb_inter / _lights.size());
	return (FinalColorShadow.getColor());
}