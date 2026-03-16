#include "CoordinateConverter.h"
#include <cmath>
#include <vector>

namespace Coordinates {

namespace { // Anonymous namespace for helper constants and functions

// Helmert transformation constants for PZ-90 to WGS-84
struct HelmertParams {
    double dx; // m
    double dy; // m
    double dz; // m
    double wx; // rad
    double wy; // rad
    double wz; // rad
    double m;  // scale factor (1e-6)
};

const HelmertParams PZ90_TO_WGS84_PARAMS = {
    -0.013,
    0.106,
    0.022,
    -1.115071e-8,
    1.716240e-8,
    -2.041066e-8,
    -0.008e-6
};

// Matrix operations
std::vector<std::vector<double>> GetCoeffMatrix(double rx, double ry, double rz, bool isDirect) {
    if (isDirect) {
        return {
            {1.0, rx, -ry},
            {-rx, 1.0, rz},
            {ry, -rz, 1.0}
        };
    } else {
         return {
            {1.0, -rx, ry},
            {rx, 1.0, -rz},
            {-ry, rz, 1.0}
        };
    }
}

std::vector<double> MultiplyMatrix(const std::vector<std::vector<double>>& coeff, const std::vector<double>& coord) {
    std::vector<double> result(3, 0.0);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i] += coeff[i][j] * coord[j];
        }
    }
    return result;
}

} // namespace

SpatialPoint GeodeticToSpatial(const GeodeticPoint& point, const Ellipsoid& ellipsoid) {
    double e2 = ellipsoid.eccentricitySquared();
    double sinB = std::sin(point.latitude);
    double cosB = std::cos(point.latitude);
    double sinL = std::sin(point.longitude);
    double cosL = std::cos(point.longitude);

    double N = ellipsoid.semiMajorAxis / std::sqrt(1.0 - e2 * sinB * sinB);

    double X = (N + point.height) * cosB * cosL;
    double Y = (N + point.height) * cosB * sinL;
    double Z = ((1.0 - e2) * N + point.height) * sinB;

    return SpatialPoint(X, Y, Z);
}

GeodeticPoint SpatialToGeodetic(const SpatialPoint& point, const Ellipsoid& ellipsoid) {
    double e2 = ellipsoid.eccentricitySquared();
    double D = std::sqrt(point.x * point.x + point.y * point.y);

    double L = 0.0;
    if (D == 0.0) {
        double B = (M_PI / 2.0) * (point.z / std::abs(point.z));
        double H = point.z * std::sin(B) - ellipsoid.semiMajorAxis * std::sqrt(1.0 - e2 * std::sin(B) * std::sin(B));
        return GeodeticPoint(B, 0.0, H);
    } else {
         double la = std::abs(std::asin(point.y / D));
         if (point.y < 0) {
              if (point.x > 0) L = 2.0 * M_PI - la;
              else L = M_PI + la;
         } else if (point.y > 0) {
              if (point.x < 0) L = M_PI - la;
              else L = la;
         } else {
              L = (point.x < 0) ? M_PI : 0.0;
         }
    }

    double B = 0.0;
    double H = 0.0;

    if (point.z == 0.0) {
         B = 0.0;
         H = D - ellipsoid.semiMajorAxis;
    } else {
         double R = std::sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
         double C = std::asin(point.z / R);
         double Ro = (e2 * ellipsoid.semiMajorAxis) / (2.0 * R);
         double S1 = 0.0;
         double S2 = 0.0;

         while (true) {
              double currentB = C + S1;
              S2 = std::asin((Ro * std::sin(2.0 * currentB)) / std::sqrt(1.0 - e2 * std::pow(std::sin(currentB), 2)));
              if (std::abs(S2 - S1) < 1e-12) { // Increased precision from 1e-4
                   B = currentB;
                   H = D * std::cos(B) + point.z * std::sin(B) - ellipsoid.semiMajorAxis * std::sqrt(1.0 - e2 * std::pow(std::sin(B), 2));
                   break;
              } else {
                   S1 = S2;
              }
         }
    }

    return GeodeticPoint(B, L, H);
}

