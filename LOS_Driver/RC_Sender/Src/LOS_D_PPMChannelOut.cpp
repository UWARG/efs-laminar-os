#include "LOS_D_PPMChannelOut.hpp"

PPMChannelOut::PPMChannelOut(TIM_HandleTypeDef* timer, uint16_t timer_channel, uint8_t num_channels) :
    timer_(timer),
    timer_channel_(timer_channel),
    num_channels_(num_channels)
{
    for (uint8_t i = 0; i < MAX_PPM_CHANNELS; ++i) {
        ppm_output_[i] = 0;
        channel_vals_[i] = 0;
    }
}

uint8_t PPMChannelOut::setChannelValue(uint8_t channel, float value)
{
    if (channel > num_channels_) {
        return 0;
    }
    channel_vals_[channel - 1] = value;
    return 1;
}

void PPMChannelOut::init()
{
    // Get the base frequency and prescaler our timer is running at
    float base_frequency_ = HAL_RCC_GetPCLK1Freq();
    float prescaler = timer_->Init.Prescaler;

    counts_per_microsecond_ = base_frequency_ / (prescaler + 1.0f) / SEC_TO_MICROSEC;
    ccr_ = PULSE_WIDTH * counts_per_microsecond_;
    output_index_ = 0;

    __HAL_TIM_SET_COMPARE(timer_, timer_channel_, ccr_);
    __HAL_TIM_SET_AUTORELOAD(timer_, getNextPPM());

    // Start PWM output in interrupt mode
    HAL_TIM_PWM_Start_IT(timer_, timer_channel_);
}

void PPMChannelOut::interrupt_callback(TIM_HandleTypeDef* timer)
{
    if (timer->Instance == timer_->Instance) {
        // Constantly update and send PPM signal
        __HAL_TIM_SET_AUTORELOAD(timer_, getNextPPM());
    }
}

uint8_t PPMChannelOut::setNumChannels(uint8_t num)
{
    if (num <= 0 || num > MAX_PPM_CHANNELS) {
        return 0;
    }
    num_channels_ = num;
    return 1;
}

uint32_t PPMChannelOut::getNextPPM() 
{
    if (ppm_output_[0] == 0 || output_index_ == num_channels_ + 1) {
        // Re-calculate the array of output PPM values
        for (uint8_t i = 0; i < num_channels_; ++i) {
            ppm_output_[i] = percentageToCount(channel_vals_[i]);
        }
        ppm_output_[num_channels_] = calculatePulseReset();
        output_index_ = 0;
    }

    return ppm_output_[output_index_++];
}

uint32_t PPMChannelOut::percentageToCount(float percentage)
{
    float pulse = MIN_PULSE_WIDTH + percentage * DOWN_INTERVAL;
    return static_cast<uint32_t>(pulse * counts_per_microsecond_);
}

uint32_t PPMChannelOut::calculatePulseReset()
{
    float remaining_out = (float)num_channels_;
	float summation = 0;

	for(uint8_t i = 0; i < num_channels_; i++) {
		summation += channel_vals_[i];
	}

	remaining_out -= summation;

    float pulse = PULSE_WIDTH + remaining_out * DOWN_INTERVAL;
    return static_cast<uint32_t>(pulse * counts_per_microsecond_);
}