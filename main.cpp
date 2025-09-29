#include <iostream>
using namespace std;
#include <thread>

#include <string>
#include <cstdio>
#include <cstring>
#include <chrono>


//Marquee logic – handles the animation logic for the marquee text
void marquee_logic_thread(string text, int speed, bool status, size_t display_width) {
    int direction = 1;
    size_t x = 0;

    while (status) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Draw the display line
        for (size_t i = 0; i < display_width; ++i) {
            if (i >= x && i < x + text.length())
                cout << text[i - x];
            else
                cout << " ";
        }

        cout << "\r"; // return to start of line
        this_thread::sleep_for(chrono::milliseconds(speed));

        // Bounce logic
        if (x + text.length() >= display_width) direction = -1;
        if (x == 0) direction = 1;

        x += direction;
    }
}


        /*
        for (int i = 0; i < text.length(); i++){
            cout << text[i];
            this_thread::sleep_for(chrono::milliseconds(speed));        //what does this do?
            //end after it finishes printing the whole text
            //bounce
        }
            */

// Command interpreter – accepts command and control the marquee logic
void command_interpreter_thread(string input) {
    if (input == "help") {
        cout << "List of commands:\n";
        cout << "“help” – displays the commands and its description\n";
        cout << "“start_marquee” – starts the marquee “animation”\n";
        cout << "“stop_marquee” – stops the marquee “animation”\n";
        cout << "“set_text” – accepts a text input and displays it as a marquee\n";
        cout << "“set_speed” – sets the marquee animation refresh in milliseconds\n";
        cout << "“exit” – terminates the console\n" <<endl;
    } 
    else if (input == "start_marquee"){
        thread marqueeThread(marquee_logic_thread, string ("Welcome to CSOPESY"), 1, true, 40);  //thread for marquee animation
        marqueeThread.join();
    }
    else if (input == "exit"){
        cout << "Exiting program...\n";
        exit(0);
    }
    else {
        cout << "Unknown command. Type 'help' to see the list of commands.";
    }
}

// Display handler – handles the display for the command interpreter and marquee logic
void display_handler_thread() {
    //i want maruee logic to play here

    cout << "Group developer:" <<endl;
    cout << "CISNEROS, JOHN MAVERICK ZARAGOSA\nILUSTRE, SOPHIA MACAPINLAC\nJOCSON, VINCE MIGUEL\nVERGARA, ROYCE AARON ADAM\n" <<endl;

    cout << "Version date:\n" <<endl;
    cout << "Command> ";

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
        cin >> input;
        thread commandThread(command_interpreter_thread, input);
        commandThread.join();       //so main doesnt end 
    }


    return 0;
}