// Gauss-Krüger Projection constants (PZ-90 to Rectangular)
RectangularPoint PZ90ToRectangular(const GeodeticPoint& point) {
    double B = point.latitude;
    double L = point.longitude * 180.0 / M_PI; // Degrees

    int zoneN = static_cast<int>((6.0 + L) / 6.0);
    double distL = (L - (3.0 + 6.0 * (zoneN - 1.0))) / 57.29577951; // Radians

    double sinB = std::sin(B);
    double sinB2 = sinB * sinB;
    double l2 = distL * distL;

    double X = 6367558.4968 * B - std::sin(2 * B) * (16002.8900 + 66.9607 * sinB2 + 0.3515 * sinB2 * sinB2
            - l2 * (1594561.25 + 5336.535 * sinB2 + 26.790 * sinB2 * sinB2 + 0.149 * sinB2 * sinB2 * sinB2
            + l2 * (672483.4 - 811219.9 * sinB2 + 5420.0 * sinB2 * sinB2 - 10.6 * sinB2 * sinB2 * sinB2
            + l2 * (278194.0 - 830174.0 * sinB2 + 572434.0 * sinB2 * sinB2 - 16010.0 * sinB2 * sinB2 * sinB2
            + l2 * (109500.0 - 574700.0 * sinB2 + 863700.0 * sinB2 * sinB2 - 398600.0 * sinB2 * sinB2 * sinB2)))));

    double Y = (5.0 + 10.0 * zoneN) * std::pow(10, 5) + distL * std::cos(B) * (6378245.0 + 21346.1415 * sinB2 + 107.1590 * sinB2 * sinB2
            + 0.5977 * sinB2 * sinB2 * sinB2 + l2 * (1070204.16 - 2136826.66 * sinB2 + 17.98 * sinB2 * sinB2 - 11.99 * sinB2 * sinB2 * sinB2
            + l2 * (270806.0 - 1523417.0 * sinB2 + 1327645.0 * sinB2 * sinB2 - 21701.0 * sinB2 * sinB2 * sinB2
            + l2 * (79690.0 - 866190.0 * sinB2 + 1730360.0 * sinB2 * sinB2 - 945460.0 * sinB2 * sinB2 * sinB2))));

    return RectangularPoint(X, Y);
}

GeodeticPoint RectangularToPZ90(const RectangularPoint& point) {
    double beta = point.x / 6367558.4968;
    int zoneN = static_cast<int>(point.y / 1000000.0);

    double sinBeta = std::sin(beta);
    double sinBeta2 = sinBeta * sinBeta;

    double B0 = beta + std::sin(2 * beta) * (0.00252588685 - 0.0000149186 * sinBeta2 + 0.00000011904 * sinBeta2 * sinBeta2);

    double cosB0 = std::cos(B0);
    double Z = (point.y - (10 * zoneN + 5) * 100000.0) / (6378245 * cosB0);

    double sinB0 = std::sin(B0);
    double sinB02 = sinB0 * sinB0;
    double Z2 = Z * Z;

    double deltaB = -Z2 * std::sin(2 * B0) * (0.251684631 - 0.003369263 * sinB02 + 0.00001127 * sinB02 * sinB02
            - Z2 * (0.10500614 - 0.04559916 * sinB02 + 0.00228901 * sinB02 * sinB02 - 0.00002987 * sinB02 * sinB02 * sinB02
            - Z2 * (0.042858 - 0.025318 * sinB02 + 0.014346 * sinB02 * sinB02 - 0.001264 * sinB02 * sinB02 * sinB02
            - Z2 * (0.01672 - 0.00630 * sinB02 + 0.01188 * sinB02 * sinB02 - 0.00328 * sinB02 * sinB02 * sinB02))));

    double distL = Z * (1.0 - 0.0033467108 * sinB02 - 0.0000056002 * sinB02 * sinB02 - 0.0000000187 * sinB02 * sinB02 * sinB02
            - Z2 * (0.16778975 + 0.16273586 * sinB02 - 0.00052490 * sinB02 * sinB02 - 0.00000846 * sinB02 * sinB02 * sinB02
            - Z2 * (0.0420025 + 0.1487407 * sinB02 + 0.0059420 * sinB02 * sinB02 - 0.0000150 * sinB02 * sinB02 * sinB02
            - Z2 * (0.01225 + 0.09477 * sinB02 + 0.03282 * sinB02 * sinB02 - 0.00034 * sinB02 * sinB02 * sinB02
            - Z2 * (0.0038 + 0.0524 * sinB02 + 0.0482 * sinB02 * sinB02 - 0.0032 * sinB02 * sinB02 * sinB02)))));

    double B = deltaB + B0;
    double L = 6.0 * (static_cast<double>(zoneN) - 0.5) / 57.29577951 + distL;

    return GeodeticPoint(B, L);
}

