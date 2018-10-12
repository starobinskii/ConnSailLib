#if !defined(CONNSAILLIB_HH)
#define CONNSAILLIB_HH

/// \file conn.hh
/// \author Egor Starobinskii
/// \date 12 Oct 2018
/// \brief Single-header C++ Library
/// \details This is a single-header C++ Library from Ailurus Studio that 
/// we are using to create Unmanned Surface Vehicles. Inspired by Chris Veness 
/// (https://github.com/chrisveness/)
/// \see https://starobinskii.github.io/ConnSailLib
/// \see https://github.com/starobinskii/ConnSailLib
/// \see https://ailurus.ru/

/// \brief If defined, funstions will be marked as inline. 
/// \details If defined, funstions will be marked as inline. Delete the line 
/// if you want to omit this behavior.
#define INLINE inline

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

/// \namespace conn
/// \brief Main namespace
/// \details Main namespace containing all the functions of ConnSailLib
/// \defgroup ConnNamespace ConnSailLib Namespace
/// \brief Main group
/// \details Main group containing all the functions of ConnSailLib
/// \{

namespace conn{

    /// \defgroup LibraryConstans Library Constants
    /// \brief Mathematical and physics constans
    /// \details Group of mathematical and physics constans that are used 
    /// during calculations
    /// \{

    /// \brief Number Pi
    /// \details The number Pi up to 25 decimal places
    const double pi = 3.1415926535798932384626433;

    /// \brief Radius of Earth
    /// \details Average radius of Earth
    const double earthRadius = 6371000.;

    /// \brief Semi-major Earth axis
    /// \details Semi-major Earth axis according to WGS-84 model
    const double semiMajorEarthAxis = 6378137.;

    /// \brief Semi-minor Earth axis
    /// \details Semi-minor Earth axis according to WGS-84 model
    const double semiMinorEarthAxis = 6356752.314245;

    /// \} End of LibraryConstans Group

    /// \defgroup LibraryInfo Library Info
    /// \brief Functions providing info about the library
    /// \details Group of functions that provides information about this 
    /// library
    /// \{

    /// \fn std::string getVersion();
    /// \brief Gets version of the lib
    /// \details This function returns version of the ConnSailLib (we use 
    /// SemVer)
    /// \return Version as a string
    INLINE std::string getVersion(){
        return std::string("1.0.0");
    }

    /// \} End of LibraryInfo Group

    /// \defgroup TestFunctions Test Functions
    /// \brief Functions to test your income
    /// \details Group of functions that test incoming data and throw runtime
    /// error if data is inappropriate
    /// \{

    /// \fn void failIfNotAGPSCoordinate(const std::vector<double> coordinate);
    /// \brief Fails if the parameter is not an appropriate type
    /// \details This function checks if the parameter is an appropriate type 
    /// and throws an exception otherwise
    /// \param coordinate Coordinate to test
    /// \exception std::runtime_error If \p coordinate size is not 3
    INLINE void failIfNotAGPSCoordinate(
        const std::vector<double> coordinate
    ){
        if(3 != coordinate.size()){
            throw std::runtime_error("GPS coordinate should have 3 values.");
        }
    }

    /// \fn void failIfNotAGPSPoint(const std::vector< std::vector<double> > 
    /// point);
    /// \brief Fails if the parameter is not an appropriate type
    /// \details This function checks if the parameter is an appropriate type 
    /// and throws an exception otherwise
    /// \param point Point to test
    /// \exception std::runtime_error If \p coordinate size is not 3
    INLINE void failIfNotAGPSPoint(
        const std::vector< std::vector<double> > point
    ){
        if(2 != point.size()){
            throw std::runtime_error("GPS point should have 2 coordinates.");
        }

        conn::failIfNotAGPSCoordinate(point[0]);
        conn::failIfNotAGPSCoordinate(point[1]);
    }

    /// \} End of TestFunctions Group

