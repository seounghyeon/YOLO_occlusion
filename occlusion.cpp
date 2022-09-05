/*
occlusion.cpp is a data augmentation program in C++ with OpenCV for Data sets written in the YOLO darknet format. 
This program will do occlusion by drawing a rectangle (white) over the object in the image and will also remove the coordinates in the text files.

You have to define several things here:
    - the folder path to the images and text files
    - the type of image (.jpg or .png etc.)
    - the object class you want to remove
    - the probability with which it is removed (if you want to remove all instances of the object, define probability as 1.0)
    
ATTENTION: YOUR FILES WILL BE OVERWRITTEN. MAKE SURE TO SAVE YOUR ORIGINAL DATA SET SEPERATELY.
*/

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

/* this function deletes substring ".jpg" which is read in with cv::glob */
std::string delete_substring(std::string &main_string, const std::string &delete_string)
{
    // Search for the substring in string
    size_t pos = main_string.find(delete_string);
    if (pos != std::string::npos)
    {
        // If found then erase it from string
        main_string.erase(pos, delete_string.length());
    }
    return main_string;
}


int main()
{
    //DEFINE FOLDER PATH TO IMAGES AND TEXT FILES HERE (needs to be like this /home/USERNAME/abc/ )
    std::string path = "/home/pictures/test/";
    //DEFINE WHAT TYPE OF IMAGE FILE IT IS .jpg or .png
    std::string extension = ".jpg";
    //DEFINE WHICH OBJECT YOU WANT TO DELETE
    int ID = 12;
    //DEFINE PROBABILITY WITH WHICH TO REMOVE THE OBJECTS
    float probability = 0.4;

    std::string name_text_file{};
    std::string name_image_file{};
    std::ifstream infile;
    std::vector<std::string> filenames;
    std::string folderpath = path+"*"+extension;
    cv::glob(folderpath, filenames);


    //iterates through all images 
    for (size_t i=0; i<filenames.size(); i++)
    {
        cv::Mat img = cv::imread(filenames[i]);
        float image_w = img.cols;
        float image_h = img.rows;
        std::string no_img_substring = delete_substring(filenames[i], extension);
        std::string no_img_substring_txt = no_img_substring+".txt";
        std::vector<float> text_vector {};


        std::cout<<"file "<<filenames[i]<<std::endl;

        //opens text file and reads in all the values inside, storing it in a vector
        infile.open(no_img_substring_txt);
        if(infile.is_open()){
            float number {};
            int counter {};
            /* iterate through all numbers */ 
            while(infile >> number){
            text_vector.push_back(number);
            }
            infile.close();
        }
        else{
            std::cout<<"file does not exist"<<std::endl;
        }


        float r = ((double) rand() / (RAND_MAX)); 
        int ID_remove{100000};
        std::string text_string = no_img_substring_txt;
        std::ofstream outfile (text_string);

        //checks the text file for the object class
        for(int i=0; i<text_vector.size(); i++){
            float r = ((double) rand() / (RAND_MAX)); 
            //if the object class is found, with a certain probability, draw rectangle over the object in image
            if(text_vector[i]==ID && r<probability)
            {
                //i-th value in text vector is stored for removal
                ID_remove = i;
                std::cout<<"removed line of ID "<<ID<<std::endl;

                // draw black box into image from text coordinates 
                float x = text_vector[i+1];
                float y = text_vector[i+2];
                float w = text_vector[i+3];
                float h = text_vector[i+4];

                float nx = int(float(x)*image_w);
                float ny = int(float(y)*image_h);
                float nw = int(float(w)*image_w);
                float nh = int(float(h)*image_h);

                cv::Point p1(nx+0.5*nw, ny+0.5*nh);
                cv::Point p2(nx-0.5*nw, ny-0.5*nh);
                cv::rectangle(img,p1, p2,cv::Scalar(255,255,255),-1);
                cv::imshow("Display window", img);
                std::string no_img_substring_jpg = no_img_substring+extension;
                cv::imwrite(no_img_substring_jpg,img);
            }

            //remove the whole line with the object (skips the save of the line in new text file)
            if (i!=ID_remove &&i!= ID_remove+1 &&i!= ID_remove+2 &&i!= ID_remove+3 &&i!= ID_remove+4){
                std::cout<<text_vector[i]<<" ";
                outfile << text_vector[i] << " ";
                    if ((i+1)%5==0 && i!=0){
                        outfile<<std::endl;
                        std::cout<<std::endl;
                    }
            }
        }

        int k = cv::waitKey(1);

    }


    return 0;
}

