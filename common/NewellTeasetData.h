// Definitions of constants

#ifndef NewellTeasetData_h
#define NewellTeasetData_h

// The Newell's teapot dataset has 32 patches, teacup dataset has 26 patches,
// tea spoon dataset has 16 patches, which need not to be rotated or reflected.
// The vertices' index stored in Newell's patches arrays start from 1, not from 0


// The Newell's teapot has 32 patches
const unsigned int newellTeapotPatch[][16] = {
    {	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16	},
    {	4, 17, 18, 19, 8, 20, 21, 22, 12, 23, 24, 25, 16, 26, 27, 28	},
    {	19, 29, 30, 31, 22, 32, 33, 34, 25, 35, 36, 37, 28, 38, 39, 40	},
    {	31, 41, 42, 1, 34, 43, 44, 5, 37, 45, 46, 9, 40, 47, 48, 13	},
    {	13, 14, 15, 16, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60	}
    ,
    {	16, 26, 27, 28, 52, 61, 62, 63, 56, 64, 65, 66, 60, 67, 68, 69	},
    {	28, 38, 39, 40, 63, 70, 71, 72, 66, 73, 74, 75, 69, 76, 77, 78	},
    {	40, 47, 48, 13, 72, 79, 80, 49, 75, 81, 82, 53, 78, 83, 84, 57	},
    {	57, 58, 59, 60, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96	},
    {	60, 67, 68, 69, 88, 97, 98, 99, 92, 100, 101, 102, 96, 103, 104, 105	},
    {	69, 76, 77, 78, 99, 106, 107, 108, 102, 109, 110, 111, 105, 112, 113, 114	},
    {	78, 83, 84, 57, 108, 115, 116, 85, 111, 117, 118, 89, 114, 119, 120, 93	},
    {	121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136	},
    {	124, 137, 138, 121, 128, 139, 140, 125, 132, 141, 142, 129, 136, 143, 144, 133	},
    {	133, 134, 135, 136, 145, 146, 147, 148, 149, 150, 151, 152, 69, 153, 154, 155	},
    {	136, 143, 144, 133, 148, 156, 157, 145, 152, 158, 159, 149, 155, 160, 161, 69	},
    {	162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177	},
    {	165, 178, 179, 162, 169, 180, 181, 166, 173, 182, 183, 170, 177, 184, 185, 174	},
    {	174, 175, 176, 177, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197	},
    {	177, 184, 185, 174, 189, 198, 199, 186, 193, 200, 201, 190, 197, 202, 203, 194	},
    {	204, 204, 204, 204, 207, 208, 209, 210, 211, 211, 211, 211, 212, 213, 214, 215	},
    {	204, 204, 204, 204, 210, 217, 218, 219, 211, 211, 211, 211, 215, 220, 221, 222	},
    {	204, 204, 204, 204, 219, 224, 225, 226, 211, 211, 211, 211, 222, 227, 228, 229	},
    {	204, 204, 204, 204, 226, 230, 231, 207, 211, 211, 211, 211, 229, 232, 233, 212	},
    {	212, 213, 214, 215, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245	},
    {	215, 220, 221, 222, 237, 246, 247, 248, 241, 249, 250, 251, 245, 252, 253, 254	},
    {	222, 227, 228, 229, 248, 255, 256, 257, 251, 258, 259, 260, 254, 261, 262, 263	},
    {	229, 232, 233, 212, 257, 264, 265, 234, 260, 266, 267, 238, 263, 268, 269, 242	},
    {	270, 270, 270, 270, 279, 280, 281, 282, 275, 276, 277, 278, 271, 272, 273, 274	},
    {	270, 270, 270, 270, 282, 289, 290, 291, 278, 286, 287, 288, 274, 283, 284, 285	},
    {	270, 270, 270, 270, 291, 298, 299, 300, 288, 295, 296, 297, 285, 292, 293, 294	},
    {	270, 270, 270, 270, 300, 305, 306, 279, 297, 303, 304, 275, 294, 301, 302, 271	}
};
  //{	13, 14, 15, 16, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60	}
  //{	1.500000, 0.000000, 2.400000	},{	1.500000, -0.840000, 2.400000	},{	0.840000, -1.500000, 2.400000	}, {	0.000000, -1.500000, 2.400000	}, 
  //{	1.750000, 0.000000, 1.875000	},{	1.750000, -0.980000, 1.875000	},{	0.980000, -1.750000, 1.875000	}, {	0.000000, -1.750000, 1.875000	},
  //{	2.000000, 0.000000, 1.350000	},{	2.000000, -1.120000, 1.350000	},{	1.120000, -2.000000, 1.350000	}, {	0.000000, -2.000000, 1.350000	},
  //{	2.000000, 0.000000, 0.900000	},{	2.000000, -1.120000, 0.900000	},{	1.120000, -2.000000, 0.900000	}, {	0.000000, -2.000000, 0.900000	}, 
	