    /// \defgroup ConvertFunctions Convert Functions
    /// \brief Functions providing info about the library
    /// \details Group of functions that provides information about this 
    /// library
    /// \{

    /// \fn double radiansFromDegrees(const double degrees);
    /// \brief Converts degrees to radians
    /// \details This function converts degrees to radians
    /// \param degrees Value to convert
    /// \return Converted radians
    INLINE double radiansFromDegrees(const double degrees){
        return degrees * conn::pi / 180.;
    }

    /// \fn double degreesFromRadians(const double radians);
    /// \brief Converts radians to degrees
    /// \details This function converts radians to degrees
    /// \param radians Value to convert
    /// \return Converted degrees
    INLINE double degreesFromRadians(const double radians){
        return radians * 180. / conn::pi;
    }
    
    /// \fn double degreesFromGPSCoordinate(const std::vector<double> 
    /// coordinate);
    /// \brief Converts GPS coordinate to degrees (one-value)
    /// \details This function converts GPS coordinate to degrees
    /// \param coordinate Value to convert
    /// \exception std::runtime_error If \p coordinate is not an appropriate 
    /// type
    /// \return Converted degrees
    INLINE double degreesFromGPSCoordinate(
        const std::vector<double> coordinate
    ){
        conn::failIfNotAGPSCoordinate(coordinate);

        return coordinate[0] + coordinate[1] / 60. 
            + coordinate[2] / (60. * 60.);
    }
    
    /// \fn double radiansFromGPSCoordinate(const std::vector<double> 
    /// coordinate);
    /// \brief Converts GPS coordinate to radians (one-value)
    /// \details This function converts GPS coordinate to radians
    /// \param coordinate Value to convert
    /// \exception std::runtime_error If \p coordinate is not an appropriate 
    /// type
    /// \return Converted radians
    INLINE double radiansFromGPSCoordinate(
        const std::vector<double> coordinate
    ){
        return conn::radiansFromDegrees(
            conn::degreesFromGPSCoordinate(coordinate)
        );
    }

    /// \fn std::vector<double> degreesFromGPSPoint(const 
    /// std::vector< std::vector<double> > point);
    /// \brief Converts GPS point to degrees (one-value)
    /// \details This function converts GPS point to degrees
    /// \param point Value to convert
    /// \return Converted degress for latitude and longitude
    /// \exception std::runtime_error If \p point is not an appropriate 
    /// type
    INLINE std::vector<double> degreesFromGPSPoint(
        const std::vector< std::vector<double> > point
    ){
        conn::failIfNotAGPSPoint(point);

        return std::vector<double>{
            conn::degreesFromGPSCoordinate(point[0]),
            conn::degreesFromGPSCoordinate(point[1])
        };
    }

    /// \fn std::vector<double> radiansFromGPSPoint(const 
    /// std::vector< std::vector<double> > point);
    /// \brief Converts GPS point to radians (one-value)
    /// \details This function converts GPS point to radians
    /// \param point Value to convert
    /// \return Converted radians for latitude and longitude
    /// \exception std::runtime_error If \p point is not an appropriate 
    /// type
    INLINE std::vector<double> radiansFromGPSPoint(
        const std::vector< std::vector<double> > point
    ){
        conn::failIfNotAGPSPoint(point);

        return std::vector<double>{
            conn::radiansFromDegrees(conn::degreesFromGPSCoordinate(point[0])),
            conn::radiansFromDegrees(conn::degreesFromGPSCoordinate(point[1]))
        };
    }

    /// \fn std::vector<double> gpsCoordinateFromDegrees(const 
    /// double income);
    /// \brief Converts degrees to a GPS coordinate
    /// \details This function converts degrees to a GPS coordinate
    /// \param income Value to convert
    /// \return Converted GPS coordinate
    INLINE std::vector<double> gpsCoordinateFromDegrees(
        const double income
    ){
        const double degrees = floor(income);
        const double minutes = floor((income - degrees) * 60.);
        const double seconds = floor(
            (income - degrees - minutes / 60.) * 3600.
        );

        return std::vector<double>{degrees, minutes, seconds};
    }

