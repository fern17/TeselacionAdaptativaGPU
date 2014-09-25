namespace TE {
const float terrain_positions[][2] = {
	{0, 0}, 
	{0.0625, 0}, 
	{0.125, 0}, 
	{0.1875, 0}, 
	{0.25, 0}, 
	{0.3125, 0}, 
	{0.375, 0}, 
	{0.4375, 0}, 
	{0.5, 0}, 
	{0.5625, 0}, 
	{0.625, 0}, 
	{0.6875, 0}, 
	{0.75, 0}, 
	{0.8125, 0}, 
	{0.875, 0}, 
	{0.9375, 0}, 
	{1, 0}, 
	{0, 0.0625}, 
	{0.0625, 0.0625}, 
	{0.125, 0.0625}, 
	{0.1875, 0.0625}, 
	{0.25, 0.0625}, 
	{0.3125, 0.0625}, 
	{0.375, 0.0625}, 
	{0.4375, 0.0625}, 
	{0.5, 0.0625}, 
	{0.5625, 0.0625}, 
	{0.625, 0.0625}, 
	{0.6875, 0.0625}, 
	{0.75, 0.0625}, 
	{0.8125, 0.0625}, 
	{0.875, 0.0625}, 
	{0.9375, 0.0625}, 
	{1, 0.0625}, 
	{0, 0.125}, 
	{0.0625, 0.125}, 
	{0.125, 0.125}, 
	{0.1875, 0.125}, 
	{0.25, 0.125}, 
	{0.3125, 0.125}, 
	{0.375, 0.125}, 
	{0.4375, 0.125}, 
	{0.5, 0.125}, 
	{0.5625, 0.125}, 
	{0.625, 0.125}, 
	{0.6875, 0.125}, 
	{0.75, 0.125}, 
	{0.8125, 0.125}, 
	{0.875, 0.125}, 
	{0.9375, 0.125}, 
	{1, 0.125}, 
	{0, 0.1875}, 
	{0.0625, 0.1875}, 
	{0.125, 0.1875}, 
	{0.1875, 0.1875}, 
	{0.25, 0.1875}, 
	{0.3125, 0.1875}, 
	{0.375, 0.1875}, 
	{0.4375, 0.1875}, 
	{0.5, 0.1875}, 
	{0.5625, 0.1875}, 
	{0.625, 0.1875}, 
	{0.6875, 0.1875}, 
	{0.75, 0.1875}, 
	{0.8125, 0.1875}, 
	{0.875, 0.1875}, 
	{0.9375, 0.1875}, 
	{1, 0.1875}, 
	{0, 0.25}, 
	{0.0625, 0.25}, 
	{0.125, 0.25}, 
	{0.1875, 0.25}, 
	{0.25, 0.25}, 
	{0.3125, 0.25}, 
	{0.375, 0.25}, 
	{0.4375, 0.25}, 
	{0.5, 0.25}, 
	{0.5625, 0.25}, 
	{0.625, 0.25}, 
	{0.6875, 0.25}, 
	{0.75, 0.25}, 
	{0.8125, 0.25}, 
	{0.875, 0.25}, 
	{0.9375, 0.25}, 
	{1, 0.25}, 
	{0, 0.3125}, 
	{0.0625, 0.3125}, 
	{0.125, 0.3125}, 
	{0.1875, 0.3125}, 
	{0.25, 0.3125}, 
	{0.3125, 0.3125}, 
	{0.375, 0.3125}, 
	{0.4375, 0.3125}, 
	{0.5, 0.3125}, 
	{0.5625, 0.3125}, 
	{0.625, 0.3125}, 
	{0.6875, 0.3125}, 
	{0.75, 0.3125}, 
	{0.8125, 0.3125}, 
	{0.875, 0.3125}, 
	{0.9375, 0.3125}, 
	{1, 0.3125}, 
	{0, 0.375}, 
	{0.0625, 0.375}, 
	{0.125, 0.375}, 
	{0.1875, 0.375}, 
	{0.25, 0.375}, 
	{0.3125, 0.375}, 
	{0.375, 0.375}, 
	{0.4375, 0.375}, 
	{0.5, 0.375}, 
	{0.5625, 0.375}, 
	{0.625, 0.375}, 
	{0.6875, 0.375}, 
	{0.75, 0.375}, 
	{0.8125, 0.375}, 
	{0.875, 0.375}, 
	{0.9375, 0.375}, 
	{1, 0.375}, 
	{0, 0.4375}, 
	{0.0625, 0.4375}, 
	{0.125, 0.4375}, 
	{0.1875, 0.4375}, 
	{0.25, 0.4375}, 
	{0.3125, 0.4375}, 
	{0.375, 0.4375}, 
	{0.4375, 0.4375}, 
	{0.5, 0.4375}, 
	{0.5625, 0.4375}, 
	{0.625, 0.4375}, 
	{0.6875, 0.4375}, 
	{0.75, 0.4375}, 
	{0.8125, 0.4375}, 
	{0.875, 0.4375}, 
	{0.9375, 0.4375}, 
	{1, 0.4375}, 
	{0, 0.5}, 
	{0.0625, 0.5}, 
	{0.125, 0.5}, 
	{0.1875, 0.5}, 
	{0.25, 0.5}, 
	{0.3125, 0.5}, 
	{0.375, 0.5}, 
	{0.4375, 0.5}, 
	{0.5, 0.5}, 
	{0.5625, 0.5}, 
	{0.625, 0.5}, 
	{0.6875, 0.5}, 
	{0.75, 0.5}, 
	{0.8125, 0.5}, 
	{0.875, 0.5}, 
	{0.9375, 0.5}, 
	{1, 0.5}, 
	{0, 0.5625}, 
	{0.0625, 0.5625}, 
	{0.125, 0.5625}, 
	{0.1875, 0.5625}, 
	{0.25, 0.5625}, 
	{0.3125, 0.5625}, 
	{0.375, 0.5625}, 
	{0.4375, 0.5625}, 
	{0.5, 0.5625}, 
	{0.5625, 0.5625}, 
	{0.625, 0.5625}, 
	{0.6875, 0.5625}, 
	{0.75, 0.5625}, 
	{0.8125, 0.5625}, 
	{0.875, 0.5625}, 
	{0.9375, 0.5625}, 
	{1, 0.5625}, 
	{0, 0.625}, 
	{0.0625, 0.625}, 
	{0.125, 0.625}, 
	{0.1875, 0.625}, 
	{0.25, 0.625}, 
	{0.3125, 0.625}, 
	{0.375, 0.625}, 
	{0.4375, 0.625}, 
	{0.5, 0.625}, 
	{0.5625, 0.625}, 
	{0.625, 0.625}, 
	{0.6875, 0.625}, 
	{0.75, 0.625}, 
	{0.8125, 0.625}, 
	{0.875, 0.625}, 
	{0.9375, 0.625}, 
	{1, 0.625}, 
	{0, 0.6875}, 
	{0.0625, 0.6875}, 
	{0.125, 0.6875}, 
	{0.1875, 0.6875}, 
	{0.25, 0.6875}, 
	{0.3125, 0.6875}, 
	{0.375, 0.6875}, 
	{0.4375, 0.6875}, 
	{0.5, 0.6875}, 
	{0.5625, 0.6875}, 
	{0.625, 0.6875}, 
	{0.6875, 0.6875}, 
	{0.75, 0.6875}, 
	{0.8125, 0.6875}, 
	{0.875, 0.6875}, 
	{0.9375, 0.6875}, 
	{1, 0.6875}, 
	{0, 0.75}, 
	{0.0625, 0.75}, 
	{0.125, 0.75}, 
	{0.1875, 0.75}, 
	{0.25, 0.75}, 
	{0.3125, 0.75}, 
	{0.375, 0.75}, 
	{0.4375, 0.75}, 
	{0.5, 0.75}, 
	{0.5625, 0.75}, 
	{0.625, 0.75}, 
	{0.6875, 0.75}, 
	{0.75, 0.75}, 
	{0.8125, 0.75}, 
	{0.875, 0.75}, 
	{0.9375, 0.75}, 
	{1, 0.75}, 
	{0, 0.8125}, 
	{0.0625, 0.8125}, 
	{0.125, 0.8125}, 
	{0.1875, 0.8125}, 
	{0.25, 0.8125}, 
	{0.3125, 0.8125}, 
	{0.375, 0.8125}, 
	{0.4375, 0.8125}, 
	{0.5, 0.8125}, 
	{0.5625, 0.8125}, 
	{0.625, 0.8125}, 
	{0.6875, 0.8125}, 
	{0.75, 0.8125}, 
	{0.8125, 0.8125}, 
	{0.875, 0.8125}, 
	{0.9375, 0.8125}, 
	{1, 0.8125}, 
	{0, 0.875}, 
	{0.0625, 0.875}, 
	{0.125, 0.875}, 
	{0.1875, 0.875}, 
	{0.25, 0.875}, 
	{0.3125, 0.875}, 
	{0.375, 0.875}, 
	{0.4375, 0.875}, 
	{0.5, 0.875}, 
	{0.5625, 0.875}, 
	{0.625, 0.875}, 
	{0.6875, 0.875}, 
	{0.75, 0.875}, 
	{0.8125, 0.875}, 
	{0.875, 0.875}, 
	{0.9375, 0.875}, 
	{1, 0.875}, 
	{0, 0.9375}, 
	{0.0625, 0.9375}, 
	{0.125, 0.9375}, 
	{0.1875, 0.9375}, 
	{0.25, 0.9375}, 
	{0.3125, 0.9375}, 
	{0.375, 0.9375}, 
	{0.4375, 0.9375}, 
	{0.5, 0.9375}, 
	{0.5625, 0.9375}, 
	{0.625, 0.9375}, 
	{0.6875, 0.9375}, 
	{0.75, 0.9375}, 
	{0.8125, 0.9375}, 
	{0.875, 0.9375}, 
	{0.9375, 0.9375}, 
	{1, 0.9375}, 
	{0, 1}, 
	{0.0625, 1}, 
	{0.125, 1}, 
	{0.1875, 1}, 
	{0.25, 1}, 
	{0.3125, 1}, 
	{0.375, 1}, 
	{0.4375, 1}, 
	{0.5, 1}, 
	{0.5625, 1}, 
	{0.625, 1}, 
	{0.6875, 1}, 
	{0.75, 1}, 
	{0.8125, 1}, 
	{0.875, 1}, 
	{0.9375, 1}, 
	{1, 1}
};

const GLuint terrain_elements[][4] = {
	{0, 17, 18, 1}, 
	{1, 18, 19, 2}, 
	{2, 19, 20, 3}, 
	{3, 20, 21, 4}, 
	{4, 21, 22, 5}, 
	{5, 22, 23, 6}, 
	{6, 23, 24, 7}, 
	{7, 24, 25, 8}, 
	{8, 25, 26, 9}, 
	{9, 26, 27, 10}, 
	{10, 27, 28, 11}, 
	{11, 28, 29, 12}, 
	{12, 29, 30, 13}, 
	{13, 30, 31, 14}, 
	{14, 31, 32, 15}, 
	{15, 32, 33, 16}, 
	{17, 34, 35, 18}, 
	{18, 35, 36, 19}, 
	{19, 36, 37, 20}, 
	{20, 37, 38, 21}, 
	{21, 38, 39, 22}, 
	{22, 39, 40, 23}, 
	{23, 40, 41, 24}, 
	{24, 41, 42, 25}, 
	{25, 42, 43, 26}, 
	{26, 43, 44, 27}, 
	{27, 44, 45, 28}, 
	{28, 45, 46, 29}, 
	{29, 46, 47, 30}, 
	{30, 47, 48, 31}, 
	{31, 48, 49, 32}, 
	{32, 49, 50, 33}, 
	{34, 51, 52, 35}, 
	{35, 52, 53, 36}, 
	{36, 53, 54, 37}, 
	{37, 54, 55, 38}, 
	{38, 55, 56, 39}, 
	{39, 56, 57, 40}, 
	{40, 57, 58, 41}, 
	{41, 58, 59, 42}, 
	{42, 59, 60, 43}, 
	{43, 60, 61, 44}, 
	{44, 61, 62, 45}, 
	{45, 62, 63, 46}, 
	{46, 63, 64, 47}, 
	{47, 64, 65, 48}, 
	{48, 65, 66, 49}, 
	{49, 66, 67, 50}, 
	{51, 68, 69, 52}, 
	{52, 69, 70, 53}, 
	{53, 70, 71, 54}, 
	{54, 71, 72, 55}, 
	{55, 72, 73, 56}, 
	{56, 73, 74, 57}, 
	{57, 74, 75, 58}, 
	{58, 75, 76, 59}, 
	{59, 76, 77, 60}, 
	{60, 77, 78, 61}, 
	{61, 78, 79, 62}, 
	{62, 79, 80, 63}, 
	{63, 80, 81, 64}, 
	{64, 81, 82, 65}, 
	{65, 82, 83, 66}, 
	{66, 83, 84, 67}, 
	{68, 85, 86, 69}, 
	{69, 86, 87, 70}, 
	{70, 87, 88, 71}, 
	{71, 88, 89, 72}, 
	{72, 89, 90, 73}, 
	{73, 90, 91, 74}, 
	{74, 91, 92, 75}, 
	{75, 92, 93, 76}, 
	{76, 93, 94, 77}, 
	{77, 94, 95, 78}, 
	{78, 95, 96, 79}, 
	{79, 96, 97, 80}, 
	{80, 97, 98, 81}, 
	{81, 98, 99, 82}, 
	{82, 99, 100, 83}, 
	{83, 100, 101, 84}, 
	{85, 102, 103, 86}, 
	{86, 103, 104, 87}, 
	{87, 104, 105, 88}, 
	{88, 105, 106, 89}, 
	{89, 106, 107, 90}, 
	{90, 107, 108, 91}, 
	{91, 108, 109, 92}, 
	{92, 109, 110, 93}, 
	{93, 110, 111, 94}, 
	{94, 111, 112, 95}, 
	{95, 112, 113, 96}, 
	{96, 113, 114, 97}, 
	{97, 114, 115, 98}, 
	{98, 115, 116, 99}, 
	{99, 116, 117, 100}, 
	{100, 117, 118, 101}, 
	{102, 119, 120, 103}, 
	{103, 120, 121, 104}, 
	{104, 121, 122, 105}, 
	{105, 122, 123, 106}, 
	{106, 123, 124, 107}, 
	{107, 124, 125, 108}, 
	{108, 125, 126, 109}, 
	{109, 126, 127, 110}, 
	{110, 127, 128, 111}, 
	{111, 128, 129, 112}, 
	{112, 129, 130, 113}, 
	{113, 130, 131, 114}, 
	{114, 131, 132, 115}, 
	{115, 132, 133, 116}, 
	{116, 133, 134, 117}, 
	{117, 134, 135, 118}, 
	{119, 136, 137, 120}, 
	{120, 137, 138, 121}, 
	{121, 138, 139, 122}, 
	{122, 139, 140, 123}, 
	{123, 140, 141, 124}, 
	{124, 141, 142, 125}, 
	{125, 142, 143, 126}, 
	{126, 143, 144, 127}, 
	{127, 144, 145, 128}, 
	{128, 145, 146, 129}, 
	{129, 146, 147, 130}, 
	{130, 147, 148, 131}, 
	{131, 148, 149, 132}, 
	{132, 149, 150, 133}, 
	{133, 150, 151, 134}, 
	{134, 151, 152, 135}, 
	{136, 153, 154, 137}, 
	{137, 154, 155, 138}, 
	{138, 155, 156, 139}, 
	{139, 156, 157, 140}, 
	{140, 157, 158, 141}, 
	{141, 158, 159, 142}, 
	{142, 159, 160, 143}, 
	{143, 160, 161, 144}, 
	{144, 161, 162, 145}, 
	{145, 162, 163, 146}, 
	{146, 163, 164, 147}, 
	{147, 164, 165, 148}, 
	{148, 165, 166, 149}, 
	{149, 166, 167, 150}, 
	{150, 167, 168, 151}, 
	{151, 168, 169, 152}, 
	{153, 170, 171, 154}, 
	{154, 171, 172, 155}, 
	{155, 172, 173, 156}, 
	{156, 173, 174, 157}, 
	{157, 174, 175, 158}, 
	{158, 175, 176, 159}, 
	{159, 176, 177, 160}, 
	{160, 177, 178, 161}, 
	{161, 178, 179, 162}, 
	{162, 179, 180, 163}, 
	{163, 180, 181, 164}, 
	{164, 181, 182, 165}, 
	{165, 182, 183, 166}, 
	{166, 183, 184, 167}, 
	{167, 184, 185, 168}, 
	{168, 185, 186, 169}, 
	{170, 187, 188, 171}, 
	{171, 188, 189, 172}, 
	{172, 189, 190, 173}, 
	{173, 190, 191, 174}, 
	{174, 191, 192, 175}, 
	{175, 192, 193, 176}, 
	{176, 193, 194, 177}, 
	{177, 194, 195, 178}, 
	{178, 195, 196, 179}, 
	{179, 196, 197, 180}, 
	{180, 197, 198, 181}, 
	{181, 198, 199, 182}, 
	{182, 199, 200, 183}, 
	{183, 200, 201, 184}, 
	{184, 201, 202, 185}, 
	{185, 202, 203, 186}, 
	{187, 204, 205, 188}, 
	{188, 205, 206, 189}, 
	{189, 206, 207, 190}, 
	{190, 207, 208, 191}, 
	{191, 208, 209, 192}, 
	{192, 209, 210, 193}, 
	{193, 210, 211, 194}, 
	{194, 211, 212, 195}, 
	{195, 212, 213, 196}, 
	{196, 213, 214, 197}, 
	{197, 214, 215, 198}, 
	{198, 215, 216, 199}, 
	{199, 216, 217, 200}, 
	{200, 217, 218, 201}, 
	{201, 218, 219, 202}, 
	{202, 219, 220, 203}, 
	{204, 221, 222, 205}, 
	{205, 222, 223, 206}, 
	{206, 223, 224, 207}, 
	{207, 224, 225, 208}, 
	{208, 225, 226, 209}, 
	{209, 226, 227, 210}, 
	{210, 227, 228, 211}, 
	{211, 228, 229, 212}, 
	{212, 229, 230, 213}, 
	{213, 230, 231, 214}, 
	{214, 231, 232, 215}, 
	{215, 232, 233, 216}, 
	{216, 233, 234, 217}, 
	{217, 234, 235, 218}, 
	{218, 235, 236, 219}, 
	{219, 236, 237, 220}, 
	{221, 238, 239, 222}, 
	{222, 239, 240, 223}, 
	{223, 240, 241, 224}, 
	{224, 241, 242, 225}, 
	{225, 242, 243, 226}, 
	{226, 243, 244, 227}, 
	{227, 244, 245, 228}, 
	{228, 245, 246, 229}, 
	{229, 246, 247, 230}, 
	{230, 247, 248, 231}, 
	{231, 248, 249, 232}, 
	{232, 249, 250, 233}, 
	{233, 250, 251, 234}, 
	{234, 251, 252, 235}, 
	{235, 252, 253, 236}, 
	{236, 253, 254, 237}, 
	{238, 255, 256, 239}, 
	{239, 256, 257, 240}, 
	{240, 257, 258, 241}, 
	{241, 258, 259, 242}, 
	{242, 259, 260, 243}, 
	{243, 260, 261, 244}, 
	{244, 261, 262, 245}, 
	{245, 262, 263, 246}, 
	{246, 263, 264, 247}, 
	{247, 264, 265, 248}, 
	{248, 265, 266, 249}, 
	{249, 266, 267, 250}, 
	{250, 267, 268, 251}, 
	{251, 268, 269, 252}, 
	{252, 269, 270, 253}, 
	{253, 270, 271, 254}, 
	{255, 272, 273, 256}, 
	{256, 273, 274, 257}, 
	{257, 274, 275, 258}, 
	{258, 275, 276, 259}, 
	{259, 276, 277, 260}, 
	{260, 277, 278, 261}, 
	{261, 278, 279, 262}, 
	{262, 279, 280, 263}, 
	{263, 280, 281, 264}, 
	{264, 281, 282, 265}, 
	{265, 282, 283, 266}, 
	{266, 283, 284, 267}, 
	{267, 284, 285, 268}, 
	{268, 285, 286, 269}, 
	{269, 286, 287, 270}, 
	{270, 287, 288, 271}
};

unsigned int terrain_cant_elementos = 256;
}