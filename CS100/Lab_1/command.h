#ifndef __COMMAND_CLASS__
#define __COMMAND_CLASS__

#include "composite.h"

class Command {
	protected:
		Base* root;
	
	public:
		Command() { };
		double execute() {
			return root->evaluate();
		};
		Base* get_root() {
			return root;
		};
};

class OpCommand : public Command {
	//OpCommand Code Here
	public:
		//OpCommand() : Command(), root(NULL){};
		OpCommand(int op)
		{
	     	this->root = new Op(op);
		}
};

class AddCommand : public Command {
	//AddCommand Code Here
	public:
		AddCommand() { };
		AddCommand(Command* curr, int val)
		{
	        Base* temp = new Op(val);
			this->root = new Add(curr->get_root(),temp);
	        //cout << "I am in AddCommand" << endl;
		}
};

class SubCommand : public Command {
	//SubCommand Code Here
	public:
		SubCommand() {};
		SubCommand(Command* curr, int val)
		{
			Base* temp = new Op(val);
			this->root = new Sub(curr->get_root(), temp);
		}
};

class MultCommand : public Command {
	//MultCommand Code Here
	public:
		MultCommand() {};
		MultCommand(Command* curr, int val)
		{
	        Base* temp = new Op(val);
			this->root = new Mult(curr->get_root(),temp);
		}
};

class SqrCommand : public Command {
	//SqrCommand Code Here
	public:
		SqrCommand() {};
		SqrCommand(Command* curr)
		{
			this->root = new Sqr(curr->get_root());
		}
};

#endif //__COMMAND_CLASS__