    /// \fn std::vector<double> gpsCoordinateFromRadians(const 
    /// double income);
    /// \brief Converts radians to a GPS coordinate
    /// \details This function converts radians to a GPS coordinate
    /// \param income Value to convert
    /// \return Converted GPS coordinate
    INLINE std::vector<double> gpsCoordinateFromRadians(
        const double income
    ){
        return conn::gpsCoordinateFromDegrees(
            conn::degreesFromRadians(income)
        );
    }

    /// \fn std::vector< std::vector<double> > gpsPointFromDegrees( 
    /// const double latitude, const double longitude);
    /// \brief Converts degrees to a GPS point
    /// \details This function converts degrees to a GPS point
    /// \param latitude Value to convert
    /// \param longitude Value to convert
    /// \return Converted GPS point
    INLINE std::vector< std::vector<double> > gpsPointFromDegrees(
        const double latitude,
        const double longitude
    ){
        std::vector< std::vector<double> > point(2);

        point[0] = conn::gpsCoordinateFromDegrees(latitude);
        point[1] = conn::gpsCoordinateFromDegrees(longitude);

        return point;
    }

    /// \fn std::vector< std::vector<double> > gpsPointFromRadians( 
    /// const double latitude, const double longitude);
    /// \brief Converts radians to a GPS point
    /// \details This function converts radians to a GPS point
    /// \param latitude Value to convert
    /// \param longitude Value to convert
    /// \return Converted GPS point
    INLINE std::vector< std::vector<double> > gpsPointFromRadians(
        const double latitude,
        const double longitude
    ){
        std::vector< std::vector<double> > point(2);

        point[0] = conn::gpsCoordinateFromDegrees(latitude);
        point[1] = conn::gpsCoordinateFromDegrees(longitude);

        return point;
    }

    /// \fn std::string stringFromGPSCoordinate(const std::vector<double> 
    /// coordinate);
    /// \brief Converts GPS coordinate to a string
    /// \details This function converts GPS coordinate to a string
    /// \param coordinate Value to convert
    /// \return String representation of a GPS coordinate
    /// \exception std::runtime_error If \p coordinate is not an appropriate 
    /// type
    INLINE std::string stringFromGPSCoordinate(
        const std::vector<double> coordinate
    ){
        conn::failIfNotAGPSCoordinate(coordinate);

        return std::to_string((int) coordinate[0]) + std::string("º ")
            + std::to_string((int) coordinate[1]) + std::string("' ")
            + std::to_string((int) coordinate[2]) + std::string("\"");
    }

    /// \fn std::string stringFromGPSCoordinate(const std::vector<double> 
    /// coordinate, const bool itIsLatitude);
    /// \brief Converts GPS coordinate to a string
    /// \details This function converts GPS coordinate to a string
    /// \param coordinate Value to convert
    /// \param itIsLatitude Shows if coordinate is a latitude or a longitude
    /// \return String representation of a GPS coordinate
    /// \exception std::runtime_error If \p coordinate is not an appropriate 
    /// type
    INLINE std::string stringFromGPSCoordinate(
        const std::vector<double> coordinate,
        const bool itIsLatitude
    ){
        std::string text = conn::stringFromGPSCoordinate(coordinate);

        if(itIsLatitude){
            if(coordinate[0] > 0){
                text += std::string(" N");
            }else{
                text += std::string(" S");
            }
        }else{
            if(coordinate[0] > 0){
                text += std::string(" E");
            }else{
                text += std::string(" W");
            }
        }

        return text;
    }

