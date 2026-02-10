#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include<cstdlib>
/*SECTION 20 Challenge
In this challenge you will create a menu driven application that
will simulate a user playing songs from a playlist of songs.

We will use a list to simulate the user selecting the the first song in the playlist and
then selecting next and previous to play forward of backwards through the 
playlist.

Please refer to the video demo run.

We will also allow users to add new song to the playlist and they
will be added prior to the currently playing song.
The menu looks as follows:

F - Play First Song
N - Play Next song
P - Play Previous song
A - Add and play a new Song at current location
L - List the current playlist
========================
Enter a selection (Q to quit):

And the available playlist is modeled as a std::list<Song>
I will provide the Song class. Following are the songs in the playlist.
*/

using namespace std;

class Song {
    friend std::ostream& operator<<(std::ostream& os, const Song& s);
    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
        : name{ name }, artist{ artist }, rating{ rating } {
    }
    std::string get_name() const {
        return name;
    }
    std::string get_artist() const {
        return artist;
    }
    int get_rating() const {
        return rating;
    }

    bool operator<(const Song& rhs) const {
        return this->name < rhs.name;
    }

    bool operator==(const Song& rhs) const {
        return this->name == rhs.name;
    }
};

std::ostream& operator<<(std::ostream& os, const Song& s) {
    os << std::setw(20) << std::left << s.name
        << std::setw(30) << std::left << s.artist
        << std::setw(2) << std::left << s.rating;
    return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song& song) {
    // This function should display 
    // Playing: followed by the song that is playing
    cout << endl;
    cout << "Playing: \n" << song << endl;
}

void display_playlist(const std::list<Song>& playlist, const Song& current_song) {
    // This function should display the current playlist 
    // and then the current song playing.
    for (auto& song : playlist) {
        cout << song << endl;
    }
    cout << "Currently playing: " << endl << current_song << endl;
}
//extra part
void call_youtube(const Song& song) {
    string query = song.get_name() + " " + song.get_artist();
    for (auto& c : query) {
        if (c == ' ') {
            c = '+';
        }
    }
    string url = "https://www.youtube.com/results?search_query=" + query;
    cout << "Launching youtube for: " << song.get_name() << endl;
    #ifdef _WIN32
        system(("start " + url).c_str());
    #elif __APPLE
    system(("open " + url).c_str());
    #endif
}
int main() {

    std::list<Song> playlist{
            {"Hummingbird",        "Metro Boomin, James Blake",            5},
            {"Happy",                           "Kanye West, Future",        3},
            {"Don't Let Me Down",               "The Chainsmokers, Daya",    4},
            {"Get Low",                         "Zedd, Liam Payne",          3},
            {"Liberate",                        "Eric Prydz",                4},
            {"Dawn",                            "Axwell & Ingrosso",         4},
            {"GOLDEN",                          "HUNTR/X",                   5},
    };

    std::list<Song>::iterator current_song = playlist.begin();
    // Your program logic goes here
    display_playlist(playlist, *current_song);
    char option = NULL;
    do {
        display_menu();
        cin >> option;
        option = toupper(option);
        cin.ignore(1000, '\n');
        if (option == 'F') {
            cout << "Playing first song" << endl;
            current_song = playlist.begin();
            play_current_song(*current_song);
            call_youtube(*current_song);
        }
        else if(option == 'N') {
            cout << "Playing next in queue" << endl;
            current_song++;
            if (current_song == playlist.end()) {
                current_song = playlist.begin();
            }
            else {
                play_current_song(*current_song);
                call_youtube(*current_song);
            }
        }
        else if(option == 'P') {
            cout << "Playing previous song!" << endl;
            if (current_song == playlist.begin()) {
                current_song = playlist.end();
            }
            else {
                current_song--;
                play_current_song(*current_song);
                call_youtube(*current_song);
            }
        }
        else if (option == 'A') {
            string name;
            int rating;
            string artist;
            cout << "Adding a song... Enter Details" << endl;
            cout << "Enter song name: ";
            getline(cin, name);
            cout << "Enter artist name: ";
            getline(cin, artist);
            cout << "Enter rating: ";
            cin >> rating;
            playlist.insert(current_song, Song{ name, artist, rating });
            current_song--;
            play_current_song(*current_song);
            call_youtube(*current_song);
        }
        else if(option =='L'){
            display_playlist(playlist, *current_song);
        }
    } while (option != 'Q');
    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}
