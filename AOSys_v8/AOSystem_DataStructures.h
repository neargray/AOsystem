#pragma once

///////////////////////////////////////////////////////////////////////////////
// AOSystem_DataStructures.h
//   Header file for the AOSystem.DLL
//
//   Copyright (C) 2008 Thorlabs, Inc., All Rights Reserved.
//              
///////////////////////////////////////////////////////////////////////////////


// These are the return values for the AOS_Initialize call.
#define DEVICES_ALREADY_INITIALIZED			-1	//The AOSystem has already been initialized.
#define DEVICE_NONE							0x0	//No devices were found.
#define DEVICE_DM_FOUND						0x1	//A Deformable Mirror (DM) was found.
#define DEVICE_SH_FOUND						0x2	//The Shack-Hartmann (SH) was found.
#define DEVICE_DM_AND_SH_FOUND				0x3	//Both the DM & the SH were found.
#define DEVICE_MINI_DM_FOUND				0x4	//The Mini Deformable Mirror (DM) was found.

// These are the return values for the AOS_Close call.
#define SHUTDOWN_OK							0	//The AOSystem has already been shutdown properly.
#define SHUTDOWN_ERROR						1	//The AOSystem has encountered an error during shutdown.

//These are used as the first parameter in the GetVarAddress & SetVarAddress calls.
#define VAR_DM_DESIRED						1
#define VAR_DM_ACTUAL						2
#define VAR_DM_VOLTAGE						3
#define VAR_DM_ALTERNATE					4
#define VAR_DM_FIT							5
#define VAR_DM_COEFF						6
#define VAR_DM_CELLMASK						8
#define VAR_IMAGEBUFFER						9
#define VAR_SVD_M							10
#define VAR_SVD_N							11
#define VAR_SVD_U							12
#define VAR_SVD_V							13
#define VAR_SVD_VT							14
#define VAR_SVD_R							15
#define VAR_SVD_R2							16
#define VAR_SVD_R2INV						17
#define VAR_SVD_W							18
#define VAR_SVD_RTMP						19
#define VAR_SVD_ORIG						20
#define VAR_SPOTINCLUSION					21
#define VAR_DM_COMMAND						22
#define VAR_INSTR							23
#define VAR_INSTR_SETUP						24
#define VAR_SPOTINFO						25
#define VAR_DESIRED							26
#define VAR_ZERNIKE_BASE					27
#define VAR_ZERNIKE_COEF					28
#define VAR_ZERNIKE_ACTUAL					29
#define VAR_ZERNIKE_WAVEFRONT				30
#define VAR_CAPTURED_WAVEFRONT				31
#define VAR_DM_DATA							999

// These are the return values for the SH_SetGainExposure call.
#define NO_SETTINGS_CHANGED					0x0	//Neither setting was adjusted.				
#define GAIN_ADJUSTED						0x1	//The Gain "Limit" was adjusted.
#define EXPOS_ADJUSTED						0x2	//The Exposure "Limit" was adjusted.
#define BOTH_SETTINGS_ACCEPTED				0x3	//Both the Gain & Exposure "Limits" were adjusted.

// These are used in the first parameter to SH_CalcSpotDeviations
//#define  WFS_REF_INTERNAL					0	//Use the internal zernike reference grid
//#define  WFS_REF_USER						1   //Use a user supplied reference grid (taken from a reference measurement)

// max number of detectable spots
//#define  MAX_SPOTS_X						50  //SH: max spots in width, for 1280x1024 with 4.65um pixels and 150um lenslet pitch
//#define  MAX_SPOTS_Y						40  //SH: max spots in height, determines also arrays sizes and 3D display size 
//#define  WFS_BUFFER_SIZE					256 //General buffer size
#define  EE_SIZE							64  //bytes in camera's EEPROM

// Wavefront Sensors' number of pixel resolution settings
#define  NUM_WFS_RESOLUTION_SETTINGS		5




#ifndef AO_INIT				//Make sure this is only defined once

