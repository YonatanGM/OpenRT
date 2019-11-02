#pragma once

#include "types.h"

namespace rt {
	struct Ray;

	/**
	 * @brief Base light source abstract interface class
	 */
	class ILight
	{
	public:
		DllExport ILight(void) = default;
		DllExport ILight(const ILight&) = delete;
		DllExport virtual ~ILight(void) = default;
		DllExport const ILight& operator=(const ILight&) = delete;

		/**
		 * @brief Calculates the light intensity, at the point \b ray.org which is to be illuminated.
		 * @details This function sets the \b ray.dir to be the the direction vector from the surface point \b ray.org to the light source.
		 * @param[in, out] ray The ray from object point to the light source
		 * @return The intensity of light hitting the point \b ray.org
		 */
		DllExport virtual std::optional<Vec3f> illuminate(Ray& ray) = 0;
	};
}
