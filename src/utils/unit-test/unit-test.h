#pragma once
#include <string>
#include <iostream>
#include <list>

namespace Test
{
  class UnitTest
  {
  private:
    std::list<std::string> failures;

  protected:
    // Método assert atualizado para receber o arquivo e a linha
    void assert(bool condition, const std::string_view &failureMessage, const char *file, int line)
    {
      if (condition)
      {
        std::cout << ".";
        return;
      }
      else
      {
        std::cout << "F";
        this->failures.push_back("Assertion failed at " + std::string(file) + ":" + std::to_string(line) + " - " + std::string(failureMessage));
      }
    }

  public:
    virtual void run() = 0;

    auto getFailures()
    {
      return this->failures;
    }
  };
}

// Defina a macro ASSERT aqui
#define ASSERT(condition) assert(condition, "Assertion failed: " #condition, __FILE__, __LINE__)