///////////////////////////////////////////////////////////////////////////////
//  DM_Voltage  --- DM: Pointer to DM voltage variables
///////////////////////////////////////////////////////////////////////////////
struct DM_Voltage
{

	double		DMMinVoltage;			//The minimum voltage of the DM
	double		DMMaxVoltage;			//The maximum voltage of the DM
	double		DMStartStroke;			//The start-range voltage of the DM used in calibration
	double		DMEndStroke;			//The end-range voltage of the DM used in calibration
	double		DMVoltageScale;			//Calculation multipier for nm stroke DM movements-This is a constant multiplier equal to the total digital-
										//range of stroke (16384) divided by the max voltage for the DM (300).
	double		DMVoltageScaleInv;		//Represents inverse of above (1 / DMVoltageScale)
	int			DMBaseMin;				//Calculated values not to be changed
	int			DMBaseMax;				//Calculated values not to be changed

};


///////////////////////////////////////////////////////////////////////////////
//  spotinfo_t  ---  SH: Ptr to SH spot data structure.
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int			spots_x;										// max (x) spots according to selected image size
	int			spots_y;										// max (y) spots according to selected image size
	int			center_spot_x;									// index of center spot (x)
	int			center_spot_y;									// index of center spot (y)

	float		scale_x_mm[MAX_SPOTS_X];						// for internal use only
	float		scale_y_mm[MAX_SPOTS_Y];						// for internal use only

	float		centroid_x[MAX_SPOTS_Y + 1][MAX_SPOTS_X + 1];	// spot centroid positions in pixels
	float		centroid_y[MAX_SPOTS_Y + 1][MAX_SPOTS_X + 1];	// +1 for adaption to MathLab

	float		diameter_x[MAX_SPOTS_Y][MAX_SPOTS_X];			// spot diameters (x) in pixels
	float		diameter_y[MAX_SPOTS_Y][MAX_SPOTS_X];			// spot diameters (y) in pixels
	float		diameter[MAX_SPOTS_Y][MAX_SPOTS_X];				// geometric mean diameter in pixels

	float		peak_level[MAX_SPOTS_Y][MAX_SPOTS_X];			// max intensity level in spot area
	float		intensity[MAX_SPOTS_Y][MAX_SPOTS_X];			// sum intensity level in spot area

	double		reference_x[MAX_SPOTS_Y][MAX_SPOTS_X];			// measured spot reference positions (x) in pixels
	double		reference_y[MAX_SPOTS_Y][MAX_SPOTS_X];			// measured spot reference positions (y) in pixels
	double		ref_grid_x[MAX_SPOTS_Y + 1][MAX_SPOTS_X + 1];	//ideal ref grid in pixels
	double		ref_grid_y[MAX_SPOTS_Y + 1][MAX_SPOTS_X + 1];	// +1 for adaption to MathLab

	float		deviation_x[MAX_SPOTS_Y][MAX_SPOTS_X];			// measured deviation = spot centroids - reference in pixels 
	float		deviation_y[MAX_SPOTS_Y][MAX_SPOTS_X];			// measured deviation = spot centroids - reference in pixels 

	float		devdiff_x[MAX_SPOTS_Y][MAX_SPOTS_X];			// deviation difference between wavefront points on same grid
	float		devdiff_y[MAX_SPOTS_Y][MAX_SPOTS_X];			// deviation difference between wavefront points on same grid

	float		deviation_rec_x[MAX_SPOTS_Y][MAX_SPOTS_X];		// reconstructed deviations (x) from Zernike modes 
	float		deviation_rec_y[MAX_SPOTS_Y][MAX_SPOTS_X];		// reconstructed deviations (y) from Zernike modes 

	float		deviation_diff_x[MAX_SPOTS_Y][MAX_SPOTS_X];		// deviation difference (x) between measured and reconstructed
	float		deviation_diff_y[MAX_SPOTS_Y][MAX_SPOTS_X];		// deviation difference (y) between measured and reconstructed

	float		wavefront[MAX_SPOTS_Y][MAX_SPOTS_X];			// absolute wavefront results in um  
	float		wavefront_waves[MAX_SPOTS_Y][MAX_SPOTS_X];		// wavefront results in waves (lambda dependent)

	float		wavefront_flip[MAX_SPOTS_X][MAX_SPOTS_Y];		//flipped indices, only used for 3D display
	float		wf_scale[2][2];									// for scale of 3D graph

	float		sum_intensity;									// data related to detected spots only
	float		mean_intensity;

	float		weighted_tilt_x;								// not used, for simulations only
	float		weighted_tilt_y;								// not used, for simulations only 

	// wavefront statistics
	float		wf_min;											// minimum wavefront value in um
	float		wf_max;											// maximum wavefront value in um
	float		wf_diff;										// peak-peak of wavefront in um
	float		wf_mean;										// mean wavefront level
	float		wf_rms;											// RMS value of wavefront
	float		weighted_wf_rms;								// RMS of wavefront, weighted to individual spot intensity

	float		wf_min_waves;									// same in waves (lambda dependent)
	float		wf_max_waves;
	float		wf_diff_waves;
	float		wf_mean_waves;
	float		wf_rms_waves;
	float		weighted_wf_rms_waves;

	float		diameter_min;									// min diameter of all valid spots
	float		diameter_max;									// max diameter of all valid spots
	float		diameter_mean;									// mean diameter of all valid spots
	float		spots_centroid_x;								// x,y centroid of an individual spot in pixel
	float		spots_centroid_y;
	float		spots_diameter_x;								// x,y diameter of an individual spot in pixel
	float		spots_diameter_y;

	float		spots_centroid_x_mm;							// same in mm
	float		spots_centroid_y_mm;
	float		spots_diameter_x_mm;
	float		spots_diameter_y_mm;

	float		steepness_x;									// x,y steepness of the deviation_xy values..
	float		steepness_y;									// which indicates a defocus term which can be removed optionally         
	float		mean_x;											// mean, offset, ns relate to also to this linear fit to approximate the
	float		mean_y;											// steepness of deviation_xy values
	float		offset_x;
	float		offset_y;
	float		ns_x;
	float		ns_y;

	// Added for new fast WFS functions and new Zernike functionality
	double		ref_grid_center_x_pix;										// location of ref grid center in pixels from sensor origin. Calculate after MLA is selected.
	double		ref_grid_center_y_pix;
	double		captured_reference_x[MAX_SPOTS_Y + 1][MAX_SPOTS_X + 1];		// measured ref (x) in pixels
	double		captured_reference_y[MAX_SPOTS_Y + 1][MAX_SPOTS_X + 1];		// measured ref (y) in pixels
} spotinfo_t;


