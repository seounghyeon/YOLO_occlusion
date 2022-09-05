# YOLO_occlusion


occlusion.cpp is a data augmentation program in C++ with OpenCV for Data sets written in the YOLO darknet format. 
This program will do occlusion by drawing a rectangle (white) over the object in the image and will also remove the coordinates in the text files.

You have to define several things here:
    - the folder path to the images and text files
    - the type of image (.jpg or .png etc.)
    - the object class you want to remove
    - the probability with which it is removed (if you want to remove all instances of the object, define probability as 1.0)
    
ATTENTION: YOUR FILES WILL BE OVERWRITTEN. MAKE SURE TO SAVE YOUR ORIGINAL DATA SET SEPERATELY.


To run this program, you will need OpenCV.
Clone this repo and go into the occlusion.cpp file. Change your folder directory, image file type and object class.
Then run "make" in the folder terminal and "./occlude" after that. 
