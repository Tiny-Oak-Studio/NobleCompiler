#include <gtest/gtest.h>
#include "../Frame.h"

using namespace Noble::Compiler;

/// @brief Write an op and then read it and compare the result
TEST(Frame, WriteReadOneOp)
{
    constexpr Op::Type op = 123;
    Frame frame;
    frame.WriteOp(op);
    EXPECT_EQ(frame.ReadOp(0), op);
}

/// @brief Writes one address, then reads it and makes sure they match
TEST(Frame, WriteReadOneAddress)
{
    constexpr Address::Single address = 12313;
    Frame frame;
    frame.WriteAddress(address);
    EXPECT_EQ(frame.ReadAddress(0), address);
}

/// @brief Writes one op and one address, then reads them and matches output
TEST(Frame, WriteReadOneOpOneAddress)
{
    constexpr Op::Type op = 123;
    constexpr Address::Single address = 12313;

    Frame frame;
    frame.WriteOp(op);
    frame.WriteAddress(address);
    EXPECT_EQ(frame.ReadAddress(1), address);
    EXPECT_EQ(frame.ReadOp(0), op);
}

/// @brief Adds 100 ops and addresses, then reads them to match against expected output
TEST(Frame, WriteReadOneHundredOpsAndAddresses)
{
    Frame frame;
    for (Address::Single i = 0; i < 100; ++i)
    {
        const Op::Type op = i;
        const Address::Single address = 12313 + i;

        frame.WriteOp(op);
        frame.WriteAddress(address);
    }

    for (Address::Single i = 0; i < 100; ++i)
    {
        const Op::Type op = i;
        const Address::Single address = 12313 + i;

        EXPECT_EQ(frame.ReadAddress(i * (sizeof(Op::Type) + Translation::OpsPerAddress) + 1), address);
        EXPECT_EQ(frame.ReadOp(i * (sizeof(Op::Type) + Translation::OpsPerAddress)), op);
    }
}

TEST(Frame, WriteReadOneConstant)
{
    Frame frame;
    const ValueType testValue = ToValue(198.87f);
    const Address::Single address = frame.AddConstant(testValue);
    EXPECT_EQ(frame.ReadConstant(address), testValue);
}

TEST(Frame, WriteReadOneHundredConstants)
{
    Frame frame;
    const ValueType RandomOffset = ToValue(120.543f);
    for (Address::Single i = 0; i < 100; ++i)
    {
        frame.AddConstant(static_cast<float>(i) + RandomOffset);
    }
    for (Address::Single i = 0; i < 100; ++i)
    {
        EXPECT_EQ(frame.ReadConstant(i), static_cast<float>(i) + RandomOffset);
    }
}