#include "test-framework.h"
#include <exception>
#include <iostream>

static std::vector<TestCase> tests;
static std::optional<std::string> currentGroup;

void TestFramework::RegisterTest(const std::string& name, std::function<void()> func)
{
  std::string fullName = currentGroup ? (*currentGroup + "::" + name) : name;
  GetTests().push_back({fullName, func});
}

std::vector<TestCase>& TestFramework::GetTests()
{
  return tests;
}

void TestFramework::SetCurrentGroup(const std::string& groupName)
{
  currentGroup = groupName;
}

void TestFramework::ClearCurrentGroup()
{
  currentGroup.reset();
}

void TestFramework::RunTests(const std::optional<std::string>& groupName)
{
  int totalTests = 0;
  int passed = 0;
  int failed = 0;

  for (const auto& test : GetTests()) {
    if (groupName && test.name.find(*groupName) != 0) {
      continue;
    }

    try {
      test.testFunc();
      std::cout << "[PASS] " << test.name << std::endl;
      ++passed;
    }
    catch (const std::exception& exception) {
      std::cerr << "[FAIL] " << test.name << ": " << exception.what() << std::endl;
      ++failed;
    }
  }

  totalTests = passed + failed;
  std::cout << "\nTest run: " << totalTests << ", Passed: " << passed << ", Failed: " << failed
            << std::endl;
}
