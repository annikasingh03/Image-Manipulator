#include "Image.h"
#include <iostream>
#include <fstream>
using namespace std;


Image::Image(){

}

Image& Image::operator=(const Image& other) {
    if (this != &other) { // Check for
        header = other.header;
        pixels = other.pixels;
    }
    return *this;
}


void Image::read(const string& inName){
    //read the TGA file
    ifstream file(inName, ios::binary);
    name = inName.substr(0, inName.length()-4);

    if (!file.is_open()){
        //cout << "file was not opened properly!" << endl;
    }

    file.read(&header.idLength, 1);
    file.read(&header.colorMapType, 1);
    file.read(&header.dataTypeCode, 1);
    file.read((char*) &header.colorMapOrigin, 2);
    file.read((char*) &header.colorMapLength, 2);
    file.read(&header.colorMapDepth, 1);
    file.read((char*) &header.xOrigin, 2);
    file.read((char*) &header.yOrigin, 2);
    file.read((char*) &header.width, 2);
    file.read((char*) &header.height, 2);
    file.read(&header.pixelDepth, 1);
    file.read(&header.imageDescriptor, 1);

    int imSize = header.width * header.height;

//(18) Create a for loop to read in all the pixels
    for(int i = 0; i < imSize; i++){
//make a pixel
        Pixel p;
        file.read((char*)&p.blue,1); //read
        file.read((char*)&p.green,1); //rea
        file.read((char*)&p.red,1);
        pixels.push_back(p);

    }
}


void Image::write(const string& outName) {
    ofstream outFile(outName, ios::binary); //outName is the name of the file we want to pass in

    outFile.write(&header.idLength, 1);
    outFile.write(&header.colorMapType, 1);
    outFile.write(&header.dataTypeCode, 1);
    outFile.write((char*) &header.colorMapOrigin, 2);
    outFile.write((char*) &header.colorMapLength, 2);
    outFile.write(&header.colorMapDepth, 1);
    outFile.write((char*) &header.xOrigin, 2);
    outFile.write((char*) &header.yOrigin, 2);
    outFile.write((char*) &header.width, 2);
    outFile.write((char*) &header.height, 2);
    outFile.write(&header.pixelDepth, 1);
    outFile.write(&header.imageDescriptor, 1);

    //(18) Create a for loop to read in all the pixels
    for(int i = 0; i < pixels.size(); i++){
        outFile.write((char*) &pixels[i].blue,1); //read in blue green red
        outFile.write((char*) &pixels[i].green,1); //read in blue green red
        outFile.write((char*) &pixels[i].red,1); //read in blue green red
    }
}


void Image::multiply(const Image& secondIm){
    Image result;
    result.header = header;

    for(int i = 0; i < pixels.size(); i++) {
        Pixel p1 = pixels[i];
        Pixel p2 = secondIm.pixels[i];

        Pixel final;

        float red1 = p1.red;
        float red2 = p2.red;
        red1 /= 255;
        red2 /= 255;
        final.red = char( ( (red1 * red2) * 255 ) + 0.5 ) ;

        float green1 = p1.green;
        float green2 = p2.green;
        green1 /= 255;
        green2 /= 255;
        final.green = char( ( (green1 * green2) * 255 ) + 0.5 ) ;

        float blue1 = p1.blue;
        float blue2 = p2.blue;
        blue1 /= 255;
        blue2 /= 255;
        final.blue = char( ( (blue1 * blue2) * 255 ) + 0.5 ) ;

        result.pixels.push_back(final);

    }
    *this = result;
}

void Image::subtract(const Image& secondIm){
    Image result;
    result.header = header;
    for(int i = 0; i < pixels.size(); i++) {
        Pixel p1 = pixels[i];
        Pixel p2 = secondIm.pixels[i];

        Pixel final;

        final.red = char( max(0, ((int) (p2.red) - (int) (p1.red)) ) );
        final.green = char( max(0, ((int) (p2.green) - (int) (p1.green)) ) );
        final.blue = char( max(0, ((int) (p2.blue) - (int) (p1.blue)) ) );

        result.pixels.push_back(final);
    }
    *this = result;

}

void Image::multText(const Image &secondIm){
    Image mresult;
    mresult.header = header;

    for(int i = 0; i < pixels.size(); i++) {
        Pixel p1 = pixels[i];
        Pixel p2 = secondIm.pixels[i];

        Pixel final;

        float red1 = p1.red;
        float red2 = p2.red;
        red1 /= 255;
        red2 /= 255;
        final.red = char( ( (red1 * red2) * 255 ) + 0.5 ) - 3 ;

        float green1 = p1.green;
        float green2 = p2.green;
        green1 /= 255;
        green2 /= 255;
        final.green = char( ( (green1 * green2) * 255 ) + 0.5 ) -3  ;

        float blue1 = p1.blue;
        float blue2 = p2.blue;
        blue1 /= 255;
        blue2 /= 255;
        final.blue = char( ( (blue1 * blue2) * 255 ) + 0.5 ) - 3 ;

        mresult.pixels.push_back(final);
    }

    Image text;
    text.read("input/text.tga");
    for(int i = 0; i < mresult.pixels.size(); i++) {
        Pixel p1 = mresult.pixels[i];
        Pixel p2 = text.pixels[i];

        Pixel final;

        float red1 = p1.red;
        float red2 = p2.red;
        red1 /= 255;
        red2 /= 255;
        final.red = char((1.0 - (1.0 - red1) * (1.0 - red2) * 255 + 0.5));

        float green1 = p1.green;
        float green2 = p2.green;
        green1 /= 255;
        green2 /= 255;
        final.green = char((1.0 - (1.0 - green1) * (1.0 - green2) * 255 + 0.5));

        float blue1 = p1.blue;
        float blue2 = p2.blue;
        blue1 /= 255;
        blue2 /= 255;
        final.blue = char((1.0 - (1.0 - blue1) * (1.0 - blue2) * 255 + 0.5));

        mresult.pixels[i] = final;
    }

    *this = mresult;

}

