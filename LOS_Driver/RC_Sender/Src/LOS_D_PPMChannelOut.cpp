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

uint8_t PPMChannelOut::setChannelValue(uint8_t channel, uint8_t value)
{
    if (channel > num_channels_) {
        return 0;
    }
    channel_vals_[channel - 1] = static_cast<float>(value) / 100.0f;
    return 1;
}

void PPMChannelOut::init()
{
    // Get the base frequency and prescaler our timer is running at
    float base_frequency_ = HAL_RCC_GetPCLK1Freq();
    float prescaler = timer_->Init.Prescaler;

    counts_per_microsecond_ = base_frequency_ / (prescaler + 1.0f) / SEC_TO_MICROSEC;
    output_index_ = 0;

    setNextPPM();

    // Start PWM output
    HAL_TIM_PWM_Start(timer_, timer_channel_);
    // Start interrupt
    __HAL_TIM_ENABLE_IT(timer_, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(timer_);
}

void PPMChannelOut::interrupt_callback(TIM_HandleTypeDef* timer)
{
    if (timer->Instance == timer_->Instance) {
        // Constantly update and send PPM signal
        setNextPPM();
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

void PPMChannelOut::setNextPPM()
{
    if (ppm_output_[0] == 0 || output_index_ == num_channels_ + 1) {
        // Re-calculate the array of output PPM values
        for (uint8_t i = 1; i <= num_channels_; ++i) {
            ppm_output_[i] = percentageToCount(channel_vals_[i - 1]);
        }
        ppm_output_[0] = calculatePulseReset(); // Start pulse at the beginning
        output_index_ = 0;
    }

    uint32_t output = ppm_output_[output_index_];
    __HAL_TIM_SET_COMPARE(timer_, timer_channel_, output);
    __HAL_TIM_SET_AUTORELOAD(timer_, output + getCCR());

    output_index_++;
}

uint32_t PPMChannelOut::calculatePulseReset()
{
    float remaining_out = (float)num_channels_;
	float summation = 0;

	for(uint8_t i = 1; i <= num_channels_; i++) {
		summation += channel_vals_[i];
	}

	remaining_out -= summation;

    float pulse = MIN_RESET_PULSE + remaining_out * UP_INTERVAL;
    return static_cast<uint32_t>(pulse * counts_per_microsecond_);
}