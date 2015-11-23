// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
#include "../gSLICr_defines.h"

namespace gSLICr
{
	namespace objects
	{
		struct spixel_info
		{
			Vector2f center;	//< center in uv coordinate
			Vector4f color_info;
			int id;
			int no_pixels;
		};

		struct spixel_d_info
		{
			Vector2f center;	//< center in uv coordinate
			Vector4f color_info;
			int id;
			int no_pixels;
			float depth_info;		//< depth in scaled Z coordinate
//			static float fx;
//			static float fy;
//			static float cx;
//			static float cy;
		};
	}

	/// superpixel
	typedef ORUtils::Image<objects::spixel_info> SpixelMap;
	/// supervoxel with depth channel, not superpixel voxel accurately
	typedef ORUtils::Image<objects::spixel_d_info> SpixelDMap;
}
