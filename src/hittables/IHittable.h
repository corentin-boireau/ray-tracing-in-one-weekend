#pragma once

#include <memory>

#include "../Vec3.h"
#include "../Ray.h"

class IMaterial;

struct Hit
{
	using mat_ptr = std::shared_ptr<IMaterial>;

	Point3  p;
	Vec3    normal;
	mat_ptr material;
	float   t;
	bool    isFrontFace;

	inline void setFaceNormal(Ray const& ray, Vec3 const& outwardNormal)
	{
		isFrontFace = dot(ray.direction(), outwardNormal) < 0.f;
		normal      = isFrontFace ? outwardNormal : -outwardNormal;
	}
};

/**
  Describes an object that a Ray can hit.
*/
class IHittable
{
public:
	/**
	  Returns whether this object has been hit by the given ray.
	*/
	virtual bool hit(Ray const& ray, float tMin, float tMax, Hit& result) const = 0;
};