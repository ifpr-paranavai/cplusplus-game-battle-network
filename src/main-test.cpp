#include <iostream>
#include <vector>
#include "./utils/unit-test/unit-test.h"

int main()
{
  std::vector<Test::UnitTest *> tests = {};
  bool hasFailures = false;

  // Executar todos os testes
  for (auto test : tests)
  {
    test->run();
  }

  std::cout << std::endl;

  // Exibir falhas dos testes
  for (auto test : tests)
  {
    for (const auto &failureMessage : test->getFailures())
    {
      hasFailures = true;
      std::cout << failureMessage << std::endl;
    }
  }

  std::cout << std::endl;

  // Exibir resultado dos testes
  if (hasFailures)
  {
    std::cout << "Tests have failed!" << std::endl;
  }
  else
  {
    std::cout << "Tests successfully finished!" << std::endl;
  }

  // Liberar a memória alocada
  for (auto test : tests)
  {
    delete test;
  }

  return 0;
}
