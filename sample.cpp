#include "stdafx.h"
#include <iostream>
#include "wedo.h"
/*
 A sample using WeDo class.
*/
int _tmain(int argc, _TCHAR* argv[]){
	HANDLE handles[4];
	WeDo *wedo[4];
	int found_wedo =  findWedo(handles, 4);
	std::cout << found_wedo << " wedo found." << std::endl;
	for(int i=0; i<found_wedo && i<4; i++){
		std::cout << "-----WeDo No. " << i << "-----"<< std::endl;
		wedo[i] = new WeDo(handles[i]);
		wedo[i]->detectDevice();
		switch(wedo[i]->deviceA()){
		case MOTOR:
			std::cout << "A MOTOR is connected to A." << std::endl;
			wedo[i]->setA(100);
			break;
		case TILTSENSOR:
			std::cout << "A TILT SENSOR is connected to A." << std::endl;
			wedo[i]->read();
			switch(wedo[i]->tiltA()){
			case FLAT:
				std::cout << "FLAT" << std::endl;
				break;
			case TILT_BACK:
				std::cout << "TILT BACK" << std::endl;
				break;
			case TILT_FORWARD:
				std::cout << "TILT FORWARD" << std::endl;
				break;
			case TILT_LEFT:
				std::cout << "TILT LEFT" << std::endl;
				break;
			case TILT_RIGHT:
				std::cout << "TILT RIGHT" << std::endl;
				break;
			}
			break;
		case DISTANCESENSOR:
			std::cout << "A DISTANCE SENSOR is connected to A." << std::endl;
			wedo[i]->read();
			std::cout << "Measured distance:" << wedo[i]->distanceA() << "meter." << std::endl;
			break;
		case LED:
			std::cout << "LEDs are connected to A." << std::endl;
			wedo[i]->setA(100);
			break;
		default:
			std::cout << "Port A is empty." << std::endl;
			break;
		}
		switch(wedo[i]->deviceB()){
		case MOTOR:
			std::cout << "A MOTOR is connected to B." << std::endl;
			wedo[i]->setB(100);
			break;
		case TILTSENSOR:
			std::cout << "A TILT SENSOR is connected to B." << std::endl;
			wedo[i]->read();
			switch(wedo[i]->tiltB()){
			case FLAT:
				std::cout << "FLAT" << std::endl;
				break;
			case TILT_BACK:
				std::cout << "TILT BACK" << std::endl;
				break;
			case TILT_FORWARD:
				std::cout << "TILT FORWARD" << std::endl;
				break;
			case TILT_LEFT:
				std::cout << "TILT LEFT" << std::endl;
				break;
			case TILT_RIGHT:
				std::cout << "TILT RIGHT" << std::endl;
				break;
			}
			break;
		case DISTANCESENSOR:
			std::cout << "A DISTANCE SENSOR is connected to B." << std::endl;
			wedo[i]->read();
			std::cout << "Measured distance:" << wedo[i]->distanceB() << "meter." << std::endl;
			break;
		case LED:
			std::cout << "LEDs are connected to B." << std::endl;
			wedo[i]->setB(100);
			break;
		default:
			std::cout << "Port B is empty." << std::endl;
			std::cout << wedo[i]->rawB() << std::endl;
			break;
		}
		wedo[i]->write();

	}
	std::cout << std::endl;
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();
	for(int i=0; i<found_wedo && i<4; i++){
		delete wedo[i];
	}
	return 0;
}