    /// \fn std::string stringFromGPSPoint(const 
    /// std::vector< std::vector<double> > point);
    /// \brief Converts GPS point to a string
    /// \details This function converts GPS point to a string
    /// \param point Value to convert
    /// \return String representation of a GPS point
    /// \exception std::runtime_error If \p point is not an appropriate 
    /// type
    INLINE std::string stringFromGPSPoint(
        const std::vector< std::vector<double> > point
    ){
        conn::failIfNotAGPSPoint(point);

        return conn::stringFromGPSCoordinate(point[0], true)
            + std::string(" ") 
            + conn::stringFromGPSCoordinate(point[1], false);
    }

    /// \} End of ConvertFunctions Group

    /// \defgroup InterfaceFunctions Interface Functions
    /// \brief Functions printing and styling incoming data 
    /// \details Group of functions that allow to print data and style it
    /// \{

    /// \fn void printGPSCoordinate(const std::vector<double> coordinate);
    /// \brief Prints GPS coordinate to stdout
    /// \details This function prints GPS coordinate to stdout
    /// \param coordinate Value to print
    INLINE void printGPSCoordinate(
        const std::vector<double> coordinate
    ){
        std::cout << conn::stringFromGPSCoordinate(coordinate) << std::endl;
    }

    /// \fn void printGPSCoordinate(const std::vector<double> coordinate, 
    /// const bool itIsLatitude);
    /// \brief Prints GPS coordinate to stdout
    /// \details This function prints GPS coordinate to stdout
    /// \param coordinate Value to print
    /// \param itIsLatitude Shows if coordinate is a latitude or a longitude
    INLINE void printGPSCoordinate(
        const std::vector<double> coordinate,
        const bool itIsLatitude
    ){
        std::cout << conn::stringFromGPSCoordinate(coordinate, itIsLatitude)
            << std::endl;
    }

    /// \fn void printGPSPoint(const std::vector< std::vector<double> > point);
    /// \brief Prints GPS point to stdout
    /// \details This function prints GPS point to stdout
    /// \param point Value to print
    INLINE void printGPSPoint(
        const std::vector< std::vector<double> > point
    ){
        std::cout << conn::stringFromGPSPoint(point) << std::endl;
    }

    /// \} End of InterfaceFunctions Group

    /// \defgroup CalculationFunctions Calculation Functions
    /// \brief Functions providing different math methods and checks
    /// \details Group of functions that are usable to work with GPS and 
    /// calculate tracks
    /// \{

    /// \fn double calculateEarthRadius(const double latitude);
    /// \brief Calculate Earth radius by latitude
    /// \details This function calculates Earth radius by given latitude
    /// \param latitude Latitude for which the radius of Earth is calculated
    /// \return Earth radius
    INLINE double calculateEarthRadius(const double latitude){
        double radius = 0.;

        const double beta = conn::radiansFromDegrees(latitude);
        const double a = conn::semiMajorEarthAxis;
        const double b = conn::semiMinorEarthAxis;
        const double A = std::pow(a * cos(beta), 2);
        const double B = std::pow(b * sin(beta), 2);

        radius = (std::pow(a, 2) * A + std::pow(b, 2) * B) / (A + B);

        return sqrt(radius);
    };

    /// \fn double calculateEarthRadius(const std::vector<double> latitude);
    /// \brief Calculate Earth radius by latitude
    /// \details This function calculates Earth radius by given latitude (as a 
    /// GPS coordinate)
    /// \param latitude Latitude (as a GPS coordinate) for which the radius of 
    /// Earth is calculated
    /// \return Earth radius
    /// \exception std::runtime_error If \p latitude is not an appropriate 
    /// type
    INLINE double calculateEarthRadius(const std::vector<double> latitude){
        conn::failIfNotAGPSCoordinate(latitude);

        return conn::calculateEarthRadius(
            conn::degreesFromGPSCoordinate(latitude)
        );
    };
    
