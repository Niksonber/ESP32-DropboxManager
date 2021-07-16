#pragma once
#include <Update.h>

/// Interface class between UpdaterClass and Stream, this allows usse updater as stream
class StreamUpdater: public Stream, public UpdateClass{
public:
    /// Write a byte in flash @param data byte to be stored @return writed size
    size_t write(uint8_t data);

    /// Write buffer in flash
    /// @param buffer @param size buffer size @return writed size
    size_t write(const uint8_t *buffer, size_t size);
    
    /// Update type (program or SPIFFS)
    enum type : uint8_t;
protected:
    /// not used only for overload virtual method (protected)
    /// @return 0
    int read();

    /// not used only for overload virtual method (protected)
    /// @return 0
    int peek();

    /// not used only for overload virtual method (protected)
    /// clear error flag
    void flush();

    /// not used only for overload virtual method (protected)
    /// remaining bytes to be stored in flash @return remaning bytes
    int available();
};

enum StreamUpdater::type : uint8_t{
    FLASH_TYPE = U_FLASH,
    SPIFFS_TYPE = U_SPIFFS
};
