#ifndef __SIMPLE_REMOTE_CONTROL_H__
#define __SIMPLE_REMOET_CONTROL_H__

#include <iostream>
#include <vector>

#include "Command.h"

class RemoteControl {
public:	
	RemoteControl() {
		Command* noCommand = new NoCommand;
		for (int i = 0; i < 7; ++i) {
			mOnCommands.push_back(noCommand);
			mOffCommands.push_back(noCommand);
		}
		undoCommand = noCommand;
	}

	void setCommand(int slot, Command* onCmd, Command* offCmd) {
		mOnCommands[slot] = onCmd;
		mOffCommands[slot] = offCmd;
	}

	void setCommand(int slot, Command* onCmd) {
		mOnCommands[slot] = onCmd;
	}

	void onButtonWasPressed(int slot) {
		mOnCommands[slot]->execute();
		undoCommand = mOnCommands[slot];
	}

	void offButtonWasPressed(int slot) {
		mOffCommands[slot]->execute();
		undoCommand = mOffCommands[slot];
	}

	void undoButtonWasPressed() {
		undoCommand->undo();
	}

	void status() {
		std::cout << "---------- Remote Control ----------\n";
		for (int i = 0; i < mOnCommands.size(); ++i) {
			std::cout << "[slot " << i << "] " << typeid(mOnCommands[i]).name() << ' ';
			std::cout << typeid(mOffCommands[i]).name() << '\n';
		}
	}

private:
	std::vector<Command*> mOnCommands;
	std::vector<Command*> mOffCommands;
	Command* undoCommand;
};

#endif