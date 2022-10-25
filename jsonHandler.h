#pragma once

#include <json/json.h>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

class JsonHandler
{
public:
	JsonHandler(std::string path,
				std::function<void(Json::Value &, void *const)> parser,
				std::function<void(Json::Value &, void *const)> encoder,
				void *const data);

	int read();
	int write();

private:
	Json::Value mRoot;
	const std::string mPath;
	std::function<void(Json::Value &, void *const)> mParser;
	std::function<void(Json::Value &, void *const)> mEncoder;
	void *const mStruct;

};