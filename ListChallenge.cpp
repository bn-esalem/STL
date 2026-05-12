#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
#include <list>

class Song{
    friend std::ostream &operator<<(std::ostream &os, const Song &s);
    std::string song_name;
    std::string atrist_name;
    int rate;
public:
    Song() = default;
    Song(std::string s_name, std::string a_name, int rate)
        : song_name{std::move(s_name)}, atrist_name{a_name}, rate{rate}{}

    bool operator<(const Song &rhs) const {
        return this->song_name < rhs.song_name;
    }

    bool operator==(const Song &rhs) const {
        return this->song_name == rhs.song_name;
    }
};

std::ostream &operator<<(std::ostream &os, const Song &s){
    os << std::setw(20) << std::left << s.song_name 
       << std::setw(30) << s.atrist_name << std::setw(5) << s.rate;
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

void play_current_song(const Song &song){
    std::cout << "Playing: " << std::endl;
    std::cout << song << std::endl;
}

void display_playlist(const std::list<Song> &playlist, Song &current_song){
    for(const auto &song: playlist)
        std::cout << song << std::endl;
    std::cout << "Current song: " << std::endl;
    std::cout << current_song << std::endl;
}
int main (){

    std::list<Song> playlist{
        {"God's Plan",        "Drake",                     5},
        {"Never Be The Same", "Camila Cabello",            5},
        {"Pray For Me",       "The Weekend and K. Lamar",  4},
        {"The Middle",        "Zedd, Maren Morris & Grey", 5},
        {"Wait",              "Maroone 5",                 4},
        {"Whatever It Takes", "Imagine Dragons",           3}
    };

    std::list<Song>::iterator current_song = playlist.begin();
    display_playlist(playlist, *current_song);

    char selection{};

    do{
        display_menu();
        std::cin >> selection;
        selection = std::toupper(selection);

        if(selection == 'F'){
            std::cout << "Playing first song" << std::endl;
            current_song = playlist.begin();
            play_current_song(*current_song);
        }
        else if(selection == 'N'){
            std::cout << "Playing next song" << std::endl;
            current_song++;
            if(current_song == playlist.end()){
                std::cout << "Wrapping to start of playlist" << std::endl;
                current_song = playlist.begin();
            }
            play_current_song(*current_song);
        }
        else if(selection == 'P'){
             std::cout << "Playing previous song" << std::endl;
             if(current_song == playlist.begin()){
                std::cout << "Wrapping to end of playlist" << std::endl;
                current_song = playlist.end();
             }
             current_song --;
             play_current_song(*current_song);
        }
        else if(selection == 'A'){
            std::string name, artist;
            int rate;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            
            std::cout << "Adding and playing new song" << std::endl;
            
            std::cout << "Enter song name:";
            getline(std::cin, name);
            
            std::cout << "Enter song artist: ";
            getline(std::cin, artist);
            
            std::cout << "Enter your rating (1-5): ";
            std::cin >> rate;

            playlist.insert(current_song, Song{name, artist, rate});
            current_song --;
            play_current_song(*current_song);
        }
        else if(selection == 'L'){
            std::cout << std::endl;
            display_playlist(playlist, *current_song);
        }
        else if(selection == 'Q'){
            std::cout << "Quitting" << std::endl;
        }
        else
            std::cout << "Illegal choice, try again ...";
    }while (selection != 'Q');
    
    std::cout << "Thanks for listening!" << std::endl;

    return 0;
}