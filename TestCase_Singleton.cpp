/*
  Copyright (C) 2021 hidenorly

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <gtest/gtest.h>
#include "Singleton.hpp"

TestCase_System::TestCase_System()
{
}

TestCase_System::~TestCase_System()
{
}

void TestCase_System::SetUp()
{
}

void TestCase_System::TearDown()
{
}


TEST_F(TestCase_System, testSingleton)
{
  class SingletonTest : public SingletonBase<SingletonTest>
  {
  public:
    bool isWorking(void){ return true; };
  };

  std::cout << SingletonTest::getReferenceCount() << std::endl;
  EXPECT_EQ( SingletonTest::getReferenceCount(), 0 );
  std::weak_ptr<SingletonTest> pWeakInstance = SingletonTest::getInstance();
  EXPECT_EQ( SingletonTest::getReferenceCount(), 1 );
  EXPECT_EQ( pWeakInstance.expired(), false );
  if( !pWeakInstance.expired() ){
    std::cout << SingletonTest::getReferenceCount() << std::endl;
    std::shared_ptr<SingletonTest> pSharedInstance = pWeakInstance.lock();
    EXPECT_EQ( SingletonTest::getReferenceCount(), 2 );
    std::cout << SingletonTest::getReferenceCount() << std::endl;
    EXPECT_NE( pSharedInstance, nullptr );
    if( pSharedInstance ){
      EXPECT_TRUE( pSharedInstance->isWorking() );
    }
    pSharedInstance.reset();
    std::cout << SingletonTest::getReferenceCount() << std::endl;
  EXPECT_EQ( SingletonTest::getReferenceCount(), 1 );
  }
  SingletonTest::close();
  std::cout << SingletonTest::getReferenceCount() << std::endl;
  EXPECT_EQ( SingletonTest::getReferenceCount(), 0 );
  EXPECT_EQ( pWeakInstance.expired(), true );
}
