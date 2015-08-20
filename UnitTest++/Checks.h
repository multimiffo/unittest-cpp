#ifndef UNITTEST_CHECKS_H
#define UNITTEST_CHECKS_H

#include "Config.h"
#include "TestResults.h"
#include "MemoryOutStream.h"

namespace UnitTest {


template< typename Value >
bool Check(Value const value)
{
    return !!value; // doing double negative to avoid silly VS warnings
}


template< typename Expected, typename Actual >
bool AreEqual(Expected const& expected, Actual const& actual)
{
    return expected == actual;
}

template< typename Expected, typename Actual >
void CheckEqual(TestResults& results, Expected const& expected, Actual const& actual, TestDetails const& details)
{
    if (!AreEqual(expected, actual))
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " but was " << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}

UNITTEST_LINKAGE bool AreEqual(char const* expected, char const* actual);
UNITTEST_LINKAGE void CheckEqual(TestResults& results, char const* expected, char const* actual, TestDetails const& details);

UNITTEST_LINKAGE bool AreEqual(char* expected, char* actual);
UNITTEST_LINKAGE void CheckEqual(TestResults& results, char* expected, char* actual, TestDetails const& details);

UNITTEST_LINKAGE bool AreEqual(char* expected, char const* actual);
UNITTEST_LINKAGE void CheckEqual(TestResults& results, char* expected, char const* actual, TestDetails const& details);

UNITTEST_LINKAGE bool AreEqual(char const* expected, char* actual);
UNITTEST_LINKAGE void CheckEqual(TestResults& results, char const* expected, char* actual, TestDetails const& details);


template< typename Expected, typename Actual, typename Tolerance >
bool AreClose(Expected const& expected, Actual const& actual, Tolerance const& tolerance)
{
    return (actual >= (expected - tolerance)) && (actual <= (expected + tolerance));
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckClose(TestResults& results, Expected const& expected, Actual const& actual, Tolerance const& tolerance,
                TestDetails const& details)
{
    if (!AreClose(expected, actual, tolerance))
    {
        UnitTest::MemoryOutStream stream;
        stream << "Expected " << expected << " +/- " << tolerance << " but was " << actual;

        results.OnTestFailure(details, stream.GetText());
    }
}

template< typename Expected, typename Actual >
    bool ArrayAreEqual(Expected const& expected, Actual const& actual, int const count)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= (expected[i] == actual[i]);

    return equal;
}

template< typename Expected, typename Actual >
void CheckArrayEqual(TestResults& results, Expected const& expected, Actual const& actual,
                     int const count, TestDetails const& details)
{
    if (!ArrayAreEqual(expected, actual, count))
    {
        UnitTest::MemoryOutStream stream;

        stream << "Expected [ ";

        for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << " ";

        stream << "] but was [ ";

        for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << " ";

        stream << "]";

        results.OnTestFailure(details, stream.GetText());
    }
}

template< typename Expected, typename Actual, typename Tolerance >
bool ArrayAreClose(Expected const& expected, Actual const& actual, int const count, Tolerance const& tolerance)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= AreClose(expected[i], actual[i], tolerance);
    return equal;
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArrayClose(TestResults& results, Expected const& expected, Actual const& actual,
                     int const count, Tolerance const& tolerance, TestDetails const& details)
{
    bool equal = ArrayAreClose(expected, actual, count, tolerance);

    if (!equal)
    {
        UnitTest::MemoryOutStream stream;

        stream << "Expected [ ";
        for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << " ";
        stream << "] +/- " << tolerance << " but was [ ";

        for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << " ";
        stream << "]";

        results.OnTestFailure(details, stream.GetText());
    }
}


template< typename Expected, typename Actual, typename Tolerance >
bool Array2DAreClose(Expected const& expected, Actual const& actual,
                     int const rows, int const columns, Tolerance const& tolerance)
{
    bool equal = true;
    for (int i = 0; i < rows; ++i)
        equal &= ArrayAreClose(expected[i], actual[i], columns, tolerance);

    return equal;
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArray2DClose(TestResults& results, Expected const& expected, Actual const& actual,
                       int const rows, int const columns, Tolerance const& tolerance, TestDetails const& details)
{

    if (!Array2DAreClose(expected, actual, rows, columns, tolerance))
    {
        UnitTest::MemoryOutStream stream;

        stream << "Expected [ ";

        for (int expectedRow = 0; expectedRow < rows; ++expectedRow)
        {
            stream << "[ ";
            for (int expectedColumn = 0; expectedColumn < columns; ++expectedColumn)
                stream << expected[expectedRow][expectedColumn] << " ";
            stream << "] ";
        }

        stream << "] +/- " << tolerance << " but was [ ";

        for (int actualRow = 0; actualRow < rows; ++actualRow)
        {
            stream << "[ ";
            for (int actualColumn = 0; actualColumn < columns; ++actualColumn)
                stream << actual[actualRow][actualColumn] << " ";
            stream << "] ";
        }

        stream << "]";

        results.OnTestFailure(details, stream.GetText());
    }
}

}

#endif
