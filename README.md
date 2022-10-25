# JsonHandler

## Description
Simple wrapper for [jsoncpp](https://github.com/open-source-parsers/jsoncpp) that provides read and write functionality with user specified _parser/encoder_ functions.

All that requered from user is to pass custom parse and encode function with the structure to which it will be written/read from.

## How to use
- Copy jsonHandler.h and jsonHandler.cc into you project;
- Create structure with field that you want to read/write from json file; 
- Create parser and/or encoder function(s):
``` C++
voic func(Json::Value &root, void *const data)
{
    // Parse or encode json code ...
}
```
- Done.

## Requisites
- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
- [GoogleTest](https://github.com/google/googletest)
