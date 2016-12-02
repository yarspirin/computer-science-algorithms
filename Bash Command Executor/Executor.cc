//
// Created by whoami on 12/2/16.
//

#include "Executor.h"

#include <iostream>

Executor::Executor()
    : start_time_(clock()) {
      std::string current_string;

  // Go through the whole file, parse lines and put commands' info into commands_
  while (std::getline(std::cin, current_string)) {
    size_t whitespace = current_string.find(" ");

    int time = std::stoi(current_string.substr(0, whitespace));
    std::string command = current_string.substr(whitespace + 1, current_string.length() - whitespace - 1);

    commands_.push_back(PendingCommand(time, command));
  }
}

void Executor::SortCommands() {
  std::sort(commands_.begin(), commands_.end());
}

const std::vector<PendingCommand>& Executor::GetCommands() const {
  return commands_;
}

void Executor::Execute() {
  for (auto& command : commands_) {
    while (clock() - start_time_ < command.time * CLOCKS_PER_SEC) {
      int tmp = 0;
      tmp++;
    }
    exit_status_.push_back(system(command.command.c_str()));
  }
}

const std::vector<int>& Executor::GetExitStatus() const {
  return exit_status_;
}
