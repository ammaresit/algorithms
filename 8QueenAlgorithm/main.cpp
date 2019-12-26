#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class square {

    public:
    int value; // IF CONTAINS QUEEN, THEN VALUE IS 1, ELSE 0
    int threat; // AMOUNT OF THREAT

    square() {
        this->value = 0;
        this->threat = 0;
    }

};

int main()
{
    srand((unsigned)time(0));

    square chessboard[8][8];
    int random;
    int arr[8] = {0,1,2,3,4,5,6,7}; // WILL BE USED TO SHUFFLE CAUSE LOCATING QUEENS ON BOARD RANDOMLY

    // SHUFFLES ARRAY TO LOCATE QUEENS RANDOMLY
    random_shuffle(arr, arr + 8);

    // LOCATES THE QUEENS RANDOMLY
    for(int i=0; i<8; ++i) {
        chessboard[i][arr[i]].value = 1;
    }


    // CONTROLS THREAT AMOUNT FOR EACH CELL (SQUARE) !!
    bool done = false;
    square* lowest;
    int step=0, threat, queen, it;

    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j){
            cout << chessboard[i][j].value << "  ";
        }
        cout << endl;
    }

    while(!done){

        for(int col=0; col<8; ++col) {

            lowest = &chessboard[0][col];

            for(int row=0; row<8; ++row) {

                threat = 0;
                if(chessboard[row][col].value == 1)
                    queen = row;

                for(int j=0; j<8; ++j) { // CONTROLS HORIZONTAL !!

                    if(chessboard[row][j].value == 1 && j!=col)
                        ++threat;
                }
                for(int i=col-1, j=row-1; i>-1 && j>-1; --i,--j) { // CONTROLS LEFT UPPER DIAGONAL !!

                    if(chessboard[j][i].value == 1)
                        ++threat;
                }
                for(int i=col+1, j=row+1; i<8 && j<8; ++i,++j) { // CONTROLS RIGHT LOWER DIAGONAL !!

                        if(chessboard[j][i].value == 1)
                            ++threat;
                }
                for(int i=col-1, j=row+1;  i>-1 && j<8; --i,++j) { // CONTROLS LEFT LOWER DIAGONAL !!

                    if(chessboard[j][i].value == 1)
                        ++threat;
                }
                for(int i=col+1, j=row-1; i<8 && j>-1; ++i,--j) { // CONTROLS RIGHT UPPER DIAGONAL !!

                    if(chessboard[j][i].value == 1)
                        ++threat;
                }

                chessboard[row][col].threat = threat;

                    if(threat < lowest->threat) {
                        lowest = &chessboard[row][col];
                    }

            }

            chessboard[queen][col].value = 0;
            lowest->value = 1;
        }

        it=0;

        for(int p=0; p<8; ++p) { // DONE CRITERIA !! CHECKS EACH COLUMN TO DETECT IF ANY QUEEN HAS NO THREATS !!
            for(int e=0; e<8; ++e) {

                if(chessboard[e][p].value == 1){
                    if(chessboard[e][p].threat == 0) {
                        ++it;
                    }
                }
            }
        }

        if(it==8) {
            done=true;
        }
        else {
            done=false;
        }

        cout << "Step: " << ++step << "\n";
        // SCREEN CHESSBOARD
        for(int i=0; i<8; ++i) {
            for(int j=0; j<8; ++j){
                cout << chessboard[i][j].value << "-" << chessboard[i][j].threat << "  ";
            }
            cout << endl;
        }

    }

    cout << "\n\n";

    return 0;
}
