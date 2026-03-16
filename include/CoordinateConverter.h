#ifndef COORDINATES_CONVERTER_H
#define COORDINATES_CONVERTER_H

#include "CoordinateTypes.h"
#include <vector>

namespace Coordinates {

// Geodetic <-> Spatial (Cartesian)
SpatialPoint GeodeticToSpatial(const GeodeticPoint& point, const Ellipsoid& ellipsoid);
GeodeticPoint SpatialToGeodetic(const SpatialPoint& point, const Ellipsoid& ellipsoid);

// PZ-90 Geodetic <-> PZ-90 Rectangular (Gauss-Krüger)
RectangularPoint PZ90ToRectangular(const GeodeticPoint& point);
GeodeticPoint RectangularToPZ90(const RectangularPoint& point);

// SK-42 <-> PZ-90
RectangularPoint SK42ToPZ90(const RectangularPoint& point);
RectangularPoint PZ90ToSK42(const RectangularPoint& point);

// WGS-84 <-> PZ-90 (Helmert 7-parameter transformation)
SpatialPoint WGS84ToPZ90(const SpatialPoint& point);
SpatialPoint PZ90ToWGS84(const SpatialPoint& point);

// High-level coordinate system transitions
GeodeticPoint WGS84ToSK42Geodetic(const GeodeticPoint& point);
GeodeticPoint SK42ToWGS84Geodetic(const GeodeticPoint& point);

} // namespace Coordinates

#endif // COORDINATES_CONVERTER_H