///////////////////////////////////////////////////////////////////////////////
// instr_setup_t ---  SH: Ptr to instrument structure for the SH cam
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int			wf_unit;                    // WF_UNIT_UM = 0, WF_UNIT_WAVES = 1 
	double		wf_lambda_nm;               // wavelength in nm

	int			graph_select;               // internal use in GUI
	int			setup_select;				// setup_select

	int			cam_resol_idx;              // index 0..4 of pre-defined ROI, cam_xpixel[] = {1280, 1024, 768, 512, 320}; cam_ypixel[] = {1024, 1024, 768, 512, 320};
	int			average_cnt;                // number of camera image averages
	int			cam_noise_level_auto;       // 1 = automatic (flexible) noise level in spot detection
	int			cam_noise_level;            // noise level in digits, intensities below are cut (set to 0)

	int			expos_auto;                // 0 = manual, 1 = auto exposure
	double		expos_min;                 // min exposure time in ms, read from camera
	double		expos_max;                 // max exposure time in ms, read from camera
	double		expos_incr;                // exposure time increment in ms, read from camera
	double		expos_set;                 // desired exposure time, user input
	double		expos_act;                 // actual exposure time, rounded by camera

	double		master_gain;               // electrical gain

	int			black_level_auto;          // not available for selected camera
	int			black_level_offset;        // target black level setting, sent to camera

	int			disable_calc_extra_data;   // forces calculation of extra statistical data if not disableb (=0)
	int			disable_graphics;          // 1 disables all graphics for increased speed

	int			sim_tilt;                  // for internal simulation, not used
	int			sim_defocus;
	int			sim_cylinder;
	ViInt32     cancel_tilt;               // 0 DM不去除波前的平均斜率，1 DM去除波前的平均斜率
	int			cancel_defocus;            // not used

	int			pixels_per_spot;           // cam pixels per lenslet spot, 41 for WFS150

	ViInt32     pupil_circular;            // = 1 forces a circular pupil

	int			use_intens_centroid;       // use beam centroid as Zernike center
	int			use_intens_dia;            // use beam diameter as Zernike diameter

	int			wf_calc_in_pupil;          // limit wavefront calculation and display to within pupil

	ViReal64	pupil_dia_x_mm;            // x,y  pupil diameter in mm
	ViReal64	pupil_dia_y_mm;
	ViReal64	pupil_center_x_mm;         // x,y pupil center position in mm
	ViReal64	pupil_center_y_mm;

	int			cancel_wf_tilt;            // = 1 cancels average wavefront tilt, accessible by user via setup panel

	int			zernike_orders_auto;       // = 1 calculates Zernike terms as many as possible (dependent on detected spot count)
	int			zernike_orders;            // max. calculated zernike order
	int			fourier_order;             // max. recocniced Fourier order, 2,4 or 6
	ViInt32     ref_idx;                   // used wavefront reference, WFS_REF_INTERNAL = 0, WFS_REF_USER = 1

	ViInt32     wavefront_type;             // 0 = measured (WAVEFRONT_MEAS), 1 = reconstructed (WAVEFRONT_REC), 2 = difference of both (WAVEFRONT_DIFF)

	// Added for new fast WFS functions
	double		master_gain_max;
	double		master_gain_min;

	double		pupil_dia_x_pix;			// x,y pupil diameter in pixels
	double		pupil_dia_y_pix;
	double		pupil_center_x_pix;			// x,y pupil center position in pixels, from camera's (0,0) origin.
	double		pupil_center_y_pix;

}  instr_setup_t;


