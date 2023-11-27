#include <iostream>
#include <ostream>
#include <fstream>
#include <cstring>
#include "Image.h"

using namespace std;

bool isRealFile(const string& filename) {
    ifstream file(filename.c_str());
    return file.good();
}


int main(int argc, char** argv) {
    if (argc >= 2 && argv[1] && strcmp(argv[1], "--help") == 0 || argc == 1) {
        cout << "Project 2: Image Processing, Fall 2023\n"<<endl;
        cout << "Usage: "<<endl;
        cout<<" \t./project2.out [output] [firstImage] [method]" << endl;
        return 0;
    }

    int argIndex = 1;

//checks the output arg
    if (strlen(argv[1]) >= 4) {
        string ending = argv[1];
        ending = ending.substr(ending.length() - 4);

        if (ending != ".tga") {
            cout << "Invalid file name." << endl;
            //cout << argv[2] << endl;
        }

    }

    if (int i = 2 && i < argc) {
        if (strlen(argv[i]) >= 4) {
            string ending = argv[i];
            ending = ending.substr(ending.length() - 4);

            if (ending != ".tga") {
                cout << "Invalid file name." << endl;
                return -1;
                //cout << argv[i] << endl;
            }

            if(ending == ".tga" && !( isRealFile(argv[i]) ) ){
                cout << "File does not exist."<<endl;
                return -1;
            }
        }
    }

    if (argc >= 2 && argv[1] && strcmp(argv[1], "out") == 0) {
        cout << "Invalid file name." << endl;
        return 0;
    }


    string outputF = argv[argIndex];
    string inputIm = argv[argIndex + 1];
    Image im;
    im.read(inputIm);

    for (int i = argIndex + 2; i < argc; i++) {
        if (strcmp(argv[i], "multiply") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing argument." << endl;
                return -1;
            }

            string otherImF = argv[i + 1];
            Image otherIm;
            otherIm.read(otherImF);

            cout << "Multiplying " << inputIm << " and " << otherImF << endl;
            im.multiply(otherIm);
            inputIm = otherImF;
            i++;

        } else if (strcmp(argv[i], "subtract") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing argument." << endl;
                return -1;
            }

            string otherImF = argv[i + 1];
            Image otherIm;
            otherIm.read(otherImF);

            cout << "Subtracting " << inputIm << " and " << otherImF << endl;
            im.subtract(otherIm);
            inputIm = otherImF;
            i++;
        }
        else if (strcmp(argv[i], "flip") == 0) {
            im.flip();
        }

        else if (strcmp(argv[i], "overlay") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing Argument." << endl;
                return -1;
            }

            string otherImF = argv[i + 1];
            Image otherIm;
            otherIm.read(otherImF);

            cout << "overlaying " << inputIm << " and " << otherImF << endl;
            im.overlay(otherIm);
            inputIm = otherImF;
            i++;
        }

        else if (strcmp(argv[i], "screen") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing Argument." << endl;
                return -1;
            }

            string otherImF = argv[i + 1];
            Image otherIm;
            otherIm.read(otherImF);

            cout << "Screening " << inputIm << " and " << otherImF << endl;
            Image copy = otherIm;
            copy.multiply(im);
            inputIm = otherImF;
            i++;

            im = copy;
        }

        else if (strcmp(argv[i], "combine") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing Argument." << endl;
            }

            string otherImF = argv[i + 1];
            string thirdF = argv[i + 2];

            Image third;
            third.read(thirdF);

            Image otherIm;
            otherIm.read(otherImF);

            cout << "combining " << inputIm << " and " << otherImF << endl;
            im.threeIm(im, otherIm, third, outputF);
            inputIm = otherImF;

            i+=2;
        }
        else if (strcmp(argv[i], "onlyred") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing Argument." << endl;
                return -1;
            }

            string otherImF = argv[i + 1];
            Image otherIm;
            otherIm.read(otherImF);

            cout << "Only red channel" << endl;
            im.onlyred();
            inputIm = otherImF;
            i++;
        }

        else if (strcmp(argv[i], "onlygreen") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing Argument." << endl;
                return -1;
            }

            string otherImF = argv[i + 1];
            Image otherIm;
            otherIm.read(otherImF);

            cout << "Only green channel" << endl;
            im.onlygreen();
            inputIm = otherImF;
            i++;
        }
        else if (strcmp(argv[i], "onlyblue") == 0) {
            if (i + 1 >= argc) {
                cout << "Missing Argument." << endl;
                return -1;
            }

            string otherImF = argv[i + 1];
            Image otherIm;
            otherIm.read(otherImF);

            cout << "Only blue channel" << endl;
            im.onlyblue();
            inputIm = otherImF;
            i++;
        }

        else {
            cout << "Invalid method name." << endl;
            return -1;
        }
    }


    im.write(outputF);



//part1
    Image layer1;
    layer1.read("input/layer1.tga");
    Image pattern1;
    pattern1.read("input/pattern1.tga");
    Image copy = layer1;
    copy.multiply(pattern1);
    copy.write("output/part1.tga");

    //part2
    Image layer2;
    layer2.read("input/layer2.tga");
    Image car;
    car.read("input/car.tga");
    Image layer2copy = layer2;
    Image carCopy = car;
    layer2copy.subtract(carCopy);
    layer2copy.write("output/part2.tga");

    //part3
    Image copy2 = layer1;
    Image pattern2;
    pattern2.read("input/pattern2.tga");
    Image pat2copy = pattern2;
    Image text;
    text.read("input/text.tga");
    copy2.multText(pat2copy);
    copy2.write("output/part3.tga");

    //part4
    Image circles;
    Image cc = circles;
    Image l2copy = layer2;
    cc.read("input/circles.tga");
    l2copy.multiply(cc);
    Image p2c = pattern2;
    p2c.subtract(l2copy);
    p2c.write("output/part4.tga");

    //part5
    Image lay1copy = layer1;
    Image pat1copy = pattern1;
    lay1copy.overlay(pat1copy);
    lay1copy.write("output/part5.tga");

    //part 6
    Image carC = car;
    carC.read("input/car.tga");
    carC.addGreen(200);
    carC.write("output/part6.tga");

    //part 7
    Image copyCar = car;
    copyCar.read("input/car.tga");
    copyCar.scaleIm(4);
    copyCar.write("output/part7.tga");

    //part 8
    Image c = car;
    c.read("input/car.tga");
    string oD = "output/";
    //c.taskEight(oD);

    //part 9

    Image rChan;
    Image gChan;
    Image bChan;

    rChan.read("input/layer_red.tga");
    gChan.read("input/layer_green.tga");
    bChan.read("input/layer_blue.tga");
    string resultFile = "output/part9.tga";
    rChan.threeIm(rChan, gChan, bChan, resultFile);

    //part 10
    Image text2;
    text2.read("input/text2.tga");
    text2.rotateTex();
    text2.write("output/part10.tga");

}


