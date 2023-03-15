#include "CircularBuffer.hpp"

uint8_t CircularBuffer::peek(uint8_t& res, int dist) {
    if(dist + readPtr >= writePtr) return 0;

    res = buf[(readPtr + dist) % size];  
    return 1;
}

uint8_t CircularBuffer::read(uint8_t* res, int dist) {
    if(dist + readPtr >= writePtr) return 0;

    if( (readPtr % size) + dist >= size ) {
        // two memcpys needed
        int dist_to_end = size - (readPtr % size);
        memcpy(&buf[readPtr % size],res, dist_to_end);
        readPtr += dist_to_end;
        dist -= dist_to_end;
        memcpy(&buf[readPtr % size], &res[dist_to_end], dist);
        readPtr += dist;
    } else {
        // one memcpy needed
        memcpy(&buf[readPtr % size],res, dist);
        readPtr += dist;
    }

    return 1;

}


CircularBuffer::CircularBuffer(uint8_t* buf, int size) {
    this->buf = buf;
    this->size = size;
}

bool CircularBuffer::hasSpace() {
    return !((writePtr % size == readPtr % size) && writePtr != readPtr);
}

uint8_t CircularBuffer::write(uint8_t data) {
    buf[writePtr % size] = data;
    writePtr++;
    return 1;
}