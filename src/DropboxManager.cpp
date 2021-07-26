#include "DropboxManager.h"

DropboxManager::DropboxManager(const char * token){
    if (token != NULL) _token = token;
}

void DropboxManager::begin(const char * token){
    SPIFFS.begin();
    if (token != NULL) _token = token;
}

bool DropboxManager::upload(const char * filename, const char * path){
    // check if file exists, then open
    if(!SPIFFS.exists(filename)) return false;
    File f = SPIFFS.open(filename, "rb+");
    // if path in dropbox isn' specified, use filename 
    if(path == nullptr) return uploadOrDownload(filename, &f);
    return uploadOrDownload(path, &f, true, f.size());
}

bool DropboxManager::download(const char * path, const char * filename, bool replace){
    // if filename isn' specified, then save as path
    const char * name = (filename == nullptr)? path: filename;
    // check if file exists and replace replace tag
    if(SPIFFS.exists(name) && !replace) return false;
    File f = SPIFFS.open(name, "wb+");
    // if path in dropbox isn' specified, use filename 
    return uploadOrDownload(path, &f);
}

bool DropboxManager::updateOTA(const char * path, StreamUpdater::type type, bool reboot){
    StreamUpdater updater;
    // Begin Updater
    if(updater.begin(UPDATE_SIZE_UNKNOWN, type)){
        // Download to flash
        uploadOrDownload(path, &updater);
    }
    // Try install update
    if (updater.end(true)){
        log_w("Update Success");
        if (reboot){
            log_w("Rebooting ...");  
            ESP.restart();
        }
        return true;
    }
    return false;
}

bool DropboxManager::uploadOrDownload(String path, Stream * f, bool uploadMode, size_t size){
    bool status = false;
    HTTPClient http;
    WiFiClientSecure client;
    String endpoint = _endpoint;

    if (WiFi.status() ==  WL_CONNECTED){
        // begin http with correct endpoint (for upload or download)
        endpoint +=  uploadMode?  "upload": "download";
        http.begin(client, endpoint);
        // prepare http header
        http.addHeader("Authorization", "Bearer " + _token);
        http.addHeader("Dropbox-API-Arg", "{\"path\": \"" + path + "\"}");
        http.addHeader("Content-Type", "application/octet-stream");
        //http post request, if sucess and download, send file
        if ( uploadMode ){
            status = http.sendRequest("POST", f, size) == HTTP_CODE_OK;
        } else if ( http.sendRequest("POST") == HTTP_CODE_OK){
            status = http.writeToStream(f) > 0;
        }
    }
    return status;
}