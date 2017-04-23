#include "dreamUtils.h"

namespace dream {
	namespace utilities {
		std::vector<std::string> String::Split(const std::string & s, char delim) {
			// Create a vector to hold the "splitted" elements
			std::vector<std::string> elems;		
			// save the string as a stream
			std::stringstream ss;
			ss.str(s);
			// let getline do the hard work
			std::string item;
			while (std::getline(ss, item, delim)) {
				// push the seperated element into the vector
				elems.push_back(item);
			}
			return elems;
		}
	}
}


	