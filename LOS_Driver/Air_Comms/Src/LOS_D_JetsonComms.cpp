#include "LOS_D_JetsonComms.hpp"

#define EMPTY_VAL -1

JetsonComms::JetsonComms(UART_HandleTypeDef* uart, uint16_t uart_dma_handle_index)
{
    head_ = EMPTY_VAL;
    tail_ = 0;
}

uint8_t JetsonComms::GetResult(uint8_t* buffer, uint16_t length)
{
    uint16_t bytes_transferred = 0;

    uint16_t occupied = getSize();
    
    if (length < occupied)
    {
        transferBytes(buffer, length);
        bytes_transferred = length;
    }
    else
    {
        transferBytes(buffer, occupied);
        bytes_transferred = occupied;
    }

    return bytes_transferred;
}

uint16_t JetsonComms::getSize()
{
    return (head_ < tail_) ? tail_ - head_ : tail_ + (RING_BUFFER_SIZE_ - head_);
}

void JetsonComms::transferBytes(uint8_t* buffer, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        buffer[i] = ring_buffer_[(head_ + i) % RING_BUFFER_SIZE_];
    }

    dequeueBytes(length);
}

bool JetsonComms::dequeueBytes(uint8_t num_bytes)
{
    if (num_bytes < getSize())
    {
        head_ = (head_ + num_bytes) % RING_BUFFER_SIZE_;
    }
    else
    {
        head_ = tail_;
    }
}

bool JetsonComms::queueByte(uint8_t data)
{
    bool ret_val = true;
    if (getSize() < RING_BUFFER_SIZE_)
    {
        ring_buffer_[tail_] = data;
        tail_ = (tail_ + 1) % RING_BUFFER_SIZE_;
    }
    else
    {
        ret_val = false;
    }

    return ret_val;
}

bool JetsonComms::isFull()
{
    return head_ == tail_;
}

bool JetsonComms::isEmpty()
{
    return head_ == EMPTY_VAL;
}

void JetsonComms::interrupt_callback()
{
    
    return;
}
