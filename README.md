# Smart Pointer Singleton

Singleton template with Smart Pointer

# How to use (simplified)

```
class SingletonTest : public SingletonBase<SingletonTest>
{
public:
  bool isWorking(void){ return true; };
};

std::weak_ptr<SingletonTest> pWeakInstance = SingletonTest::getInstance();

if( (std::shared_ptr<SingletonTest> pSharedInstance = pWeakInstance.lock()) ){
  pSharedInstance->isWorking();
}

SingletonTest::close();
```

# Behavior explanation

```
class SingletonTest : public SingletonBase<SingletonTest>
{
public:
  bool isWorking(void){ return true; };
};

std::cout << SingletonTest::getReferenceCount() << std::endl; // you can check ref counter. At this point, it will return 0;

std::weak_ptr<SingletonTest> pWeakInstance = SingletonTest::getInstance();
std::cout << SingletonTest::getReferenceCount() << std::endl; // it will return 1

if( !pWeakInstance.expired() ){
  std::shared_ptr<SingletonTest> pSharedInstance = pWeakInstance.lock();
  std::cout << SingletonTest::getReferenceCount() << std::endl; // it will return 2
  if( pSharedInstance ){
    pSharedInstance->isWorking();
  }
  pSharedInstance.reset(); // in this example, this is not necessary since this is smart pointer
  std::cout << SingletonTest::getReferenceCount() << std::endl; // it will return 1
}

SingletonTest::close(); // after this, pWeakInstance.expired() will return true and pWeakInstance.lock() will return nullptr of shared_ptr.

std::cout << SingletonTest::getReferenceCount() << std::endl; // it will return 0
```