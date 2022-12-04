#include <iostream>
#include <newPackage.h>


class CreatePackage : public NewPackage{
    public:

        double dimensions[3];
        double weight;
        char* origin;
        char* destination;
        

        void getPackageWeight() {
            weight = NewPackage::getPackageWeight();
        }

        void getPackageDimensions() {
            dimensions[0] = NewPackage::getPackageWidth();
            dimensions[1] = NewPackage::getPackageLengtht(); 
            dimensions[2] = NewPackage::getPackageHeight();
        }

        void getOrigin() {
            origin = NewPackage::getStartAddress();
        }

        void getDestination() {
            destination = NewPackage::getDestinationAddress();
        }
};


/*
-Dimensions: double
-Weight: double
-Origin: string
-Destination: string
-----
+ getpackageWeight(): void
+ getpackageDimensions(): void
+ getOrigin(): void
+ getDestination(): void




void getpackageWeight() {
    Weight = NewPackageClass.GetpackageWeight();
}

void getpackageDimensions() {
    Dimensions[0] = NewPackageClass.GetpackageWidth();
Dimensions[1] = NewPackageClass.GetpackageLengtht();
Dimensions[2] = NewPackageClass.GetpackageHeight();
}

void getOrigin() {
    Origin = NewPackageClass.GetstartAddress();
}

void getDestination() {
    Destination = NewPackageClass.GetdestinationAddress();
}


*/