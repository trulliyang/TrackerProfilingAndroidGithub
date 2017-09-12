//
// Created by Leisheng526 on 2017/4/5.
//

#ifndef APPMAGICSDEMO_FACETRACKER_H
#define APPMAGICSDEMO_FACETRACKER_H

#include <string>
#include <vector>
enum faceOritation{
    faceOritationUp = 0,
    faceOritationLeft = 1,
    faceOritationUpsideDown = 2,
    faceOritationRight = 3
};
struct  PtInfo
{
    PtInfo(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    PtInfo()
    {
        x = 0;
        y = 0;
    }
    float x;
    float y;
};
struct Pt3dInfo
{
    Pt3dInfo(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Pt3dInfo()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    float x;
    float y;
    float z;
};
struct faceRect
{
    faceRect(float _x, float _y, float _width, float _height)
    {
        x = _x;
        y = _y;
        width = _width;
        height = _height;
    }
    faceRect()
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }
    float x,y,width,height;
};

struct FacialInfo
{
    std::vector<PtInfo> facialLandMarklist;
    std::vector<Pt3dInfo> facial3dlist;
    std::vector<Pt3dInfo> leftEye3dlist;
    std::vector<Pt3dInfo> rightEye3dlist;
    std::vector<float> pose_estimate;
    faceRect facerect;
    float fx,fy,cx,cy;
    PtInfo leftEyeGaze;
    PtInfo rightEyeGaze;
    float detection_certainty;
    bool GetFace;
    bool GetGaze;
    bool GetEye;

};
class FaceTracker
{
public:
    FaceTracker(std::string rootPath,std::string modelPath);
    ~FaceTracker();
    FacialInfo FacialLandMarkDetectInVideoSingleFace(char* FrameBuffer, int width, int height, int bytesPerRow, int format, faceOritation rotation = faceOritationUp, bool haveRect = false, faceRect _faceRect = faceRect(0, 0, 0, 0));
    std::vector<FacialInfo> FacialLandmarkDetectInVideo(char* FrameBuffer, int width, int height, int bytesPerRow, int format, faceOritation rotation = faceOritationUp, bool haveRect = false, std::vector<faceRect> faceRects = std::vector<faceRect>());
    std::vector<FacialInfo> FacialLandmarkDetectImage(char* FrameBuffer, int width, int height, int bytesPerRow, int format, faceOritation rotation = faceOritationUp);


    void setDetectRate(int DetectRate);
    void setMaxFaceNumber(int maxFaceNumber);
    void SetCalAccuratePose(bool CalAccuratePose);
//    std::vector<faceRect> getFaceRect();

private:
    class FaceTracker_p;
    FaceTracker_p* m_facetracker_p;
};


#endif //APPMAGICSDEMO_FACETRACKER_H