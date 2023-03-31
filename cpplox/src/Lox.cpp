/**
 * @brief Main
 */
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <memory>

#include <scanner/Scanner.h>

static std::unique_ptr<Lox::Scanner> run(std::string);
static void runFile(std::string);
static void runPrompt(void);


static void runFile(std::string filepath)
{
    std::ifstream file { filepath };
    std::stringstream buffer;
    buffer << file.rdbuf();
    auto scnuptr = run(buffer.str());

    if (scnuptr->getHadError()) {
        scnuptr->outputErrors(std::cerr);
        exit(65);
    }
}

static void runPrompt(void)
{
    for (;;) {
        std::cout << "> ";

        std::string line;
        std::getline(std::cin, line);
        if (!std::cin)
            break;

        auto scnuptr = run(line);
        if (scnuptr->getHadError())
            scnuptr->outputErrors(std::cerr, true);

        scnuptr->setHadError(false);
    }
}

static std::unique_ptr<Lox::Scanner> run(std::string source)
{
    std::unique_ptr<Lox::Scanner> scn { std::make_unique<Lox::Scanner>(source) };
    std::vector<std::shared_ptr<Lox::Token>> tokens = scn->scanTokens();

    for (auto tok : tokens) {
        std::cout << tok->toString() << std::endl;
    }

    return scn;
}


int main(int argc, char *argv[])
{
    if (argc > 2) {
        std::cout << "Usage: cpplox [script]" << std::endl;
        return EXIT_FAILURE;
    }
    else if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        runPrompt();
    }
}
