#include "CovidDB.h"
#include "run.h"

#define AUTHOR "Jakob" //define a macro

/**
 * @brief The entry point of the program.
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 * @return [EXIT_SUCESS], the exit status of the program.
 */
int main() {
  show_last_compiled(__FILE__, __DATE__, __TIME__, AUTHOR);
  run();
  return EXIT_SUCCESS;
}

