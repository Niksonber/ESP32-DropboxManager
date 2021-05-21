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
    return uploadOrDownload(path, &f);
}

bool DropboxManager::download(const char * path, const char * filename, bool replace){
    // if filename isn' specified, then save as path
    const char * name = (filename == nullptr)? path: filename;
    // check if file exists and replace replace tag
    if(SPIFFS.exists(name) && !replace) return false;
    File f = SPIFFS.open(name, "wb+");
    // if path in dropbox isn' specified, use filename 
    return uploadOrDownload(path, &f, false);
}

bool DropboxManager::uploadOrDownload(String path, File * f, bool uploadMode){
    bool status = false;
    HTTPClient http;
    WiFiClientSecure client;
    String endpoint = _endpoint;
    int size = uploadMode? f->size() : 0;

    if (WiFi.status() ==  WL_CONNECTED){
        // begin http with correct endpoint (for upload or download)
        endpoint +=  uploadMode?  "upload": "download";
        http.begin(client, endpoint);
        // prepare http header
        http.addHeader("Authorization", "Bearer " + _token);
        http.addHeader("Dropbox-API-Arg", "{\"path\": \"" + path + "\"}");
        http.addHeader("Content-Type", "application/octet-stream");
        //http post request, if sucess and download, send file
        int ret = http.sendRequest("POST", f, size);
        if (ret == HTTP_CODE_OK){
            if(!uploadMode) size = http.writeToStream(f);
            status = size > 0 || uploadMode;
        }
    }
    return status;
}