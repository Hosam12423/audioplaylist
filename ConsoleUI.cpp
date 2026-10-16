#include "ConsoleUI.h"

#include <iostream>
#include <limits>

using namespace std;

string ConsoleUI::ask(const string& prompt) const {
    cout << prompt;
    string answer;
    getline(cin, answer);
    return answer;
}

int ConsoleUI::number(const string& prompt, int min, int max) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Enter a number from " << min << " to " << max << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int ConsoleUI::selectPlaylist() const {
    const Stack<Playlist>& playlists = manager_.getPlaylists();
    if (playlists.empty()) {
        cout << "No playlists yet.\n";
        return -1;
    }
    size_t i = 0;
    for (const Playlist& playlist : playlists) cout << ++i << ". " << playlist.getName() << '\n';
    return number("Choose playlist: ", 1, static_cast<int>(playlists.size())) - 1;
}

void ConsoleUI::showSurahs(const Playlist& playlist) const {
    cout << "\nPlaylist: " << playlist.getName() << '\n';
    const SinglyLinkedList<Surah>& surahs = playlist.getSurahs();
    if (surahs.empty()) cout << "(empty)\n";
    size_t i = 0;
    for (const Surah& surah : surahs)
        cout << ++i << ". " << surah.getName() << " | " << surah.getType()
             << " | " << surah.getFile() << '\n';
}

void ConsoleUI::addPlaylist() {
    const string name = ask("Playlist name: ");
    if (name.empty()) { cout << "Name cannot be empty.\n"; return; }
    manager_.addPlaylist(name);
    cout << "Playlist added.\n";
}

void ConsoleUI::addSurah() {
    const int index = selectPlaylist();
    if (index < 0) return;
    Playlist* playlist = manager_.getPlaylist(static_cast<size_t>(index));
    const string name = ask("Surah name: ");
    const string type = ask("Type (Meccan/Medinan): ");
    const string file = ask("MP3 path (example C:\\Quran\\Al-Baqarah.mp3): ");
    if (name.empty() || file.empty()) { cout << "Name and MP3 path are required.\n"; return; }
    playlist->addSurah(Surah(name, type, file));
    cout << "Surah added.\n";
}

void ConsoleUI::removeSurah() {
    const int index = selectPlaylist();
    if (index < 0) return;
    Playlist* playlist = manager_.getPlaylist(static_cast<size_t>(index));
    if (playlist->isEmpty()) { cout << "Playlist is empty.\n"; return; }
    showSurahs(*playlist);
    const int surah = number("Surah number to remove: ", 1, static_cast<int>(playlist->getSurahs().size()));
    playlist->removeSurah(static_cast<size_t>(surah - 1));
    cout << "Surah removed.\n";
}

void ConsoleUI::reorderSurah() {
    const int index = selectPlaylist();
    if (index < 0) return;
    Playlist* playlist = manager_.getPlaylist(static_cast<size_t>(index));
    const size_t count = playlist->getSurahs().size();
    if (count < 2) { cout << "Add at least two Surahs first.\n"; return; }
    showSurahs(*playlist);
    const int from = number("Surah number to move: ", 1, static_cast<int>(count)) - 1;
    const int to = number("New position: ", 1, static_cast<int>(count)) - 1;
    playlist->moveSurah(static_cast<size_t>(from), static_cast<size_t>(to));
    cout << "Order updated.\n";
}

void ConsoleUI::showAllPlaylists() const {
    if (manager_.isEmpty()) cout << "No playlists yet.\n";
    for (const Playlist& playlist : manager_.getPlaylists()) showSurahs(playlist);
}

void ConsoleUI::showPlaylistNames() const {
    const Stack<Playlist>& playlists = manager_.getPlaylists();
    if (playlists.empty()) cout << "No playlists yet.\n";
    size_t i = 0;
    for (const Playlist& playlist : playlists) cout << ++i << ". " << playlist.getName() << '\n';
}

void ConsoleUI::showOnePlaylist() const {
    const int index = selectPlaylist();
    if (index >= 0) showSurahs(*manager_.getPlaylist(static_cast<size_t>(index)));
}

void ConsoleUI::playPlaylist() const {
    const int index = selectPlaylist();
    if (index >= 0) player_.play(*manager_.getPlaylist(static_cast<size_t>(index)));
}

void ConsoleUI::savePlaylists() const {
    const string path = ask("Save file name: ");
    cout << (manager_.saveToFile(path) ? "Saved.\n" : "Cannot create file.\n");
}

void ConsoleUI::loadPlaylists() {
    const string path = ask("Load file name: ");
    cout << (manager_.loadFromFile(path) ? "Loaded.\n" : "Cannot open or invalid file.\n");
}

void ConsoleUI::removePlaylist() {
    const int index = selectPlaylist();
    if (index < 0) return;
    manager_.removePlaylist(static_cast<size_t>(index));
    cout << "Playlist removed.\n";
}

void ConsoleUI::run() {
    while (true) {
        cout << "\n=== Quran Playlist Manager ===\n"
             << "1. Add a new playlist\n2. Add Surah to a playlist\n"
             << "3. Remove Surah from a playlist\n4. Update Surah order\n"
             << "5. Display all current playlists\n6. Display playlist names\n"
             << "7. Display Surahs in a playlist\n8. Play a playlist\n"
             << "9. Save playlists to a file\n10. Load playlists from a file\n"
             << "11. Remove a playlist\n12. Exit\n";
        switch (number("Your choice: ", 1, 12)) {
            case 1: addPlaylist(); break;
            case 2: addSurah(); break;
            case 3: removeSurah(); break;
            case 4: reorderSurah(); break;
            case 5: showAllPlaylists(); break;
            case 6: showPlaylistNames(); break;
            case 7: showOnePlaylist(); break;
            case 8: playPlaylist(); break;
            case 9: savePlaylists(); break;
            case 10: loadPlaylists(); break;
            case 11: removePlaylist(); break;
            case 12: return;
        }
    }
}
