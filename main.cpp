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

// shared state
string marquee_text = "Welcome to CSOPESY";
int marquee_speed = 100;
bool marquee_active = false;
size_t display_width = 40;

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
        if(marquee_active == true) {
            cout << "Marquee is already running.\n\n";
        }
        else
            marquee_active = true;
    }
    else if (tokens[0] == "stop_marquee"){
        if(marquee_active == false) {
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
}

//main
int main () {
    string input;
    bool is_running = true;

    //start threads

    //start programs
    thread displayThread(display_handler_thread);
    displayThread.join();        //so main doesnt end

    while(is_running){

        //call thread functions
        cout << "Command> "; // Ask for input
        getline(cin, input);
        thread commandThread(command_interpreter_thread, input);
        commandThread.join();       //so main doesnt end 
    }


    return 0;
}
