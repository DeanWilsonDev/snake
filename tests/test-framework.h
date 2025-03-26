#pragma once

#include <string>
#include <functional>

struct TestCase {
  std::string name;
  std::function<void()> testFunc;
};

class TestFramework {
 public:
  static void RegisterTest(const std::string& name, std::function<void()> func);
  static void RunTests(const std::optional<std::string>& groupName = std::nullopt);
  static void SetCurrentGroup(const std::string& groupName);
  static void ClearCurrentGroup();

 private:
  static std::vector<TestCase>& GetTests();
  static std::optional<std::string>& GetCurrentGroup();
};

#define TEST(name, func)                     \
  static bool _##name = []() {               \
    TestFramework::RegisterTest(name, func); \
    return true;                             \
  }()
#define IT(name, func) TEST(name, func)

#define DESCRIBE(name, func)                \
  struct _DescribeBlock_##__LINE__ {        \
    _DescribeBlock_##__LINE__()             \
    {                                       \
      TestFramework::SetCurrentGroup(name); \
      func();                               \
      TestFramework::ClearCurrentGroup();   \
    }                                       \
  };                                        \
  static _DescribeBlock_##__LINE__ _describe_block_##__LINE__

#define ASSERT_TRUE(cond)                                                           \
  if (!(cond)) {                                                                    \
    std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT_TRUE failed: " #cond "\n"; \
    throw std::runtime_error("Test failed");                                        \
  }

#define ASSERT_EQUALS(val1, val2)                                                   \
  if ((val1) != (val2)) {                                                           \
    std::cerr << __FILE__ << ":" << __LINE__ << " ASSERT_EQUALS failed: " << (val1) \
              << " != " << (val2) << "\n";                                          \
    throw std::runtime_error("Test failed");                                        \
  }\
