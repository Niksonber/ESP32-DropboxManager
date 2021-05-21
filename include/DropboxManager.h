#ifndef __DROPBOX_MANAGER__
#define __DROPBOX_MANAGER__

#include <SPIFFS.h>
#include <string.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

class DropboxManager{
public:
    DropboxManager(const char * token = NULL);
    void begin(const char * token = NULL);
    bool upload(const char * filename, const char * path = nullptr);
    bool download(const char * path, const char * filename = nullptr, bool replace = false);
protected:
    String _token;
    const char * _endpoint = "https://content.dropboxapi.com/2/files/";

    bool uploadOrDownload(String path, File * file, bool upload = true);
};

#endif