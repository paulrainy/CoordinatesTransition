#include <gtest/gtest.h>
#include "CoordinateConverter.h"
#include <cmath>

using namespace Coordinates;

// Tolerance for comparisons (e.g. 1e-6 for coordinates)
constexpr double ABS_TOLERANCE = 1e-6;

TEST(GeodeticSpatialTest, RoundtripPZ90) {
    // 42 deg N, 32 deg E
    double lat = 42.0 * M_PI / 180.0;
    double lon = 32.0 * M_PI / 180.0;
    double height = 100.0; 

    GeodeticPoint original(lat, lon, height);
    
    // Convert to Spatial
    SpatialPoint spatial = GeodeticToSpatial(original, Standards::PZ90_11);
    
    // Convert Back
    GeodeticPoint back = SpatialToGeodetic(spatial, Standards::PZ90_11);

    EXPECT_NEAR(original.latitude, back.latitude, ABS_TOLERANCE);
    EXPECT_NEAR(original.longitude, back.longitude, ABS_TOLERANCE);
    EXPECT_NEAR(original.height, back.height, ABS_TOLERANCE);
}

TEST(GeodeticRectangularTest, RoundtripPZ90) {
    double lat = 42.0 * M_PI / 180.0;
    double lon = 32.0 * M_PI / 180.0;

    GeodeticPoint original(lat, lon);
    
    // Convert to Rectangular
    RectangularPoint rect = PZ90ToRectangular(original);
    
    // Convert Back
    GeodeticPoint back = RectangularToPZ90(rect);

    EXPECT_NEAR(original.latitude, back.latitude, ABS_TOLERANCE);
    EXPECT_NEAR(original.longitude, back.longitude, ABS_TOLERANCE);
}

TEST(SpatialHelmertTest, RoundtripWGS84PZ90) {
    SpatialPoint point(6378137.0, 0.0, 0.0); // Arbitrary point near equator
    
    // Convert to PZ90
    SpatialPoint pz90 = WGS84ToPZ90(point);
    
    // Convert Back to WGS84
    SpatialPoint back = PZ90ToWGS84(pz90);

    EXPECT_NEAR(point.x, back.x, 1e-2); // Helmert can be slightly lossy or iterative?
    EXPECT_NEAR(point.y, back.y, 1e-2);
    EXPECT_NEAR(point.z, back.z, 1e-2);
}

TEST(ValidationTest, InvalidInput) {
    // Latitude out of bounds
    EXPECT_THROW(GeodeticPoint(2.0 * M_PI, 0.0), std::invalid_argument);
    // Longitude out of bounds
    EXPECT_THROW(GeodeticPoint(0.0, 4.0 * M_PI), std::invalid_argument);
}
