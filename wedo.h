/*
 Y.Kuramata June 2014
 http://enthusiastickcoding.blogspot.jp/
 
 If you have a strange error, check the encoding of this file.
*/
#include "wedo_utils.h"

typedef enum{
	UNAVAILABLE,
	MOTOR,
	LED,
	DISTANCESENSOR,
	TILTSENSOR,
	UNKNOWN_DEVICE
}WEDO_DEVICE;

typedef enum{
	UNDEFINED_TILT = 0,
	FLAT,
	TILT_BACK,
	TILT_RIGHT,
	TILT_FORWARD,
	TILT_LEFT
}WEDO_TILT;
/*
 C++ Class for Lego(R) WeDo USB-Hub
 
 Before you create a WeDo class instance, 
 you have to find HANDLE of WeDo device using find_wedo function in wedo_utils.h.
 
 Prepare pointers to WeDo class and use 'new' and 'delete'
 to ensure that output value cleared by zero and device closed.
 If you don't do this, motor may continue to spin even after program ends.
 
 How to use, See sample.cpp.
*/
class WeDo{
private:
	HANDLE hDevHandle;
	WEDO_DEVICE device_type_a;
	WEDO_DEVICE device_type_b;
	uchar read_buffer[9];
	schar write_buffer[9];
	float distance_table[256];
public:
	bool read();
	bool write();
	bool write(int a, int b);
	void detectDevice();
	void setDevice(WEDO_DEVICE a, WEDO_DEVICE b);
	void setA(int v);
	void setB(int v);
	uchar rawA();
	uchar rawB();
	uchar raw(int i);
	void setRaw(schar *v);
	WEDO_DEVICE deviceA();
	WEDO_DEVICE deviceB();
	WEDO_TILT tiltA();
	WEDO_TILT tiltB();
	float distanceA();
	float distanceB();
	WeDo(HANDLE h);
	~WeDo();
private:
	void _setDistanceTable();
	WEDO_TILT _tilt(uchar v);
	WEDO_DEVICE _detectDevice(uchar v);
	schar _setValue(int i);
	DWORD _readValue(uchar *target, DWORD size);
	DWORD _writeValue(schar *v,  DWORD s);
	void _zeroClear();
};


