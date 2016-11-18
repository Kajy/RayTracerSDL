#include "RT.h"

#ifndef RT_SCENE_H_
#define RT_SCENE_H_



class RT_Scene
{
public:
	RT_Scene();
	~RT_Scene();

	void			setCamera(float x, float y, float z);
	void			addObjectOnScene(RT_Object *obj);
	void			addLightOnScene(float x, float y, float z, uint32_t color);

	RT_Intersec		checkCollisionAll(float x, float y) const;
	uint32_t		checkLights(RT_Intersec const &inter) const;


	RT_Vector3df	const &getCamera() const;

private:
	RT_Vector3df				_camera;
	std::vector<RT_Object *>	_objects;
	std::vector<RT_Light>		_lights;
};

#endif // !RT_SCENE_H_