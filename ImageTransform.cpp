#include <iostream>
#include <cmath>
#include <cstdlib>

#include "uiuc/PNG.h"
#include "uiuc/HSLAPixel.h"
#include "ImageTransform.h"

/* 
Name: Satyam Pandey
A Project Assignment under course "Object Oriented Data Structures in C++"
Comments provided wherever needed
*/

using uiuc::PNG;
using uiuc::HSLAPixel;


PNG grayscale(PNG image) {//parameter is image of png type

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & px = image.getPixel(x, y);

      px.s = 0;//setting saturation of every pixel to zero
    }
  }

  return image;
}

PNG createSpotlight(PNG image, int centerX, int centerY) {/*spotlight here is ought to be centered at centerX and centerY,
 we will decrease luminance by 0.5% per 1 pixel, and after 160 pixels the luminance is decreased by 80% always and then return the modified image*/
for (unsigned i = 0; i < image.width(); i++) {
    for (unsigned j = 0; j < image.height(); j++) {
      //firstly get pixel from HLS (Hue, Luminance and Saturation) create an object
      if(i==centerX&&j==centerY)
      continue;
      HSLAPixel & px = image.getPixel(i, j);
      //now using circle locus we have
      double r=sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));
      //as we know for r>160 l=l*0.2 so
      if(r>160)
      px.l=px.l*0.2;//reduced to 80%
      else
      px.l=px.l-px.l*r*0.005;//0.5%
      
    }
}


  return image;
  
}
 

PNG illinify(PNG image) {
//The cold of the blue tones emphasises the warmth of the orange ones:)
int oval=11;
int bval=216;
for (unsigned i = 0; i < image.width(); i++) {
    for (unsigned j = 0; j < image.height(); j++) {
      //firstly get pixel from HLS (Hue, Luminance and Saturation) create an object
      
      HSLAPixel & px = image.getPixel(i, j);
      //pixel hue belongs to [200,330)
      if( px.h >= 200 && px.h < 330) 
        px.h = 216;//blue value
      else 
        px.h = 11;//orange value
      }
    }
 

  return image;
}

PNG watermark(PNG firstImage, PNG secondImage) {
  //here first image is reference image second one is stencil
  //we check l of 2nd image at every pixel and then if any of it is 1, we make pixel at same location of first image as adding 0.2 
 for (unsigned x = 0; x < secondImage.width(); x++) {
    for (unsigned y = 0; y < secondImage.height(); y++) {
      HSLAPixel& fpx = firstImage.getPixel(x, y);
      HSLAPixel& spx = secondImage.getPixel(x, y);
      if(spx.l == 1.0) 
        fpx.l += 0.2;//corresponding first image location luminance increased by 0.2
      
    }
  }
  return firstImage;

}