// The Newell teapot has 306 vertices
const float newellTeapotVertices[][3] = { {0.0000, 0.0000, 0.0000},
	{	1.400000, 0.000000, 2.400000	},{	1.400000, -0.784000, 2.400000	},{	0.784000, -1.400000, 2.400000	}, //3
	{	0.000000, -1.400000, 2.400000	},{	1.337500, 0.000000, 2.531250	},{	1.337500, -0.749000, 2.531250	}, //6 
	{	0.749000, -1.337500, 2.531250	},{	0.000000, -1.337500, 2.531250	},{	1.437500, 0.000000, 2.531250	}, //9
	{	1.437500, -0.805000, 2.531250	},{	0.805000, -1.437500, 2.531250	},{	0.000000, -1.437500, 2.531250	}, //12
	{	1.500000, 0.000000, 2.400000	},{	1.500000, -0.840000, 2.400000	},{	0.840000, -1.500000, 2.400000	}, //15
	{	0.000000, -1.500000, 2.400000	},{	-0.784000, -1.400000, 2.400000	},{	-1.400000, -0.784000, 2.400000	}, //18
	{	-1.400000, 0.000000, 2.400000	},{	-0.749000, -1.337500, 2.531250	},{	-1.337500, -0.749000, 2.531250	}, //21
	{	-1.337500, 0.000000, 2.531250	},{	-0.805000, -1.437500, 2.531250	},{	-1.437500, -0.805000, 2.531250	}, //24
	{	-1.437500, 0.000000, 2.531250	},{	-0.840000, -1.500000, 2.400000	},{	-1.500000, -0.840000, 2.400000	}, //27
	{	-1.500000, 0.000000, 2.400000	},{	-1.400000, 0.784000, 2.400000	},{	-0.784000, 1.400000, 2.400000	}, //30
	{	0.000000, 1.400000, 2.400000	},{	-1.337500, 0.749000, 2.531250	},{	-0.749000, 1.337500, 2.531250	}, //33
	{	0.000000, 1.337500, 2.531250	},{	-1.437500, 0.805000, 2.531250	},{	-0.805000, 1.437500, 2.531250	}, //36
	{	0.000000, 1.437500, 2.531250	},{	-1.500000, 0.840000, 2.400000	},{	-0.840000, 1.500000, 2.400000	}, //39
	{	0.000000, 1.500000, 2.400000	},{	0.784000, 1.400000, 2.400000	},{	1.400000, 0.784000, 2.400000	}, //42
	{	0.749000, 1.337500, 2.531250	},{	1.337500, 0.749000, 2.531250	},{	0.805000, 1.437500, 2.531250	}, //45
	{	1.437500, 0.805000, 2.531250	},{	0.840000, 1.500000, 2.400000	},{	1.500000, 0.840000, 2.400000	}, //48
	{	1.750000, 0.000000, 1.875000	},{	1.750000, -0.980000, 1.875000	},{	0.980000, -1.750000, 1.875000	}, //51
	{	0.000000, -1.750000, 1.875000	},{	2.000000, 0.000000, 1.350000	},{	2.000000, -1.120000, 1.350000	}, //54
	{	1.120000, -2.000000, 1.350000	},{	0.000000, -2.000000, 1.350000	},{	2.000000, 0.000000, 0.900000	}, //57
	{	2.000000, -1.120000, 0.900000	},{	1.120000, -2.000000, 0.900000	},{	0.000000, -2.000000, 0.900000	}, //60
	{	-0.980000, -1.750000, 1.875000	},{	-1.750000, -0.980000, 1.875000	},{	-1.750000, 0.000000, 1.875000	}, //63
	{	-1.120000, -2.000000, 1.350000	},{	-2.000000, -1.120000, 1.350000	},{	-2.000000, 0.000000, 1.350000	}, //66
	{	-1.120000, -2.000000, 0.900000	},{	-2.000000, -1.120000, 0.900000	},{	-2.000000, 0.000000, 0.900000	}, //3
	{	-1.750000, 0.980000, 1.875000	},{	-0.980000, 1.750000, 1.875000	},{	0.000000, 1.750000, 1.875000	}, //3
	{	-2.000000, 1.120000, 1.350000	},{	-1.120000, 2.000000, 1.350000	},{	0.000000, 2.000000, 1.350000	}, //3
	{	-2.000000, 1.120000, 0.900000	},{	-1.120000, 2.000000, 0.900000	},{	0.000000, 2.000000, 0.900000	}, //3
	{	0.980000, 1.750000, 1.875000	},{	1.750000, 0.980000, 1.875000	},{	1.120000, 2.000000, 1.350000	}, //3
	{	2.000000, 1.120000, 1.350000	},{	1.120000, 2.000000, 0.900000	},{	2.000000, 1.120000, 0.900000	}, //3
	{	2.000000, 0.000000, 0.450000	},{	2.000000, -1.120000, 0.450000	},{	1.120000, -2.000000, 0.450000	}, //3
	{	0.000000, -2.000000, 0.450000	},{	1.500000, 0.000000, 0.225000	},{	1.500000, -0.840000, 0.225000	}, //3
	{	0.840000, -1.500000, 0.225000	},{	0.000000, -1.500000, 0.225000	},{	1.500000, 0.000000, 0.150000	}, //3
	{	1.500000, -0.840000, 0.150000	},{	0.840000, -1.500000, 0.150000	},{	0.000000, -1.500000, 0.150000	}, //3
	{	-1.120000, -2.000000, 0.450000	},{	-2.000000, -1.120000, 0.450000	},{	-2.000000, 0.000000, 0.450000	}, //3
	{	-0.840000, -1.500000, 0.225000	},{	-1.500000, -0.840000, 0.225000	},{	-1.500000, 0.000000, 0.225000	}, //3
	{	-0.840000, -1.500000, 0.150000	},{	-1.500000, -0.840000, 0.150000	},{	-1.500000, 0.000000, 0.150000	},
	{	-2.000000, 1.120000, 0.450000	},{	-1.120000, 2.000000, 0.450000	},{	0.000000, 2.000000, 0.450000	},
	{	-1.500000, 0.840000, 0.225000	},{	-0.840000, 1.500000, 0.225000	},{	0.000000, 1.500000, 0.225000	},
	{	-1.500000, 0.840000, 0.150000	},{	-0.840000, 1.500000, 0.150000	},{	0.000000, 1.500000, 0.150000	},
	{	1.120000, 2.000000, 0.450000	},{	2.000000, 1.120000, 0.450000	},{	0.840000, 1.500000, 0.225000	},
	{	1.500000, 0.840000, 0.225000	},{	0.840000, 1.500000, 0.150000	},{	1.500000, 0.840000, 0.150000	},
	{	-1.600000, 0.000000, 2.025000	},{	-1.600000, -0.300000, 2.025000	},{	-1.500000, -0.300000, 2.250000	},
	{	-1.500000, 0.000000, 2.250000	},{	-2.300000, 0.000000, 2.025000	},{	-2.300000, -0.300000, 2.025000	},
	{	-2.500000, -0.300000, 2.250000	},{	-2.500000, 0.000000, 2.250000	},{	-2.700000, 0.000000, 2.025000	},
	{	-2.700000, -0.300000, 2.025000	},{	-3.000000, -0.300000, 2.250000	},{	-3.000000, 0.000000, 2.250000	},
	{	-2.700000, 0.000000, 1.800000	},{	-2.700000, -0.300000, 1.800000	},{	-3.000000, -0.300000, 1.800000	},
	{	-3.000000, 0.000000, 1.800000	},{	-1.500000, 0.300000, 2.250000	},{	-1.600000, 0.300000, 2.025000	},
	{	-2.500000, 0.300000, 2.250000	},{	-2.300000, 0.300000, 2.025000	},{	-3.000000, 0.300000, 2.250000	},
	{	-2.700000, 0.300000, 2.025000	},{	-3.000000, 0.300000, 1.800000	},{	-2.700000, 0.300000, 1.800000	},
	{	-2.700000, 0.000000, 1.575000	},{	-2.700000, -0.300000, 1.575000	},{	-3.000000, -0.300000, 1.350000	},
	{	-3.000000, 0.000000, 1.350000	},{	-2.500000, 0.000000, 1.125000	},{	-2.500000, -0.300000, 1.125000	},
	{	-2.650000, -0.300000, 0.937500	},{	-2.650000, 0.000000, 0.937500	},{	-2.000000, -0.300000, 0.900000	},
	{	-1.900000, -0.300000, 0.600000	},{	-1.900000, 0.000000, 0.600000	},{	-3.000000, 0.300000, 1.350000	},
	{	-2.700000, 0.300000, 1.575000	},{	-2.650000, 0.300000, 0.937500	},{	-2.500000, 0.300000, 1.125000	},
	{	-1.900000, 0.300000, 0.600000	},{	-2.000000, 0.300000, 0.900000	},{	1.700000, 0.000000, 1.425000	},
	{	1.700000, -0.660000, 1.425000	},{	1.700000, -0.660000, 0.600000	},{	1.700000, 0.000000, 0.600000	},
	{	2.600000, 0.000000, 1.425000	},{	2.600000, -0.660000, 1.425000	},{	3.100000, -0.660000, 0.825000	},
	{	3.100000, 0.000000, 0.825000	},{	2.300000, 0.000000, 2.100000	},{	2.300000, -0.250000, 2.100000	},
	{	2.400000, -0.250000, 2.025000	},{	2.400000, 0.000000, 2.025000	},{	2.700000, 0.000000, 2.400000	},
	{	2.700000, -0.250000, 2.400000	},{	3.300000, -0.250000, 2.400000	},{	3.300000, 0.000000, 2.400000	},
	{	1.700000, 0.660000, 0.600000	},{	1.700000, 0.660000, 1.425000	},{	3.100000, 0.660000, 0.825000	},
	{	2.600000, 0.660000, 1.425000	},{	2.400000, 0.250000, 2.025000	},{	2.300000, 0.250000, 2.100000	},
	{	3.300000, 0.250000, 2.400000	},{	2.700000, 0.250000, 2.400000	},{	2.800000, 0.000000, 2.475000	},
	{	2.800000, -0.250000, 2.475000	},{	3.525000, -0.250000, 2.493750	},{	3.525000, 0.000000, 2.493750	},
	{	2.900000, 0.000000, 2.475000	},{	2.900000, -0.150000, 2.475000	},{	3.450000, -0.150000, 2.512500	},
	{	3.450000, 0.000000, 2.512500	},{	2.800000, 0.000000, 2.400000	},{	2.800000, -0.150000, 2.400000	},
	{	3.200000, -0.150000, 2.400000	},{	3.200000, 0.000000, 2.400000	},{	3.525000, 0.250000, 2.493750	},
	{	2.800000, 0.250000, 2.475000	},{	3.450000, 0.150000, 2.512500	},{	2.900000, 0.150000, 2.475000	},
	{	3.200000, 0.150000, 2.400000	},{	2.800000, 0.150000, 2.400000	},{	0.000000, 0.000000, 3.150000	},
	{	0.000000, -0.002000, 3.150000	},{	0.002000, 0.000000, 3.150000	},{	0.800000, 0.000000, 3.150000	},
	{	0.800000, -0.450000, 3.150000	},{	0.450000, -0.800000, 3.150000	},{	0.000000, -0.800000, 3.150000	},
	{	0.000000, 0.000000, 2.850000	},{	0.200000, 0.000000, 2.700000	},{	0.200000, -0.112000, 2.700000	},
	{	0.112000, -0.200000, 2.700000	},{	0.000000, -0.200000, 2.700000	},{	-0.002000, 0.000000, 3.150000	},
	{	-0.450000, -0.800000, 3.150000	},{	-0.800000, -0.450000, 3.150000	},{	-0.800000, 0.000000, 3.150000	},
	{	-0.112000, -0.200000, 2.700000	},{	-0.200000, -0.112000, 2.700000	},{	-0.200000, 0.000000, 2.700000	},
	{	0.000000, 0.002000, 3.150000	},{	-0.800000, 0.450000, 3.150000	},{	-0.450000, 0.800000, 3.150000	},
	{	0.000000, 0.800000, 3.150000	},{	-0.200000, 0.112000, 2.700000	},{	-0.112000, 0.200000, 2.700000	},
	{	0.000000, 0.200000, 2.700000	},{	0.450000, 0.800000, 3.150000	},{	0.800000, 0.450000, 3.150000	},
	{	0.112000, 0.200000, 2.700000	},{	0.200000, 0.112000, 2.700000	},{	0.400000, 0.000000, 2.550000	},
	{	0.400000, -0.224000, 2.550000	},{	0.224000, -0.400000, 2.550000	},{	0.000000, -0.400000, 2.550000	},
	{	1.300000, 0.000000, 2.550000	},{	1.300000, -0.728000, 2.550000	},{	0.728000, -1.300000, 2.550000	},
	{	0.000000, -1.300000, 2.550000	},{	1.300000, 0.000000, 2.400000	},{	1.300000, -0.728000, 2.400000	},
	{	0.728000, -1.300000, 2.400000	},{	0.000000, -1.300000, 2.400000	},{	-0.224000, -0.400000, 2.550000	},
	{	-0.400000, -0.224000, 2.550000	},{	-0.400000, 0.000000, 2.550000	},{	-0.728000, -1.300000, 2.550000	},
	{	-1.300000, -0.728000, 2.550000	},{	-1.300000, 0.000000, 2.550000	},{	-0.728000, -1.300000, 2.400000	},
	{	-1.300000, -0.728000, 2.400000	},{	-1.300000, 0.000000, 2.400000	},{	-0.400000, 0.224000, 2.550000	},
	{	-0.224000, 0.400000, 2.550000	},{	0.000000, 0.400000, 2.550000	},{	-1.300000, 0.728000, 2.550000	},
	{	-0.728000, 1.300000, 2.550000	},{	0.000000, 1.300000, 2.550000	},{	-1.300000, 0.728000, 2.400000	},
	{	-0.728000, 1.300000, 2.400000	},{	0.000000, 1.300000, 2.400000	},{	0.224000, 0.400000, 2.550000	},
	{	0.400000, 0.224000, 2.550000	},{	0.728000, 1.300000, 2.550000	},{	1.300000, 0.728000, 2.550000	},
	{	0.728000, 1.300000, 2.400000	},{	1.300000, 0.728000, 2.400000	},{	0.000000, 0.000000, 0.000000	},
	{	1.500000, 0.000000, 0.150000	},{	1.500000, 0.840000, 0.150000	},{	0.840000, 1.500000, 0.150000	},
	{	0.000000, 1.500000, 0.150000	},{	1.500000, 0.000000, 0.075000	},{	1.500000, 0.840000, 0.075000	},
	{	0.840000, 1.500000, 0.075000	},{	0.000000, 1.500000, 0.075000	},{	1.425000, 0.000000, 0.000000	},
	{	1.425000, 0.798000, 0.000000	},{	0.798000, 1.425000, 0.000000	},{	0.000000, 1.425000, 0.000000	},
	{	-0.840000, 1.500000, 0.150000	},{	-1.500000, 0.840000, 0.150000	},{	-1.500000, 0.000000, 0.150000	},
	{	-0.840000, 1.500000, 0.075000	},{	-1.500000, 0.840000, 0.075000	},{	-1.500000, 0.000000, 0.075000	},
	{	-0.798000, 1.425000, 0.000000	},{	-1.425000, 0.798000, 0.000000	},{	-1.425000, 0.000000, 0.000000	},
	{	-1.500000, -0.840000, 0.150000	},{	-0.840000, -1.500000, 0.150000	},{	0.000000, -1.500000, 0.150000	},
	{	-1.500000, -0.840000, 0.075000	},{	-0.840000, -1.500000, 0.075000	},{	0.000000, -1.500000, 0.075000	},
	{	-1.425000, -0.798000, 0.000000	},{	-0.798000, -1.425000, 0.000000	},{	0.000000, -1.425000, 0.000000	},
	{	0.840000, -1.500000, 0.150000	},{	1.500000, -0.840000, 0.150000	},{	0.840000, -1.500000, 0.075000	},
	{	1.500000, -0.840000, 0.075000	},{	0.798000, -1.425000, 0.000000	},{	1.425000, -0.798000, 0.000000	}};