///////////////////////////////////////////////////////////////////////////////
// instr_t  ---  SH: Ptr to hardware info of the SH camera
///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int			selected_dev_id;							// id to identify the selected WFS camera
	char		version_cam_driver[WFS_BUFFER_SIZE];		// version of camera driver (IDS)
	char		version_wfs_driver[WFS_BUFFER_SIZE];		// version of WFS driver (Thorlabs)
	ViInt32		status;										// single bits indicate errors and warnings
	int			stop_pressed;								// = 1 continuous measurement stopped, finalize remaining calculations and drawings

	int         reg_cal_key;								// internal use
	int         bytes_per_row;								// bytes per row in actual image buffer
	int         rows;										// rows within actual image size
	int         cols;										// columns within actual image size

	char        ee_string[EE_SIZE + 1];						// string read from camera's EEPROM, contains SN and calibration data
	char        ee_string_backup[EE_SIZE + 1];				// backup stored in registry
	char        instrument_name[WFS_BUFFER_SIZE];			// "WFS150" or "WFS150C"
	char        serial_number_cam_dll[WFS_BUFFER_SIZE];		// cam SN from camera driver
	char        serial_number_cam_ee[WFS_BUFFER_SIZE];		// cam SN from EEPROM,must be same!
	char        serial_number_wfs[WFS_BUFFER_SIZE];			// Thorlabs SN of WFS

	int         user_ref_valid;								// 1 = user reference spots data are valid
	float       center_spot_offset_x;						// calibration value, +- pixel from image center
	float       center_spot_offset_y;						// calibration value
	float       lenslet_f_um;								// calibration value, lenslet focal length
	double      roc_set_mm;									// target radius of curvature during calibration
	int         reset_roll_avg;								// = 1 forces restart of rolling averages
	int         do_zernike_preparation;						// = 1 prepares least square fit data, required when pupil is changed
	ViInt32     do_spherical_reference;						// = 1 during a spherical reference run

	// Added for new fast WFS functions
	char		manufacturer_name[WFS_BUFFER_SIZE];			// Thorlabs
	char		mla_name[WFS_BUFFER_SIZE];
	int			mla_count;
	int			selected_mla;
	int			selected_mla_index;
	int			cam_x_resolution[NUM_WFS_RESOLUTION_SETTINGS];
	int			cam_y_resolution[NUM_WFS_RESOLUTION_SETTINGS];

	unsigned long	handle;							// Handle for WFS，使用AOSystem.dll调用时，使用此句柄

	double		cam_pitch_um;
	double		lenslet_pitch_um;
	double		grd_corr_0;
	double		grd_corr_45;
}  instr_t;



