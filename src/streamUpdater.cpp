#include "streamUpdater.h"


size_t StreamUpdater::write(uint8_t data){
    return UpdateClass::write(&data, 1);
}
size_t StreamUpdater::write(const uint8_t *buffer, size_t size){
    return UpdateClass::write(const_cast<uint8_t*>(buffer), size);
}

int StreamUpdater::read(){
    return 0;
}
int StreamUpdater::peek(){
    return 0;
}

void StreamUpdater::flush(){
    UpdateClass::clearError();
}

int StreamUpdater::available(){
    return UpdateClass::remaining();
}