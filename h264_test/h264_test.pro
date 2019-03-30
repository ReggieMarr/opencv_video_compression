TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

INCLUDEPATH += /usr/local/include/opencv
#INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui \
-L/usr/local/lib -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape \
 -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d \
-lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs \
-lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_viz -lopencv_core -ldl -lm -lpthread -lrt -lGL -lGLU
