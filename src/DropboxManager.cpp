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

bool DropboxManager::download(const char * path, const char * filename, bool replace){
    // if filename isn' specified, then save as path
    const char * name = (filename == nullptr)? path: filename;
    // check if file exists and replace replace tag
    if(SPIFFS.exists(name) && !replace) return false;
    File f = SPIFFS.open(name, "wb+");
    // if path in dropbox isn' specified, use filename 
    return uploadOrDownload(path, &f);
}
