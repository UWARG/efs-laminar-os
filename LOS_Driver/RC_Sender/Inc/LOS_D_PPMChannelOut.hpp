#ifndef LOS_D_PPM_CHANNEL_OUT_HPP_
#define LOS_D_PPM_CHANNEL_OUT_HPP_

#include <cstdint>
#include "LOS_D_RcSender.hpp"

class PPMChannelOut : public RcSender {

public:
    PPMChannelOut(TIM_HandleTypeDef* timer, uint16_t timer_channel, uint8_t num_channels);
    uint8_t setChannelValue(uint8_t channel, float value);
    void init();
    void interrupt_callback(TIM_HandleTypeDef* timer);
    uint8_t setNumChannels(uint8_t num_channels);

private:
    /* Constants */
    static constexpr float SEC_TO_MICROSEC             = 1000000.0f;
    static constexpr float PULSE_WIDTH                 = 310.0f; // in us

    // not really a pulse, this is slightly smaller than the difference in time between sequential
    // PPM packets
    static constexpr float MIN_RESET_PULSE             = 3000.0f; 
    static constexpr float MIN_PULSE_WIDTH             = 700.0f;
    static constexpr float MAX_PULSE_WIDTH             = 1670.0f;
    static constexpr float DOWN_INTERVAL               = MAX_PULSE_WIDTH - MIN_PULSE_WIDTH;
    static constexpr uint8_t MAX_PPM_CHANNELS          = 12;

    /* Member Variables */
    TIM_HandleTypeDef* timer_;
    uint16_t timer_channel_;

    uint8_t num_channels_;
    float channel_vals_[MAX_PPM_CHANNELS];
    uint32_t ppm_output_[MAX_PPM_CHANNELS+1]; // One more element for reset pulse

    float counts_per_microsecond_;
    uint32_t ccr_;
    uint8_t output_index_;

    /* Helper Functions */
    uint32_t getNextPPM();
    uint32_t percentageToCount(float percentage);
    uint32_t calculatePulseReset();
};

#endif