bool WeDo::read(){
	if(_readValue(read_buffer, 9)==9){
		return true;
	}
	return false;
}
bool WeDo::write(){
	if(write_buffer[2]==0 && write_buffer[3]==0){
		write_buffer[1] = 0;
	}else{
		write_buffer[1] = 64;
	}
	if(_writeValue(write_buffer, 9)==9){
		return true;
	}
	return false;
}
bool WeDo::write(int a, int b){
	write_buffer[2] = _setValue(a);
	write_buffer[3] = _setValue(b);
	return write();
}
void WeDo::detectDevice(){
	read();
	device_type_a = _detectDevice(read_buffer[4]);
	device_type_b = _detectDevice(read_buffer[6]);
}
void WeDo::setA(int v){
	write_buffer[2] = _setValue(v);
}
void WeDo::setB(int v){
	write_buffer[3] = _setValue(v);
}
uchar WeDo::rawA(){
	return read_buffer[3];
}
uchar WeDo::rawB(){
	return read_buffer[5];
}
uchar WeDo::raw(int i){
	return (-1<i && i<9) ? read_buffer[i] : 0;
}
void WeDo::setRaw(schar *v){
	for(int i=0; i<9; i++){
		write_buffer[i] = v[i];
	}
}
WEDO_DEVICE WeDo::deviceA(){
	return device_type_a;
}
WEDO_DEVICE WeDo::deviceB(){
	return device_type_b;
}
void WeDo::setDevice(WEDO_DEVICE a, WEDO_DEVICE b){
	device_type_a = a;
	device_type_b = b;
}
WEDO_TILT WeDo::tiltA(){
	return _tilt(read_buffer[3]);
}
WEDO_TILT WeDo::tiltB(){
	return _tilt(read_buffer[5]);
}
float WeDo::distanceA(){
	return distance_table[read_buffer[3]];
}
float WeDo::distanceB(){
	return distance_table[read_buffer[5]];
}
WeDo::WeDo(HANDLE h){
	hDevHandle = h;
	_zeroClear();
	write();
	device_type_a = UNAVAILABLE;
	device_type_b = UNAVAILABLE;
	_setDistanceTable();
}
WeDo::~WeDo(){
	_zeroClear();
	write();
	CloseHandle(hDevHandle);
}
void WeDo::_setDistanceTable(){
	for(int i=0; i<68; i++){
		distance_table[i] = 0;
	}
	distance_table[68] = 0;
	distance_table[69] = 0.053;
	distance_table[70] = 0.06;
	distance_table[71] = 0.065;
	distance_table[72] = 0.065;
	distance_table[73] = 0.066;
	distance_table[74] = 0.066;
	distance_table[75] = 0.066;
	distance_table[76] = 0.067;
	distance_table[77] = 0.067;
	distance_table[78] = 0.067;
	distance_table[79] = 0.068;
	distance_table[80] = 0.068;
	distance_table[81] = 0.068;
	distance_table[82] = 0.069;
	distance_table[83] = 0.069;
	distance_table[84] = 0.069;
	distance_table[85] = 0.07;
	distance_table[86] = 0.07;
	distance_table[87] = 0.071;
	distance_table[88] = 0.071;
	distance_table[89] = 0.071;
	distance_table[90] = 0.072;
	distance_table[91] = 0.072;
	distance_table[92] = 0.072;
	distance_table[93] = 0.073;
	distance_table[94] = 0.073;
	distance_table[95] = 0.073;
	distance_table[96] = 0.074;
	distance_table[97] = 0.074;
	distance_table[98] = 0.074;
	distance_table[99] = 0.075;
	distance_table[100] = 0.075;
	distance_table[101] = 0.076;
	distance_table[102] = 0.077;
	distance_table[103] = 0.078;
	distance_table[104] = 0.079;
	distance_table[105] = 0.08;
	distance_table[106] = 0.081;
	distance_table[107] = 0.082;
	distance_table[108] = 0.083;
	distance_table[109] = 0.084;
	distance_table[110] = 0.085;
	distance_table[111] = 0.086;
	distance_table[112] = 0.087;
	distance_table[113] = 0.088;
	distance_table[114] = 0.089;
	distance_table[115] = 0.09;
	distance_table[116] = 0.091;
	distance_table[117] = 0.092;
	distance_table[118] = 0.093;
	distance_table[119] = 0.094;
	distance_table[120] = 0.095;
	distance_table[121] = 0.096;
	distance_table[122] = 0.096;
	distance_table[123] = 0.097;
	distance_table[124] = 0.097;
	distance_table[125] = 0.098;
	distance_table[126] = 0.098;
	distance_table[127] = 0.099;
	distance_table[128] = 0.099;
	distance_table[129] = 0.1;
	distance_table[130] = 0.1;
	distance_table[131] = 0.101;
	distance_table[132] = 0.101;
	distance_table[133] = 0.102;
	distance_table[134] = 0.102;
	distance_table[135] = 0.103;
	distance_table[136] = 0.103;
	distance_table[137] = 0.104;
	distance_table[138] = 0.104;
	distance_table[139] = 0.105;
	distance_table[140] = 0.105;
	distance_table[141] = 0.106;
	distance_table[142] = 0.106;
	distance_table[143] = 0.107;
	distance_table[144] = 0.107;
	distance_table[145] = 0.108;
	distance_table[146] = 0.108;
	distance_table[147] = 0.109;
	distance_table[148] = 0.109;
	distance_table[149] = 0.11;
	distance_table[150] = 0.11;
	distance_table[151] = 0.112;
	distance_table[152] = 0.113;
	distance_table[153] = 0.115;
	distance_table[154] = 0.116;
	distance_table[155] = 0.118;
	distance_table[156] = 0.119;
	distance_table[157] = 0.121;
	distance_table[158] = 0.122;
	distance_table[159] = 0.124;
	distance_table[160] = 0.125;
	distance_table[161] = 0.126;
	distance_table[162] = 0.126;
	distance_table[163] = 0.127;
	distance_table[164] = 0.127;
	distance_table[165] = 0.128;
	distance_table[166] = 0.128;
	distance_table[167] = 0.129;
	distance_table[168] = 0.129;
	distance_table[169] = 0.13;
	distance_table[170] = 0.13;
	distance_table[171] = 0.132;
	distance_table[172] = 0.134;
	distance_table[173] = 0.136;
	distance_table[174] = 0.138;
	distance_table[175] = 0.14;
	distance_table[176] = 0.142;
	distance_table[177] = 0.144;
	distance_table[178] = 0.146;
	distance_table[179] = 0.148;
	distance_table[180] = 0.15;
	distance_table[181] = 0.152;
	distance_table[182] = 0.154;
	distance_table[183] = 0.155;
	distance_table[184] = 0.157;
	distance_table[185] = 0.159;
	distance_table[186] = 0.161;
	distance_table[187] = 0.163;
	distance_table[188] = 0.165;
	distance_table[189] = 0.166;
	distance_table[190] = 0.168;
	distance_table[191] = 0.17;
	distance_table[192] = 0.175;
	distance_table[193] = 0.18;
	distance_table[194] = 0.195;
	distance_table[195] = 0.2;
	distance_table[196] = 0.215;
	distance_table[197] = 0.22;
	distance_table[198] = 0.225;
	distance_table[199] = 0.235;
	distance_table[200] = 0.245;
	distance_table[201] = 0.25;
	distance_table[202] = 0.26;
	distance_table[203] = 0.27;
	distance_table[204] = 0.29;
	distance_table[205] = 0.305;
	distance_table[206] = 0.32;
	distance_table[207] = 0.34;
	distance_table[208] = 0.39;
	distance_table[209] = 0.425;
	distance_table[210] = 0.46;
	for(int i=211; i<256; i++){
		distance_table[i] = 1.0;
	}
}
WEDO_TILT WeDo::_tilt(uchar v){
	if(10<= v && v <=40){
		return TILT_BACK;
	} else if(60 <= v && v <= 90){
		return TILT_RIGHT;
	} else if(170 <= v && v <= 190){
		return TILT_FORWARD;
	} else if(220 <= v && v <= 240){
		return TILT_LEFT;
	} else {
		return FLAT;
	}
}
WEDO_DEVICE WeDo::_detectDevice(uchar v){
	switch(v){
	case 0:
	case 1:
	case 2:
	case 3:
	case 238:
	case 239:
	case 240:
	case 241:
		return MOTOR;
		break;
	case 203://?
	case 204:
	case 205://?
		return LED;
		break;
	case 176:
	case 177:
	case 178:
	case 179:
		return DISTANCESENSOR;
		break;
	case 38:
	case 39:
		return TILTSENSOR;
		break;
	default:
		return UNAVAILABLE;
		break;
	}
}
schar WeDo::_setValue(int i){
	if(i<0){
		i -= 27;
		return i<-126 ? -126 : (schar)i;
	} else if(i>0) {
		i += 27;
		return i>127 ? 127 : (schar)i;			
	}
	return 0;
}
DWORD WeDo::_readValue(uchar *target, DWORD size){
	DWORD readsize;
	ReadFile(hDevHandle, target, size, &readsize, NULL);
	return readsize;
}
DWORD WeDo::_writeValue(schar *v,  DWORD s){
	DWORD writesize;
	WriteFile(hDevHandle, v, s, &writesize, NULL);
	FlushFileBuffers(hDevHandle);
	return writesize;
}	
void WeDo::_zeroClear(){
	for(int i=0; i<9; i++){
		read_buffer[i] = 0;
		write_buffer[i] = 0;
	}

}
