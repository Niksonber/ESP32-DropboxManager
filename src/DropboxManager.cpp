#include "DropboxManager.h"

DropboxManager::DropboxManager(const char * token){
    _token = token;
}

void DropboxManager::begin(){
    SPIFFS.begin();
}

bool DropboxManager::upload(const char * filename, const char * path){
    // check if file exists, then open
    if(!SPIFFS.exists(filename)) return false;
    File f = SPIFFS.open(filename, "rb+");
    // if path in dropbox isn' specified, use filename 
    if(path == nullptr) return uploadOrDownload(filename, &f);
    return uploadOrDownload(path, &f);
}

