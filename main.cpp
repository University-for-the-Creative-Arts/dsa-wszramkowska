/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// stores story text for each scene, the choices available and name of the next scene

struct Scene {
    string text;
    vector<pair<string, string>> choices; // {choiceText, nextSceneKey}
};

// creates a pause 

void printWithPause(const string& text, int delay = 40) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << "\n\n";
}

int main() {
    map<string, Scene> story;


    // --- Define scenes --- 
    story["start"] = {
        "The fire flickers weakly. Wind howls outside. You hear scratching on the walls.\n"
        "What do you do?",
        {
            {"Check the basement", "basement"},
            {"Barricade the door", "door"},
            {"Look out the window", "window"}
        }
    };

    story["basement"] = {
        "You descend into darkness. A faint hum echoes — a generator.\n"
        "1. Turn it on\n2. Stay quiet",
        {
            {"Turn it on", "power restore"},
            {"Search in darkness", "tunnel"}
        }
    };
    
    story["power restore"] = {
        "The lights flicker for a brief moment - you glimpse a shadowy figure.\n"
        "1. Turn it on\n2. Stay quiet",
        {
            {"Run out of the basement", "death"},
            {"Stay quiet", "tunnel"}
        }
    };

    story["door"] = {
        "You barricade the door with furniture.\n1. Wait it out\n2. Peek outside",
        {
            {"Wait it out", "safe"},
            {"Peek outside", "reflection"}
        }
    };

    story["window"] = {
        "You wipe frost from the glass.\n1. Wave for help\n2. Smash window and run",
        {
            {"Wave for help", "reflection"},
            {"Smash window and run", "freeze"}
        }
    };

    // Endings
    story["death"] = {"A roar fills the air. The creature found you.\nYou never make it out.\n--- DEATH ENDING ---", {}};
    story["safe"] = {"Hours later, light breaks through the storm.\nYou survived the night.\n--- SAFE ENDING ---", {}};
    story["freeze"] = {"You stumble into the snow... and everything fades to white.\n--- FROZEN ENDING ---", {}};
    story["reflection"] = {"You see your reflection smiling back at you.\nBut you're not smiling.\n--- HORROR ENDING ---", {}};
    story["tunnel"] = {"You crawl through a tunnel beneath the cabin... and emerge into the dawn.\n--- SECRET SURVIVAL ENDING ---", {}};



// Main gameplay loop

    // --- Story loop ---
    string current = "start";
    while (true) {
        printWithPause(story[current].text);

        if (story[current].choices.empty()) break; // end reached

        for (int i = 0; i < story[current].choices.size(); ++i) {
            cout << i + 1 << ". " << story[current].choices[i].first << "\n";
        }

        int choice;
        cout << "> ";
        cin >> choice;

        if (choice < 1 || choice > story[current].choices.size()) {
            cout << "Invalid choice.\n";
            continue;
        }

        current = story[current].choices[choice - 1].second;
    }

    return 0;
}