    /// \fn double calculateEarthRadius(const 
    /// std::vector< std::vector<double> > point);
    /// \brief Calculate Earth radius by GPS point
    /// \details This function calculates Earth radius by given GPS point
    /// \param point GPS point for which the radius of Earth is calculated
    /// \return Earth radius
    /// \exception std::runtime_error If \p point is not an appropriate 
    /// type
    INLINE double calculateEarthRadius(
        const std::vector< std::vector<double> > point
    ){
        conn::failIfNotAGPSPoint(point);

        return conn::calculateEarthRadius(
            conn::degreesFromGPSCoordinate(point[0])
        );
    };
    
    
    /// \fn double distance(double latitude1, double longitude1, double 
    /// latitude2, double longitude2, const bool shouldCalculateEarthRadius = 
    /// false);
    /// \brief Calculates distance between two points
    /// \details This function calculates distance in meters between two points
    /// using Haversine formula. This method runs well for a short range. If 
    /// this is not your case, see Vincenty's algorithm.
    /// \param latitude1 Latitude of the first point
    /// \param longitude1 Longitude of the first point
    /// \param latitude2 Latitude of the second point
    /// \param longitude2 Longitude of the second point
    /// \param shouldCalculateEarthRadius Optional. True if Earth radius 
    /// should be calculated for a mid-point using WSG-84 model, average 
    /// radius is used otherwise. False by default
    /// \return Distance in meters
    INLINE double distance(
        double latitude1,
        double longitude1,
        double latitude2,
        double longitude2,
        const bool shouldCalculateEarthRadius = false
    ){
        double radius = conn::earthRadius;

        if(shouldCalculateEarthRadius){
            radius = conn::calculateEarthRadius(0.5 * (latitude1 + latitude2));
        }

        latitude1 = conn::radiansFromDegrees(latitude1);
        longitude1 = conn::radiansFromDegrees(longitude1);
        latitude2 = conn::radiansFromDegrees(latitude2);
        longitude2 = conn::radiansFromDegrees(longitude2);

        const double deltaLatitude = latitude2 - latitude1;
        const double deltaLongitude = longitude2 - longitude1;

        const double a = std::pow(sin(0.5 * deltaLatitude), 2)
            + cos(latitude1) * cos(latitude2)
            * std::pow(sin(0.5 * deltaLongitude), 2);
        const double b = 2. * atan2(sqrt(a), sqrt(1. - a));

        return radius * b;
    };

    /// \fn double distance(const std::vector< std::vector<double> > point1, 
    /// const std::vector< std::vector<double> > point2, const bool 
    /// shouldCalculateEarthRadius = false);
    /// \brief Calculates distance between two points
    /// \details This function calculates distance in meters between two GPS
    /// points using Haversine formula. This method runs well for a short 
    /// range. If this is not your case, see Vincenty's algorithm.
    /// \param point1 First GPS point
    /// \param point2 Second GPS point
    /// \param shouldCalculateEarthRadius Optional. True if Earth radius 
    /// should be calculated for a mid-point using WSG-84 model, average 
    /// radius is used otherwise. False by default
    /// \return Distance in meters
    /// \exception std::runtime_error If \p point1 or \p point2 are not an 
    /// appropriate type
    INLINE double distance(
        const std::vector< std::vector<double> > point1,
        const std::vector< std::vector<double> > point2,
        const bool shouldCalculateEarthRadius = false
    ){
        conn::failIfNotAGPSPoint(point1);
        conn::failIfNotAGPSPoint(point2);

        return conn::distance(
            conn::degreesFromGPSCoordinate(point1[0]),
            conn::degreesFromGPSCoordinate(point1[1]),
            conn::degreesFromGPSCoordinate(point2[0]),
            conn::degreesFromGPSCoordinate(point2[1])
        );
    };