void Image::overlay(const Image &secondIm){
    Image result;
    result.header = header;

    for(int i = 0; i < pixels.size(); i++){
        Pixel p1 = pixels[i];
        Pixel p2 = secondIm.pixels[i];

        Pixel final;

        float red1 = float(p1.red);
        float red2 = float(p2.red);
        red1 /= 255.0f;
        red2 /= 255.0f;
        if(red2 <= 0.5) {
            final.red = char( (2.0 * red1 * red2 * 255) + 0.5);
        }
        else {
            //final.red = char(1.0 - 2.0 * (1.0 - red1) * (1.0 - red2) * 255 + 0.5);
            final.red = (1-((1-(red1)) * (1 - (red2))) * 2)*(255)+.5f;

        }

        float green1 = float(p1.green);
        float green2 = float(p2.green);
        green1 /= 255;
        green2 /= 255;

        if(green2 <= 0.5) {
            final.green = char( (2.0 * green1 * green2 * 255) + 0.5);
        }
        else{
            //final.green = char(1.0 - 2.0 * (1.0 - green1) * (1.0 - green2) * 255 + 0.5);
            final.green = (1-((1-(green1)) * (1 - (green2))) * 2)*(255)+.5f;
        }

        float blue1 = float(p1.blue);
        float blue2 = float(p2.blue);
        blue1 /= 255;
        blue2 /= 255;
        if(blue2 <= 0.5) {
            final.blue = char( (2.0 * blue1 * blue2 * 255) + 0.5);
        }
        else{
            final.blue = (1-((1-(blue1)) * (1 - (blue2))) * 2)*(255)+.5f;
        }
        result.pixels.push_back(final);
    }
    *this = result;

}

void Image::addGreen(int amount){
    for(int i = 0; i < pixels.size(); i++){
        int green = int(pixels[i].green) + amount;
        green = max( 0, min(255, green));
        pixels[i].green = char(green);
    }

}

void Image::scaleIm(int scale){
    for(int i = 0; i < pixels.size(); i++) {
        int red = int(pixels[i].red) * scale;
        red = max( 0, min(255, red));
        pixels[i].red = char(red);

        int blue = int(pixels[i].blue) * 0;
        blue = max( 0, min(255, blue));
        pixels[i].blue = char(blue);
    }
}

void Image::onlyred(){
    Image r = * this;
    Image b = *this;
    for(int i = 0; i < pixels.size(); i++) {
        Pixel& pixel = r.pixels[i];
        pixel.green = pixel.red;
        pixel.blue = pixel.red;
    }
}


void Image::onlygreen() {
    Image g = *this;

    for (int i = 0; i < pixels.size(); i++) {
        Pixel &pixel = g.pixels[i];
        pixel.blue = pixel.green;
        pixel.red = pixel.green;

    }
}
void Image::onlyblue() {
    Image b = *this;
    for(int i = 0; i < pixels.size(); i++) {
        Pixel& pixel = b.pixels[i];
        pixel.red = pixel.blue;
        pixel.green = pixel.blue;
    }
}

void Image::flip() {
    Image flip;
    flip.header = header;
    int w = header.width;
    int h = header.height;

    for (int y = 0; y < h; y++) {
        for (int x = w - 1; x >= 0; x--) {
            int originalIndex = y * w + x;
            flip.pixels.push_back(pixels[originalIndex]);
        }
    }

    *this = flip;
}


void Image:: threeIm(const Image& rChan, const Image& gChan, const Image& bChan, const string& result) {
    Image finalImage;
    finalImage.header = rChan.header;
//for loop for combo
    for (int i = 0; i < rChan.pixels.size(); i++) {
        Pixel p; //this is a new pix
        p.red = rChan.pixels[i].red; //red
        p.green = gChan.pixels[i].green;
        p.blue = bChan.pixels[i].blue;
        finalImage.pixels.push_back(p);
    }
    //finalImage.write(result);
}

void Image::rotateTex(){
    Image rot;
    rot.header = header;

    int w = header.width;  //set up the dimensions
    int h = header.height;

    for (int y = h - 1; y >= 0; y--) {
        for (int x = w - 1; x >= 0; x--) {
            int Xf = (w - 1)- x;
            int Yf = (h - 1) - y;
            rot.pixels.push_back(pixels[Yf * w + Xf * h]);
        }
    }
    *this = rot;
};






//multiply
//send both set of vectors and multiply pixels into a new vectors and put that vector result into multiply image
//what you want to send to your multiply function is up to you