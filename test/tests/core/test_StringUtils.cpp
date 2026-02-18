#include <gtest/gtest.h>

#include "core/string/StringUtils.h"
// Optional: include a project header once you start testing real code
// #include "foo/foo.h"

namespace uqm
{

class StringUtilsTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		// Optional setup code
	}

	void TearDown() override
	{
		// Optional cleanup code
	}
};

TEST_F(StringUtilsTest, ToStringLiteral)
{
	EXPECT_STREQ(toString(true), "true");
	EXPECT_STREQ(toString(false), "false");
}

TEST_F(StringUtilsTest, ToStringWithBuffer_Integer)
{
	uqstl::array<char, 32> buf {};
	auto s = toString(12345, buf);
	EXPECT_STREQ(s, "12345");
}

TEST_F(StringUtilsTest, ToStringWithBuffer_SmallBuffer_Bool)
{
	// Buffer too small to hold "true" (4) or "false" (5) plus NUL
	uqstl::array<char, 3> buf {};
	auto s = toString(true, buf);
	EXPECT_STREQ(s, ""); // implementation writes empty string when too small

	buf.fill(0);
	s = toString(false, buf);
	EXPECT_STREQ(s, ""); // too small -> empty
}

TEST_F(StringUtilsTest, ToStringWithBuffer_ExactAndJustBigEnough)
{
	// true length == 4, need buffer.size() > 4 to succeed per impl
	uqstl::array<char, 5> bufTrue {};
	auto s = toString(true, bufTrue);
	EXPECT_STREQ(s, "true");

	// false length == 5, need buffer.size() > 5 to succeed; with 6 it should succeed
	uqstl::array<char, 6> bufFalse {};
	s = toString(false, bufFalse);
	EXPECT_STREQ(s, "false");
}

TEST_F(StringUtilsTest, ToStringFloatFormatting)
{
	uqstl::array<char, 32> buf {};
	auto s = toString(3.14f, buf);
	// fmt by default prints a compact representation
	EXPECT_NE(uqstl::string(s).find("3.14"), uqstl::string::npos);
}

TEST_F(StringUtilsTest, CompareICaseEdgeCases)
{
	EXPECT_TRUE(compareCharICase('A', 'a'));
	EXPECT_FALSE(compareICase("abc", "abcd")); // different lengths
	EXPECT_TRUE(compareICase("ß", "ß"));	   // identical non-ascii byte-equal
}

TEST_F(StringUtilsTest, IsEmptyVariants)
{
	EXPECT_TRUE(isEmpty(nullptr));
	EXPECT_TRUE(isEmpty(""));
	EXPECT_TRUE(isEmpty(uqstl::string_view("")));
	EXPECT_TRUE(isEmpty(uqstl::string()));
	EXPECT_FALSE(isEmpty("x"));
	EXPECT_FALSE(isEmpty(uqstl::string_view("x")));
	EXPECT_FALSE(isEmpty(uqstl::string("y")));
}

TEST_F(StringUtilsTest, CStrTemplates)
{
	uqstl::string s = "abc";
	EXPECT_STREQ(c_str(s), "abc");

	const char* c = "xyz";
	EXPECT_STREQ(c_str<const char*>(c), "xyz");

	uqstl::string_view sv = "hello";
	EXPECT_STREQ(c_str(sv), "hello");
}

TEST_F(StringUtilsTest, ParseBooleanSpecialization_VariousInputs)
{
	bool out = false;
	auto ec = parseStr("TrUe", out);
	EXPECT_EQ(ec, uqstl::errc {});
	EXPECT_TRUE(out);

	ec = parseStr("off", out);
	EXPECT_EQ(ec, uqstl::errc {});
	EXPECT_FALSE(out);

	// Numeric boolean forms:
	ec = parseStr("1", out);
	EXPECT_EQ(ec, uqstl::errc {});
	EXPECT_TRUE(out);

	ec = parseStr("0", out);
	EXPECT_EQ(ec, uqstl::errc {});
	EXPECT_FALSE(out);

	// Leading/trailing whitespace should NOT be accepted (implementation uses direct equality)
	ec = parseStr(" yes", out);
	EXPECT_EQ(ec, uqstl::errc::invalid_argument);
	ec = parseStr("no ", out);
	EXPECT_EQ(ec, uqstl::errc::invalid_argument);

	// Completely invalid
	ec = parseStr("invalid_bool", out);
	EXPECT_EQ(ec, uqstl::errc::invalid_argument);
}

