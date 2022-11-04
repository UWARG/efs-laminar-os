#ifndef INC_MPL3115A2_HPP_
#define INC_MPL3115A2_HPP_

#include "altimeter.hpp"

class MPL3115A2 : public Altimeter {
    public:
        /**
         * This module is built as a singleton. Thus to access an MPL3115A2 object, this function must be called.
         * Only a single MPL3115A2 object will ever be created and will be shared by all callers of this function.
         * @return      Altimeter        reference to the singleton object.
         * */
        static Altimeter& getInstance();

        /**
         * Deletes the constructor to disallow users to instantiate objects.
         * */
        MPL3115A2(const MPL3115A2*) = delete;

        void Begin_Measuring();
        void GetResult(AltimeterData_t& Data);
    private:
        
        MPL3115A2();

        void ConfigAltimeter(void);

        void Calibrate(void);

        union AltimeterAltitudeRepresentation rawAltimeter;
        float altimeterCalibrationFinal;
};

#endif /* INC_MPL3115A2_HPP_ */