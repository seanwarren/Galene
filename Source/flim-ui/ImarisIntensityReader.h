#pragma once

#include "IntensityReader.h"
#include <H5Cpp.h>

class ImarisIntensityReader : public IntensityReader
{
public:

   ImarisIntensityReader(const std::string& filename);
   static QStringList supportedExtensions();   

protected:

   void readMetadata();
   void addStack(int chan, int t, cv::Mat& data);

   hid_t file;
   hid_t level0;
};
