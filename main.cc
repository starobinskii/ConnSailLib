#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "conn.hh"

int main(const int argc, const char *argv[]){
    std::vector< std::vector<double> > points;
    points.push_back(std::vector<double>{0., 0.});
    conn::squiggle(points, 1000., 1000., 0.5 * conn::pi, conn::pi, 8, 16);
    //conn::letterPi(points, 50., 40., 10., 0.3 * conn::pi, 16);
    
    std::vector< std::vector<double> > relativePoints(
        points.size(),
        std::vector<double>{0., 0.}
    );
    for(std::size_t i = 1; i < relativePoints.size(); ++i){
        relativePoints[i][0] = points[i][0] - points[i - 1][0];
        relativePoints[i][1] = points[i][1] - points[i - 1][1];
    }
    
    std::vector< std::vector<double> > initialGPSPoint;
    initialGPSPoint.push_back(std::vector<double>{41., 59., 04.});
    initialGPSPoint.push_back(std::vector<double>{02., 49., 16.});
    conn::printGPSPoint(initialGPSPoint);
    std::vector< std::vector<double> > nextGPSPoint;
    const double latitude = conn::degreesFromGPSCoordinate(
        initialGPSPoint[0]
    );
    const double longitude = conn::degreesFromGPSCoordinate(
        initialGPSPoint[1]
    );
    for(std::size_t i = 1; i < relativePoints.size(); ++i){
        const double destination = sqrt(
            std::pow(points[i][0], 2) 
            + std::pow(points[i][1], 2)
        );
        const double bearing = asin(points[i][0] / destination);
        nextGPSPoint = conn::destinationGPSPoint(
            latitude,
            longitude,
            destination,
            bearing,
            false
        );
        conn::printGPSPoint(nextGPSPoint);
    }
    
    return 0;
}