    /// \fn std::vector<double> destination(double latitude, double longitude,
    /// const double distance, double bearing, const bool 
    /// shouldCalculateEarthRadius = false);
    /// \brief Calculates destination point by a given distance and bearing. 
    /// \details This function calculates destination point by a given 
    /// distance and bearing. Borrowed this method from a cool guy Chris 
    /// Veness (https://github.com/chrisveness)
    /// \param latitude Latitude of the start point
    /// \param longitude Longitude of the start point
    /// \param distance Distance to go
    /// \param bearing Bearing to go
    /// \param shouldCalculateEarthRadius True if Earth radius should be 
    /// calculated for a mid-point using WSG-84 model, average radius is used 
    /// otherwise.
    /// \return Latitude and longitude of the destination point
    INLINE std::vector<double> destination(
        double latitude,
        double longitude,
        const double distance,
        double bearing,
        const bool shouldCalculateEarthRadius = false
    ){
        double radius = conn::earthRadius;

        if(shouldCalculateEarthRadius){
            radius = conn::calculateEarthRadius(latitude);
        }

        double angularDistance = distance / radius;

        bearing = conn::radiansFromDegrees(bearing);
        latitude = conn::radiansFromDegrees(latitude);
        longitude = conn::radiansFromDegrees(longitude);

        const double sin1 = sin(latitude);
        const double cos1 = cos(latitude);
        const double sin2 = sin(angularDistance);
        const double cos2 = cos(angularDistance);
        const double sin3 = sin(bearing);
        const double cos3 = cos(bearing);

        const double sin4 = sin1 * cos2 + cos1 * sin2 * cos3;
        const double nextLatitude = asin(sin4);

        const double y = sin3 * sin2 * cos1;
        const double x = cos2 - sin1 * sin4;
        const double nextLongitude = longitude + atan2(y, x);

        return std::vector<double>{
            conn::degreesFromRadians(nextLatitude),
            fmod(conn::degreesFromRadians(nextLongitude) + 540., 360.) - 180.
        };
    }

    /// \fn std::vector< std::vector<double> > destinationGPSPoint(double 
    /// latitude, double longitude, const double distance, double bearing, 
    /// const bool shouldCalculateEarthRadius = false);
    /// \brief Calculates destination point by a given distance and bearing. 
    /// \details This function calculates destination point by a given 
    /// distance and bearing. Borrowed this method from a cool guy Chris 
    /// Veness (https://github.com/chrisveness)
    /// \param latitude Latitude of the start point
    /// \param longitude Longitude of the start point
    /// \param distance Distance to go
    /// \param bearing Bearing to go
    /// \param shouldCalculateEarthRadius True if Earth radius should be 
    /// calculated for a mid-point using WSG-84 model, average radius is used 
    /// otherwise.
    /// \return GPS point
    INLINE std::vector< std::vector<double> > destinationGPSPoint(
        double latitude,
        double longitude,
        const double distance,
        double bearing,
        const bool shouldCalculateEarthRadius = false
    ){
        std::vector<double> destination = conn::destination(
            latitude,
            longitude,
            distance,
            bearing,
            shouldCalculateEarthRadius
        );

        return conn::gpsPointFromDegrees(destination[0], destination[1]);
    }

    /// \} End of CalculationFunctions Group

    /// \defgroup TrackFunctions Track Functions
    /// \brief Functions creating different tracks to test your vehicle
    /// \details Group of functions that creates different track to test your
    /// vehicle. The angle is calculated from the vertical axis clockwise in
    /// radians.
    /// \{

    /// \fn void line(std::vector< std::vector<double> > &points, const double 
    /// length, const double angle, const std::size_t numberOfPoints);
    /// \brief Calculates points that form a line
    /// \details This function calculates points that form a line
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param length Length of the line in meters
    /// \param angle Tilt angle of the line in radians
    /// \param numberOfPoints Number of points per elementary figure
    void line(
        std::vector< std::vector<double> > &points,
        const double length,
        const double angle,
        const std::size_t numberOfPoints
    ){
        const double xOffset = points[points.size() - 1][0];
        const double yOffset = points[points.size() - 1][1];
        const double xLength = length * sin(angle);
        const double yLength = length * cos(angle);

        double cut = 0.;

        for(std::size_t i = 1; i <= numberOfPoints; ++i){
            cut = (double) i / numberOfPoints;
 
            points.push_back(
                std::vector<double>{
                    xOffset + cut * xLength,
                    yOffset + cut * yLength
                }
            );
        }
    }

