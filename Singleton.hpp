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

#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <memory>

template<typename Derived> class SingletonBase
{
private:
  static inline std::shared_ptr<Derived> mInstance;

protected:
  SingletonBase(void) noexcept{};
  virtual ~SingletonBase(void) noexcept = default;

public:
  SingletonBase(const SingletonBase&) noexcept = delete;
  SingletonBase(SingletonBase&&) noexcept = delete;
  SingletonBase& operator=(const SingletonBase&) noexcept = delete;
  SingletonBase& operator=(SingletonBase&&) noexcept = delete;

  template<typename... Ts> static std::weak_ptr<Derived> getInstance(Ts&&... _args) noexcept {
    if( !mInstance ){
      mInstance = std::make_shared<Derived>(std::forward<Derived>(_args)...);
    }
    return mInstance;
  }
  static int getReferenceCount(){
    return mInstance.use_count();
  }

  static void close(void) noexcept{
    mInstance.reset();
  };
};

#endif /* __SINGLETON_HPP__ */