#ifndef RT_SCENE_H_
#define RT_SCENE_H_

#include "RT_Intersec.h"
#include "RT_Object.h"
#include "RT_Light.h"
#include "RT_Vector3df.h"
#include "RT_Color.h"


class RT_Scene
{
public:
	RT_Scene();
	~RT_Scene();

	void			setCamera(float x, float y, float z);
	void			addObjectOnScene(RT_Object *obj);

	void			addLightOnScene(float x, float y, float z, uint32_t color);
	void			addLightOnScene(float x, float y, float z, uint32_t color, float diffuse);

	RT_Intersec		checkCollisionAll(float x, float y) const;
	uint32_t		checkLights(RT_Intersec const &inter) const;
	uint32_t		checkShadows(RT_Intersec const &inter, uint32_t color, RT_Object *obj) const;


	RT_Vector3df	const &getCamera() const;

private:
	RT_Vector3df				_camera;
	std::vector<RT_Object *>	_objects;
	std::vector<RT_Light *>		_lights;
};

#endif // !RT_SCENE_H_