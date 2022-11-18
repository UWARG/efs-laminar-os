#ifndef LOS_Telem_HPP_
#define LOS_Telem_HPP_

#include "interface_datatypes.hpp"

class LOS_Telem {
    public:
        static LOS_Telem& getInstance();

        void init(void);

        /**
         * @brief Retrieves latest data from ground, if any.
         *
         * @param dataFromGround Struct in which retrieved data is stored.
         *
         * @return true if data was retrieved, otherwise false.
         */
        bool get_from_ground(Data_From_Ground_t &dataFromGround);

        /**
         * @brief Sends data to ground.
         *
         * @param dataToGround Data to send.
         */
        void send_to_ground(Data_To_Ground_t &dataToGround);

    private:
        LOS_Telem();
};

#endif