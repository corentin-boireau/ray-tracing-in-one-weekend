#pragma once

#include "Vec3.h"
#include "Ray.h"

struct Hit
{
	Point3 p;
	Vec3   normal;
	float  t;
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