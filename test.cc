#include "gtest/gtest.h"
#include "jsonHandler.h"

const std::string JSON_PATH = "test.json";
const std::string JSON_PAYLOAD = "{\"test\" : 42, \"array\" : [1.0, 0.0, 0.0]}";

typedef struct {
	int test;
	float array[3];
} testStruct_t;

class JsonHanderTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		std::fstream file(JSON_PATH);
		file << JSON_PAYLOAD;
		file.close();
	}

	virtual void TearDown()
	{
	}
};

static void parser(Json::Value &root, void *const data)
{
	testStruct_t *st = (testStruct_t *)data;

	st->test = root["test"].asInt();

	for (int i = 0; i < 3; i++) {
		st->array[i] = root["array"][i].asFloat();
	}
}

static void encoder(Json::Value &root, void *const data)
{
	testStruct_t *st = (testStruct_t *)data;

	root["test"] = st->test;

	for (int i = 0; i < 3; i++) {
		root["array"][i] = st->array[i];
	}
}

TEST_F(JsonHanderTest, readJsonFile)
{
	testStruct_t test_struct;
	JsonHandler jsonHandler(JSON_PATH, parser, nullptr, &test_struct);
	int res = jsonHandler.read();
	ASSERT_EQ(res, 0);	

	EXPECT_EQ(test_struct.test, 42);
	EXPECT_FLOAT_EQ(test_struct.array[0], 1.0);
	EXPECT_FLOAT_EQ(test_struct.array[1], 0.0);
	EXPECT_FLOAT_EQ(test_struct.array[2], 0.0);
}

TEST_F(JsonHanderTest, writeJsonFile)
{
	testStruct_t test_struct = {
		.test = 1,
		.array = {0.0, 1.0, 0.0}
	};

	JsonHandler jsonHander(JSON_PATH, parser, encoder, &test_struct);
	int res = jsonHander.write();
	ASSERT_EQ(res, 0);

	res = jsonHander.read();
	EXPECT_EQ(test_struct.test, 1);
	EXPECT_FLOAT_EQ(test_struct.array[0], 0.0);
	EXPECT_FLOAT_EQ(test_struct.array[1], 1.0);
	EXPECT_FLOAT_EQ(test_struct.array[2], 0.0);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	std::cout << "RUNNING TESTS ..." << std::endl;
	return RUN_ALL_TESTS();
}