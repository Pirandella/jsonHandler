#include "jsonHandler.h"

JsonHandler::JsonHandler(std::string path,
						 std::function<void(Json::Value &, void *const)> parser,
						 std::function<void(Json::Value &, void *const)> encoder,
						 void *const data) 
						 : mPath(path), mStruct(data)
{
	mParser = parser;
	mEncoder = encoder;
}

int JsonHandler::read()
{
	if (mParser == nullptr) {
		std::cout << "Failed to read json file: No parser function is specified!" << std::endl;
		return -3;
	}

	std::ifstream file(mPath);
	if (!file.good()) {
		std::cout << "File doesn't exits: " << mPath << std::endl;
		return -1;
	}
	
	Json::CharReaderBuilder builder;
	JSONCPP_STRING error;
	if (!parseFromStream(builder, file, &mRoot, &error)) {
		std::cout << error << std::endl;
		return -2;
	}
	
	mParser(mRoot, mStruct);

	file.close();
	return 0;
}

int JsonHandler::write()
{
	if (mEncoder == nullptr) {
		std::cout << "Faild to write to json file: No encoder function is specified!" << std::endl;
		return -3;
	}

	mEncoder(mRoot, mStruct);

	std::ofstream file(mPath);
	if (!file.good()) {
		std::cout << "Failed open/create json file" << std::endl;
		return -1;
	}

	Json::StyledWriter styledWriter;
	file << styledWriter.write(mRoot);
	file.close();

	return 0;
}