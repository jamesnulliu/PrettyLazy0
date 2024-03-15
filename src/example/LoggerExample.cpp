// This file is a simple example of how to use plazy logger system.
#include "example.hpp"
#include "plazy/Common/Logger.hpp"

void loggerExample()
{
    PLAZY_CRITICAL("********** Logger Example Begin **********");

    // Log a trace message
    PLAZY_TRACE("This is a trace message");
    // Log an info message
    PLAZY_INFO("This is an info message");
    // Log a warning message
    PLAZY_WARNING("This is a warning message");
    // Log an error message
    PLAZY_ERROR("This is an error message");
    // Log a critical message
    PLAZY_CRITICAL("This is a critical message");

    // Also, you can format the message just like using std::format
    // `{}` is the placeholder for the arguments, 42
    PLAZY_TRACE("The {} is {}", "answer", 42);
    // `:.2f` formats the number as a floating-point number with two decimal places
    PLAZY_INFO("The diameter of earth is {:.2f} km", 12742.0);
    // `:.2e` formats the number in scientific notation with two decimal places
    PLAZY_WARNING("The speed of light is {:.2e} m/s", 299792458.0);
    // `:>10` aligns the string to the right with a width of 6
    PLAZY_ERROR("epoch: {:>6}; acc: {:>6.2f}%, loss: {:>6.2f}", 114514, 0.99, 0.01);

    PLAZY_CRITICAL("********** Logger Example End **********");
}
