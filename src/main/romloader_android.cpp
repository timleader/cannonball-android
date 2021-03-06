/***************************************************************************
Binary File Loader.

Handles loading an individual binary file to memory.
Supports reading bytes, words and longs from this area of memory.

Copyright Chris White.
See license.txt for more details.
***************************************************************************/

#include <iostream>
#include <fstream>
#include <cstddef>       // for std::size_t
#include <boost/crc.hpp> // CRC Checking via Boost library.

#include "stdint.hpp"
#include "romloader.hpp"

#include "android_debug.h"

#include <unistd.h>
#include <jni.h>

#include <android/asset_manager.h>
extern AAssetManager * __assetManager;

RomLoader::RomLoader()
{
}

RomLoader::~RomLoader()
{
}

void RomLoader::init(const uint32_t length)
{
	this->length = length;
	rom = new uint8_t[length];
}

void RomLoader::unload(void)
{
	delete[] rom;
}

int RomLoader::load(const char* filename, const int offset, const int length, const int expected_crc, const uint8_t interleave)
{
	std::string path = "roms/";
	path += std::string(filename);

	// Open rom file
	AAsset * asset = AAssetManager_open(__assetManager, path.c_str(), 3);
	if (!asset)
	{
		std::cout << "cannot open rom: " << filename << std::endl;
		return 1; // fail
	}

	// Read file
	char * buffer = new char[length];
	AAsset_read(asset, buffer, length);

	int gcount = static_cast<int>(AAsset_getLength(asset));

	// Check CRC on file
	boost::crc_32_type result;
	result.process_bytes(buffer, (size_t)gcount);

	if (expected_crc != result.checksum())
	{
		std::cout << std::hex <<
			filename << " has incorrect checksum.\nExpected: " << expected_crc << " Found: " << result.checksum() << std::endl;
	}

	// Interleave file as necessary
	for (int i = 0; i < length; i++)
	{
		rom[(i * interleave) + offset] = buffer[i];
	}

	// Clean Up
	delete[] buffer;
	AAsset_close(asset);

	printf("rom loaded : %s", filename);

	return 0; // success
}

// Load LayOut Level As Binary File
int RomLoader::load_binary(const char* filename)
{
	// --------------------------------------------------------------------------------------------
	// Read LayOut Data File
	// --------------------------------------------------------------------------------------------
	AAsset * asset = AAssetManager_open(__assetManager, filename, 3);
	if (!asset)
	{
		std::cout << "cannot open level: " << filename << std::endl;
		return 1; // fail
	}

	int length = static_cast<int>(AAsset_getLength(asset));

	// Read file
	char* buffer = new char[length];
	AAsset_read(asset, buffer, length);
	rom = (uint8_t*)buffer;

	// Clean Up
	AAsset_close(asset);

	return 0; // success
}

int RomLoader::filesize(const char* filename)
{
	return 0;
}

