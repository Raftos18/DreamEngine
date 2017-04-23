#include "dreamUtils.h"

namespace dream {
	namespace utilities {

		// Straight out of STACK but as long as it gets the job done
		std::string File::ReadFile(const char * filepath)
		{
			FILE* file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];

			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}

		BYTE * File::LoadImage(const char * filename, GLsizei * width, GLsizei * height)
		{
			//image format
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			//pointer to the image, once loaded
			FIBITMAP *dib = nullptr;
			//pointer to the image data		

			//check the file signature and deduce its format
			fif = FreeImage_GetFileType(filename, 0);
			//if still unknown, try to guess the file format from the file extension
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(filename);
			//if still unkown, return failure
			if (fif == FIF_UNKNOWN)
				return nullptr;

			//check that the plugin has reading capabilities and load the file
			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, filename);
			//if the image failed to load, return failure
			if (!dib)
				return nullptr;

			//retrieve the image data
			BYTE* pixels = FreeImage_GetBits(dib);
			//get the image width and height
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);
			auto bits = FreeImage_GetBPP(dib);

			auto size = (*width) * (*height) * (bits / 8);
			BYTE* result = new BYTE[size];
			memcpy(result, pixels, size);

			return result;
		}
	}
}