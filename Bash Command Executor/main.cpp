#include <iostream>
#include <vector>

#include "Executor.h"

int main(int argc, const char * argv[]) {

  // Handle wrong command-line arguments
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " " << "<filename>" << std::endl;
    return EXIT_FAILURE;
  }

  // Handle file open error
  if (std::freopen(argv[1], "r", stdin) == NULL) {
    perror(("freopen() failed with arguments: " + std::string(argv[1]) + " r" + " stdin").c_str());
    return EXIT_FAILURE;
  }

  Executor executor;
  executor.SortCommands();
  executor.Execute();

  std::vector<PendingCommand> commands = executor.GetCommands();
  std::vector<int> exit_status = executor.GetExitStatus();

  std::cout << std::endl;
  for (int i = 0; i < commands.size(); ++i) {
    std::cout << "Command: " << commands[i].time << " " << commands[i].command << std::endl;
    std::cout << "Status: " << exit_status[i] << std::endl << std::endl;
  }

  std::fclose(stdin);
  return 0;
}
