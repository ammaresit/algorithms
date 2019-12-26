#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


class room{

    public: bool dirty;
    public: int n;

    room() {

        this->n = 0;
    }

};

class agent{

    public: int loc;
    public: int prevLoc;
    public: int point;

    agent() {

        this->point = 0;
        this->loc = rand() % 9;
        this->prevLoc = this->loc; // SETS PREVIOUS LOCATION AS CURRENT LOCATION (ONLY IN BEGINNING CASE)
    }

    // IF ROOM WHICH AGENT WANTS TO GO IS NOT THE ROOM COMES FROM OR THERE IS NO WALL, THEN AGENT GOES.
    bool go(int loc, room* r) {

        bool movement = false;
        r->n += 1;

        if(this->prevLoc != loc || this->loc != loc) {

            this->loc = loc;
            movement = true;

            if((r->n) % 4 == 0) {
                r->dirty = true;
                cout << "You made it dirty!" << endl;
            }
        }

        return movement;
    }

    // IF ROOM IS CLEAN, LOSES POINT; ELSE, GAINS POINT.
    void clean(room* r) {

        if(r->dirty) {
            this->point += 1; cout << "point +1, ";
        }
        else {
            this->point -= 1; cout << "point -1, ";
        }

        r->dirty = false;
    }

};


int main()
{
    srand((unsigned)time(0));

    // CREATING the ROOMS
    room apartment[9];

    for(int i=0; i<9; ++i) {

        apartment[i].dirty = (rand() % 2 ? true : false);

        cout << apartment[i].dirty << " ";

        if((i+1) % 3 == 0)
            cout << endl;
    }

    // CREATING the AGENT
    agent agentSalt;

    // MOVING the AGENT
    bool done;
    do{

        done = true;

        cout << "Current Location: " << agentSalt.loc << endl;

        // REGISTERS RANDOM NUMBER AND MOVES THERE
        int targetRoom;
        do{
            targetRoom = rand() % 9;

        }while(targetRoom == agentSalt.loc);

        cout << "Target Location: " << targetRoom << endl;

        if(agentSalt.go(targetRoom, &apartment[targetRoom])) { // IF MOVEMENT OCCURED THEN CLEANED

            agentSalt.clean(&apartment[targetRoom]);
            cout << "n: " << apartment[targetRoom].n << endl;
            cout << agentSalt.loc << " Cleaned!" << endl;
            cout << "Agent's Point: " << agentSalt.point << endl << endl << endl;

            for(int i=0; i<9; ++i) {

                cout << apartment[i].dirty << " ";

                if((i+1) % 3 == 0)
                    cout << endl;
            }

        }

        // CHECKS IF ALL CLEAN
        for(int i=0; i<9; ++i) {

            if(apartment[i].dirty) {
                done = false;
                break;
            }
        }

    }while(!done);

    cout << "\n\nYour Final Point: " << agentSalt.point << endl;
    cout << "\nCongrats! You have a fresh cleaned home now" << endl << endl;

    return 0;
}
