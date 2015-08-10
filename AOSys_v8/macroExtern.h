#pragma once

#define  DEVICE_OFFSET_WFS10           0x00100 // device IDs of WFS10 instruments start at 256 decimal
#define  DEVICE_OFFSET_WFS20           0x00200 // device IDs of WFS20 instruments start at 512 decimal

// settings for this sample program, you may adapt settings to your preferences
#define  OPTION_OFF                    0
#define  OPTION_ON                     1

#define  SAMPLE_PIXEL_FORMAT           PIXEL_FORMAT_MONO8   // only 8 bit format is supported
#define  SAMPLE_CAMERA_RESOL_WFS       CAM_RES_768          // 768x768 pixels, see wfs.h for alternative cam resolutions


// 下面的参数用于设置WFS的分辨率
										//CAM_RES_WFS10_640(0) // 640x480
										//CAM_RES_WFS10_480(1) // 480x480
										//CAM_RES_WFS10_360(2) // 360x360
										//CAM_RES_WFS10_260(3) // 260x260
										//CAM_RES_WFS10_180(4) // 180x180 smallest!
										//CAM_RES_WFS10_MAX_IDX(4)
#define  SAMPLE_CAMERA_RESOL_WFS10     CAM_RES_WFS10_480    // 480x480 pixels



#define  SAMPLE_CAMERA_RESOL_WFS20     CAM_RES_WFS20_512    // 512x512 pixels

// 						  WFS_REF_INTERNAL              (0)
// 						  WFS_REF_USER                  (1)
#define  SAMPLE_REF_PLANE              WFS_REF_INTERNAL

// 使用	instr_setup.pupil_center_x_mm 和 instr_setup.pupil_center_y_mm代替    17:09 2015/1/25
#define  SAMPLE_PUPIL_CENTROID_X       0.0 // in mm
#define  SAMPLE_PUPIL_CENTROID_Y       0.0 // in mm

// 使用instr_setup.pupil_dia_x_mm 和instr_setup.pupil_dia_y_mm代替      17:09 2015/1/25
#define  SAMPLE_PUPIL_DIAMETER_X       4 // in mm, needs to fit to selected camera resolution
#define  SAMPLE_PUPIL_DIAMETER_Y       4

#define  SAMPLE_IMAGE_READINGS         10 // trials to read a exposed spotfield image

#define  OPTION_DYN_NOISE_CUT			OPTION_OFF   // use dynamic noise cut features  
#define  SAMPLE_OPTION_CALC_SPOT_DIAS	OPTION_OFF  // don't calculate spot diameters

// 使用instr_setup.cancel_tilt代替		21:19 2015/1/25
#define  SAMPLE_OPTION_CANCEL_TILT		OPTION_ON   // cancel average wavefront tip and tilt

#define  SAMPLE_OPTION_LIMIT_TO_PUPIL	OPTION_ON  // don't limit wavefront calculation to pupil interior

// 高速模式的参数设置    10:42 2015/5/9
#define  OPTION_HIGHSPEED				OPTION_ON   // use highspeed mode (only for WFS10 and WFS20 instruments)
#define  OPTION_HS_ADAPT_CENTR			OPTION_OFF   // adapt centroids in highspeed mode to previously measured centroids
#define  OPTION_ALLOW_AUTOEXPOS			OPTION_OFF         // allow autoexposure in highspeed mode (runs somewhat slower)


// 该定义目前已被instr_setup.wavefront_type代替    14:28 2015/1/24
#define  SAMPLE_WAVEFRONT_TYPE         WAVEFRONT_MEAS // calculate measured wavefront
									   // WAVEFRONT_MEAS  WAVEFRONT_REC  WAVEFRONT_DIFF

#define  SAMPLE_ZERNIKE_ORDERS         4  // fcalculate up to 3rd Zernike order

#define  SAMPLE_PRINTOUT_SPOTS         5  // printout results for first 5 x 5 spots only

#define  SAMPLE_OUTPUT_FILE_NAME       "WFS_sample_output.txt"


#define DM_MAX_VOLTAGE				   230
#define DM_MAX_ACTUATORS			   144

#define SPOTNUM						   29


