#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../main.h"

TEST_CASE("test direct search", "[search]")
{
    REQUIRE(!search(""));
    REQUIRE(!search(" "));
}

TEST_CASE("test ISBN", "[isISBNvalid]")
{
    REQUIRE(!isISBNvalid("978032114653"));
    REQUIRE(!isISBNvalid("978020163361"));
    REQUIRE(isISBNvalid("9780070446878"));
    REQUIRE(!isISBNvalid("∆^~µ¬øΩπ≈ø ∫"));
    REQUIRE(!isISBNvalid(""));
    REQUIRE(!isISBNvalid("     "));
}

TEST_CASE("test qty entered", "[isQtyDigit]")
{
    REQUIRE(isQtyDigit("978032"));
    REQUIRE(!isQtyDigit(" "));
    REQUIRE(!isQtyDigit(""));
    REQUIRE(!isQtyDigit("¯˘ø ∫¬≤∂"));
    REQUIRE(!isQtyDigit("Θ"));
}

TEST_CASE("test new book's title", "[isTitleFirstLetterCapital]")
{
    REQUIRE(!isTitleFirstLetterCapital("ldeo"));
    REQUIRE(isTitleFirstLetterCapital("Tebana"));
    REQUIRE(!isTitleFirstLetterCapital(""));
    REQUIRE(isTitleFirstLetterCapital("¯˘ø ∫¬≤∂"));
    REQUIRE(isTitleFirstLetterCapital("Θ"));
}

