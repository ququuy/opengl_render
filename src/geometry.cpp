// Project Header
#include "geometry.h"

// --------------------------------------------------------------------------------
// Create Blade of Grass - Positions, Normals, Colours
void createBlade(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
	// ---------- Positions ----------
	std::vector<glm::vec4> positions = std::vector<glm::vec4> {
		glm::vec4( 0.105482,  71.0945, -32.9529, 1.0), glm::vec4( 0.233865,  65.7234, -27.8888, 1.0), glm::vec4( 0.896803,  65.5832, -28.2526, 1.0), glm::vec4(-0.487749,  65.2987, -27.8997, 1.0), 
		glm::vec4( 0.233865,  65.7234, -27.8888, 1.0), glm::vec4( 0.105482,  71.0945, -32.9529, 1.0), glm::vec4( 0.233865,  65.7234, -27.8888, 1.0), glm::vec4( -0.02236,  57.8201, -20.8453, 1.0), 
		glm::vec4(  1.31645,  57.7019, -21.3651, 1.0), glm::vec4( 0.896803,  65.5832, -28.2526, 1.0), glm::vec4(-0.487749,  65.2987, -27.8997, 1.0), glm::vec4(-0.924761,  57.3641, -21.2652, 1.0), 
		glm::vec4( -0.02236,  57.8201, -20.8453, 1.0), glm::vec4( 0.233865,  65.7234, -27.8888, 1.0), glm::vec4( -0.02236,  57.8201, -20.8453, 1.0), glm::vec4(-0.518637,  45.5033, -12.6912, 1.0), 
		glm::vec4(  1.00899,  45.3367, -12.9401, 1.0), glm::vec4(  1.31645,  57.7019, -21.3651, 1.0), glm::vec4(-0.924761,  57.3641, -21.2652, 1.0), glm::vec4( -1.63826,  44.9744, -13.3583, 1.0), 
		glm::vec4(-0.518637,  45.5033, -12.6912, 1.0), glm::vec4( -0.02236,  57.8201, -20.8453, 1.0), glm::vec4(-0.726309,  39.9304, -9.79272, 1.0), glm::vec4( 0.791151,  39.8283, -9.99038, 1.0), 
		glm::vec4(  1.00899,  45.3367, -12.9401, 1.0), glm::vec4(-0.518637,  45.5033, -12.6912, 1.0), glm::vec4( -1.63826,  44.9744, -13.3583, 1.0), glm::vec4( -1.90059,  39.5531, -10.6465, 1.0), 
		glm::vec4(-0.726309,  39.9304, -9.79272, 1.0), glm::vec4(-0.518637,  45.5033, -12.6912, 1.0), glm::vec4(-0.726309,  39.9304, -9.79272, 1.0), glm::vec4( -1.06588,  25.5589,  -4.0642, 1.0), 
		glm::vec4( 0.382765,   25.488, -4.25906, 1.0), glm::vec4( 0.791151,  39.8283, -9.99038, 1.0), glm::vec4( -1.90059,  39.5531, -10.6465, 1.0), glm::vec4( -1.91341,  25.1813, -5.10192, 1.0), 
		glm::vec4( -1.06588,  25.5589,  -4.0642, 1.0), glm::vec4(-0.726309,  39.9304, -9.79272, 1.0), glm::vec4(-0.250998,   4.5732, 0.290198, 1.0), glm::vec4( 0.001138,  -0.1593, 0.583624, 1.0), 
		glm::vec4( 0.861219,-0.166096, 0.082775, 1.0), glm::vec4(  0.89546,  4.53411,-0.081083, 1.0), glm::vec4( -1.20253,  10.1455, -1.60109, 1.0), glm::vec4(-0.745989,  4.46367,-0.846991, 1.0), 
		glm::vec4(-0.250998,   4.5732, 0.290198, 1.0), glm::vec4(-0.645254,  10.4881,-0.465713, 1.0), glm::vec4(  0.89546,  4.53411,-0.081083, 1.0), glm::vec4( 0.753828,  10.4848,-0.735277, 1.0), 
		glm::vec4(-0.645254,  10.4881,-0.465713, 1.0), glm::vec4(-0.250998,   4.5732, 0.290198, 1.0), glm::vec4(-0.273912,-0.332354,-0.443628, 1.0), glm::vec4( 0.001138,  -0.1593, 0.583624, 1.0), 
		glm::vec4(-0.250998,   4.5732, 0.290198, 1.0), glm::vec4(-0.745989,  4.46367,-0.846991, 1.0), glm::vec4( -1.06588,  25.5589,  -4.0642, 1.0), glm::vec4(-0.645254,  10.4881,-0.465713, 1.0), 
		glm::vec4( 0.753828,  10.4848,-0.735277, 1.0), glm::vec4( 0.382765,   25.488, -4.25906, 1.0), glm::vec4( -1.91341,  25.1813, -5.10192, 1.0), glm::vec4( -1.20253,  10.1455, -1.60109, 1.0), 
		glm::vec4(-0.645254,  10.4881,-0.465713, 1.0), glm::vec4( -1.06588,  25.5589,  -4.0642, 1.0), glm::vec4( -1.91341,  25.1813, -5.10192, 1.0), glm::vec4(-0.970837,  25.4012, -4.40519, 1.0), 
		glm::vec4(-0.550213,  10.3304,-0.806704, 1.0), glm::vec4( -1.20253,  10.1455, -1.60109, 1.0), glm::vec4(-0.970837,  25.4012, -4.40519, 1.0), glm::vec4( 0.382765,   25.488, -4.25906, 1.0), 
		glm::vec4( 0.753828,  10.4848,-0.735277, 1.0), glm::vec4(-0.550213,  10.3304,-0.806704, 1.0), glm::vec4(-0.273912,-0.332354,-0.443628, 1.0), glm::vec4(-0.745989,  4.46367,-0.846991, 1.0), 
		glm::vec4(-0.155957,   4.4155,-0.050793, 1.0), glm::vec4( 0.096179,   -0.317, 0.242633, 1.0), glm::vec4(  0.89546,  4.53411,-0.081083, 1.0), glm::vec4(-0.155957,   4.4155,-0.050793, 1.0), 
		glm::vec4(-0.550213,  10.3304,-0.806704, 1.0), glm::vec4( 0.753828,  10.4848,-0.735277, 1.0), glm::vec4( -1.20253,  10.1455, -1.60109, 1.0), glm::vec4(-0.550213,  10.3304,-0.806704, 1.0), 
		glm::vec4(-0.155957,   4.4155,-0.050793, 1.0), glm::vec4(-0.745989,  4.46367,-0.846991, 1.0), glm::vec4(-0.155957,   4.4155,-0.050793, 1.0), glm::vec4(  0.89546,  4.53411,-0.081083, 1.0), 
		glm::vec4( 0.861219,-0.166096, 0.082775, 1.0), glm::vec4( 0.096179,   -0.317, 0.242633, 1.0), glm::vec4( -1.90059,  39.5531, -10.6465, 1.0), glm::vec4(-0.631268,  39.7727, -10.1337, 1.0), 
		glm::vec4(-0.970837,  25.4012, -4.40519, 1.0), glm::vec4( -1.91341,  25.1813, -5.10192, 1.0), glm::vec4(-0.631268,  39.7727, -10.1337, 1.0), glm::vec4( 0.791151,  39.8283, -9.99038, 1.0), 
		glm::vec4( 0.382765,   25.488, -4.25906, 1.0), glm::vec4(-0.970837,  25.4012, -4.40519, 1.0), glm::vec4( -1.63826,  44.9744, -13.3583, 1.0), glm::vec4(-0.423596,  45.3456, -13.0322, 1.0), 
		glm::vec4(-0.631268,  39.7727, -10.1337, 1.0), glm::vec4( -1.90059,  39.5531, -10.6465, 1.0), glm::vec4(-0.631268,  39.7727, -10.1337, 1.0), glm::vec4(-0.423596,  45.3456, -13.0322, 1.0), 
		glm::vec4(  1.00899,  45.3367, -12.9401, 1.0), glm::vec4( 0.791151,  39.8283, -9.99038, 1.0), glm::vec4(-0.924761,  57.3641, -21.2652, 1.0), glm::vec4( 0.072681,  57.6624, -21.1863, 1.0), 
		glm::vec4(-0.423596,  45.3456, -13.0322, 1.0), glm::vec4( -1.63826,  44.9744, -13.3583, 1.0), glm::vec4( 0.072681,  57.6624, -21.1863, 1.0), glm::vec4(  1.31645,  57.7019, -21.3651, 1.0), 
		glm::vec4(  1.00899,  45.3367, -12.9401, 1.0), glm::vec4(-0.423596,  45.3456, -13.0322, 1.0), glm::vec4(-0.487749,  65.2987, -27.8997, 1.0), glm::vec4( 0.328906,  65.5657, -28.2298, 1.0), 
		glm::vec4( 0.072681,  57.6624, -21.1863, 1.0), glm::vec4(-0.924761,  57.3641, -21.2652, 1.0), glm::vec4( 0.328906,  65.5657, -28.2298, 1.0), glm::vec4( 0.896803,  65.5832, -28.2526, 1.0), 
		glm::vec4(  1.31645,  57.7019, -21.3651, 1.0), glm::vec4( 0.072681,  57.6624, -21.1863, 1.0), glm::vec4(-0.487749,  65.2987, -27.8997, 1.0), glm::vec4( 0.105482,  71.0945, -32.9529, 1.0), 
		glm::vec4( 0.328906,  65.5657, -28.2298, 1.0), glm::vec4( 0.105482,  71.0945, -32.9529, 1.0), glm::vec4( 0.896803,  65.5832, -28.2526, 1.0), glm::vec4( 0.328906,  65.5657, -28.2298, 1.0), 
		glm::vec4( 0.001138,  -0.1593, 0.583624, 1.0), glm::vec4(-0.273912,-0.332354,-0.443628, 1.0), glm::vec4( 0.096179,   -0.317, 0.242633, 1.0), glm::vec4( 0.861219,-0.166096, 0.082775, 1.0), 
		glm::vec4( 0.001138,  -0.1593, 0.583624, 1.0), glm::vec4( 0.096179,   -0.317, 0.242633, 1.0)
	};

	// ---------- Normals ----------
	std::vector<glm::vec4> normals = std::vector<glm::vec4> {
		glm::vec4(   0.4766,   0.6091,   0.6339, 0.0), glm::vec4(   0.4253,   0.6123,   0.6665, 0.0), glm::vec4(   0.4341,   0.6119,   0.6611, 0.0), glm::vec4(  -0.4505,   0.6004,   0.6608, 0.0), 
		glm::vec4(  -0.4221,   0.6128,   0.6681, 0.0), glm::vec4(  -0.3807,   0.6295,   0.6773, 0.0), glm::vec4(   0.4253,   0.6123,   0.6665, 0.0), glm::vec4(   0.3206,   0.5697,   0.7568, 0.0), 
		glm::vec4(   0.3329,   0.5784,   0.7447, 0.0), glm::vec4(   0.4341,   0.6119,   0.6611, 0.0), glm::vec4(  -0.4505,   0.6004,   0.6608, 0.0), glm::vec4(  -0.5421,   0.5185,   0.6613, 0.0), 
		glm::vec4(  -0.5339,   0.5288,   0.6598, 0.0), glm::vec4(  -0.4221,   0.6128,   0.6681, 0.0), glm::vec4(   0.3206,   0.5697,   0.7568, 0.0), glm::vec4(   0.2182,   0.4938,   0.8417, 0.0), 
		glm::vec4(   0.2195,   0.4948,   0.8408, 0.0), glm::vec4(   0.3329,   0.5784,   0.7447, 0.0), glm::vec4(  -0.5421,   0.5185,   0.6613, 0.0), glm::vec4(   -0.599,   0.4185,   0.6827, 0.0), 
		glm::vec4(  -0.5969,   0.4248,   0.6806, 0.0), glm::vec4(  -0.5339,   0.5288,   0.6598, 0.0), glm::vec4(   0.1557,   0.4093,    0.899, 0.0), glm::vec4(   0.1561,   0.4106,   0.8983, 0.0), 
		glm::vec4(   0.2195,   0.4948,   0.8408, 0.0), glm::vec4(   0.2182,   0.4938,   0.8417, 0.0), glm::vec4(   -0.599,   0.4185,   0.6827, 0.0), glm::vec4(  -0.6628,    0.323,   0.6756, 0.0), 
		glm::vec4(  -0.6618,   0.3241,    0.676, 0.0), glm::vec4(  -0.5969,   0.4248,   0.6806, 0.0), glm::vec4(   0.1557,   0.4093,    0.899, 0.0), glm::vec4(   0.1531,   0.2986,    0.942, 0.0), 
		glm::vec4(   0.1531,   0.2981,   0.9422, 0.0), glm::vec4(   0.1561,   0.4106,   0.8983, 0.0), glm::vec4(  -0.6628,    0.323,   0.6756, 0.0), glm::vec4(  -0.7876,   0.1777,   0.5901, 0.0), 
		glm::vec4(  -0.7849,    0.181,   0.5925, 0.0), glm::vec4(  -0.6618,   0.3241,    0.676, 0.0), glm::vec4(   0.3199,   0.0912,    0.943, 0.0), glm::vec4(   0.3991,   0.0536,   0.9154, 0.0), 
		glm::vec4(   0.3991,   0.0536,   0.9154, 0.0), glm::vec4(   0.3238,   0.0894,   0.9419, 0.0), glm::vec4(   -0.882,   0.0372,   0.4698, 0.0), glm::vec4(  -0.9234,  -0.0286,   0.3827, 0.0), 
		glm::vec4(  -0.9241,  -0.0293,    0.381, 0.0), glm::vec4(  -0.8792,   0.0423,   0.4746, 0.0), glm::vec4(   0.3238,   0.0894,   0.9419, 0.0), glm::vec4(   0.2036,    0.179,   0.9626, 0.0), 
		glm::vec4(   0.2034,   0.1793,   0.9625, 0.0), glm::vec4(   0.3199,   0.0912,    0.943, 0.0), glm::vec4(  -0.9392,  -0.0465,   0.3402, 0.0), glm::vec4(  -0.9392,  -0.0465,   0.3402, 0.0), 
		glm::vec4(  -0.9241,  -0.0293,    0.381, 0.0), glm::vec4(  -0.9234,  -0.0286,   0.3827, 0.0), glm::vec4(   0.1531,   0.2986,    0.942, 0.0), glm::vec4(   0.2034,   0.1793,   0.9625, 0.0), 
		glm::vec4(   0.2036,    0.179,   0.9626, 0.0), glm::vec4(   0.1531,   0.2981,   0.9422, 0.0), glm::vec4(  -0.7876,   0.1777,   0.5901, 0.0), glm::vec4(   -0.882,   0.0372,   0.4698, 0.0), 
		glm::vec4(  -0.8792,   0.0423,   0.4746, 0.0), glm::vec4(  -0.7849,    0.181,   0.5925, 0.0), glm::vec4(    0.604,  -0.2337,  -0.7619, 0.0), glm::vec4(   0.3681,  -0.2759,  -0.8879, 0.0), 
		glm::vec4(   0.4349,  -0.1363,  -0.8901, 0.0), glm::vec4(   0.7447,  -0.0815,  -0.6624, 0.0), glm::vec4(   0.3681,  -0.2759,  -0.8879, 0.0), glm::vec4(    0.108,   -0.301,  -0.9475, 0.0), 
		glm::vec4(   0.0673,   -0.175,  -0.9823, 0.0), glm::vec4(   0.4349,  -0.1363,  -0.8901, 0.0), glm::vec4(   0.8393,   0.0241,  -0.5431, 0.0), glm::vec4(   0.8121,  -0.0018,  -0.5836, 0.0), 
		glm::vec4(     0.44,  -0.0456,  -0.8968, 0.0), glm::vec4(    0.452,  -0.0141,  -0.8919, 0.0), glm::vec4(  -0.0286,   -0.086,  -0.9959, 0.0), glm::vec4(     0.44,  -0.0456,  -0.8968, 0.0), 
		glm::vec4(   0.4349,  -0.1363,  -0.8901, 0.0), glm::vec4(   0.0673,   -0.175,  -0.9823, 0.0), glm::vec4(   0.7447,  -0.0815,  -0.6624, 0.0), glm::vec4(   0.4349,  -0.1363,  -0.8901, 0.0), 
		glm::vec4(     0.44,  -0.0456,  -0.8968, 0.0), glm::vec4(   0.8121,  -0.0018,  -0.5836, 0.0), glm::vec4(     0.44,  -0.0456,  -0.8968, 0.0), glm::vec4(  -0.0286,   -0.086,  -0.9959, 0.0), 
		glm::vec4(  -0.0966,  -0.0504,   -0.994, 0.0), glm::vec4(    0.452,  -0.0141,  -0.8919, 0.0), glm::vec4(   0.4431,   -0.378,  -0.8129, 0.0), glm::vec4(   0.2734,  -0.4058,  -0.8721, 0.0), 
		glm::vec4(   0.3681,  -0.2759,  -0.8879, 0.0), glm::vec4(    0.604,  -0.2337,  -0.7619, 0.0), glm::vec4(   0.2734,  -0.4058,  -0.8721, 0.0), glm::vec4(   0.0976,  -0.4206,   -0.902, 0.0), 
		glm::vec4(    0.108,   -0.301,  -0.9475, 0.0), glm::vec4(   0.3681,  -0.2759,  -0.8879, 0.0), glm::vec4(   0.3467,  -0.4773,  -0.8075, 0.0), glm::vec4(   0.1858,  -0.5068,  -0.8418, 0.0), 
		glm::vec4(   0.2734,  -0.4058,  -0.8721, 0.0), glm::vec4(   0.4431,   -0.378,  -0.8129, 0.0), glm::vec4(   0.2734,  -0.4058,  -0.8721, 0.0), glm::vec4(   0.1858,  -0.5068,  -0.8418, 0.0), 
		glm::vec4(   0.0303,  -0.5133,  -0.8576, 0.0), glm::vec4(   0.0976,  -0.4206,   -0.902, 0.0), glm::vec4(   0.2188,  -0.5865,  -0.7798, 0.0), glm::vec4(   0.0745,  -0.6089,  -0.7898, 0.0), 
		glm::vec4(   0.1858,  -0.5068,  -0.8418, 0.0), glm::vec4(   0.3467,  -0.4773,  -0.8075, 0.0), glm::vec4(   0.0745,  -0.6089,  -0.7898, 0.0), glm::vec4(   -0.043,  -0.6138,  -0.7883, 0.0), 
		glm::vec4(   0.0303,  -0.5133,  -0.8576, 0.0), glm::vec4(   0.1858,  -0.5068,  -0.8418, 0.0), glm::vec4(   0.0362,  -0.6542,  -0.7554, 0.0), glm::vec4(  -0.0318,  -0.6544,  -0.7555, 0.0), 
		glm::vec4(   0.0745,  -0.6089,  -0.7898, 0.0), glm::vec4(   0.2188,  -0.5865,  -0.7798, 0.0), glm::vec4(  -0.0318,  -0.6544,  -0.7555, 0.0), glm::vec4(  -0.0369,  -0.6556,  -0.7542, 0.0), 
		glm::vec4(   -0.043,  -0.6138,  -0.7883, 0.0), glm::vec4(   0.0745,  -0.6089,  -0.7898, 0.0), glm::vec4(   0.0362,  -0.6542,  -0.7554, 0.0), glm::vec4(  -0.0585,  -0.6498,  -0.7579, 0.0), 
		glm::vec4(  -0.0318,  -0.6544,  -0.7555, 0.0), glm::vec4(  -0.0585,  -0.6498,  -0.7579, 0.0), glm::vec4(  -0.0369,  -0.6556,  -0.7542, 0.0), glm::vec4(  -0.0318,  -0.6544,  -0.7555, 0.0), 
		glm::vec4(  -0.0268,  -0.9101,   0.4135, 0.0), glm::vec4(  -0.4568,  -0.8491,   0.2653, 0.0), glm::vec4(  -0.1396,   -0.913,   0.3833, 0.0), glm::vec4(   0.2638,  -0.8454,   0.4645, 0.0), 
		glm::vec4(  -0.0268,  -0.9101,   0.4135, 0.0), glm::vec4(  -0.1396,   -0.913,   0.3833, 0.0)
	};

	for(int i = 0; i < positions.size(); ++i) {
		buffer.push_back(positions[i]);
		buffer.push_back(normals[i]);
		buffer.push_back(glm::vec4(0.375471, 0.500000, 0.219608, 0));
	}

	// ---------- Indexes ----------
	indexes = std::vector<glm::ivec3> {
		glm::ivec3(  0,  1,  2), glm::ivec3(  3,  4,  5), glm::ivec3(  6,  7,  8), glm::ivec3(  6,  8,  9), 
		glm::ivec3( 10, 11, 12), glm::ivec3( 10, 12, 13), glm::ivec3( 14, 15, 16), glm::ivec3( 14, 16, 17), 
		glm::ivec3( 18, 19, 20), glm::ivec3( 18, 20, 21), glm::ivec3( 22, 23, 24), glm::ivec3( 22, 24, 25), 
		glm::ivec3( 26, 27, 28), glm::ivec3( 26, 28, 29), glm::ivec3( 30, 31, 32), glm::ivec3( 30, 32, 33), 
		glm::ivec3( 34, 35, 36), glm::ivec3( 34, 36, 37), glm::ivec3( 38, 39, 40), glm::ivec3( 38, 40, 41), 
		glm::ivec3( 42, 43, 44), glm::ivec3( 42, 44, 45), glm::ivec3( 46, 47, 48), glm::ivec3( 46, 48, 49), 
		glm::ivec3( 50, 51, 52), glm::ivec3( 50, 52, 53), glm::ivec3( 54, 55, 56), glm::ivec3( 54, 56, 57), 
		glm::ivec3( 58, 59, 60), glm::ivec3( 58, 60, 61), glm::ivec3( 62, 63, 64), glm::ivec3( 62, 64, 65), 
		glm::ivec3( 66, 67, 68), glm::ivec3( 66, 68, 69), glm::ivec3( 70, 71, 72), glm::ivec3( 70, 72, 73), 
		glm::ivec3( 74, 75, 76), glm::ivec3( 74, 76, 77), glm::ivec3( 78, 79, 80), glm::ivec3( 78, 80, 81), 
		glm::ivec3( 82, 83, 84), glm::ivec3( 82, 84, 85), glm::ivec3( 86, 87, 88), glm::ivec3( 86, 88, 89), 
		glm::ivec3( 90, 91, 92), glm::ivec3( 90, 92, 93), glm::ivec3( 94, 95, 96), glm::ivec3( 94, 96, 97), 
		glm::ivec3( 98, 99,100), glm::ivec3( 98,100,101), glm::ivec3(102,103,104), glm::ivec3(102,104,105), 
		glm::ivec3(106,107,108), glm::ivec3(106,108,109), glm::ivec3(110,111,112), glm::ivec3(110,112,113), 
		glm::ivec3(114,115,116), glm::ivec3(114,116,117), glm::ivec3(118,119,120), glm::ivec3(121,122,123), 
		glm::ivec3(124,125,126), glm::ivec3(127,128,129)
	};

	// // Top - 0
	// buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  1.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Top - Left - 1
	// buffer.push_back(glm::vec4(-0.03f, 0.9f,  0.01f, 1.0f));
	// buffer.push_back(glm::vec4(-0.5f,  0.0f,  0.5f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Top - Right - 2
	// buffer.push_back(glm::vec4( 0.03f, 0.9f,  0.01f, 1.0f));
	// buffer.push_back(glm::vec4( 0.5f,  0.0f,  0.5f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Top - Back - 3
	// buffer.push_back(glm::vec4( 0.0f,  0.9f, -0.01f, 1.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Mid - Left - 4
	// buffer.push_back(glm::vec4(-0.05f, 0.7f,  0.01f, 1.0f));
	// buffer.push_back(glm::vec4(-0.5f,  0.0f,  0.5f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Mid - Right - 5
	// buffer.push_back(glm::vec4( 0.05f, 0.7f,  0.01f, 1.0f));
	// buffer.push_back(glm::vec4( 0.5f,  0.0f,  0.5f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Mid - Back - 6
	// buffer.push_back(glm::vec4( 0.0f,  0.7f, -0.01f, 1.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Bottom - Left - 7
	// buffer.push_back(glm::vec4(-0.05f, 0.0f,  0.01f, 1.0f));
	// buffer.push_back(glm::vec4(-0.5f,  0.0f,  0.5f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Bottom - Right - 8
	// buffer.push_back(glm::vec4( 0.05f, 0.0f,  0.01f, 1.0f));
	// buffer.push_back(glm::vec4( 0.5f,  0.0f,  0.5f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Bottom - Back - 9
	// buffer.push_back(glm::vec4( 0.0f,  0.0f, -0.01f, 1.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f));
	// buffer.push_back(glm::vec4( 0.0f,  0.48f, 0.05f, 0.0f));

	// // Indexes
	// indexes.push_back(glm::ivec3(0, 1, 2));
	// indexes.push_back(glm::ivec3(0, 2, 3));
	// indexes.push_back(glm::ivec3(0, 3, 1));

	// indexes.push_back(glm::ivec3(1, 4, 5));
	// indexes.push_back(glm::ivec3(1, 5, 2));
	// indexes.push_back(glm::ivec3(2, 5, 6));
	// indexes.push_back(glm::ivec3(2, 6, 3));
	// indexes.push_back(glm::ivec3(3, 6, 4));
	// indexes.push_back(glm::ivec3(3, 4, 1));

	// indexes.push_back(glm::ivec3(4, 7, 8));
	// indexes.push_back(glm::ivec3(4, 8, 5));
	// indexes.push_back(glm::ivec3(5, 8, 9));
	// indexes.push_back(glm::ivec3(5, 9, 6));
	// indexes.push_back(glm::ivec3(6, 9, 7));
	// indexes.push_back(glm::ivec3(6, 7, 4));
}