// The Newell cup has 26 pathces
const unsigned int cupPatch[][16] = {
	{	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16	},
	{	4, 17, 18, 19, 8, 20, 21, 22, 12, 23, 24, 25, 16, 26, 27, 28	},
	{	19, 29, 30, 31, 22, 32, 33, 34, 25, 35, 36, 37, 28, 38, 39, 40	},
	{	31, 41, 42, 1, 34, 43, 44, 5, 37, 45, 46, 9, 40, 47, 48, 13	},
	{	13, 14, 15, 16, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60	},
	{	16, 26, 27, 28, 52, 61, 62, 63, 56, 64, 65, 66, 60, 67, 68, 69	},
	{	28, 38, 39, 40, 63, 70, 71, 72, 66, 73, 74, 75, 69, 76, 77, 78	},
	{	40, 47, 48, 13, 72, 79, 80, 49, 75, 81, 82, 53, 78, 83, 84, 57	},
	{	193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 1, 2, 3, 4	},
	{	196, 205, 206, 207, 200, 208, 209, 210, 204, 211, 212, 213, 4, 17, 18, 19	},
	{	207, 214, 215, 216, 210, 217, 218, 219, 213, 220, 221, 222, 19, 29, 30, 31	},
	{	216, 223, 224, 193, 219, 225, 226, 197, 222, 227, 228, 201, 31, 41, 42, 1	},
	{	229, 230, 231, 28, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243	},
	{	28, 244, 245, 229, 235, 246, 247, 232, 239, 248, 249, 236, 243, 250, 251, 240	},
	{	57, 58, 59, 60, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96	},
	{	60, 67, 68, 69, 88, 97, 98, 99, 92, 100, 101, 102, 96, 103, 104, 105	},
	{	69, 76, 77, 78, 99, 106, 107, 108, 102, 109, 110, 111, 105, 112, 113, 114	},
	{	78, 83, 84, 57, 108, 115, 116, 85, 111, 117, 118, 89, 114, 119, 120, 93	},
	{	93, 94, 95, 96, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132	},
	{	96, 103, 104, 105, 124, 133, 134, 135, 128, 136, 137, 138, 132, 139, 140, 141	},
	{	105, 112, 113, 114, 135, 142, 143, 144, 138, 145, 146, 147, 141, 148, 149, 150	},
	{	114, 119, 120, 93, 144, 151, 152, 121, 147, 153, 154, 125, 150, 155, 156, 129	},
	{	129, 130, 131, 132, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168	},
	{	132, 139, 140, 141, 160, 169, 170, 171, 164, 172, 173, 174, 168, 175, 176, 177	},
	{	141, 148, 149, 150, 171, 178, 179, 180, 174, 181, 182, 183, 177, 184, 185, 186	},
	{	150, 155, 156, 129, 180, 187, 188, 157, 183, 189, 190, 161, 186, 191, 192, 165	}};

