// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_settings.h"
#include "../objects/gSLICr_spixel_info.h"

namespace gSLICr
{
	namespace engines
	{
		class seg_engine
		{
		protected:

			// normalizing distances
			float max_color_dist;
			float max_xy_dist;
			float max_depth_dist;

			// images
			UChar4Image *source_img; ///< rgb_img
			Float4Image *cvt_img;
			IntImage *idx_img;		 ///< segment indices
			ShortImage* dep_img;	 ///< depth image

			// superpixel map
			SpixelMap* spixel_map;
			SpixelDMap* spixel_d_map;
			int spixel_size;

			objects::settings gSLICr_settings;

			virtual void Cvt_Img_Space(UChar4Image* inimg, Float4Image* outimg, COLOR_SPACE color_space) = 0;
			virtual void Init_Cluster_Centers() = 0;
			virtual void Find_Center_Association() = 0;
			virtual void Update_Cluster_Center() = 0;
			virtual void Enforce_Connectivity() = 0;

		public:

			seg_engine(const objects::settings& in_settings );
			virtual ~seg_engine();

			const IntImage* Get_Seg_Mask() const {
				idx_img->UpdateHostFromDevice();
				return idx_img;
			}

			void Perform_Segmentation(UChar4Image* in_img);

			void Perform_Segmentation(UChar4Image* in_img, ShortImage* in_depth);

			virtual void Draw_Segmentation_Result(UChar4Image* out_img){}

			virtual const IntImage* Get_Seg_Mask_With_Boundary() = 0;
		};
	}
}

