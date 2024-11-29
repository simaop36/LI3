#ifndef ALBUM_H
#define ALBUM_H

typedef struct album *Album;

Album create_Album();

char *getIdAlbum(Album a);

char *getTitleAlbum(Album a);


#endif