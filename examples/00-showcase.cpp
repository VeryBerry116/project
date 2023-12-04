#include "openai.hpp"

#include <iostream>

int main() {
    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable
    // openai::start("your_API_key", "optional_organization"); // Or you can handle it yourself

    /*auto completion = openai::completion().create(R"(
    {
        "model": "gpt-3.5-turbo",
        "prompt": "Who win the 2002 World Cup?",
        "max_tokens": 7,
        "temperature": 0
    }
    )"_json); // Using user-defined (raw) string literals
    std::cout << "Response is:\n" << completion.dump(2) << '\n'; */

    auto image = openai::image().create({
        { "prompt", "A logo with a cello in a heart"},
        { "n", 1 },
        { "size", "512x512" }
    }); // Using initializer lists
    std::cout << "Image URL is: " << image << '\n'; 
}
