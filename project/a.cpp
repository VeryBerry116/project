
#include "openai.hpp"

#include <iostream>

int main() {
    openai::start();

    auto completion = openai::completion().create(R"(
    {
        "model": "text-davinci-003",
        "prompt": "Who is Korean President",
        "max_tokens": 7,
        "temperature": 0
    }
    )"_json);
    std::cout << "Response is:\n" << completion["choices"]["text"];
}