TEST_F(StringUtilsTest, ParseIntegers_EdgeCases)
{
	int value = 0;

	// Normal parse
	auto ec = parseStr("42", value);
	EXPECT_EQ(ec, uqstl::errc {});
	EXPECT_EQ(value, 42);

	// Partial parse: from_chars parses prefix digits; implementation doesn't require full-consumption
	ec = parseStr("12abc", value);
	EXPECT_EQ(ec, uqstl::errc {}); // success, 12 parsed
	EXPECT_EQ(value, 12);

	// Leading whitespace is not skipped by from_chars -> invalid_argument
	ec = parseStr(" 45", value);
	EXPECT_EQ(ec, uqstl::errc::invalid_argument);

	// Overflow should return result_out_of_range
	long long big = 0;
	uqstl::string huge = uqstl::to_string(uqstl::numeric_limits<long long>::max());
	huge.push_back('9'); // make it overflow
	ec = parseStr(huge, big);
	EXPECT_EQ(ec, uqstl::errc::result_out_of_range);
}

TEST_F(StringUtilsTest, ParseEnumUnderlying)
{
	enum class TestColor : int
	{
		Red = 1,
		Blue = 2,
		Green = 3
	};
	TestColor c = TestColor::Red;

	// valid numeric enum string
	auto ec = parseStr("2", c);
	EXPECT_EQ(ec, uqstl::errc {});
	EXPECT_EQ(c, TestColor::Blue);

	// invalid
	ec = parseStr("x", c);
	EXPECT_EQ(ec, uqstl::errc::invalid_argument);
}

enum class TestEnum
{
	a=10,
	b,
	c
};

enum class TestEnumWithToStringImpl
{
	x=20,
	y,
	z
};
static constexpr const char* toStringImpl(TestEnumWithToStringImpl v)
{
	if (v == TestEnumWithToStringImpl::x)
	{
		return "x-string";
	}
	if (v == TestEnumWithToStringImpl::y)
	{
		return "y-string";
	}
	if (v == TestEnumWithToStringImpl::z)
	{
		return "z-string";
	}
	return "???";
}

TEST_F(StringUtilsTest, FormatEnum)
{
	EXPECT_STREQ("10", fmt::format("{}", TestEnum::a).c_str());
	EXPECT_STREQ("a", fmt::format("{:s}", TestEnum::a).c_str());
	EXPECT_STREQ("a (10)", fmt::format("{:sn}", TestEnum::a).c_str());
	EXPECT_STREQ("a (0xa)", fmt::format("{:sn#x}", TestEnum::a).c_str());

	EXPECT_STREQ("20", fmt::format("{}", TestEnumWithToStringImpl::x).c_str());
	EXPECT_STREQ("x-string", fmt::format("{:s}", TestEnumWithToStringImpl::x).c_str());
	EXPECT_STREQ("x-string (20)", fmt::format("{:sn}", TestEnumWithToStringImpl::x).c_str());
	EXPECT_STREQ("x-string (0x14)", fmt::format("{:sn#x}", TestEnumWithToStringImpl::x).c_str());
}

TEST_F(StringUtilsTest, FormatEnumNames)
{
	EXPECT_STREQ("10, 11, 12", fmt::format("{}", EnumNames<TestEnum>{}).c_str());
	EXPECT_STREQ("a, b, c", fmt::format("{:s}", EnumNames<TestEnum>{}).c_str());
	EXPECT_STREQ("a (10) | b (11) | c (12)", fmt::format("{:|sn}", EnumNames<TestEnum>{}).c_str());

	EXPECT_STREQ("20 | 21 | 22", fmt::format("{:|}", EnumNames<TestEnumWithToStringImpl> {}).c_str());
	EXPECT_STREQ("x-string, y-string, z-string", fmt::format("{:s}", EnumNames<TestEnumWithToStringImpl> {}).c_str());
	EXPECT_STREQ("x-string (20) | y-string (21) | z-string (22)", fmt::format("{:|sn}", EnumNames<TestEnumWithToStringImpl> {}).c_str());
}

} // namespace uqm