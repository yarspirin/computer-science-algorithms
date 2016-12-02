//
// Created by whoami on 12/2/16.
//

#ifndef EXECUTOR_EXECUTOR_H
#define EXECUTOR_EXECUTOR_H

#include <ctime>
#include <string>
#include <vector>

// Store info about command in an appropriate way
struct PendingCommand {
  PendingCommand(int _time, const std::string& _command)
      : time(_time),
        command(_command) { }

  bool operator < (const PendingCommand& other) const {
    return time < other.time;
  }

  int time;
  std::string command;
};

// Process the input file and execute given commands
class Executor {
 public:
  Executor();

  // Sort commands by their execution time
  void SortCommands();

  // Dump all commands in the sorted order
  const std::vector<PendingCommand>& GetCommands() const;

  // Execute all commands, keep track of their exit statuses
  void Execute();

  // Return exit statuses of programs
  const std::vector<int>& GetExitStatus() const;


 private:
  std::clock_t start_time_;

  std::vector<int> exit_status_;
  std::vector<PendingCommand> commands_;
};


#endif //EXECUTOR_EXECUTOR_H
