/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                          License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "precomp.hpp"
#include "opencv2/video.hpp"


#define CV_INIT_ALGORITHM_2(classname, algname, memberinit) \
    static inline ::cv::Algorithm* create##classname##_hidden() \
    { \
        return create##classname(); \
    } \
    \
    static inline ::cv::Ptr< ::cv::Algorithm> create##classname##_ptr_hidden() \
    { \
        return create##classname(); \
    } \
    \
    static inline ::cv::AlgorithmInfo& classname##_info() \
    { \
        static ::cv::AlgorithmInfo classname##_info_var(algname, create##classname##_hidden); \
        return classname##_info_var; \
    } \
    \
    static ::cv::AlgorithmInfo& classname##_info_auto = classname##_info(); \
    \
    ::cv::AlgorithmInfo* classname::info() const \
    { \
        static volatile bool initialized = false; \
        \
        if( !initialized ) \
        { \
            initialized = true; \
            ::cv::Ptr<classname> obj = create##classname(); \
            memberinit; \
        } \
        return &classname##_info(); \
    }

//namespace cv
//{

using namespace cv;

/*Ptr<BackgroundSubtractor> BackgroundSubtractor::create( const String& backgroundSubtractorType )
{
    return Algorithm::create<BackgroundSubtractor>("BackgroundSubtractor." + backgroundSubtractorType);
}*/

/////////////////////// AlgorithmInfo for various background subtractors ////////////////////////////

/* NOTE!!!
   All the AlgorithmInfo-related stuff should be in the same file as initModule_video().
   Otherwise, linker may throw away some seemingly unused stuff.
*/

CV_INIT_ALGORITHM_2(BackgroundSubtractorMOG, "BackgroundSubtractor.MOG",
                    int i = 0;

                   obj->info()->addParam(*obj, "history", i, false, obj->getHistory, obj->setHistory, "Help-String!"))

///////////////////////////////////////////////////////////////////////////////////////////////////////////

CV_INIT_ALGORITHM_2(BackgroundSubtractorMOG2, "BackgroundSubtractor.MOG2",;)

///////////////////////////////////////////////////////////////////////////////////////////////////////////

CV_INIT_ALGORITHM_2(BackgroundSubtractorGMG, "BackgroundSubtractor.GMG",;)

///////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cv::initModule_video(void)
{
    bool all = true;
    all &= !BackgroundSubtractorMOG_info_auto.name().empty();
    all &= !BackgroundSubtractorMOG2_info_auto.name().empty();
    all &= !BackgroundSubtractorGMG_info_auto.name().empty();

    return all;
}

//}
