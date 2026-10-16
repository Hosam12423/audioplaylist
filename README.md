# Quran Playlist Manager

The program keeps the original playlist manager features while separating its classes into individual files:

- `Surah`: Surah name, type, and MP3 path.
- `SinglyLinkedList.h`: custom singly linked list used to store Surahs.
- `Stack.h`: custom stack used to store playlists (new playlists are placed on top).
- `Playlist`: owns a singly linked list of Surahs and supports add, remove, and reorder.
- `PlaylistManager`: manages the playlist stack and saves/loads it from a text file.
- `AudioPlayer`: Windows MP3 playback with previous, next, pause, resume, and stop controls.
- `ConsoleUI`: prompts, menu, and display operations.
- `main.cpp`: starts the console application.

Build with MinGW/GCC on Windows:

```sh
g++ -std=c++14 main.cpp Surah.cpp Playlist.cpp PlaylistManager.cpp AudioPlayer.cpp ConsoleUI.cpp -o QuranPlaylist.exe -lwinmm
```

On non-Windows platforms, omit `-lwinmm`; playlist management works, but audio playback is Windows-only.