// The Newell cup has 251 vertices
const float cupVertices[][3]= { {0.0000, 0.0000, 0.0000}, 
	{	0.409091, 0.772727, 0.000000	},{	0.409091, 0.772727, -0.229091	},{	0.229091, 0.772727, -0.409091	},
	{	0.000000, 0.772727, -0.409091	},{	0.409091, 0.886364, 0.000000	},{	0.409091, 0.886364, -0.229091	},
	{	0.229091, 0.886364, -0.409091	},{	0.000000, 0.886364, -0.409091	},{	0.454545, 0.886364, 0.000000	},
	{	0.454545, 0.886364, -0.254545	},{	0.254545, 0.886364, -0.454545	},{	0.000000, 0.886364, -0.454545	},
	{	0.454545, 0.772727, 0.000000	},{	0.454545, 0.772727, -0.254545	},{	0.254545, 0.772727, -0.454545	},
	{	0.000000, 0.772727, -0.454545	},{	-0.229091, 0.772727, -0.409091	},{	-0.409091, 0.772727, -0.229091	},
	{	-0.409091, 0.772727, 0.000000	},{	-0.229091, 0.886364, -0.409091	},{	-0.409091, 0.886364, -0.229091	},
	{	-0.409091, 0.886364, 0.000000	},{	-0.254545, 0.886364, -0.454545	},{	-0.454545, 0.886364, -0.254545	},
	{	-0.454545, 0.886364, 0.000000	},{	-0.254545, 0.772727, -0.454545	},{	-0.454545, 0.772727, -0.254545	},
	{	-0.454545, 0.772727, 0.000000	},{	-0.409091, 0.772727, 0.229091	},{	-0.229091, 0.772727, 0.409091	},
	{	0.000000, 0.772727, 0.409091	},{	-0.409091, 0.886364, 0.229091	},{	-0.229091, 0.886364, 0.409091	},
	{	0.000000, 0.886364, 0.409091	},{	-0.454545, 0.886364, 0.254545	},{	-0.254545, 0.886364, 0.454545	},
	{	0.000000, 0.886364, 0.454545	},{	-0.454545, 0.772727, 0.254545	},{	-0.254545, 0.772727, 0.454545	},
	{	0.000000, 0.772727, 0.454545	},{	0.229091, 0.772727, 0.409091	},{	0.409091, 0.772727, 0.229091	},
	{	0.229091, 0.886364, 0.409091	},{	0.409091, 0.886364, 0.229091	},{	0.254545, 0.886364, 0.454545	},
	{	0.454545, 0.886364, 0.254545	},{	0.254545, 0.772727, 0.454545	},{	0.454545, 0.772727, 0.254545	},
	{	0.454545, 0.545455, 0.000000	},{	0.454545, 0.545455, -0.254545	},{	0.254545, 0.545455, -0.454545	},
	{	0.000000, 0.545455, -0.454545	},{	0.454545, 0.272727, 0.000000	},{	0.454545, 0.272727, -0.254545	},
	{	0.254545, 0.272727, -0.454545	},{	0.000000, 0.272727, -0.454545	},{	0.318182, 0.045454, 0.000000	},
	{	0.318182, 0.045454, -0.178182	},{	0.178182, 0.045454, -0.318182	},{	0.000000, 0.045454, -0.318182	},
	{	-0.254545, 0.545455, -0.454545	},{	-0.454545, 0.545455, -0.254545	},{	-0.454545, 0.545455, 0.000000	},
	{	-0.254545, 0.272727, -0.454545	},{	-0.454545, 0.272727, -0.254545	},{	-0.454545, 0.272727, 0.000000	},
	{	-0.178182, 0.045454, -0.318182	},{	-0.318182, 0.045454, -0.178182	},{	-0.318182, 0.045454, 0.000000	},
	{	-0.454545, 0.545455, 0.254545	},{	-0.254545, 0.545455, 0.454545	},{	0.000000, 0.545455, 0.454545	},
	{	-0.454545, 0.272727, 0.254545	},{	-0.254545, 0.272727, 0.454545	},{	0.000000, 0.272727, 0.454545	},
	{	-0.318182, 0.045454, 0.178182	},{	-0.178182, 0.045454, 0.318182	},{	0.000000, 0.045454, 0.318182	},
	{	0.254545, 0.545455, 0.454545	},{	0.454545, 0.545455, 0.254545	},{	0.254545, 0.272727, 0.454545	},
	{	0.454545, 0.272727, 0.254545	},{	0.178182, 0.045454, 0.318182	},{	0.318182, 0.045454, 0.178182	},
	{	0.545455, 0.045454, 0.000000	},{	0.545455, 0.045454, -0.305455	},{	0.305455, 0.045454, -0.545455	},
	{	0.000000, 0.045454, -0.545455	},{	0.727273, 0.136364, 0.000000	},{	0.727273, 0.136364, -0.407273	},
	{	0.407273, 0.136364, -0.727273	},{	0.000000, 0.136364, -0.727273	},{	0.909091, 0.136364, 0.000000	},
	{	0.909091, 0.136364, -0.509091	},{	0.509091, 0.136364, -0.909091	},{	0.000000, 0.136364, -0.909091	},
	{	-0.305455, 0.045454, -0.545455	},{	-0.545455, 0.045454, -0.305455	},{	-0.545455, 0.045454, 0.000000	},
	{	-0.407273, 0.136364, -0.727273	},{	-0.727273, 0.136364, -0.407273	},{	-0.727273, 0.136364, 0.000000	},
	{	-0.509091, 0.136364, -0.909091	},{	-0.909091, 0.136364, -0.509091	},{	-0.909091, 0.136364, 0.000000	},
	{	-0.545455, 0.045454, 0.305455	},{	-0.305455, 0.045454, 0.545455	},{	0.000000, 0.045454, 0.545455	},
	{	-0.727273, 0.136364, 0.407273	},{	-0.407273, 0.136364, 0.727273	},{	0.000000, 0.136364, 0.727273	},
	{	-0.909091, 0.136364, 0.509091	},{	-0.509091, 0.136364, 0.909091	},{	0.000000, 0.136364, 0.909091	},
	{	0.305455, 0.045454, 0.545455	},{	0.545455, 0.045454, 0.305455	},{	0.407273, 0.136364, 0.727273	},
	{	0.727273, 0.136364, 0.407273	},{	0.509091, 0.136364, 0.909091	},{	0.909091, 0.136364, 0.509091	},
	{	1.000000, 0.136364, 0.000000	},{	1.000000, 0.136364, -0.560000	},{	0.560000, 0.136364, -1.000000	},
	{	0.000000, 0.136364, -1.000000	},{	1.000000, 0.090909, 0.000000	},{	1.000000, 0.090909, -0.560000	},
	{	0.560000, 0.090909, -1.000000	},{	0.000000, 0.090909, -1.000000	},{	0.909091, 0.090909, 0.000000	},
	{	0.909091, 0.090909, -0.509091	},{	0.509091, 0.090909, -0.909091	},{	0.000000, 0.090909, -0.909091	},
	{	-0.560000, 0.136364, -1.000000	},{	-1.000000, 0.136364, -0.560000	},{	-1.000000, 0.136364, 0.000000	},
	{	-0.560000, 0.090909, -1.000000	},{	-1.000000, 0.090909, -0.560000	},{	-1.000000, 0.090909, 0.000000	},
	{	-0.509091, 0.090909, -0.909091	},{	-0.909091, 0.090909, -0.509091	},{	-0.909091, 0.090909, 0.000000	},
	{	-1.000000, 0.136364, 0.560000	},{	-0.560000, 0.136364, 1.000000	},{	0.000000, 0.136364, 1.000000	},
	{	-1.000000, 0.090909, 0.560000	},{	-0.560000, 0.090909, 1.000000	},{	0.000000, 0.090909, 1.000000	},
	{	-0.909091, 0.090909, 0.509091	},{	-0.509091, 0.090909, 0.909091	},{	0.000000, 0.090909, 0.909091	},
	{	0.560000, 0.136364, 1.000000	},{	1.000000, 0.136364, 0.560000	},{	0.560000, 0.090909, 1.000000	},
	{	1.000000, 0.090909, 0.560000	},{	0.509091, 0.090909, 0.909091	},{	0.909091, 0.090909, 0.509091	},
	{	0.727273, 0.090909, 0.000000	},{	0.727273, 0.090909, -0.407273	},{	0.407273, 0.090909, -0.727273	},
	{	0.000000, 0.090909, -0.727273	},{	0.545455, 0.000000, 0.000000	},{	0.545455, 0.000000, -0.305455	},
	{	0.305455, 0.000000, -0.545455	},{	0.000000, 0.000000, -0.545455	},{	0.318182, 0.000000, 0.000000	},
	{	0.318182, 0.000000, -0.178182	},{	0.178182, 0.000000, -0.318182	},{	0.000000, 0.000000, -0.318182	},
	{	-0.407273, 0.090909, -0.727273	},{	-0.727273, 0.090909, -0.407273	},{	-0.727273, 0.090909, 0.000000	},
	{	-0.305455, 0.000000, -0.545455	},{	-0.545455, 0.000000, -0.305455	},{	-0.545455, 0.000000, 0.000000	},
	{	-0.178182, 0.000000, -0.318182	},{	-0.318182, 0.000000, -0.178182	},{	-0.318182, 0.000000, 0.000000	},
	{	-0.727273, 0.090909, 0.407273	},{	-0.407273, 0.090909, 0.727273	},{	0.000000, 0.090909, 0.727273	},
	{	-0.545455, 0.000000, 0.305455	},{	-0.305455, 0.000000, 0.545455	},{	0.000000, 0.000000, 0.545455	},
	{	-0.318182, 0.000000, 0.178182	},{	-0.178182, 0.000000, 0.318182	},{	0.000000, 0.000000, 0.318182	},
	{	0.407273, 0.090909, 0.727273	},{	0.727273, 0.090909, 0.407273	},{	0.305455, 0.000000, 0.545455	},
	{	0.545455, 0.000000, 0.305455	},{	0.178182, 0.000000, 0.318182	},{	0.318182, 0.000000, 0.178182	},
	{	0.272727, 0.045454, 0.000000	},{	0.272727, 0.045454, -0.152727	},{	0.152727, 0.045454, -0.272727	},
	{	0.000000, 0.045454, -0.272727	},{	0.409091, 0.272727, 0.000000	},{	0.409091, 0.272727, -0.229091	},
	{	0.229091, 0.272727, -0.409091	},{	0.000000, 0.272727, -0.409091	},{	0.409091, 0.545455, 0.000000	},
	{	0.409091, 0.545455, -0.229091	},{	0.229091, 0.545455, -0.409091	},{	0.000000, 0.545455, -0.409091	},
	{	-0.152727, 0.045454, -0.272727	},{	-0.272727, 0.045454, -0.152727	},{	-0.272727, 0.045454, 0.000000	},
	{	-0.229091, 0.272727, -0.409091	},{	-0.409091, 0.272727, -0.229091	},{	-0.409091, 0.272727, 0.000000	},
	{	-0.229091, 0.545455, -0.409091	},{	-0.409091, 0.545455, -0.229091	},{	-0.409091, 0.545455, 0.000000	},
	{	-0.272727, 0.045454, 0.152727	},{	-0.152727, 0.045454, 0.272727	},{	0.000000, 0.045454, 0.272727	},
	{	-0.409091, 0.272727, 0.229091	},{	-0.229091, 0.272727, 0.409091	},{	0.000000, 0.272727, 0.409091	},
	{	-0.409091, 0.545455, 0.229091	},{	-0.229091, 0.545455, 0.409091	},{	0.000000, 0.545455, 0.409091	},
	{	0.152727, 0.045454, 0.272727	},{	0.272727, 0.045454, 0.152727	},{	0.229091, 0.272727, 0.409091	},
	{	0.409091, 0.272727, 0.229091	},{	0.229091, 0.545455, 0.409091	},{	0.409091, 0.545455, 0.229091	},
	{	-0.454545, 0.704545, 0.000000	},{	-0.454545, 0.704545, -0.045454	},{	-0.454545, 0.772727, -0.045454	},
	{	-0.772727, 0.863636, 0.000000	},{	-0.772727, 0.863636, -0.045454	},{	-0.818182, 0.954545, -0.045454	},
	{	-0.818182, 0.954545, 0.000000	},{	-0.772727, 0.522727, 0.000000	},{	-0.772727, 0.522727, -0.045454	},
	{	-0.909091, 0.477273, -0.045454	},{	-0.909091, 0.477273, 0.000000	},{	-0.409091, 0.363636, 0.000000	},
	{	-0.409091, 0.363636, -0.045454	},{	-0.409091, 0.295455, -0.045454	},{	-0.409091, 0.295455, 0.000000	},
	{	-0.454545, 0.772727, 0.045454	},{	-0.454545, 0.704545, 0.045454	},{	-0.818182, 0.954545, 0.045454	},
	{	-0.772727, 0.863636, 0.045454	},{	-0.909091, 0.477273, 0.045454	},{	-0.772727, 0.522727, 0.045454	},
	{	-0.409091, 0.295455, 0.045454	},{	-0.409091, 0.363636, 0.045454	}};

