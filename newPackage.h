#include <Courier.h>

#ifndef newPackage
#define newPackage

class NewPackage : public Courier{
    public:
        double pkgWeight;
        double pkgWidth;
        double pkgLength;
        double pkgHeight;
        char* startAddress;
        char* destinationAddress;
        char* shippingSpeed;
        char* shippingSpeedTypes[3];
        char* courier;

        void setPackageWeight(double a);
        void setPackageWidth(double a);
        void setPackageLength(double a);
        void setPackageHeight(double a);
        void setStartAddress(char* a);
        void setDestinationAddress(char* a);
        
        /*
        input: number between 0 and 2, one for each shippingSpeed type 0: Express (fastest), 1: Priority Mail, 2: First Class
        */
        void setShippingSpeed(int a);
        void estimatedTimeArrival();
        void courier();
        double getPackageWeight();
        double geePackageWidth();
        double getPackageLength();
        double getpackageHeight();
        char* getStartAddress();
        char* getDestinationAddress();
};

#endif