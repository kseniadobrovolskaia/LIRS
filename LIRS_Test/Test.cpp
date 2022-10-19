#include "Test.hpp"




//-----------------Test_LIRS--------------------------

TEST(Test_Hits_LIRS, Test1)
{
  EXPECT_EQ(read_file(answers_lirs, 1), read_file(results_lirs, 1));

}

TEST(Test_Hits_LIRS, Test2)
{

  EXPECT_EQ(read_file(answers_lirs, 2), read_file(results_lirs, 2));

}

TEST(Test_Hits_LIRS, Test3)
{

  EXPECT_EQ(read_file(answers_lirs, 3), read_file(results_lirs, 3));

}

TEST(Test_Hits_LIRS, Test4)
{

  EXPECT_EQ(read_file(answers_lirs, 4), read_file(results_lirs, 4));

}

TEST(Test_Hits_LIRS, Test5)
{

  EXPECT_EQ(read_file(answers_lirs, 5), read_file(results_lirs, 5));

}


//-----------------Test_Perfect_Cash-----------------


TEST(Test_Hits_Perfect_Cash, Test1)
{

  EXPECT_EQ(read_file(answers_perf, 1), read_file(results_perf, 1));

}

TEST(Test_Hits_Perfect_Cash, Test2)
{

  EXPECT_EQ(read_file(answers_perf, 2), read_file(results_perf, 2));

}

TEST(Test_Hits_Perfect_Cash, Test3)
{

  EXPECT_EQ(read_file(answers_perf, 3), read_file(results_perf, 3));

}

TEST(Test_Hits_Perfect_Cash, Test4)
{

  EXPECT_EQ(read_file(answers_perf, 4), read_file(results_perf, 4));

}

TEST(Test_Hits_Perfect_Cash, Test5)
{

  EXPECT_EQ(read_file(answers_perf, 5), read_file(results_perf, 5));

}


