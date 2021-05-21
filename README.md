# ESP32-DropboxManager

ESP-32 library for Dropbox handler, providing a download and upload interface 



Before use this library, is necessary go to [Dropbox apps](https://www.dropbox.com/developers/apps) and create a new app. Then, in  Permissions tab, mark 

1. files.content.write
2. files.content.read

Then, **submit**. after this, select Settings tab and choose type of token (No expiration or short live) then generate a token. (copy this and don't share with anyone).



in your code, include the library and create a instance of DropbocManager:

```cpp
#include "DropboxManager.h"

DropboxManager db;
```

Then, initialize the DropbocManager

```cpp
db.begin("<YOUR TOKEN>");
```

To download a file:

```cpp
db.upload(PATH_IN_DROPBOX, FILE_NAME_IN_SPIFFS);
```

Alternativaly, to save in SPIFFS with the same  Dropbox path filename:

```cpp
db.upload(PATH_IN_DROPBOX);
```

To upload a file in dropbox:

```cpp
db.upload(FILE_NAME_IN_SPIFFS, PATH_IN_DROPBOX);
```

Alternativaly, to upload filein Dropbox with same name of SPIFFS:

```cpp
db.upload(FILE_NAME_IN_SPIFFS);
```



Obs: ALL FILE NAMES AND PATHS MUST BEGIN WITH THE '/' CHARACTER.
