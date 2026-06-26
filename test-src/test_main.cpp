#include "example/main.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(main, print_version_short)
{
    char arg0[] = "app";
    char arg1[] = "-v";
    int const argc = 2;
    char * argv[] = {arg0, arg1, nullptr};

    std::ostringstream out;
    std::ostringstream err;
    int const exit_code = example::main(argc, argv, out, err);

    ASSERT_EQ(exit_code, 0);
    ASSERT_EQ(std::string("1.0.0\n"), out.str());
    ASSERT_TRUE(err.str().empty());
}

TEST(main, print_version_long)
{
    char arg0[] = "app";
    char arg1[] = "--version";
    int const argc = 2;
    char * argv[] = {arg0, arg1, nullptr};

    std::ostringstream out;
    std::ostringstream err;
    int const exit_code = example::main(argc, argv, out, err);

    ASSERT_EQ(exit_code, 0);
    ASSERT_EQ(std::string("1.0.0\n"), out.str());
    ASSERT_TRUE(err.str().empty());
}

TEST(main, print_help_short)
{
    char arg0[] = "app";
    char arg1[] = "-h";
    int const argc = 2;
    char * argv[] = {arg0, arg1, nullptr};

    std::ostringstream out;
    std::ostringstream err;
    int const exit_code = example::main(argc, argv, out, err);

    ASSERT_EQ(exit_code, 0);
    ASSERT_FALSE(out.str().empty());
    ASSERT_TRUE(err.str().empty());
}

TEST(main, print_help_long)
{
    char arg0[] = "app";
    char arg1[] = "--help";
    int const argc = 2;
    char * argv[] = {arg0, arg1, nullptr};

    std::ostringstream out;
    std::ostringstream err;
    int const exit_code = example::main(argc, argv, out, err);

    ASSERT_EQ(exit_code, 0);
    ASSERT_FALSE(out.str().empty());
    ASSERT_TRUE(err.str().empty());
}

TEST(main, print_help_without_arguments)
{
    char arg0[] = "app";
    int const argc = 1;
    char * argv[] = {arg0, nullptr};

    std::ostringstream out;
    std::ostringstream err;
    int const exit_code = example::main(argc, argv, out, err);

    ASSERT_EQ(exit_code, 0);
    ASSERT_FALSE(out.str().empty());
    ASSERT_TRUE(err.str().empty());
}

TEST(main, invalid_option)
{
    char arg0[] = "app";
    char arg1[] = "--invalid";
    int const argc = 2;
    char * argv[] = {arg0, arg1, nullptr};

    std::ostringstream out;
    std::ostringstream err;
    int const exit_code = example::main(argc, argv, out, err);

    ASSERT_NE(exit_code, 0);
    ASSERT_TRUE(out.str().empty());
    ASSERT_FALSE(err.str().empty());
}