// SK-42 <-> PZ-90 (Direct assignment in previous code?)
RectangularPoint SK42ToPZ90(const RectangularPoint& point) {
    // Original Translate code: CoordinateObjectPZ90.setRectangularCoordinates(X, Y)
    // So it might just be the same coordinate system projection but with different ellipsoid parameters?
    // Wait, original translation says:
    // void CoordinatesTranslation::PZ90toSK42() {
    //      coordinateObjectPZ90.geodeticToRectangular();
    //      coordinateObjectSK42.setRectangularCoordinates(...)
    // }
    // There is no complex transformation, just copying coordinates!
    // I will return the same point if that's what that was doing, or add comments.
    return point;
}

RectangularPoint PZ90ToSK42(const RectangularPoint& point) {
    return point;
}

// WGS-84 <-> PZ-90
SpatialPoint PZ90ToWGS84(const SpatialPoint& point) {
    const auto& p = PZ90_TO_WGS84_PARAMS;
    auto matrix = GetCoeffMatrix(p.wx, p.wy, p.wz, false);
    std::vector<double> coord = {point.x, point.y, point.z};
    auto mid = MultiplyMatrix(matrix, coord);

    for (int i = 0; i < 3; ++i) {
        mid[i] *= (1.0 - p.m);
    }

    mid[0] -= p.dx;
    mid[1] -= p.dy;
    mid[2] -= p.dz;

    return SpatialPoint(mid[0], mid[1], mid[2]);
}

SpatialPoint WGS84ToPZ90(const SpatialPoint& point) {
     const auto& p = PZ90_TO_WGS84_PARAMS;
     auto matrix = GetCoeffMatrix(p.wx, p.wy, p.wz, true);
     std::vector<double> coord = {point.x, point.y, point.z};
     auto mid = MultiplyMatrix(matrix, coord);

     for (int i = 0; i < 3; ++i) {
         mid[i] *= (1.0 + p.m);
     }

     mid[0] += p.dx;
     mid[1] += p.dy;
     mid[2] += p.dz;

     return SpatialPoint(mid[0], mid[1], mid[2]);
}

// High-level transitions using Spatial intermediating
GeodeticPoint WGS84ToSK42Geodetic(const GeodeticPoint& point) {
    // PZ90.setGeodeticCoordinates(B + 0.00036, L - 0.00018)
    // Then convert PZ90 to Rectangular, then set SK42 setRectangular.
    // This looks like an empirical correction.
    GeodeticPoint mid(point.latitude + 0.00036, point.longitude - 0.00018);
    // Since original PZ90toSK42 is just copy rectangular, we can return the geodetic of that corrected point?
    // Wait, PZ90toSK42 sets rectangular coordinates of SK42 to rectangular PZ90.
    // So to get Geodetic of SK42? SK42 didn't have Geodetic in original code or it was disabled!
    // Let's create a Geodetic from the corrected coordinates.
    return mid;
}

GeodeticPoint SK42ToWGS84Geodetic(const GeodeticPoint& point) {
    // B - 0.00036, L + 0.00018
    return GeodeticPoint(point.latitude - 0.00036, point.longitude + 0.00018);
}

} // namespace Coordinates
