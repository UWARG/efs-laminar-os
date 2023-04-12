#ifndef LOS_D_PPM_CHANNEL_OUT_HPP_
#define LOS_D_PPM_CHANNEL_OUT_HPP_

#include <cstdint>
#include "LOS_D_RcSender.hpp"

class PPMChannelOut : public RcSender {

public:
    /* Constructor */
    PPMChannelOut(TIM_HandleTypeDef* timer, uint16_t timer_channel, uint8_t num_channels);

    /* Implementation of the RcSender Interface. See LOS_D_RcSender.hpp */
    uint8_t setChannelValue(uint8_t channel, uint8_t value);

    /* Implementation of the RcSender Interface. See LOS_D_RcSender.hpp
     * After initialization, we will be constantly sending PPM signals.
     */
    void init();

    /* Implementation of the RcSender Interface. See LOS_D_RcSender.hpp */
    void interrupt_callback(TIM_HandleTypeDef* timer);

    /* Set the number of channels. Returns 1 if success, 0 if failed. */
    uint8_t setNumChannels(uint8_t num_channels);


private:
    /* Constants */
    static constexpr float SEC_TO_MICROSEC             = 1000000.0f;
    static constexpr float PULSE_WIDTH_START	       = 800.0f; // in us
    static constexpr float PULSE_WIDTH_N	       = 400.0f; // in us

    // not really a pulse, this is slightly smaller than the difference in time between sequential
    // PPM packets
    static constexpr float MIN_RESET_PULSE             = 3200.0f;
    static constexpr float MIN_PULSE_WIDTH             = 600.0f;
    static constexpr float MAX_PULSE_WIDTH             = 1600.0f;
    static constexpr float UP_INTERVAL                 = MAX_PULSE_WIDTH - MIN_PULSE_WIDTH;
    static constexpr uint8_t MAX_PPM_CHANNELS          = 12;

    /* Member Variables */
    TIM_HandleTypeDef* timer_;
    uint16_t timer_channel_;

    uint8_t num_channels_;
    /* Channel values in percentages (0.0f-1.0f)*/
    float channel_vals_[MAX_PPM_CHANNELS];
    /* PPM output in coutner ticks. +1 element for storing the reset pulse. */
    uint32_t ppm_output_[MAX_PPM_CHANNELS+1];

    float counts_per_microsecond_;
    #define CCR_ 					(output_index_ != 0)? PULSE_WIDTH_N: PULSE_WIDTH_START
    uint8_t output_index_;

    /* Helper Functions */
    uint32_t getNextPPM();
    uint32_t percentageToCount(float percentage);
    uint32_t calculatePulseReset();

#endif
