#include <gtest/gtest.h>

#include "options/OptionTypes.h"

namespace uqm
{

class OptionTypesTests : public ::testing::Test
{
protected:
	void SetUp() override {}
	void TearDown() override {}
};

// Basic OptionT behavior: default state, assignment, set flag, conversion and dereference
TEST_F(OptionTypesTests, OptionT_AssignConversionAndDereference)
{
	OptionT<int> intOpt;
	// default constructed, value-initialized but not "set"
	EXPECT_FALSE(intOpt.set);
	// operator* and conversion should return the stored value (0)
	EXPECT_EQ(*intOpt, 0);
	EXPECT_EQ(static_cast<int>(intOpt), 0);

	// assignment marks option as set and updates value
	int assigned = (intOpt = 7);
	EXPECT_EQ(assigned, 7);
	EXPECT_TRUE(intOpt.set);
	EXPECT_EQ(intOpt.value, 7);
	EXPECT_EQ(*intOpt, 7);
	EXPECT_EQ(static_cast<int>(intOpt), 7);

	// copy preserves value and set flag
	OptionT<int> intOptCopy = intOpt;
	EXPECT_TRUE(intOptCopy.set);
	EXPECT_EQ(intOptCopy.value, 7);
}

// Specialization: BoolOption toString uses OptionTrueText/OptionFalseText ("on"/"off")
TEST_F(OptionTypesTests, BoolOption_ToStringAndSet)
{
	BoolOption bDefault;
	EXPECT_FALSE(bDefault.set);
	EXPECT_EQ(bDefault.value, false);
	// default toString for false
	EXPECT_STREQ(bDefault.toString(), OptionFalseText);

	bDefault = true;
	EXPECT_TRUE(bDefault.set);
	EXPECT_TRUE(bDefault.value);
	EXPECT_STREQ(bDefault.toString(), OptionTrueText);

	// assign false again
	bDefault = false;
	EXPECT_TRUE(bDefault.set);
	EXPECT_FALSE(bDefault.value);
	EXPECT_STREQ(bDefault.toString(), OptionFalseText);
}

// Constructor taking default value must not set the 'set' flag (per header implementation)
TEST_F(OptionTypesTests, OptionT_DefaultCtorDoesNotSetFlag)
{
	OptionT<Resolution> resDefault({800, 600});
	EXPECT_FALSE(resDefault.set);
	EXPECT_EQ(resDefault.value.width, 800);
	EXPECT_EQ(resDefault.value.height, 600);

	// assigning marks set
	resDefault = Resolution {1024, 768};
	EXPECT_TRUE(resDefault.set);
	EXPECT_EQ(resDefault.value.width, 1024);
	EXPECT_EQ(resDefault.value.height, 768);
}

// Enum toString functions for SeedType and EmulationMode
TEST_F(OptionTypesTests, EnumToString_SeedAndEmulation)
{
	EXPECT_STREQ(toString(SeedType::None), "None");
	EXPECT_STREQ(toString(SeedType::Planet), "Planet");
	EXPECT_STREQ(toString(SeedType::Prime), "Prime");
	EXPECT_STREQ(toString(EmulationMode::Console3DO), "3DO");
	EXPECT_STREQ(toString(EmulationMode::PC), "PC");

	// Unknown / out of range value should return ??? string
	EmulationMode mixed = static_cast<EmulationMode>(static_cast<int>(EmulationMode::Console3DO) | static_cast<int>(EmulationMode::PC));
	EXPECT_STREQ(toString(mixed), "???");
}

// OptionListValueT default initialization and manual initialization
TEST_F(OptionTypesTests, OptionListValue_DefaultAndManual)
{
	OptionListValueT<int> defaultItem;
	EXPECT_EQ(defaultItem.name, nullptr);
	EXPECT_EQ(defaultItem.value, 0);

	OptionListValueT<int> item {"test", 42};
	EXPECT_STREQ(item.name, "test");
	EXPECT_EQ(item.value, 42);
}

// Resolution struct basic semantics and boundaries
TEST_F(OptionTypesTests, Resolution_DefaultsAndAssignment)
{
	Resolution r;
	EXPECT_EQ(r.width, 0);
	EXPECT_EQ(r.height, 0);

	r.width = 123;
	r.height = 456;
	EXPECT_EQ(r.width, 123);
	EXPECT_EQ(r.height, 456);
}

// RunMode enum basic checks
TEST_F(OptionTypesTests, RunMode_Values)
{
	EXPECT_EQ(static_cast<int>(RunMode::Normal), 0);
	EXPECT_EQ(static_cast<int>(RunMode::Usage), 1);
	EXPECT_EQ(static_cast<int>(RunMode::Version), 2);
}

// Ensure OptionT<bool>::toString specialization returns on/off and doesn't call generic toString
TEST_F(OptionTypesTests, OptionT_BoolToStringSpecialization)
{
	OptionT<bool> optFalse(false);
	EXPECT_FALSE(optFalse.set);
	EXPECT_STREQ(optFalse.toString(), OptionFalseText);

	optFalse = true;
	EXPECT_TRUE(optFalse.set);
	EXPECT_STREQ(optFalse.toString(), OptionTrueText);
}

// Copy and move semantics keep the set flag and value
TEST_F(OptionTypesTests, OptionT_CopyAndMovePreserveState)
{
	OptionT<SeedType> original(SeedType::MRQ);
	EXPECT_FALSE(original.set); // constructor should not set
	original = SeedType::Prime;
	EXPECT_TRUE(original.set);
	EXPECT_EQ(original.value, SeedType::Prime);

	// Copy
	OptionT<SeedType> copy = original;
	EXPECT_TRUE(copy.set);
	EXPECT_EQ(copy.value, SeedType::Prime);

	// Move (moves the value and set flag; semantics same for trivially copyable)
	OptionT<SeedType> moved = std::move(original);
	EXPECT_TRUE(moved.set);
	EXPECT_EQ(moved.value, SeedType::Prime);
}

// Validate that OptionT<T>::toString is usable for types that have uqm::toString overloads (SeedType tested above).
// We avoid calling toString for int because no suitable overload exists in current headers.
TEST_F(OptionTypesTests, OptionT_ToString_UsesUqmToStringForEnums)
{
	OptionT<SeedType> st {SeedType::StarSeed};
	EXPECT_STREQ(st.toString(), "StarSeed");
}

} // namespace uqm