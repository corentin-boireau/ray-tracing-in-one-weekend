#include "Vec3.h"

Point3 randomPointInUnitSphere()
{
	Vec3 v = Vec3::random(-1.f, 1.f);

	while (v.length_squared() > 1.f)
		v = Vec3::random(-1.f, 1.f);

	return v;
}
