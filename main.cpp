#include <iostream>
using namespace std;
#include <thread>

#include <string>
#include <cstdio>
#include <cstring>
#include <chrono>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <queue>
#include <mutex>

// shared state
string marquee_text = "Welcome to CSOPESY";
int marquee_speed = 100;
bool marquee_active = false;
size_t display_width = 100;
std::queue<char> key_buffer;
std::mutex key_buffer_mutex;

//HELPER FUNCTION - TOKENIZER
vector<string> tokenize_input(const string& input) {
    vector<string> tokens;
    istringstream iss(input);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

//Marquee logic – handles the animation logic for the marquee text
void marquee_logic_thread() {
    int direction = 1;
    size_t x = 0;       // current position
    while (true) {
        if (!marquee_active) {
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        cout << "\r"; // return to line start

        for (size_t i = 0; i < display_width; ++i) {
            if (i >= x && i < x + marquee_text.length())
                cout << marquee_text[i - x];
            else
                cout << " ";
        }
        
        cout.flush(); 
        this_thread::sleep_for(chrono::milliseconds(marquee_speed));

        if (x + marquee_text.length() >= display_width) direction = -1;
        if (x == 0) direction = 1;
        x += direction;
    }
}

// Command interpreter – accepts command and control the marquee logic
void command_interpreter_thread(string input) {
    vector<string> tokens = tokenize_input(input);
    if (tokens[0] == "help") {
        cout << "List of commands:\n";
        cout << "\"help\" displays the commands and its description\n";
        cout << "\"start_marquee\" starts the marquee \"animation\"\n";
        cout << "\"stop_marquee\" stops the marquee \"animation\"\n";
        cout << "\"set_text <text_input>\" accepts a text input and displays it as a marquee\n";
        cout << "\"set_speed <milliseconds>\" sets the marquee animation refresh in milliseconds\n";
        cout << "\"exit\" terminates the console\n" <<endl;
    } 
    else if (tokens[0] == "start_marquee"){
        if(marquee_active) {
            cout << "Marquee is already running.\n\n";
        }
        else
            marquee_active = true;
    }
    else if (tokens[0] == "stop_marquee"){
        if(!marquee_active) {
            cout << "Marquee is not currently running.\n\n";
        }
        else
            marquee_active = false;
    }
     
    //set text 
    else if (tokens[0] == "set_text"){
        if (tokens.size() > 1) {
            string new_text;
            for (size_t i = 1; i < tokens.size(); ++i) {
                new_text += tokens[i];
                if (i != tokens.size() - 1) 
                    new_text += " ";
            }
            marquee_text = new_text;
        }
        else {
            cout << "Error: No text provided.\n\n";
        }

        //ALTERNATIVE METHOD THAT CAN ACCEPT ASCII ART. NOT SURE HOW TO IMPLEMENT ON MARQUEE LOGIC
        /*string new_text;
        cout << "Enter new marquee text or ASCII art. (type 'END' on a new line to finish):\n";
        while (true) {
            string line;
            getline(cin, line);
            if (line == "END") 
                break;
            new_text += line + "\n";
        }
        if (!new_text.empty()) {
            marquee_text = new_text;
        } else {
            cout << "Error: No text provided.\n\n";
        }*/
    }
    //set speed
    else if (tokens[0] == "set_speed"){
        if (tokens.size() > 1) {
            int speed = stoi(tokens[1]);
            if (speed < 0) {
                cout << "Error: Speed must be a positive number.\n\n";
            } 
            else {
                marquee_speed = speed;
            }
        }
        else {
            cout << "Error: No speed value provided.\n\n";
        }
    }
    else if (tokens[0] == "exit"){
        cout << "Exiting program...\n\n";
        exit(0);
    }
    else {
        cout << "Unknown command. Type 'help' to see the list of commands.\n\n";
    }
}

// Display handler – handles the display for the command interpreter and marquee logic
void display_handler_thread() {
    thread marqueeThread(marquee_logic_thread);
    marqueeThread.detach();

    cout << "Group developer:" <<endl;
    cout << "CISNEROS, JOHN MAVERICK ZARAGOSA\nILUSTRE, SOPHIA MACAPINLAC\nJOCSON, VINCE MIGUEL\nVERGARA, ROYCE AARON ADAM\n" <<endl;

    cout << "Version date:\n" <<endl;

    //layout and design of the console
}

// Keyboard handler – handles keyboard buffering and polling

void keyboard_handler_thread() {
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            std::lock_guard<std::mutex> lock(key_buffer_mutex);
            key_buffer.push(ch); // Buffer the key press
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

int main () {
    string input;
    bool is_running = true;

    thread displayThread(display_handler_thread);
    thread keyboardThread(keyboard_handler_thread);

    cout << "Command> ";
    while(is_running){
        // start of command input for buffered keys
        {
            std::lock_guard<std::mutex> lock(key_buffer_mutex);
            while (!key_buffer.empty()) {
                char ch = key_buffer.front();
                key_buffer.pop();
                if (ch == '\r') { // enter
                    cout << endl;
                    thread commandThread(command_interpreter_thread, input);
                    commandThread.join();
                    input.clear();
                    cout << "Command> ";
                } else if (ch == '\b') { // backspace
                    if (!input.empty()) {
                        input.pop_back();
                        cout << "\b \b";
                    }
                } else if (isprint(ch)) {
                    input += ch;
                    cout << ch;
                }
            }
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    displayThread.join();
    keyboardThread.join();
    return 0;
}