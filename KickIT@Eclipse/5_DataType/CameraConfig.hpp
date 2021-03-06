/**
 * @file CameraConfig.hpp
 * @brief Classe
 */

#ifndef CAMERACONFIG_HPP
#define CAMERACONFIG_HPP

#include "../4_Utilities/ConfigReader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

/**CameraConfig class
 *
 */
class CameraConfig {
protected:
	ConfigReader cr;

public:
	int redLow;
	int redHigh;
	int greenLow;
	int greenHigh;
	int blueLow;
	int blueHigh;
	int width;
	int height;
	int packetsize;
	int exposureTime;
	int offsetx;
	int offsety;

	/**CameraConfig constructor
	 *
	 */
	CameraConfig():cr("6_Configuration/CameraConfig.txt"){
		loadConfig();
	}

	/**loadConfig function
	 *
	 */
	void loadConfig() {
		redLow = cr.getIntValue("redLow");
		redHigh = cr.getIntValue("redHigh");
		greenLow = cr.getIntValue("greenLow");
		greenHigh = cr.getIntValue("greenHigh");
		blueLow = cr.getIntValue("blueLow");
		blueHigh = cr.getIntValue("blueHigh");
		width = cr.getIntValue("width");
		height = cr.getIntValue("height");
		packetsize = cr.getIntValue("packetsize");
		exposureTime = cr.getIntValue("exposureTime");
		offsetx = cr.getIntValue("offsetx");
		offsety = cr.getIntValue("offsety");
	}

	/**sevaConfig function
	 *
	 */
	void saveConfig() {
		cr.setIntValue("redLow",redLow);
		cr.setIntValue("redHigh",redHigh);
		cr.setIntValue("greenLow",greenLow);
		cr.setIntValue("greenHigh",greenHigh);
		cr.setIntValue("blueLow",blueLow);
		cr.setIntValue("blueHigh",blueHigh);
		cr.setIntValue("width",width);
		cr.setIntValue("height",height);
		cr.setIntValue("packetsize",packetsize);
		cr.setIntValue("exposureTime",exposureTime);
		cr.setIntValue("offsetx",offsetx);
		cr.setIntValue("offsety",offsety);
		cr.writeOut();
	}

	/**printConfig function
	 *
	 */
	void printConfig() {
		std::cout << "CAMERA CONFIGURATION\n" << "RedLow: "
				<< redLow << "\n" << "RedHigh: " << redHigh << "\n"
				<< "GreenLow: " << greenLow << "\n" << "GreenHigh: "
				<< greenHigh << "\n" << "BlueLow: " << blueLow << "\n"
				<< "BlueHigh: " << blueHigh << "\n" << "Width: " << width
				<< "\n" << "Height: " << height << "\n" << "Packetsize: "
				<< packetsize << "\n"
				<< "ExposureTime: "  << exposureTime << "\n"
				<< "OffsetX: " << "\n" << "OffsetY: " << std::endl;
	}

};

#endif //CAMERACONFIG_HPP