struct AOSystemData
{
	double*		dDMDesired;				//DM:The desired actuators array setting (in nm)
	double*		dDMActual;				//DM:The actual actuator array setting (in nm)
	double*		dDMFit;					//DM:Future use:Array of desired actuator settings minus the actual setting achieved

	double*		dDMCoeff;				//DM:These are the 3 coefficients found with the deformable mirror documentation

	double**	svd_u;					//SH:singular value decomposition- used internally
	double**	svd_v;					//SH:singular value decomposition- used internally
	double**	svd_vt;					//SH:singular value decomposition- used internally
	double**	svd_r;					//SH:singular value decomposition- used internally
	double**	svd_r2;					//SH:singular value decomposition- used internally
	double**	svd_r2inv;				//SH:singular value decomposition- used internally
	double*		svd_w;					//SH:singular value decomposition- used internally
	double**	svd_rtmp;				//SH:singular value decomposition- used internally
	double**	svd_orig;				//SH:singular value decomposition- used internally

	double*		dDMCommand;				//Holds the inverse matrix multiplication
	double*		dDesired;
	double*		dZernikeValue;			//These are the zernike coeffiecients
	double*		dZernikeWavefront;		//Used to calculate the Zernike Polynomial wavefront surface array

	double**	sh_spots_dx_pix;		//Used to store the delta X of the Zernike after a call to AOS_CalcZernikeWavefront
	double**	sh_spots_dy_pix;		//Used to store the delta Y of the Zernike after a call to AOS_CalcZernikeWavefront

	double*		dCapturedWavefrontValue;//The captured wavefront values (in nm)

	float		SH_Threshold_Off;		//SH:Minimum historisis threshold
	float		SH_Threshold_On;		//SH:Maximum historisis threshold

	int*		iDMVoltage;				//DM:Voltage array used to set all actuators. This is voltage * the DMVoltageScale (see page 10)
	int*		iDMAlternate;			//DM:Used to extrapolate edge actuators values not actively set

	int*		uiDMCellMask;			//The is the mask of what actuators are used or not
	int*		svd_m;					//SH:singular value decomposition- used internally
	int*		svd_n;					//SH:singular value decomposition- used internally
	int*		iSpotInclusion;			//SH:Determines if a particule SH spot will be included based on the the minimum and maximum threshold set by the user

	int			iCalImageAverages;		// Value used to set # images used during AO calibration
	int*		iZernikeBase;			//Used as base values in the EditControlArray
	unsigned char*		ImageBuffer;	// Used to point to the actual image obtained

	instr_t*			instr;			//SH: Ptr to hardware info of the SH camera
	instr_setup_t*		instr_setup;	//SH: Ptr to instrument structure for the SH cam
	spotinfo_t*			spotinfo;		//SH: Ptr to SH spot data structure.
	struct				DM_Voltage Volt;//DM: Pointer to DM voltage variables
};

#define AO_INIT		1	//This will stop a redefinition of this structure
#endif


