#include <iostream>
using namespace std;
#include <thread>

#include <string>
#include <cstdio>

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
    } else {
        cout << "Unknown command. Type 'help' to see the list of commands.";
    }
}

// Display handler – handles the display for the command interpreter and marquee logic
void display_handler_thread() {
    //code here
}

// Keyboard handler – handles keyboard buffering and polling
void keyboard_handler_thread() {
    //code here
}

//Marquee logic – handles the animation logic for the marquee text
void marquee_logic_thread() {
    //code here
}


//main
int main () {
    string input;
    bool is_running = true;

    //start threads

    //start programs
    cout << "Welcome to CSOPESY!\n" <<endl;
    cout << "Group developer:" <<endl;
    cout << "CISNEROS, JOHN MAVERICK ZARAGOSA\nILUSTRE, SOPHIA MACAPINLAC\nJOCSON, VINCE MIGUEL\nVERGARA, ROYCE AARON ADAM\n" <<endl;

    cout << "Version date:\n" <<endl;

    while(is_running){
        cout << "Command> ";

        //call thread functions
        cin >> input;
        thread command_interpreter(command_interpreter_thread, input);
        command_interpreter.join();       //so main doesnt end 
    }


    return 0;
}
