#include "RealignmentResultsWriter.h"
#include <QFileInfo>
#include <QMessageBox>
#include "WriteMultipageTiff.h"

void RealignmentResultsWriter::exportAlignedMovie(const std::vector<RealignmentResult>& results, const QString& filename)
{
   std::vector<cv::Mat> images;
   for (const auto& r : results)
   {
      cv::Mat b;
      r.realigned.convertTo(b, CV_16U);
      images.push_back(b);
   }

   writeMovie(filename, images);
}

void RealignmentResultsWriter::exportAlignedIntensityPreservingMovie(const std::vector<RealignmentResult>& results, const QString& filename)
{
   std::vector<cv::Mat> images;
   for (const auto& r : results)
   {
      cv::Mat b;
      r.realigned_preserving.convertTo(b, CV_16U);
      images.push_back(b);
   }

   writeMovie(filename, images);
}
 
void RealignmentResultsWriter::exportUnalignedMovie(const std::vector<RealignmentResult>& results, const QString& filename)
{
   std::vector<cv::Mat> images;
   for (const auto& r : results)
   {
      cv::Mat b;
      r.frame.convertTo(b, CV_16U);
      images.push_back(b);
   }

   writeMovie(filename, images);
}


void RealignmentResultsWriter::writeMovie(const QString& filename, const std::vector<cv::Mat>& images)
{
   QString extension = QFileInfo(filename).suffix();

   if (extension == "avi")
   {
#ifndef SUPPRESS_OPENCV_HIGHGUI
      auto sz = images[0].size();
      auto writer = cv::VideoWriter(filename.toStdString(), -1, 4, sz, false);

      double mn, mx;
      cv::minMaxIdx(images[0], &mn, &mx);
      double scale = 255 / (0.8*mx);

      cv::Mat buf(sz, CV_8U);
      for (const auto& im : images)
      {
         im.convertTo(buf, CV_8U, scale);
         writer.write(buf);
      }
#else
      QMessageBox::warning(nullptr, "Could not export", "Cannot export when compiled in debug mode");
#endif
   }
   else if (extension == "tif")
   {
      writeMultipageTiff(filename.toStdString(), images);
   }
}