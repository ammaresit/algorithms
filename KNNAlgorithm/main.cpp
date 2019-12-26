#include <iostream>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

struct object
{
    int clss;     // Group of point
    float a1, a2, a3, a4;     // Co-ordinate of point
    float dist; // Distance from test point
};

bool tempFunctionReturnsMin(object const & a, object const & b) // this function for adding extra sorting algorithm
{
    return a.dist < b.dist;
}

void classify(object arrTra[], int k, object arrTest[])
{

    int sizeOfArrTra = 120;
    int sizeOfArrTest = 30;
    object tempArr[sizeOfArrTra];
    int a;
    object minimum;

    // Fills distances of all points from test data
    for (int i=0; i < sizeOfArrTest; ++i) {

        a = -1;

        for(int j=0; j < sizeOfArrTra; ++j) {

            tempArr[++a].dist = sqrt(pow((arrTra[j].a1 - arrTest[i].a1),2) + pow((arrTra[j].a2 - arrTest[i].a2),2) + pow((arrTra[j].a3 - arrTest[i].a3),2) + pow((arrTra[j].a4 - arrTest[i].a4),2));
            tempArr[a].clss = arrTra[j].clss;

        }

        // SORTING OF ARRAY
        sort(tempArr, tempArr+sizeOfArrTra, tempFunctionReturnsMin);
        // DETERMINING THE MINIMUM DISTANCES
        minimum = tempArr[0];
        for(int w=1; w<k; w++) {

            if(minimum.dist > tempArr[w].dist) {
                minimum = tempArr[w];
            }
        }

        arrTest[i].clss = minimum.clss;

        cout << arrTest[i].a1 << " " << arrTest[i].a2 << " " << arrTest[i].a3 << " " << arrTest[i].a4 << " " << arrTest[i].clss << endl;

    }


}


int main()
{

    int k;
    cout << "Please enter 'k' => ";
    cin >> k;


    // TRAINING DATA SET PROCESS
    int n = 120;
    object trainingArr[n];

    fstream file;
    file.open("trainingdataset.txt");
    string fileS, sentence;

        // GETS DATA SET FROM TEXT FILE AND FITS IT INTO STRING VARIABLE NAMED AS "sentence"

    int a=0;

    do
    {
        file >> fileS;
        sentence += fileS+" ";
        if(++a == 5) {

            sentence += "\n";
            a=0;
        }

    }while(!file.eof());
    file.close();


        // GETS DATA FROM STRING VARIABLE AND FITS IT INTO STRUCT ARRAY NAMED AS "trainingArr"

    string temp = "";
    int indicator=0; // featurelar arasinda gecis yapabilmek icin
    int q = 0; bool bln;

    for(int i=0; i<sentence.length(); i++) {

        bln = false;

        if(sentence[i] == '\n') {

            ++q;
            temp = "";
            indicator=0;
            continue;
        }

        else if(sentence[i] == ' ') {

            switch(indicator) {

                case 0: trainingArr[q].a1 = strtof(temp.c_str(), nullptr); temp = ""; indicator++; bln=true; break;
                case 1: trainingArr[q].a2 = strtof(temp.c_str(), nullptr); temp = ""; indicator++; bln=true; break;
                case 2: trainingArr[q].a3 = strtof(temp.c_str(), nullptr); temp = ""; indicator++; bln=true; break;
                case 3: trainingArr[q].a4 = strtof(temp.c_str(), nullptr); temp = ""; indicator++; bln=true; break;
                case 4: trainingArr[q].clss = atoi(temp.c_str()); temp = ""; indicator=0; bln=true; break;
                default: break;
            }
        }

        if(!bln) temp += sentence[i];

    }


    // TEST DATA SET PROCESS
    int n1 = 30;
    object testArr[n1];

    fstream file2;
    file2.open("testdataset.txt");
    string fileS2, sentence2;

        // GETS DATA SET FROM TEXT FILE AND FITS IT INTO STRING VARIABLE NAMED AS "sentence2"

    int a2=0;

    do
    {
        file2 >> fileS2;
        sentence2 += fileS2+" ";
        if(++a2 == 4) {

            sentence2 += "\n";
            a2=0;
        }

    }while(!file2.eof());
    file2.close();


        // GETS DATA FROM STRING VARIABLE AND FITS IT INTO STRUCT ARRAY NAMED AS "testingArr"

    string temp2 = "";
    int indicator2 = 0; // featurelar arasinda gecis yapabilmek icin
    int q2 = 0; bool bln2;

    for(int i=0; i<sentence2.length(); i++) {

        bln2 = false;

        if(sentence2[i] == '\n') {

            q2++;
            temp2 = "";
            indicator2=0;
            continue;
        }

        else if(sentence2[i] == ' ') {

            switch(indicator2) {

                case 0: testArr[q2].a1 = strtof(temp2.c_str(), nullptr); temp2 = ""; indicator2++; bln2=true; break;
                case 1: testArr[q2].a2 = strtof(temp2.c_str(), nullptr); temp2 = ""; indicator2++; bln2=true; break;
                case 2: testArr[q2].a3 = strtof(temp2.c_str(), nullptr); temp2 = ""; indicator2++; bln2=true; break;
                case 3: testArr[q2].a4 = strtof(temp2.c_str(), nullptr); temp2 = ""; indicator2=0; bln2=true; break;
                default: break;
            }
        }

        if(!bln2) temp2 += sentence2[i];

    }


    // MAIN PROGRESS !!!
    cout << "\n\nThe list => \n\n";
    classify(trainingArr, k, testArr);





























    return 0;
}
