#ifndef COORDINATES_COORD_TYPES_H
#define COORDINATES_COORD_TYPES_H

#include <cmath>
#include <stdexcept>
#include <string>

namespace Coordinates {

// Ellipsoid parameters
struct Ellipsoid {
    int semiMajorAxis; // a
    double flattening;  // f (compression)

    // Derived parameters
    double eccentricitySquared() const {
        return 2 * flattening - flattening * flattening;
    }
};

// Common Ellipsoids
namespace Standards {
    inline constexpr Ellipsoid PZ90_11 = {6378136, 1.0 / 298.25784};
    inline constexpr Ellipsoid SK42 = {6378245, 1.0 / 298.3};
    inline constexpr Ellipsoid WGS84 = {6378137, 1.0 / 298.257223563};
}

// Geodetic Coordinates (B, L, H)
struct GeodeticPoint {
    double latitude;  // B (radians) [-PI/2, PI/2]
    double longitude; // L (radians) [-PI, PI]
    double height;    // H (meters)

    GeodeticPoint(double b, double l, double h = 0.0) : latitude(b), longitude(l), height(h) {
        validate();
    }

private:
    void validate() const {
        if (latitude < -M_PI / 2.0 || latitude > M_PI / 2.0) {
            throw std::invalid_argument("Invalid latitude: " + std::to_string(latitude) + " must be in [-PI/2, PI/2]");
        }
        if (longitude < -M_PI || longitude > M_PI) {
             throw std::invalid_argument("Invalid longitude: " + std::to_string(longitude) + " must be in [-PI, PI]");
        }
    }
};

// Rectangular Grid Coordinates (X, Y)
struct RectangularPoint {
    double x; // meters
    double y; // meters

    RectangularPoint(double x_val, double y_val) : x(x_val), y(y_val) {
        validate();
    }

private:
    void validate() const {
        if (x < -20037500.0 || x > 20037500.0) { // Approx limit, but usually less
             // Optional validation based on projection, but let's keep it loose or remove if too restrictive
        }
    }
};

// Spatial Geocentric Coordinates (X, Y, Z)
struct SpatialPoint {
    double x; // meters
    double y; // meters
    double z; // meters

    SpatialPoint(double x_val, double y_val, double z_val) : x(x_val), y(y_val), z(z_val) {}
};

} // namespace Coordinates

#endif // COORDINATES_COORD_TYPES_H
