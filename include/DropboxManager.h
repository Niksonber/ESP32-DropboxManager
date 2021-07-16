#ifndef __DROPBOX_MANAGER__
#define __DROPBOX_MANAGER__

#include <SPIFFS.h>
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include "streamUpdater.h"

/// Class to download and upload files in Dropbox
class DropboxManager{
public:
    /// Constructor @param token (optional)
    DropboxManager(const char * token = NULL);
    
    /// initiliza SPIFFS and set token @param token 
    void begin(const char * token = NULL);

    /// Upload file in Dropbox @param filename filename in SPIFFS @param dropbox_path (optinal) name/path in Dropbox.
    /// if not provided, filename is used @return true if sucessfull upload false otherwise.
    bool upload(const char * filename, const char * path = nullptr);
    
    /// Download file from Dropbox @param dropbox_path name/path in Dropbox. @param filename (optinal) filename in SPIFFS
    /// if not provided, dropbox_path is used @return true if sucessfull download false otherwise.
    bool download(const char * path, const char * filename = nullptr, bool replace = false);

    /// Download image (program or SPIFFS) and install in next OTA partition
    /// @param path  name/path in Dropbox @param type (optional) image type StreamUpdater::type::FLASH_TYPE for program StreamUpdater::type::SPIFFS_TYPE to SPIFFS image, defaut - FLASH_TYPE
    /// @param reboot (optional) if true reboot esp on sucessfull instalation - default true @return true if sucessfully update 
    bool updateOTA(const char * path, StreamUpdater::type type = StreamUpdater::type::FLASH_TYPE, bool reboot = true);

protected:
    String _token;
    
    /// Dropbox api endpoint 
    const char * _endpoint = "https://content.dropboxapi.com/2/files/";

    /// Upload or download file to/from Dropbox, mathod used internaly
    /// @param dropbox_path (optinal) name/path in Dropbox. @param file_pointer pointer to opened file 
    /// @return true if sucessfull upload/download false otherwise.
    bool uploadOrDownload(String path, Stream *file, bool upload = false, size_t size = 0);
};

#endif