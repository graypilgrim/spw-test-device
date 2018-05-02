#include <catch/catch.hpp>
#include <Package.hpp>

TEST_CASE( "Package constructors", "[package]" ) {
	SECTION( "Zero len" ) {
		Package p{0};

		REQUIRE( p.isValid() == true );
		REQUIRE( p.getDataLen() == 0 );
		REQUIRE( p.getDataCRC() == 0 );
	}

	SECTION( "Small package" ) {
		size_t size = 16;
		Package p{size};

		REQUIRE( p.isValid() == true );
		REQUIRE( p.getDataLen() == size );
	}

	SECTION( "Big package" ) {
		size_t size = 65536;
		Package p{size};

		REQUIRE( p.isValid() == true );
		REQUIRE( p.getDataLen() == size );
	}
}
