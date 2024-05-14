#pragma once
#include <functional>
#include <string>
#include <vector>

namespace plazy
{

namespace Action
{
int print(const std::vector<int>& operand);
int assign(const std::vector<int>& operand);
int opposite(const std::vector<int>& operand);
int add(const std::vector<int>& operands);
int subtract(const std::vector<int>& operands);
int multiply(const std::vector<int>& operands);
int divide(const std::vector<int>& operands);
}  // namespace Action

}  // namespace plazy