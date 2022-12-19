#pragma once
#include "tumasulo_algorithm.h"


struct Instruction_Status
{

	short Issue_Instruction;
	short Execution_Start_Time;
	short Execution_Complete_Time;
	short Write_Back;

	short executionCyclesRemaining;
	Instruction_Status()
	{
		Issue_Instruction = Execution_Start_Time = Execution_Complete_Time = Write_Back = executionCyclesRemaining = -1;
	}
};

struct Instruction_Type
{
public:
	string static const JAL;
	string static const RETURN;
	string static const MULT;
	string static const SUB;
	string static const ADD;
	string static const DIV;
	string static const NEG;
	string static const NOR;
	string static const LOAD;
	string static const BEQ;
	string static const STORE;
};

string const Instruction_Type::JAL = "JAL";
string const Instruction_Type::RETURN = "RETURN";
string const Instruction_Type::MULT = "MUL";
string const Instruction_Type::SUB = "SUB";
string const Instruction_Type::ADD = "ADD";
string const Instruction_Type::DIV = "DIV";
string const Instruction_Type::NOR = "NOR";
string const Instruction_Type::NEG = "NEG";
string const Instruction_Type::LOAD = "LOAD";
string const Instruction_Type::BEQ = "BEQ";
string const Instruction_Type::STORE = "STORE";

struct ReservationStationType
{
	static string const ADD;
	static string const MULT;
	static string const NEG;
	static string const NOR;
	static string const BEQ;
	static string const JAL;
};

string const ReservationStationType::ADD = "ADD";
string const ReservationStationType::MULT = "MUL";
string const ReservationStationType::NEG = "NEG";
string const ReservationStationType::NOR = "NOR";
string const ReservationStationType::BEQ = "BEQ";
string const ReservationStationType::JAL = "JAL";
struct LoadStoreBufferType
{
	static string const LOAD;
	static string const STORE;
};

string const LoadStoreBufferType::LOAD = "LOAD";
string const LoadStoreBufferType::STORE = "STORE";


struct Instruction
{
	string Instruction_Type;
	string Rd;
	string Rs;
	string Rt;
	int Immediate_Offset; 
	string label;
	Instruction_Status Instruction_Status;

	Instruction()
	{
		Instruction_Type = Rd = Rs = Rt = "";
		Immediate_Offset = -1;
	}
};

struct DataMemory
{
	string Data_Memory_Location;
	int Memory_Value;
};

struct RegisterStatus
{
	string Register_Name;
	string writing_reg;
	int Register_Value;
};

struct ReservationStation
{
	string name;
	string Instruction_Type;
	string Vj;
	string Vk;
	string Qj;
	string Qk;
	bool isBusy;
	Instruction* instruction;

	ReservationStation()
	{
		isBusy = false;
		instruction = nullptr;
	}


};

struct LoadStoreBuffer
{
	string name;
	string address;
	bool isBusy;
	LoadStoreBuffer()
	{
		name = "";
		isBusy = false;
		address = "";
		instruction = nullptr;
		fu = "";
	}

	string fu;
	Instruction* instruction;
};
