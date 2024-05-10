#include "plazy/Core/Action.hpp"
#include "plazy/Common/Exceptions.hpp"
#include "plazy/Common/Logger.hpp"
#include <format>

namespace plazy
{

namespace Action
{
int print(const std::vector<int>& operand)
{
    if (operand.empty()) {
        throw SemanticError("No operand to print.");
    }
    if (operand.size() > 1) {
        throw SemanticError("Too many operands to print.");
    }
    int ans = operand[0];
    YINFO("Ans = {}", ans);
    return ans;
}

int assign(const std::vector<int>& operand)
{
    if (operand.empty()) {
        throw SemanticError("No operand for assignment.");
    }
    if (operand.size() > 1) {
        throw SemanticError("Too many operands for assignment.");
    }
    return operand[0];
}

int opposite(const std::vector<int>& operand)
{
    if (operand.empty()) {
        throw SemanticError("No operand for opposite.");
    }
    if (operand.size() > 1) {
        throw SemanticError("Too many operands for opposite.");
    }
    return -operand[0];
}

int add(const std::vector<int>& operands)
{
    if (operands.size() < 2) {
        throw SemanticError("Too few operands for addition.");
    }
    if (operands.size() > 2) {
        throw SemanticError("Too many operands for addition.");
    }

    return operands[0] + operands[1];
}

int subtract(const std::vector<int>& operands)
{
    if (operands.size() < 2) {
        throw SemanticError("Too few operands for subtraction.");
    }
    if (operands.size() > 2) {
        throw SemanticError("Too many operands for subtraction.");
    }
    return operands[0] - operands[1];
}

int multiply(const std::vector<int>& operands)
{
    if (operands.size() < 2) {
        throw SemanticError("Too few operands for multiplication.");
    }
    if (operands.size() > 2) {
        throw SemanticError("Too many operands for multiplication.");
    }
    return operands[0] * operands[1];
}

int divide(const std::vector<int>& operands)
{
    if (operands.size() < 2) {
        throw SemanticError("Too few operands for division.");
    }
    if (operands.size() > 2) {
        throw SemanticError("Too many operands for division.");
    }
    if (operands[1] == 0) {
        throw SemanticError("Division by zero.");
    }
    return operands[0] / operands[1];
}
}  // namespace Action

}  // namespace plazy