// The Newell spoon has 16 patches
const unsigned int spoonPatch[][16] = {
	{	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16	},
	{	17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32	},
	{	33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48	},
	{	49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64	},
	{	65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80	},
	{	81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96	},
	{	97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112	},
	{	113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128	},
	{	129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144	},
	{	145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160	},
	{	161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176	},
	{	177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192	},
	{	193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208	},
	{	209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224	},
	{	225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240	},
	{	241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256	}};

// The Newell spoon has 256 vertices
const float spoonVertices[][3]= {
	{	-0.000107, 0.205357, 0.000000	},{	0.000000, 0.196429, -0.017857	},{	0.000000, 0.196429, -0.017857	},
	{	0.000107, 0.205357, 0.000000	},{	-0.053571, 0.205357, 0.000000	},{	-0.022271, 0.178571, -0.053429	},
	{	0.022271, 0.178571, -0.053429	},{	0.053571, 0.205357, 0.000000	},{	-0.107143, 0.095243, -0.017857	},
	{	-0.044643, 0.095243, -0.089286	},{	0.044643, 0.095243, -0.089286	},{	0.107143, 0.095243, -0.017857	},
	{	-0.107143, 0.000000, -0.017857	},{	-0.044643, 0.000000, -0.089286	},{	0.044643, 0.000000, -0.089286	},
	{	0.107143, 0.000000, -0.017857	},{	0.000107, 0.205357, 0.000000	},{	0.000136, 0.207589, 0.004464	},
	{	0.000157, 0.216518, 0.004464	},{	0.000125, 0.214286, 0.000000	},{	0.053571, 0.205357, 0.000000	},
	{	0.061396, 0.212054, 0.013357	},{	0.071429, 0.220982, 0.015625	},{	0.062500, 0.214286, 0.000000	},
	{	0.107143, 0.095243, -0.017857	},{	0.122768, 0.095243, 0.000000	},{	0.142857, 0.095243, 0.004464	},
	{	0.125000, 0.095243, -0.017857	},{	0.107143, 0.000000, -0.017857	},{	0.122768, 0.000000, 0.000000	},
	{	0.142857, 0.000000, 0.004464	},{	0.125000, 0.000000, -0.017857	},{	0.000125, 0.214286, 0.000000	},
	{	0.000000, 0.205357, -0.017857	},{	0.000000, 0.205357, -0.017857	},{	-0.000125, 0.214286, 0.000000	},
	{	0.062500, 0.214286, 0.000000	},{	0.026786, 0.187500, -0.062500	},{	-0.026786, 0.187500, -0.062500	},
	{	-0.062500, 0.214286, 0.000000	},{	0.125000, 0.095243, -0.017857	},{	0.053571, 0.095243, -0.107143	},
	{	-0.053571, 0.095243, -0.107143	},{	-0.125000, 0.095243, -0.017857	},{	0.125000, 0.000000, -0.017857	},
	{	0.053571, 0.000000, -0.107143	},{	-0.053571, 0.000000, -0.107143	},{	-0.125000, 0.000000, -0.017857	},
	{	-0.000125, 0.214286, 0.000000	},{	-0.000157, 0.216518, 0.004464	},{	-0.000136, 0.207589, 0.004464	},
	{	-0.000107, 0.205357, 0.000000	},{	-0.062500, 0.214286, 0.000000	},{	-0.071429, 0.220982, 0.015625	},
	{	-0.061396, 0.212054, 0.013357	},{	-0.053571, 0.205357, 0.000000	},{	-0.125000, 0.095243, -0.017857	},
	{	-0.142857, 0.095243, 0.004464	},{	-0.122768, 0.095243, 0.000000	},{	-0.107143, 0.095243, -0.017857	},
	{	-0.125000, 0.000000, -0.017857	},{	-0.142857, 0.000000, 0.004464	},{	-0.122768, 0.000000, 0.000000	},
	{	-0.107143, 0.000000, -0.017857	},{	-0.107143, 0.000000, -0.017857	},{	-0.044643, 0.000000, -0.089286	},
	{	0.044643, 0.000000, -0.089286	},{	0.107143, 0.000000, -0.017857	},{	-0.107143, -0.142857, -0.017857	},
	{	-0.044643, -0.142857, -0.089286	},{	0.044643, -0.142857, -0.089286	},{	0.107143, -0.142857, -0.017857	},
	{	-0.013393, -0.160714, 0.038689	},{	-0.005579, -0.160714, 0.038689	},{	0.005579, -0.160714, 0.038689	},
	{	0.013393, -0.160714, 0.038689	},{	-0.013393, -0.250000, 0.053571	},{	-0.005579, -0.250000, 0.053571	},
	{	0.005579, -0.250000, 0.053571	},{	0.013393, -0.250000, 0.053571	},{	0.107143, 0.000000, -0.017857	},
	{	0.122768, 0.000000, 0.000000	},{	0.142857, 0.000000, 0.004464	},{	0.125000, 0.000000, -0.017857	},
	{	0.107143, -0.142857, -0.017857	},{	0.122768, -0.142857, 0.000000	},{	0.142857, -0.142857, 0.004464	},
	{	0.125000, -0.142857, -0.017857	},{	0.013393, -0.160714, 0.038689	},{	0.015346, -0.160714, 0.038689	},
	{	0.017857, -0.160714, 0.031436	},{	0.015625, -0.160714, 0.029761	},{	0.013393, -0.250000, 0.053571	},
	{	0.015346, -0.250000, 0.053571	},{	0.017857, -0.250000, 0.046318	},{	0.015625, -0.250000, 0.044643	},
	{	0.125000, 0.000000, -0.017857	},{	0.053571, 0.000000, -0.107143	},{	-0.053571, 0.000000, -0.107143	},
	{	-0.125000, 0.000000, -0.017857	},{	0.125000, -0.142857, -0.017857	},{	0.053571, -0.142857, -0.107143	},
	{	-0.053571, -0.142857, -0.107143	},{	-0.125000, -0.142857, -0.017857	},{	0.015625, -0.160714, 0.029761	},
	{	0.006696, -0.160714, 0.023064	},{	-0.007811, -0.160714, 0.020832	},{	-0.015625, -0.160714, 0.029761	},
	{	0.015625, -0.250000, 0.044643	},{	0.006696, -0.250000, 0.037946	},{	-0.007811, -0.250000, 0.035714	},
	{	-0.015625, -0.250000, 0.044643	},{	-0.125000, 0.000000, -0.017857	},{	-0.142857, 0.000000, 0.004464	},
	{	-0.122768, 0.000000, 0.000000	},{	-0.107143, 0.000000, -0.017857	},{	-0.125000, -0.142857, -0.017857	},
	{	-0.142857, -0.142857, 0.004464	},{	-0.122768, -0.142857, 0.000000	},{	-0.107143, -0.142857, -0.017857	},
	{	-0.015625, -0.160714, 0.029761	},{	-0.017579, -0.160714, 0.031993	},{	-0.015346, -0.160714, 0.038689	},
	{	-0.013393, -0.160714, 0.038689	},{	-0.015625, -0.250000, 0.044643	},{	-0.017579, -0.250000, 0.046875	},
	{	-0.015346, -0.250000, 0.053571	},{	-0.013393, -0.250000, 0.053571	},{	-0.013393, -0.250000, 0.053571	},
	{	-0.005579, -0.250000, 0.053571	},{	0.005579, -0.250000, 0.053571	},{	0.013393, -0.250000, 0.053571	},
	{	-0.013393, -0.464250, 0.089286	},{	-0.005579, -0.464250, 0.089286	},{	0.005579, -0.464250, 0.089286	},
	{	0.013393, -0.464250, 0.089286	},{	-0.044643, -0.678571, 0.053571	},{	-0.008929, -0.678571, 0.062500	},
	{	0.008929, -0.678571, 0.062500	},{	0.044643, -0.678571, 0.053571	},{	-0.044643, -0.857143, 0.035714	},
	{	-0.008929, -0.857143, 0.044643	},{	0.008929, -0.857143, 0.044643	},{	0.044643, -0.857143, 0.035714	},
	{	0.013393, -0.250000, 0.053571	},{	0.015346, -0.250000, 0.053571	},{	0.017857, -0.250000, 0.046318	},
	{	0.015625, -0.250000, 0.044643	},{	0.013393, -0.464250, 0.089286	},{	0.015346, -0.464286, 0.089286	},
	{	0.017857, -0.464250, 0.082032	},{	0.015625, -0.464250, 0.080357	},{	0.044643, -0.678571, 0.053571	},
	{	0.053571, -0.678571, 0.051339	},{	0.053571, -0.678571, 0.033482	},{	0.044643, -0.678571, 0.035714	},
	{	0.044643, -0.857143, 0.035714	},{	0.053571, -0.857143, 0.033482	},{	0.053571, -0.857143, 0.015625	},
	{	0.044643, -0.857143, 0.017857	},{	0.015625, -0.250000, 0.044643	},{	0.006696, -0.250000, 0.037946	},
	{	-0.007811, -0.250000, 0.035714	},{	-0.015625, -0.250000, 0.044643	},{	0.015625, -0.464250, 0.080357	},
	{	0.006696, -0.464286, 0.073661	},{	-0.007811, -0.464250, 0.071429	},{	-0.015625, -0.464250, 0.080357	},
	{	0.044643, -0.678571, 0.035714	},{	0.008929, -0.678571, 0.044643	},{	-0.008929, -0.678571, 0.044643	},
	{	-0.044643, -0.678571, 0.035714	},{	0.044643, -0.857143, 0.017857	},{	0.008929, -0.857143, 0.026786	},
	{	-0.008929, -0.857143, 0.026786	},{	-0.044643, -0.857143, 0.017857	},{	-0.015625, -0.250000, 0.044643	},
	{	-0.017579, -0.250000, 0.046875	},{	-0.015346, -0.250000, 0.053571	},{	-0.013393, -0.250000, 0.053571	},
	{	-0.015625, -0.464250, 0.080357	},{	-0.017579, -0.464286, 0.082589	},{	-0.015346, -0.464286, 0.089286	},
	{	-0.013393, -0.464250, 0.089286	},{	-0.044643, -0.678571, 0.035714	},{	-0.053571, -0.678571, 0.033482	},
	{	-0.053571, -0.678571, 0.051339	},{	-0.044643, -0.678571, 0.053571	},{	-0.044643, -0.857143, 0.017857	},
	{	-0.053571, -0.857143, 0.015625	},{	-0.053571, -0.857143, 0.033482	},{	-0.044643, -0.857143, 0.035714	},
	{	-0.044643, -0.857143, 0.035714	},{	-0.008929, -0.857143, 0.044643	},{	0.008929, -0.857143, 0.044643	},
	{	0.044643, -0.857143, 0.035714	},{	-0.044643, -0.928571, 0.028571	},{	-0.008929, -0.928571, 0.037500	},
	{	0.008929, -0.928571, 0.037500	},{	0.044643, -0.928571, 0.028571	},{	-0.053929, -0.999643, 0.017857	},
	{	0.000357, -0.999643, 0.017857	},{	0.000000, -0.999643, 0.017857	},{	0.053571, -0.999643, 0.017857	},
	{	-0.000357, -1.000000, 0.017857	},{	0.000357, -1.000000, 0.017857	},{	0.000000, -1.000000, 0.017857	},
	{	0.000000, -1.000000, 0.017857	},{	0.044643, -0.857143, 0.035714	},{	0.053571, -0.857143, 0.033482	},
	{	0.053571, -0.857143, 0.015625	},{	0.044643, -0.857143, 0.017857	},{	0.044643, -0.928571, 0.028571	},
	{	0.053571, -0.928571, 0.026339	},{	0.053571, -0.928571, 0.008482	},{	0.044643, -0.928571, 0.010714	},
	{	0.053571, -0.999643, 0.017857	},{	0.066964, -0.999643, 0.017857	},{	0.067321, -0.999643, 0.000000	},
	{	0.053929, -0.999643, 0.000000	},{	0.000000, -1.000000, 0.017857	},{	0.000000, -1.000000, 0.017857	},
	{	0.000357, -1.000000, 0.000000	},{	0.000357, -1.000000, 0.000000	},{	0.044643, -0.857143, 0.017857	},
	{	0.008929, -0.857143, 0.026786	},{	-0.008929, -0.857143, 0.026786	},{	-0.044643, -0.857143, 0.017857	},
	{	0.044643, -0.928571, 0.010714	},{	0.008929, -0.928571, 0.019643	},{	-0.008929, -0.928571, 0.019643	},
	{	-0.044643, -0.928571, 0.010714	},{	0.053929, -0.999643, 0.000000	},{	0.000357, -0.999643, 0.000000	},
	{	-0.000357, -0.999643, 0.000000	},{	-0.053929, -0.999643, 0.000000	},{	0.000357, -1.000000, 0.000000	},
	{	0.000357, -1.000000, 0.000000	},{	-0.000357, -1.000000, 0.000000	},{	-0.000357, -1.000000, 0.000000	},
	{	-0.044643, -0.857143, 0.017857	},{	-0.053571, -0.857143, 0.015625	},{	-0.053571, -0.857143, 0.033482	},
	{	-0.044643, -0.857143, 0.035714	},{	-0.044643, -0.928571, 0.010714	},{	-0.053571, -0.928571, 0.008482	},
	{	-0.053571, -0.928571, 0.026339	},{	-0.044643, -0.928571, 0.028571	},{	-0.053929, -0.999643, 0.000000	},
	{	-0.067321, -0.999643, 0.000000	},{	-0.067500, -0.999643, 0.017857	},{	-0.053929, -0.999643, 0.017857	},
	{	-0.000357, -1.000000, 0.000000	},{	-0.000357, -1.000000, 0.000000	},{	-0.000536, -1.000000, 0.017857	},
	{	-0.000357, -1.000000, 0.017857	}};

#endif // !defined(NewellTeasetData.h)