    /// \fn void rectangle(std::vector< std::vector<double> > &points, const 
    /// double width, const double height, double angle, const std::size_t 
    /// numberOfPoints);
    /// \brief Calculates points that form a rectangle
    /// \details This function calculates points that form a rectangle
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param width Width of the line in meters
    /// \param height Height of the line in meters
    /// \param angle Tilt angle of the rectangle in radians
    /// \param numberOfPoints Number of points per elementary figure
    void rectangle(
        std::vector< std::vector<double> > &points,
        const double width,
        const double height,
        double angle,
        const std::size_t numberOfPoints
    ){
        double length = width;

        for(size_t i = 0; i < 4; ++i){
            conn::line(points, length, angle, numberOfPoints);
            angle += 0.5 * conn::pi;
            
            if(0 == i % 2){
                length = height;
            }else{
                length = width;
            }
        }
    }

    /// \fn void square(std::vector< std::vector<double> > &points, const 
    /// double square, double angle, const std::size_t numberOfPoints);
    /// \brief Calculates points that form a square
    /// \details This function calculates points that form a square
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param length Side length of the square in meters
    /// \param angle Tilt angle of the square in radians
    /// \param numberOfPoints Number of points per elementary figure
    void square(
        std::vector< std::vector<double> > &points,
        const double length,
        const double angle,
        const std::size_t numberOfPoints
    ){
        conn::rectangle(points, length, length, angle, numberOfPoints);
    }

    /// \fn void spiral(std::vector< std::vector<double> > &points, const 
    /// double initialRadius, const double initialAngle, const double 
    /// finishRadius, const double finishAngle, const std::size_t 
    /// numberOfPoints);
    /// \brief Calculates points that form a spiral
    /// \details This function calculates points that form a spiral
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param initialRadius Initial radius of the spiral in meters
    /// \param initialAngle Initial angle of the spiral in radians
    /// \param finishRadius Finish radius of the spiral in meters
    /// \param finishAngle Finish angle of the spiral in radians
    /// \param numberOfPoints Number of points per elementary figure
    void spiral(
        std::vector< std::vector<double> > &points,
        const double initialRadius,
        const double initialAngle,
        const double finishRadius,
        const double finishAngle,
        const std::size_t numberOfPoints
    ){
        const double xOffset = points[points.size() - 1][0] 
            - initialRadius * sin(initialAngle);
        const double yOffset = points[points.size() - 1][1]
            - initialRadius * cos(initialAngle);

        double radius = 0.;
        double angle = 0.;
        double cut = 0.;

        for(std::size_t i = 1; i <= numberOfPoints; ++i){
            cut = (double) i / numberOfPoints;
            radius = initialRadius + cut * (finishRadius - initialRadius);
            angle = initialAngle + cut * (finishAngle - initialAngle);
 
            points.push_back(
                std::vector<double>{
                    xOffset + radius * sin(angle),
                    yOffset + radius * cos(angle)
                }
            );
        }
    }

    /// \fn void sector(std::vector< std::vector<double> > &points, const 
    /// double radius, const double initialAngle, const double finishAngle,
    /// const std::size_t numberOfPoints);
    /// \brief Calculates points that form a sector
    /// \details This function calculates points that form a sector
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param radius Radius of the sector in meters
    /// \param initialAngle Initial angle of the sector in radians
    /// \param finishAngle Finish angle of the sector in radians
    /// \param numberOfPoints Number of points per elementary figure
    void sector(
        std::vector< std::vector<double> > &points,
        const double radius,
        const double initialAngle,
        const double finishAngle,
        const std::size_t numberOfPoints
    ){
        conn::spiral(
            points, radius, initialAngle, radius, finishAngle, numberOfPoints
        );
    }

