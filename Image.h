#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;


struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char pixelDepth;
    char imageDescriptor;
};

struct Pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};


class Image{
private:
    string name;
    //ifstream file;
public:
    Header header;
    vector<Pixel> pixels;

    Image();
    Image& operator=(const Image& other);

    void read(const string &inName);
    void write(const string &outName);

    void multiply(const Image& secondIm);
    void subtract(const Image& secondIm);
    void flip();
    bool isRealFile(const string& filename);
    void multText(const Image& secondIm);
    void overlay(const Image& secondIm);
    void addGreen(int amount);
    void scaleIm(int scale);
    void onlyred();
    void onlygreen();
    void onlyblue();
    void threeIm(const Image& rChan, const Image& gChan, const Image& bChan, const string& result);
    void rotateTex();
};



