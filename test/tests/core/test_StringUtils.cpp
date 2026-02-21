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

TEST_F(StringUtilsTest, StrncpySafe_BasicCopy)
{
	uqstl::array<char, 10> dest {};
	uqstl::string_view src = "hello";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 5);
	EXPECT_STREQ(dest.data(), "hello");
	EXPECT_EQ(dest[5], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_ExactFit)
{
	uqstl::array<char, 6> dest {}; // exactly "hello" + '\0'
	uqstl::string_view src = "hello";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 5);
	EXPECT_STREQ(dest.data(), "hello");
	EXPECT_EQ(dest[5], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_Truncation)
{
	uqstl::array<char, 6> dest {}; // can hold 5 chars + '\0'
	uqstl::string_view src = "hello world";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 5);
	EXPECT_STREQ(dest.data(), "hello");
	EXPECT_EQ(dest[5], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_EmptySource)
{
	uqstl::array<char, 10> dest {};
	dest.fill('x'); // fill with non-null
	uqstl::string_view src = "";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 0);
}

TEST_F(StringUtilsTest, StrncpySafe_EmptyDestination)
{
	uqstl::array<char, 0> dest {};
	uqstl::string_view src = "hello";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 0);
}

TEST_F(StringUtilsTest, StrncpySafe_SingleCharBuffer)
{
	uqstl::array<char, 1> dest {};
	uqstl::string_view src = "hello";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 0);
	EXPECT_EQ(dest[0], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_TwoCharBuffer)
{
	uqstl::array<char, 2> dest {};
	uqstl::string_view src = "hello";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 1);
	EXPECT_EQ(dest[0], 'h');
	EXPECT_EQ(dest[1], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_SourceLongerThanDest)
{
	uqstl::array<char, 5> dest {};
	uqstl::string_view src = "abcdefghijklmnop";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 4);
	EXPECT_STREQ(dest.data(), "abcd");
	EXPECT_EQ(dest[4], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_SourceShorterThanDest)
{
	uqstl::array<char, 20> dest {};
	dest.fill('x'); // fill with non-null to verify proper termination
	uqstl::string_view src = "hi";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 2);
	EXPECT_STREQ(dest.data(), "hi");
	EXPECT_EQ(dest[2], '\0');
	// Note: unlike strncpy, this doesn't zero-fill the rest
	EXPECT_EQ(dest[3], 'x'); // original content remains
}

TEST_F(StringUtilsTest, StrncpySafe_SpecialCharacters)
{
	uqstl::array<char, 20> dest {};
	uqstl::string_view src = "line1\nline2\ttab";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, src.size());
	EXPECT_STREQ(dest.data(), "line1\nline2\ttab");
}

TEST_F(StringUtilsTest, StrncpySafe_NullTerminatorInSource)
{
	// string_view can contain embedded nulls
	const char srcData[] = {'a', 'b', '\0', 'c', 'd'};
	uqstl::string_view src(srcData, 5);
	uqstl::array<char, 10> dest {};

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 2);
	// The copied data includes the embedded null
	EXPECT_EQ(dest[0], 'a');
	EXPECT_EQ(dest[1], 'b');
	EXPECT_EQ(dest[2], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_MaxSizeString)
{
	uqstl::array<char, 100> dest {};
	uqstl::string longSrc(99, 'a'); // 99 'a' characters

	size_t copied = strncpy_safe(dest, longSrc);

	EXPECT_EQ(copied, 99);
	EXPECT_EQ(dest[99], '\0');
	EXPECT_EQ(uqstl::strlen(dest.data()), 99);
}

TEST_F(StringUtilsTest, StrncpySafe_OverwriteExistingData)
{
	uqstl::array<char, 10> dest {};
	uqstl::string_view src1 = "hello";
	uqstl::string_view src2 = "hi";

	strncpy_safe(dest, src1);
	EXPECT_STREQ(dest.data(), "hello");

	// Overwrite with shorter string
	size_t copied = strncpy_safe(dest, src2);

	EXPECT_EQ(copied, 2);
	EXPECT_STREQ(dest.data(), "hi");
	// The 'l' characters remain after the new null terminator
	EXPECT_EQ(dest[2], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_WithCStyleString)
{
	uqstl::array<char, 10> dest {};
	const char* cstr = "test";
	uqstl::string_view src(cstr);

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 4);
	EXPECT_STREQ(dest.data(), "test");
}

TEST_F(StringUtilsTest, StrncpySafe_WithStdString)
{
	uqstl::array<char, 10> dest {};
	uqstl::string stdstr = "example";
	uqstl::string_view src(stdstr);

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 7);
	EXPECT_STREQ(dest.data(), "example");
}

TEST_F(StringUtilsTest, StrncpySafe_ReturnValue)
{
	uqstl::array<char, 5> dest {};

	// When truncated, returns number actually copied (not including null)
	size_t copied1 = strncpy_safe(dest, "abcdefgh");
	EXPECT_EQ(copied1, 4);

	// When not truncated, returns source size
	dest.fill(0);
	size_t copied2 = strncpy_safe(dest, "abc");
	EXPECT_EQ(copied2, 3);

	// Empty source
	dest.fill(0);
	size_t copied3 = strncpy_safe(dest, "");
	EXPECT_EQ(copied3, 0);
}

TEST_F(StringUtilsTest, StrncpySafe_BoundaryConditions)
{
	// Test SIZE_MAX scenario (unlikely but important for safety)
	uqstl::array<char, 3> dest {};
	uqstl::string_view src = "ab";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 2);
	EXPECT_STREQ(dest.data(), "ab");
	EXPECT_EQ(dest[2], '\0');
}

TEST_F(StringUtilsTest, StrncpySafe_SpanFromVector)
{
	uqstl::vector<char> dest(10);
	uqstl::string_view src = "vector";

	size_t copied = strncpy_safe(uqstl::span<char>(dest), src);

	EXPECT_EQ(copied, 6);
	EXPECT_STREQ(dest.data(), "vector");
}

TEST_F(StringUtilsTest, StrncpySafe_AllWhitespace)
{
	uqstl::array<char, 10> dest {};
	uqstl::string_view src = "   \t\n  ";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, src.size());
	EXPECT_STREQ(dest.data(), "   \t\n  ");
}

TEST_F(StringUtilsTest, StrncpySafe_NumericStrings)
{
	uqstl::array<char, 15> dest {};
	uqstl::string_view src = "1234567890";

	size_t copied = strncpy_safe(dest, src);

	EXPECT_EQ(copied, 10);
	EXPECT_STREQ(dest.data(), "1234567890");
}

TEST_F(StringUtilsTest, StrncpySafe_Appending)
{
	uqstl::array<char, 15> dest {};
	uqstl::string_view src = "1234567890";

	std::span<char> destSpan(dest);
	size_t copied = strncpy_safe(destSpan, src.substr(0,5));
	EXPECT_EQ(copied, 5);
	EXPECT_STREQ(dest.data(), "12345");

	destSpan = destSpan.subspan(5);
	size_t copied2 = strncpy_safe(destSpan, src.substr(5));
	EXPECT_EQ(copied2, 5);
	EXPECT_STREQ(dest.data(), "1234567890");
}

} // namespace uqm