    /// \fn void circle(std::vector< std::vector<double> > &points, const 
    /// double radius, const double angle, const std::size_t numberOfPoints);
    /// \brief Calculates points that form a circle
    /// \details This function calculates points that form a circle
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param radius Radius of the circle in meters
    /// \param angle Initial angle of the circle in radians
    /// \param numberOfPoints Number of points per elementary figure
    void circle(
        std::vector< std::vector<double> > &points,
        const double radius,
        const double angle,
        const std::size_t numberOfPoints
    ){
        conn::spiral(
            points, radius, angle, radius, angle + 2 * conn::pi, numberOfPoints
        );
    }

    /// \fn void squiggle(std::vector< std::vector<double> > &points, const 
    /// double length, const double radius, double angle, double 
    /// rotationAngle, const std::size_t numberOfLines, const std::size_t 
    /// numberOfPoints);
    /// \brief Calculates points that form a squiggle
    /// \details This function calculates points that form a squiggle
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param length Length of the straight lines between turns in meters
    /// \param radius Radius of the turn in meters
    /// \param angle Initial angle of the squiggle in radians
    /// \param rotationAngle Angle of rotation. Assumed it is pi / 2, not cool 
    /// otherwise.
    /// \param numberOfLines Number of straight lines between turns
    /// \param numberOfPoints Number of points per elementary figure
    void squiggle(
        std::vector< std::vector<double> > &points,
        const double length,
        const double radius,
        double angle,
        double rotationAngle,
        const std::size_t numberOfLines,
        const std::size_t numberOfPoints
    ){
        conn::line(points, length, angle, numberOfPoints);

        double nextAngle = angle + rotationAngle;
        double initialRotationAngle = -0.5 * conn::pi;

        for(std::size_t i = 1; i < numberOfLines; ++i){
            conn::sector(
                points,
                radius,
                angle + initialRotationAngle,
                nextAngle + initialRotationAngle,
                numberOfPoints
            );

            angle = nextAngle;
            initialRotationAngle *= -1;

            conn::line(points, length, angle, numberOfPoints);

            if(0 == i % 2){
                nextAngle += rotationAngle;
            }else{
                nextAngle -= rotationAngle;
            }
        }
    }

    /// \fn void letterPi( std::vector< std::vector<double> > &points, const 
    /// double verticalLength, const double horizontalLength, const double 
    /// radius, double angle, const std::size_t numberOfPoints);
    /// \brief Calculates points that form a letter pi
    /// \details This function calculates points that form something that looks 
    /// close to a pi letter
    /// \param points List to add points (should already has an initial 
    /// point - a pole)
    /// \param verticalLength Length of the vertical line segment in meters
    /// \param horizontalLength Length of the horizontal line segment in meters
    /// \param radius Radius of the round segment in meters
    /// \param angle Initial angle of the letter in radians
    /// \param numberOfPoints Number of points per elementary figure
    void letterPi(
        std::vector< std::vector<double> > &points,
        const double verticalLength,
        const double horizontalLength,
        const double radius,
        double angle,
        const std::size_t numberOfPoints
    ){
        angle += conn::pi;

        double rotationAngle = -0.5 * conn::pi;

        conn::sector(
            points, radius, angle, angle + rotationAngle, numberOfPoints
        );
        
        angle += 2. * rotationAngle;

        conn::line(points, verticalLength, angle, numberOfPoints);

        angle -= rotationAngle;
        rotationAngle *= 3.;

        conn::sector(
            points, radius, angle, angle + rotationAngle, numberOfPoints
        );

        conn::line(points, horizontalLength, angle, numberOfPoints);
        
        angle += -rotationAngle / 3.;

        conn::sector(
            points, radius, angle, angle + rotationAngle, numberOfPoints
        );

        conn::line(points, verticalLength, angle, numberOfPoints);

        rotationAngle /= 3.;
        angle -= rotationAngle;

        conn::sector(
            points, radius, angle, angle + rotationAngle, numberOfPoints
        );
    }

    /// \} End of TrackFunctions Group

}

/// \} End of Main Group

#endif