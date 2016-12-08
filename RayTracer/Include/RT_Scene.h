#ifndef RT_SCENE_H_
#define RT_SCENE_H_

#include "RT_Intersec.h"
#include "RT_Object.h"
#include "RT_Light.h"
#include "RT_Vector3df.h"
#include "RT_Color.h"

namespace RT {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void			setCamera(float x, float y, float z);
		void			addObjectOnScene(RT::Object *obj);

		void			addLightOnScene(float x, float y, float z, uint32_t color);
		void			addLightOnScene(float x, float y, float z, uint32_t color, float diffuse);

		RT::Intersec		checkCollisionAll(float x, float y) const;
		uint32_t		checkLights(RT::Intersec const &inter) const;
		uint32_t		checkShadows(RT::Intersec const &inter, uint32_t color, RT::Object *obj) const;


		RT::Vector3df	const &getCamera() const;

	private:
		RT::Vector3df				_camera;
		std::vector<RT::Object *>	_objects;
		std::vector<RT::Light *>		_lights;
	};

}

#endif // !RT_SCENE_H_