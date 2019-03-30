#include <iostream> // for standard I/O
#include <string>   // for strings
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat)
#include <opencv2/videoio.hpp>  // Video write
#include <highgui.h>            //CV_CAP_PROP_FRAME_WIDTH ect
#include <opencv2/highgui.hpp>  //imshow() ect
using namespace std;
using namespace cv;
static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program shows how to write video files."                                   << endl
        << "You can extract the R or G or B color channel of the input video."              << endl
        << "Usage:"                                                                         << endl
        << "./video-write <input_video_name> [ R | G | B] [Y | N]"                          << endl
        << "------------------------------------------------------------------------------" << endl
        << endl;
}

void webcam_example() {
    // Create a VideoCapture object and use camera to capture the video
    VideoCapture cap(0);//"/home/reggiemarr/Downloads/Afie.mp4");

    // Check if camera opened successfully
    if(!cap.isOpened())
    {
      cout << "Error opening video stream" << endl;
//      return -1;
    }

    // Default resolution of the frame is obtained.The default resolution is system dependent.
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    VideoWriter video("outcpp.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));
//    VideoWriter video("outcpp_h264.avi",CV_FOURCC('H','2','6','4'),cap.get(CAP_PROP_FPS), Size(frame_width,frame_height));
    while(1)
    {
      Mat frame;

      // Capture frame-by-frame
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Write the frame into the file 'outcpp.avi'
      video.write(frame);

      // Display the resulting frame
      imshow( "Frame", frame );

      // Press  ESC on keyboard to  exit
      char c = (char)waitKey(1);
      if( c == 27 )
        break;
    }

    // When everything done, release the video capture and write object
    cap.release();
    video.release();

    // Closes all the windows
    destroyAllWindows();
}

void altVideoWriteExample() {
    help();
//    if (argc != 4)
//    {
//        cout << "Not enough parameters" << endl;
//        return -1;
//    }
//    /home/reggiemarr/Downloads/Afie.mp4 R Y
    const string source      = "/home/reggiemarr/Downloads/Afie.mp4";//argv[1];           // the source file name
    const bool askOutputType = 0;//argv[3][0] =='Y';  // If false it will use the inputs codec type
    VideoCapture inputVideo(source);              // Open input
    if (!inputVideo.isOpened())
    {
        cout  << "Could not open the input video: " << source << endl;
//        return -1;
    }
    string::size_type pAt = source.find_last_of('.');                  // Find extension point
//    const string NAME = source.substr(0, pAt) + argv[2][0] + ".avi";   // Form the new name with container
//    const string NAME = source.substr(0, pAt) + "R" + ".avi";   // Form the new name with container
    int ex = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));     // Get Codec Type- Int form
    // Transform from int to char via Bitwise operators
    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};
    Size S = Size((int) inputVideo.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) inputVideo.get(CAP_PROP_FRAME_HEIGHT));
    int fourcc = VideoWriter::fourcc('H','2','6','4');
    VideoWriter outputVideo;                                        // Open the output
    if (askOutputType)
        outputVideo.open(source, ex=-1, inputVideo.get(CAP_PROP_FPS), S, true);
    else
        outputVideo.open(source, fourcc, inputVideo.get(CAP_PROP_FPS), S, true);
    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << source << endl;
//        return -1;
    }
    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << inputVideo.get(CAP_PROP_FRAME_COUNT) << endl;
    cout << "Input codec type: " << EXT << endl;
    int channel = 2; // Select the channel to save

    //switch(argv[2][0])
    switch('R')
    {
    case 'R' : channel = 2; break;
    case 'G' : channel = 1; break;
    case 'B' : channel = 0; break;
    }
    Mat src, res;
    vector<Mat> spl;
    for(;;) //Show the image captured in the window and repeat
    {
        inputVideo >> src;              // read
        if (src.empty()) break;         // check if at end
        split(src, spl);                // process - extract only the correct channel
        for (int i =0; i < 3; ++i)
            if (i != channel)
                spl[i] = Mat::zeros(S, spl[0].type());
       merge(spl, res);
       //outputVideo.write(res); //save or
       outputVideo << res;
    }
    cout << "Finished writing" << endl;
}

int main(int argc, char *argv[])
{


    webcam_example();


    return 0;
}