// --------------------------------------------------------------------------------
// Create River - Positions, Normals
void createRiver(std::vector<glm::vec4> &buffer, std::vector<glm::ivec3> &indexes) {
    // Left-Front - 0
    buffer.push_back(glm::vec4(-1.0f,  0.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Right-Front - 1
    buffer.push_back(glm::vec4( 1.0f,  0.0f,  1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Right-Back - 2
    buffer.push_back(glm::vec4( 1.0f,  0.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Left-Back - 3
    buffer.push_back(glm::vec4(-1.0f,  0.0f, -1.0f,  1.0f));
    buffer.push_back(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f));

    // Front
    indexes.push_back(glm::ivec3(0, 1, 2));
    indexes.push_back(glm::ivec3(0, 2, 3));
}


// --------------------------------------------------------------------------------
// Create Quadrangles with Positions and Colours
void createQuads(std::vector<glm::vec4> &buffer, std::vector<glm::ivec4> &indexes, int X, int Z) {
    // Rows
    for(int iz = 0; iz < Z+1; iz++) {
        // Columns
        for(int ix = 0; ix < X+1; ix++) {
            // Vertex
            buffer.push_back(glm::vec4(-1.0f + ix * 2.0f/X, -1.0f, 1.0f - iz * 2.0f/Z, 1.0f));

            // Colour
            buffer.push_back(glm::vec4( ix * 1.0f / X,  iz * 1.0f/Z,  0.0f,  0.0f));
        }
    }

    // Index
    for(int iz = 0; iz < Z; iz++) {
        for(int ix = 0; ix < X; ix++) {
            int k = iz * (X+1) + ix;
            indexes.push_back(glm::ivec4(k, k+1, k + (X + 1) + 1, k + (X + 1)));
        }
    }
}

float uniform() {
    return rand() / (float)RAND_MAX;
}

float uniform(float min, float max) {
    return uniform() * (max - min) + min;
}

float f(int s, int X) {
    // return 0.0;
    return s / (float)X;
    // return 0.1 * s / (float)X;
    // if(s > X / 16) {
    // 	return 0.0f;
    // } else {
    // 	return s / (float)(X);
    // }
}

// --------------------------------------------------------------------------------
// Create Quadrangles with Positions and Colours
float* DiamondSquare(int X, int Y) {
    // Allocate Memory
    float *height = new float[X*Y];

    for(int k = 0; k < X*Y; k++) {
        height[k] = 0.0f;
    }

    int seed = ((int)(glfwGetTime() * 1000));
    std::cout << seed << std::endl;
    srand(seed);

    // srand(((int)glfwGetTime() * 1000));

    // Initialise Corner values
    // height[   0 *X +   0] = uniform(0.0f, 1.0f);
    // height[   0 *X + X-1] = uniform(0.0f, 1.0f);
    // height[(Y-1)*X +   0] = uniform(0.0f, 1.0f);
    // height[(Y-1)*X + X-1] = uniform(0.0f, 1.0f);

    height[   0 *X +   0] = uniform(0.5f, 1.0f);
    height[   0 *X + X-1] = uniform(0.5f, 1.0f);
    height[(Y-1)*X +   0] = uniform(0.5f, 1.0f);
    height[(Y-1)*X + X-1] = uniform(0.5f, 1.0f);

    for(int s = Y/2; s >= 1; s /= 2) {
        // Diamond
        for(int iy = s; iy < Y; iy += s*2) {
            for(int ix = s; ix < X; ix += s*2) {
                height[iy*X + ix] = (height[(iy-s)*X + (ix-s)] + height[(iy-s)*X + (ix+s)] + height[(iy+s)*X + (ix-s)] + height[(iy+s)*X + (ix+s)]) / 4.0f + uniform(-1.0f, 1.0f) * f(s, X);

                height[iy*X + ix] = glm::clamp(height[iy*X + ix], 0.0f, 1.0f);
            }
        }

        // Square
        for(int iy = 0; iy < Y; iy += s) {
            for(int ix = 0; ix < X; ix += s) {
                // Skip Diamond points
                // if((iy == ix) || (iy == X-ix)) continue;
                if((abs(ix - iy) % (2*s)) == 0) continue;

                // Check boundaries
                if(iy == 0) {
                    height[iy*X + ix] = (                        height[iy*X + (ix-s)] + height[iy*X + (ix+s)] + height[(iy+s)*X + ix]) / 3.0f + uniform(-1.0f, 1.0f) * f(s, X);
                } else if(iy == Y-1) {
                    height[iy*X + ix] = (height[(iy-s)*X + ix] + height[iy*X + (ix-s)] + height[iy*X + (ix+s)]                        ) / 3.0f + uniform(-1.0f, 1.0f) * f(s, X);
                } else if(ix == 0) {
                    height[iy*X + ix] = (height[(iy-s)*X + ix] +                       + height[iy*X + (ix+s)] + height[(iy+s)*X + ix]) / 3.0f + uniform(-1.0f, 1.0f) * f(s, X);
                } else if(ix == X-1) {
                    height[iy*X + ix] = (height[(iy-s)*X + ix] + height[iy*X + (ix-s)] +                       + height[(iy+s)*X + ix]) / 3.0f + uniform(-1.0f, 1.0f) * f(s, X);
                } else {
                    height[iy*X + ix] = (height[(iy-s)*X + ix] + height[iy*X + (ix-s)] + height[iy*X + (ix+s)] + height[(iy+s)*X + ix]) / 4.0f + uniform(-1.0f, 1.0f) * f(s, X);
                }

                height[iy*X + ix] = glm::clamp(height[iy*X + ix], 0.0f, 1.0f);
            }
        }
    }

    return height;
}

// --------------------------------------------------------------------------------
// Generate Normals from height map
glm::vec3* generateNormals(const float *height, float height_scale, int X, int Y) {
    // Normal map
    glm::vec3 *normals = new glm::vec3[X * Y];

    // For each row
    for(int iy = 0; iy < Y; iy++) {
        int ym1 = (iy ==   0) ? iy : iy - 1;
        int yp1 = (iy == Y-1) ? iy : iy + 1;

        // For each colum
        for(int ix = 0; ix < X; ix++) {
            int xm1 = (ix ==   0) ? ix : ix - 1;
            int xp1 = (ix == X-1) ? ix : ix + 1;

            // Surface Normal
            glm::vec3 normal;

            // Calculate Normal - Sobel Filter
            float dfdx = (X / 8.0f) * height_scale * -(height[yp1*X + xm1]-height[yp1*X + xp1] + (2.0f)*(height[ iy*X + xm1]-height[ iy*X + xp1]) + (height[ym1*X + xm1]-height[ym1*X + xp1]));
            float dfdz = (Y / 8.0f) * height_scale * -(height[ym1*X + xm1]-height[yp1*X + xm1] + (2.0f)*(height[ym1*X +  ix]-height[yp1*X +  ix]) + (height[ym1*X + xp1]-height[yp1*X + xp1]));
            // float dfdx = -(height[yp1*X + xm1]-height[yp1*X + xp1] + (2.0f)*(height[ iy*X + xm1]-height[ iy*X + xp1]) + (height[ym1*X + xm1]-height[ym1*X + xp1]));
            // float dfdz = -(height[ym1*X + xm1]-height[yp1*X + xm1] + (2.0f)*(height[ym1*X +  ix]-height[yp1*X +  ix]) + (height[ym1*X + xp1]-height[yp1*X + xp1]));

            normal = glm::vec3(-dfdx, 1.0, dfdz);
            // normal = glm::vec3(0.0f, 1.0f, 0.0f) - glm::vec3(dfdx, 0.0f, 0.0f) - glm::vec3(0.0f, 0.0f, dfdz);
            // float y = 1.0f - sqrt(dfdx*dfdx + dfdz*dfdz);

            // normal = glm::vec3(-dfdx, y, -dfdz);

            // Normalise
            normal = normalize(normal);

            // Set normal
            normals[iy*X + ix] = normal;
        }
    }

    // Return normals
    return normals;
}
