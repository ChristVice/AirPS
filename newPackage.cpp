#include <iostream>

class Courier{
 // place holder
};

class NewPackage : public Courier{
    public:
        double pkgWeight;
        double pkgWidth;
        double pkgLength;
        double pkgHeight;
        char* startAddress;
        char* destinationAddress;
        char* shippingSpeed;
        char* shippingSpeedTypes[3] = {"Express", "Priority Mail", "First Class"};
        char* courier;

        void setPackageWeight(double a){
            pkgWeight = a;
        }
        void setPackageWidth(double a){
            pkgWidth = a;
        }
        void setPackageLength(double a){
            pkgLength = a;
        }
        void setPackageHeight(double a){
            pkgHeight = a;
        }
        void setStartAddress(char* a){
            startAddress = a;
        }
        void setDestinationAddress(char* a){
            destinationAddress = a;
        }
        
        /*
        input: number between 0 and 2, one for each shippingSpeed type 0: Express (fastest), 1: Priority Mail, 2: First Class
        */
        void setShippingSpeed(int a){
            shippingSpeed = shippingSpeedTypes[a];
        }
        void estimatedTimeArrival(){
            
        }
        void courier(){
            printf("{Courier.getName}, {Courier.getPhoneNumber}, {Courier.getAddress}, {Courier.getEmail}");
        }

        double getPackageWeight(){
            return pkgWeight;
        }
        double getPackageWidth(){
            return pkgWidth;
        }
        double getPackageLength(){
            return pkgLength;
        }
        double getpackageHeight(){
            return pkgHeight; 
        }
        char* getStartAddress(){
            return startAddress;
        }
        char* getDestinationAddress(){
            return destinationAddress;
        }


};