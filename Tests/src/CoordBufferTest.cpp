
#include <osmscout/util/Transformation.h>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace osmscout;

TEST_CASE("Check rejection of invalid offsets")
{
  CoordBuffer buffer;
  size_t trFrom, trTo;
  // should fail - buffer is empty
  REQUIRE_FALSE(buffer.GenerateParallelWay(/*from*/0, /*to*/1, /*offset*/-1, trFrom, trTo));

  buffer.PushCoord(0,0);
  buffer.PushCoord(10,0);
  buffer.PushCoord(5,1);
  buffer.PushCoord(0,0);

  // should fail - end after last valid point
  REQUIRE_FALSE(buffer.GenerateParallelWay(/*from*/0, /*to*/4, /*offset*/-1, trFrom, trTo));
  // should fail - just one point
  REQUIRE_FALSE(buffer.GenerateParallelWay(/*from*/3, /*to*/3, /*offset*/-1, trFrom, trTo));
}

TEST_CASE("Check bounding box of generated parallel way")
{
  CoordBuffer buffer;
  size_t trFrom, trTo;

  buffer.PushCoord(0,0);
  buffer.PushCoord(10,0);
  buffer.PushCoord(5,1);
  buffer.PushCoord(0,0);

  REQUIRE(buffer.GenerateParallelWay(/*from*/0, /*to*/3, /*offset*/-1, trFrom, trTo));
  REQUIRE(trTo - trFrom >= 3);
  REQUIRE(trFrom > 3);

  // get bounding box of parallel way
  double minX, maxX, minY, maxY;
  minX = maxX = buffer.buffer[trFrom].GetX();
  minY = maxY = buffer.buffer[trFrom].GetY();
  for (size_t i=trFrom; i<=trTo; i++){
    //std::cout << buffer.buffer[i].GetX() << " , " << buffer.buffer[i].GetY() << std::endl;
    minX = std::min(minX, buffer.buffer[i].GetX());
    maxX = std::max(maxX, buffer.buffer[i].GetX());
    minY = std::min(minY, buffer.buffer[i].GetY());
    maxY = std::max(maxY, buffer.buffer[i].GetY());
  }

  REQUIRE(minX > -1);
  REQUIRE(maxX <= 12);
  REQUIRE(minY >= -1);
  REQUIRE(maxY < 3);

  REQUIRE(buffer.GenerateParallelWay(/*from*/0, /*to*/3, /*offset*/1, trFrom, trTo));
  REQUIRE(trFrom > 7);
}