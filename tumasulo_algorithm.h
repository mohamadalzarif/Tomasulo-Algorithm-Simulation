#pragma once
#include <iostream>
using namespace std;
#include <iomanip>
#include <string>
#include <fstream>
#include "definitions.h"
#include <bitset>

string decimal_to_binary(int number);
int nor_operation(string bin1, string bin2);
int twos_complement(string bin);

class Tomasulo
{
public:
	int current_Cycle_Number;
	LoadStoreBuffer* Load_ReservationStations;
	LoadStoreBuffer* Store_ReservationStations;
	ReservationStation* AddSub_ReservationStations;
	ReservationStation* MultDiv_ReservationStations;
	ReservationStation* Neg_ReservationStations;
	ReservationStation* Nor_ReservationStations;
	ReservationStation* Beq_ReservationStations;
	ReservationStation* Jal_ReservationStations;
	RegisterStatus* registerStatus;


	int totalLoad_ReservationStations;
	int totalStore_ReservationStations;
	int totalAddSub_ReservationStations;
	int totalMultDiv_ReservationStations;
	int totalNeg_ReservationStations;
	int totalNor_ReservationStations;
	int totalBeq_Reservation_Stations;
	int totalJal_Reservation_Stations;

	int totalRegisters;
	Instruction* instructions;
	DataMemory* data_memory;
	int totalInstructions;
	int totalMemoryLocations;

	int totalLoadCycles;
	int totalStoreCycles;
	int totalAddSubCycles;
	int totalMultCylcles;
	int totalDivCycles;
	int totalNegCycles;
	int totalBeqCycles;
	int totalJalCycles;
	int totalNorCycles;
	void load_data(string fileName)
	{

		if (fileName == "")
		{
			fileName = "data.txt";
		}

		ifstream read;
		read.open(fileName);
		if (read.is_open() == false)
		{
			cout << "File could not open!" << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}

		string data;

		while (read.peek() != '#')
			read.ignore();

		getline(read, data);
		read >> this->totalMemoryLocations;
		this->data_memory = new DataMemory[this->totalMemoryLocations];

		for (int i = 0; i < totalMemoryLocations; i++)
		{
			string data_memory;
			read >> data_memory;
			if (_strcmpi(data_memory.c_str(), "Data") == 0)
			{
				read >> this->data_memory[i].Data_Memory_Location;
				read >> this->data_memory[i].Memory_Value;
			}
		}



	}
	void load(string fileName)
	{

		if (fileName == "")
		{
			fileName = "data_file.txt";
		}

		ifstream read;
		read.open(fileName);
		if (read.is_open() == false)
		{
			cout << "File could not open!" << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}

		string data;
		while (read.peek() != '#')
			read.ignore();

		getline(read, data);
		bool loadDone = false,
			storeDone = false,
			addSUBDone = false,
			MULTDivDone = false,
			NEGDone = false,
			NORDone = false,
			JALDone = false,
			BEQDone = false;

		bool exit_ = false;

		for (int i = 0; i < 8; i++)
		{
			read >> data;
			if (_strcmpi(data.c_str(), "Add_Sub_Reservation_Stations") == 0)
			{
				addSUBDone = true;
				read >> this->totalAddSub_ReservationStations;
			}
			if (_strcmpi(data.c_str(), "Jal_Reservation_Stations") == 0)
			{
				JALDone = true;
				read >> this->totalJal_Reservation_Stations;
			}
			else if (_strcmpi(data.c_str(), "Mul_Div_Reservation_Stations") == 0)
			{
				MULTDivDone = true;
				read >> this->totalMultDiv_ReservationStations;
			}

			else if (_strcmpi(data.c_str(), "Load_Buffers") == 0)
			{
				loadDone = true;
				read >> this->totalLoad_ReservationStations;
			}

			else if (_strcmpi(data.c_str(), "Store_Buffers") == 0)
			{
				storeDone = true;
				read >> this->totalStore_ReservationStations;
			}

			else if (_strcmpi(data.c_str(), "Neg_Reservation_Stations") == 0)
			{
				NEGDone = true;
				read >> this->totalNeg_ReservationStations;
			}

			else if (_strcmpi(data.c_str(), "Nor_Reservation_Stations") == 0)
			{
				NORDone = true;
				read >> this->totalNor_ReservationStations;
			}
			else if (_strcmpi(data.c_str(), "Beq_Reservation_Stations") == 0)
			{
				BEQDone = true;
				read >> this->totalBeq_Reservation_Stations;
			}

		}
		if (!storeDone)
		{
			cout << "-> Information about the number of store buffers missing." << endl;
			exit_ = true;

		}
		else if (!loadDone)
		{
			cout << "-> Informaton about the number of load buffers missing." << endl;
			exit_ = true;
		}
		else if (!MULTDivDone)
		{
			cout << "-> Information about the number of Mult Div Reservation Stations missing" << endl;
			exit_ = true;
		}
		else if (!addSUBDone)
		{
			cout << "-> Information about the number of Add Sub Reservation Stations missing." << endl;
			exit_ = true;
		}
		else if (!NEGDone)
		{
			cout << "-> Information about the number of Neg Reservation Stations missing." << endl;
			exit_ = true;
		}
		else if (!NORDone)
		{
			cout << "-> Information about the number of Nor Reservation Stations missing." << endl;
			exit_ = true;
		}
		else if (!BEQDone)
		{
			cout << "-> Information about the number of Beq Reservation Stations missing." << endl;
			exit_ = true;
		}
		else if (!JALDone)
		{
			cout << "-> Information about the number of JAL Reservation Stations missing." << endl;
			exit_ = true;
		}

		bool multCyclesDone = false,
			divCyclesDones = false,
			addSubCyclesDone = false,
			NegCyclesDone = false,
			NorCyclesDone = false,
			loadCyclesDone = false,
			BeqCyclesDone = false,
			StoreCyclesDone = false,
		    JalCyclesDone = false;
		while (read.peek() != '#')
			read.ignore();

		getline(read, data); 
		for (int i = 0; i < 9; i++)
		{
			read >> data;
			if (_strcmpi(data.c_str(), "Add_Sub_Cycles") == 0)
			{

				read >> this->totalAddSubCycles;
				addSubCyclesDone = true;
			}

			else if (_strcmpi(data.c_str(), "Mul_Cycles") == 0)
			{
				read >> this->totalMultCylcles;
				multCyclesDone = true;
			}
			else if (_strcmpi(data.c_str(), "Load_Cycles") == 0)
			{
				read >> this->totalLoadCycles;
				loadCyclesDone = true;
			}
			else if (_strcmpi(data.c_str(), "Div_Cycles") == 0)
			{
				read >> this->totalDivCycles;
				divCyclesDones = true;
			}
			else if (_strcmpi(data.c_str(), "Store_Cycles") == 0)
			{
				read >> this->totalStoreCycles;
				StoreCyclesDone = true;
			}
			else if (_strcmpi(data.c_str(), "Neg_Cycles") == 0)
			{
				read >> this->totalNegCycles;
				NegCyclesDone = true;
			}
			else if (_strcmpi(data.c_str(), "Nor_Cycles") == 0)
			{
				read >> this->totalNorCycles;
				NorCyclesDone = true;
			}
			else if (_strcmpi(data.c_str(), "Beq_Cycles") == 0)
			{
				read >> this->totalBeqCycles;
				BeqCyclesDone = true;
			}
			else if (_strcmpi(data.c_str(), "Jal_Cycles") == 0)
			{
				read >> this->totalJalCycles;
				JalCyclesDone = true;
			}
		}

		if (!addSubCyclesDone)
		{
			cout << "-> Information about the number of add Sub Cycles missing.";
			exit_ = true;
		}

		if (!multCyclesDone)
		{
			cout << "-> Information about the number of mul cycles missing." << endl;
			exit_ = true;
		}
		else if (!divCyclesDones)
		{
			cout << "-> Information about the number of div cycles missing." << endl;
			exit_ = true;
		}
		else if (!loadCyclesDone)
		{
			cout << "-> Information about the number of load cycles missing." << endl;
			exit_ = true;
		}
		else if (!StoreCyclesDone)
		{
			cout << "-> Information about the number of store cycles missing." << endl;
			exit_ = true;
		}
		else if (!NegCyclesDone)
		{
			cout << "-> Information about the number of neg cycles missing." << endl;
			exit_ = true;
		}
		else if (!BeqCyclesDone)
		{
			cout << "-> Information about the number of Beq cycles missing." << endl;
			exit_ = true;
		}
		else if (!JalCyclesDone)
		{
			cout << "-> Information about the number of Jal cycles missing." << endl;
			exit_ = true;
		}
		else if (!NorCyclesDone)
		{
			cout << "-> Information about the number of nor cycles missing." << endl;
			exit_ = true;
		}

		if (exit_ == true)
		{
			system("pause");
			exit(EXIT_FAILURE);

		}

		this->Load_ReservationStations = new LoadStoreBuffer[this->totalLoad_ReservationStations];
		for (int i = 0; i < totalLoad_ReservationStations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->Load_ReservationStations[i].name = LoadStoreBufferType::LOAD;
			this->Load_ReservationStations[i].name.append(num);
		}

		this->Store_ReservationStations = new LoadStoreBuffer[this->totalStore_ReservationStations];
		for (int i = 0; i < totalStore_ReservationStations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->Store_ReservationStations[i].name = LoadStoreBufferType::STORE;
			this->Store_ReservationStations[i].name.append(num);
		}

		this->AddSub_ReservationStations = new ReservationStation[this->totalAddSub_ReservationStations];
		for (int i = 0; i < this->totalAddSub_ReservationStations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->AddSub_ReservationStations[i].name = ReservationStationType::ADD;
			this->AddSub_ReservationStations[i].name.append(num);
		}

		this->MultDiv_ReservationStations = new ReservationStation[this->totalMultDiv_ReservationStations];
		for (int i = 0; i < this->totalMultDiv_ReservationStations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->MultDiv_ReservationStations[i].name = ReservationStationType::MULT;
			this->MultDiv_ReservationStations[i].name.append(num);
		}

		this->Neg_ReservationStations = new ReservationStation[this->totalNeg_ReservationStations];
		for (int i = 0; i < this->totalNeg_ReservationStations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->Neg_ReservationStations[i].name = ReservationStationType::NEG;
			this->Neg_ReservationStations[i].name.append(num);
		}

		this->Beq_ReservationStations = new ReservationStation[this->totalBeq_Reservation_Stations];
		for (int i = 0; i < this->totalBeq_Reservation_Stations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->Beq_ReservationStations[i].name = ReservationStationType::BEQ;
			this->Beq_ReservationStations[i].name.append(num);
		}


		this->Nor_ReservationStations = new ReservationStation[this->totalNor_ReservationStations];
		for (int i = 0; i < this->totalNor_ReservationStations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->Nor_ReservationStations[i].name = ReservationStationType::NOR;
			this->Nor_ReservationStations[i].name.append(num);
		}

		this->Jal_ReservationStations = new ReservationStation[this->totalJal_Reservation_Stations];
		for (int i = 0; i < this->totalJal_Reservation_Stations; i++)
		{
			char num[10];
			_itoa_s(i, num, 10);
			this->Jal_ReservationStations[i].name = ReservationStationType::JAL;
			this->Jal_ReservationStations[i].name.append(num);
		}


		while (read.peek() != '#')
			read.ignore();

		getline(read, data);
		read >> data;
		read >> this->totalRegisters;
		this->registerStatus = new RegisterStatus[totalRegisters];

		for (int i = 0; i < 1; i++)
		{
			this->registerStatus[i].Register_Value = 0;
			this->registerStatus[i].Register_Name = "R";
			char num[10];
			_itoa_s(i, num, 10);
			this->registerStatus[i].Register_Name.append(num);
		}
		for (int i = 1; i < totalRegisters; i++)
		{
			this->registerStatus[i].Register_Value = 5;
			this->registerStatus[i].Register_Name = "R";
			char num[10];
			_itoa_s(i, num, 10);
			this->registerStatus[i].Register_Name.append(num);
		}
		


		while (read.peek() != '#')
			read.ignore();

		getline(read, data); 
		read >> this->totalInstructions;
		this->instructions = new Instruction[this->totalInstructions];

		for (int i = 0; i < totalInstructions; i++)
		{
			string instruction;
			read >> instruction;
			if (_strcmpi(instruction.c_str(), Instruction_Type::ADD.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::ADD;
				read >> this->instructions[i].Rd;
				read >> this->instructions[i].Rs;
				read >> this->instructions[i].Rt;
			}

			else if (_strcmpi(instruction.c_str(), Instruction_Type::SUB.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::SUB;
				read >> this->instructions[i].Rd;
				read >> this->instructions[i].Rs;
				read >> this->instructions[i].Rt;

			}
			else if (_strcmpi(instruction.c_str(), Instruction_Type::MULT.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::MULT;
				read >> this->instructions[i].Rd;
				read >> this->instructions[i].Rs;
				read >> this->instructions[i].Rt;

			}
			else if (_strcmpi(instruction.c_str(), Instruction_Type::DIV.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::DIV;
				read >> this->instructions[i].Rd;
				read >> this->instructions[i].Rs;
				read >> this->instructions[i].Rt;

			}

			else if (_strcmpi(instruction.c_str(), Instruction_Type::LOAD.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::LOAD;
				read >> this->instructions[i].Rt;
				read >> this->instructions[i].Immediate_Offset;
				read >> this->instructions[i].Rs;
			}

			else if (_strcmpi(instruction.c_str(), Instruction_Type::STORE.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::STORE;
				read >> this->instructions[i].Rt;
				read >> this->instructions[i].Immediate_Offset;
				read >> this->instructions[i].Rs;

			}

			else if (_strcmpi(instruction.c_str(), Instruction_Type::NEG.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::NEG;
				read >> this->instructions[i].Rd;
				read >> this->instructions[i].Rs;
			}

			else if (_strcmpi(instruction.c_str(), Instruction_Type::NOR.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::NOR;
				read >> this->instructions[i].Rd;
				read >> this->instructions[i].Rs;
				read >> this->instructions[i].Rt;
			}
			else if (_strcmpi(instruction.c_str(), Instruction_Type::BEQ.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::BEQ;
				read >> this->instructions[i].Rd;
				read >> this->instructions[i].Rs;
				read >> this->instructions[i].Immediate_Offset;
			}
			else if (_strcmpi(instruction.c_str(), Instruction_Type::JAL.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::JAL;
				read >> this->instructions[i].Immediate_Offset;
			}
			else if (_strcmpi(instruction.c_str(), Instruction_Type::RETURN.c_str()) == 0)
			{
				this->instructions[i].Instruction_Type = Instruction_Type::RETURN;
			}
		}



	}

	int find_free_RS_Store()
	{
		for (int i = 0; i < totalStore_ReservationStations; i++)
		{
			if (Store_ReservationStations[i].isBusy == false)
				return i;
		}

		return -1;
	}
	int find_free_RS_Jal()
	{
		for (int i = 0; i < totalJal_Reservation_Stations; i++)
		{
			if (Jal_ReservationStations[i].isBusy == false)
				return i;
		}

		return -1;
	}
	int find_free_RS_AddSub()
	{
		for (int i = 0; i < totalAddSub_ReservationStations; i++)
		{
			if (AddSub_ReservationStations[i].isBusy == false)
			{
				return i;
			}
		}
		return -1;
	}

	int find_free_RS_Neg()
	{
		for (int i = 0; i < totalNeg_ReservationStations; i++)
		{
			if (Neg_ReservationStations[i].isBusy == false)
			{
				return i;
			}
		}
		return -1;
	}

	int find_free_RS_Nor()
	{
		for (int i = 0; i < totalNor_ReservationStations; i++)
		{
			if (Nor_ReservationStations[i].isBusy == false)
			{
				return i;
			}
		}
		return -1;
	}

	int find_free_RS_MultDiv()
	{
		for (int i = 0; i < totalMultDiv_ReservationStations; i++)
		{
			if (MultDiv_ReservationStations[i].isBusy == false)
			{
				return i;
			}
		}
		return -1;
	}

	int find_free_RS_Load()
	{
		for (int i = 0; i < totalLoad_ReservationStations; i++)
		{
			if (Load_ReservationStations[i].isBusy == false)
				return i;

		}

		return -1;

	}
	int find_free_RS_Beq()
	{
		for (int i = 0; i < totalBeq_Reservation_Stations; i++)
		{
			if (Beq_ReservationStations[i].isBusy == false)
				return i;

		}

		return -1;

	}
	void output_result(string val, string name)
	{
		for (int i = 0; i < totalNeg_ReservationStations; i++)
		{
			if (this->Neg_ReservationStations[i].Qj == name)
			{
				this->Neg_ReservationStations[i].Qj = "";
				this->Neg_ReservationStations[i].Vj = val;

			}

		}

		for (int i = 0; i < totalBeq_Reservation_Stations; i++)
		{
			if (this->Beq_ReservationStations[i].Qj == name)
			{
				this->Beq_ReservationStations[i].Qj = "";
				this->Beq_ReservationStations[i].Vj = val;

			}
			if (this->Beq_ReservationStations[i].Qk == name)
			{
				this->Beq_ReservationStations[i].Qk = "";
				this->Beq_ReservationStations[i].Vk = val;
			}

		}
		for (int i = 0; i < totalJal_Reservation_Stations; i++)
		{
			if (this->Jal_ReservationStations[i].Qj == name)
			{
				this->Jal_ReservationStations[i].Qj = "";
				this->Jal_ReservationStations[i].Vj = val;

			}
			if (this->Jal_ReservationStations[i].Qk == name)
			{
				this->Jal_ReservationStations[i].Qk = "";
				this->Jal_ReservationStations[i].Vk = val;
			}

		}

		for (int i = 0; i < totalNor_ReservationStations; i++)
		{
			if (this->Nor_ReservationStations[i].Qj == name)
			{
				this->Nor_ReservationStations[i].Qj = "";
				this->Nor_ReservationStations[i].Vj = val;

			}

			if (this->Nor_ReservationStations[i].Qk == name)
			{
				this->Nor_ReservationStations[i].Qk = "";
				this->Nor_ReservationStations[i].Vk = val;
			}
		}

		for (int i = 0; i < totalLoad_ReservationStations; i++)
		{
			if (this->Load_ReservationStations[i].isBusy == false)
				continue;

			if (this->Load_ReservationStations[i].fu == name)
			{
				this->Load_ReservationStations[i].fu = "";
			}
		}

		for (int i = 0; i < totalStore_ReservationStations; i++)
		{
			if (this->Store_ReservationStations[i].isBusy == false)
				continue;

			if (this->Store_ReservationStations[i].fu == name)
			{
				this->Store_ReservationStations[i].fu = "";
			}
		}

		for (int i = 0; i < totalAddSub_ReservationStations; i++)
		{
			if (this->AddSub_ReservationStations[i].Qj == name)
			{
				this->AddSub_ReservationStations[i].Qj = "";
				this->AddSub_ReservationStations[i].Vj = val;

			}

			if (this->AddSub_ReservationStations[i].Qk == name)
			{
				this->AddSub_ReservationStations[i].Qk = "";
				this->AddSub_ReservationStations[i].Vk = val;
			}
		}

		for (int i = 0; i < totalMultDiv_ReservationStations; i++)
		{
			if (this->MultDiv_ReservationStations[i].Qj == name)
			{
				this->MultDiv_ReservationStations[i].Qj = "";
				this->MultDiv_ReservationStations[i].Vj = val;

			}

			if (this->MultDiv_ReservationStations[i].Qk == name)
			{
				this->MultDiv_ReservationStations[i].Qk = "";
				this->MultDiv_ReservationStations[i].Vk = val;
			}
		}
	}


	int Issue_InstructionInstruction(int currentInstruction_Number_ToBeIssued)
	{
		int bufferNo;
		char num[10];
		_itoa_s(currentInstruction_Number_ToBeIssued, num, 10);

		if (currentInstruction_Number_ToBeIssued < totalInstructions)
		{
			if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::LOAD)
			{
				bufferNo = find_free_RS_Load();

				if (bufferNo == -1)
				{

					return -1;
				}
				else
				{
					Load_ReservationStations[bufferNo].isBusy = true;
					Load_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
					Load_ReservationStations[bufferNo].address = this->instructions[currentInstruction_Number_ToBeIssued].Rs;
					char offset[10];
					_itoa_s(this->instructions[currentInstruction_Number_ToBeIssued].Immediate_Offset, offset, 10);
					Load_ReservationStations[bufferNo].address.append(offset);
					this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;
			
					this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalLoadCycles;
					int regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rt.c_str()[1]);
					this->Load_ReservationStations[bufferNo].fu = this->registerStatus[regNumber].writing_reg;


					this->registerStatus[regNumber].writing_reg = Load_ReservationStations[bufferNo].name;




				}

			}


			else if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::STORE)
			{
				bufferNo = find_free_RS_Store();

				if (bufferNo == -1)
				{
					return -1;
				}
				else
				{

				
					this->Store_ReservationStations[bufferNo].isBusy = true;

					int regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rt.c_str()[1]);
					this->Store_ReservationStations[bufferNo].fu = this->registerStatus[regNumber].writing_reg;

					this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalStoreCycles;

					Store_ReservationStations[bufferNo].isBusy = true;
					Store_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
					this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;
					Store_ReservationStations[bufferNo].address = this->instructions[currentInstruction_Number_ToBeIssued].Rs;
					char offset[10];
					_itoa_s(this->instructions[currentInstruction_Number_ToBeIssued].Immediate_Offset, offset, 10);
					Store_ReservationStations[bufferNo].address.append(offset);




				}
			}

			else if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::ADD || instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::SUB)
			{
				int bufferNo = find_free_RS_AddSub();


				if (bufferNo == -1)
				{
				
					return -1;
				}

				else
				{


					this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalAddSubCycles;
					this->AddSub_ReservationStations[bufferNo].Instruction_Type = this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Type;
					this->AddSub_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
					this->AddSub_ReservationStations[bufferNo].isBusy = true;
					this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;


					//checking RAW hazard 
					//RS
					int regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rs.c_str()[1]);

					this->AddSub_ReservationStations[bufferNo].Qj = this->registerStatus[regNumber].writing_reg;

					//Rt
					regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rt.c_str()[1]);
					this->AddSub_ReservationStations[bufferNo].Qk = this->registerStatus[regNumber].writing_reg;

					if (this->AddSub_ReservationStations[bufferNo].Qj == "")
					{
						this->AddSub_ReservationStations[bufferNo].Vj = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rs + ")";
					}

					if (this->AddSub_ReservationStations[bufferNo].Qk == "")
					{
						this->AddSub_ReservationStations[bufferNo].Vk = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rt + ")";
					}


					//setting register status
					regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rd.c_str()[1]);
					this->registerStatus[regNumber].writing_reg = this->AddSub_ReservationStations[bufferNo].name;


				}
			}
		

			else if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::NEG)
			{
			int bufferNo = find_free_RS_Neg();


			if (bufferNo == -1)
			{

				return -1;
			}

			else
			{


				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalNegCycles;
				this->Neg_ReservationStations[bufferNo].Instruction_Type = this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Type;
				this->Neg_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
				this->Neg_ReservationStations[bufferNo].isBusy = true;
				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;


				int Register_Number = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rs.c_str()[1]);

				this->Neg_ReservationStations[bufferNo].Qj = this->registerStatus[Register_Number].writing_reg;


				if (this->Neg_ReservationStations[bufferNo].Qj == "")
				{
					if (this->instructions[currentInstruction_Number_ToBeIssued].Rs.c_str()[0] == 'R') {
						this->Neg_ReservationStations[bufferNo].Vj = to_string(registerStatus[atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rs.c_str()[1])].Register_Value);
					}
					else {
						this->Neg_ReservationStations[bufferNo].Vj = this->instructions[currentInstruction_Number_ToBeIssued].Rs;
					}


				}



				Register_Number = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rd.c_str()[1]);
				this->registerStatus[Register_Number].writing_reg = this->Neg_ReservationStations[bufferNo].name;


			}
			}

			else if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::NOR)
			{
			int bufferNo = find_free_RS_Nor();


			if (bufferNo == -1)
			{

				return -1;
			}

			else
			{

				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalNorCycles;
				this->Nor_ReservationStations[bufferNo].Instruction_Type = this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Type;
				this->Nor_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
				this->Nor_ReservationStations[bufferNo].isBusy = true;
				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;


				//checking RAW hazard 
				//RS
				int regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rs.c_str()[1]);

				this->Nor_ReservationStations[bufferNo].Qj = this->registerStatus[regNumber].writing_reg;

				//Rt
				regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rt.c_str()[1]);
				this->Nor_ReservationStations[bufferNo].Qk = this->registerStatus[regNumber].writing_reg;

				if (this->Nor_ReservationStations[bufferNo].Qj == "")
				{
					this->Nor_ReservationStations[bufferNo].Vj = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rs + ")";
				}

				if (this->Nor_ReservationStations[bufferNo].Qk == "")
				{
					this->Nor_ReservationStations[bufferNo].Vk = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rt + ")";
				}


				//setting register status
				regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rd.c_str()[1]);
				this->registerStatus[regNumber].writing_reg = this->Nor_ReservationStations[bufferNo].name;


			}
			}
			else if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::BEQ)
			{
			int bufferNo = find_free_RS_Beq();


			if (bufferNo == -1)
			{

				return -1;
			}

			else
			{

				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalBeqCycles;
				this->Beq_ReservationStations[bufferNo].Instruction_Type = this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Type;
				this->Beq_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
				this->Beq_ReservationStations[bufferNo].isBusy = true;
				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;


				//checking RAW hazard 
				//RS
				int regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rd.c_str()[1]);

				this->Beq_ReservationStations[bufferNo].Qj = this->registerStatus[regNumber].writing_reg;

				//Rt
				regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rs.c_str()[1]);
				this->Beq_ReservationStations[bufferNo].Qk = this->registerStatus[regNumber].writing_reg;

				if (this->Beq_ReservationStations[bufferNo].Qj == "")
				{
					this->Beq_ReservationStations[bufferNo].Vj = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rd + ")";
				}

				if (this->Beq_ReservationStations[bufferNo].Qk == "")
				{
					this->Beq_ReservationStations[bufferNo].Vk = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rs + ")";
				}




			}
			}
			else if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::JAL || instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::RETURN)
			{
			int bufferNo = find_free_RS_Jal();


			if (bufferNo == -1)
			{

				return -1;
			}

			else
			{

				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalJalCycles;
				this->Jal_ReservationStations[bufferNo].Instruction_Type = this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Type;
				this->Jal_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
				this->Jal_ReservationStations[bufferNo].isBusy = true;
				this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;



			}
			}
			else if (instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::MULT || instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::DIV)
			{
				int bufferNo = find_free_RS_MultDiv();
				char instructionNumberConversion[10];
				_itoa_s(currentInstruction_Number_ToBeIssued, instructionNumberConversion, 10, 10);

				if (bufferNo == -1)
				{

					return -1;
				}

				else
				{


					if (this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Type == Instruction_Type::MULT)
						this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalMultCylcles;
					else
						this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.executionCyclesRemaining = this->totalDivCycles;

					this->MultDiv_ReservationStations[bufferNo].Instruction_Type = this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Type;
					this->MultDiv_ReservationStations[bufferNo].instruction = &this->instructions[currentInstruction_Number_ToBeIssued];
					this->MultDiv_ReservationStations[bufferNo].isBusy = true;
					this->instructions[currentInstruction_Number_ToBeIssued].Instruction_Status.Issue_Instruction = current_Cycle_Number;


					int regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rs.c_str()[1]);

					this->MultDiv_ReservationStations[bufferNo].Qj = this->registerStatus[regNumber].writing_reg;

					regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rt.c_str()[1]);

					this->MultDiv_ReservationStations[bufferNo].Qk = this->registerStatus[regNumber].writing_reg;

					if (this->MultDiv_ReservationStations[bufferNo].Qj == "")
					{
						this->MultDiv_ReservationStations[bufferNo].Vj = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rs + ")";
					}

					if (this->MultDiv_ReservationStations[bufferNo].Qk == "")
					{


						this->MultDiv_ReservationStations[bufferNo].Vk = "R(" + this->instructions[currentInstruction_Number_ToBeIssued].Rt + ")";


					}

					regNumber = atoi(&this->instructions[currentInstruction_Number_ToBeIssued].Rd.c_str()[1]);

					this->registerStatus[regNumber].writing_reg = this->MultDiv_ReservationStations[bufferNo].name;

				}
			}


		}
		return 0;
	}

	void Write_Back(int& currentInstruction_Number_ToBeIssued)
	{

		for (int i = 0; i < totalLoad_ReservationStations; i++)
		{
			int static num = 1;

			if (this->Load_ReservationStations[i].isBusy == false)
				continue;

			if (this->Load_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue;

			if (this->Load_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)
				continue; 
			this->Load_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;

			int regNum = atoi(&this->Load_ReservationStations[i].instruction->Rt.c_str()[1]);
			if (this->registerStatus[regNum].writing_reg == this->Load_ReservationStations[i].name)
				this->registerStatus[regNum].writing_reg = "";

			///writing into  register
			int imm, rs1;

			imm = Load_ReservationStations->instruction[i].Immediate_Offset;

			if (Load_ReservationStations[i].instruction->Rs.c_str()[0] == 'R') {
				rs1 = registerStatus[atoi(&Load_ReservationStations[i].instruction->Rs.c_str()[1])].Register_Value;
			}
			int regnum_rd = atoi(&this->Load_ReservationStations[i].instruction->Rt.c_str()[1]);
			//result written into Rd
			int mem_loc;
			for (int i = 0; i < totalMemoryLocations; i++)
			{
				if (stoi(this->data_memory[i].Data_Memory_Location) == imm + rs1) {
					mem_loc = i;
				}
			}
			
			if (registerStatus[regnum_rd].Register_Name != "R0")
				registerStatus[regnum_rd].Register_Value = this->data_memory[mem_loc].Memory_Value;
			else
				registerStatus[regnum_rd].Register_Value = 0;

			/// 

			this->Load_ReservationStations[i].isBusy = false;
			this->Load_ReservationStations[i].address = "";
			this->Load_ReservationStations[i].instruction = nullptr;

			char numChar[10];
			_itoa_s(num, numChar, 10);
			string val = "M(A";
			val.append(numChar);
			val += ")";
			output_result(val, this->Load_ReservationStations[i].name);
			num++;
		}


		for (int i = 0; i < totalStore_ReservationStations; i++)
		{
			if (this->Store_ReservationStations[i].isBusy == false)
				continue;

			if (this->Store_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue; 

			if (this->Store_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)
				continue; 
			///writing into  register
			int imm, rs1, rs2;

			imm = Store_ReservationStations->instruction[i].Immediate_Offset;
			if (Store_ReservationStations[i].instruction->Rs.c_str()[0] == 'R') {
				rs1 = registerStatus[atoi(&Store_ReservationStations[i].instruction->Rt.c_str()[1])].Register_Value;
			}

			rs2 = registerStatus[atoi(&Store_ReservationStations[i].instruction->Rs.c_str()[1])].Register_Value;
			//result written into Rd
			int mem_loc;
			bool mem_loc_found=false;
			for (int i = 0; i < totalMemoryLocations; i++)
			{
				if (stoi(this->data_memory[i].Data_Memory_Location) == imm + rs2) {
					mem_loc = i;
					mem_loc_found = true;
				}
			}
			if (mem_loc_found) {
				this->data_memory[mem_loc].Memory_Value = rs1;
			}

			/// 
			this->Store_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;
			this->Store_ReservationStations[i].isBusy = false;
			this->Store_ReservationStations[i].address = "";
			this->Store_ReservationStations[i].instruction = nullptr;
			
		}

		for (int i = 0; i < totalAddSub_ReservationStations; i++)
		{
			int static num = 1;

			if (this->AddSub_ReservationStations[i].isBusy == false)
				continue;

			if (this->AddSub_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue; 

			if (this->AddSub_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)
				continue; 

			this->AddSub_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;

			int regNum = atoi(&this->AddSub_ReservationStations[i].instruction->Rd.c_str()[1]);
			if (this->registerStatus[regNum].writing_reg == this->AddSub_ReservationStations[i].name)
				this->registerStatus[regNum].writing_reg = "";

			///writing into  register
			int rs1, rs2;
			if (AddSub_ReservationStations[i].instruction->Rs.c_str()[0] == 'R') {
				rs1 = registerStatus[atoi(&AddSub_ReservationStations[i].instruction->Rs.c_str()[1])].Register_Value;
			}
			else {
				rs1 = stoi(AddSub_ReservationStations->instruction[i].Rs);
			}

			if (AddSub_ReservationStations[i].instruction->Rt.c_str()[0] == 'R') {
				rs2 = registerStatus[atoi(&AddSub_ReservationStations[i].instruction->Rt.c_str()[1])].Register_Value;
			}
			else {
				rs2 = stoi(AddSub_ReservationStations->instruction[i].Rt);
			}

			int regnum_rd = atoi(&this->AddSub_ReservationStations[i].instruction->Rd.c_str()[1]);
			//result written into Rd
			if (registerStatus[regnum_rd].Register_Name != "R0")
				registerStatus[regnum_rd].Register_Value = rs1 + rs2;
			else
				registerStatus[regnum_rd].Register_Value = 0;
			
			/// 
			this->AddSub_ReservationStations[i].isBusy = false;
			this->AddSub_ReservationStations[i].Instruction_Type = "";
			this->AddSub_ReservationStations[i].Qj = "";
			this->AddSub_ReservationStations[i].Qk = "";
			this->AddSub_ReservationStations[i].Vj = "";
			this->AddSub_ReservationStations[i].Vk = "";
			this->AddSub_ReservationStations[i].instruction = nullptr;

			char numChar[10];
			_itoa_s(num, numChar, 10);
			string val = "V";
			val.append(numChar);

			output_result(val, this->AddSub_ReservationStations[i].name);
			num++;
		}

		for (int i = 0; i < totalBeq_Reservation_Stations; i++)
		{
			int static num = 1;

			if (this->Beq_ReservationStations[i].isBusy == false)
				continue;

			if (this->Beq_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue;

			if (this->Beq_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)
				continue;

			this->Beq_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;

			int regNum = atoi(&this->Beq_ReservationStations[i].instruction->Rd.c_str()[1]);
			if (this->registerStatus[regNum].writing_reg == this->Beq_ReservationStations[i].name)
				this->registerStatus[regNum].writing_reg = "";

			///writing into  register
			int rs1, rs2;
			if (Beq_ReservationStations[i].instruction->Rd.c_str()[0] == 'R') {
				rs1 = registerStatus[atoi(&Beq_ReservationStations[i].instruction->Rd.c_str()[1])].Register_Value;
			}
			else {
				rs1 = stoi(Beq_ReservationStations->instruction[i].Rd);
			}

			if (Beq_ReservationStations[i].instruction->Rs.c_str()[0] == 'R') {
				rs2 = registerStatus[atoi(&Beq_ReservationStations[i].instruction->Rs.c_str()[1])].Register_Value;
			}
			else {
				rs2 = stoi(Beq_ReservationStations->instruction[i].Rs);
			}


			if (rs1 == rs2) {
				currentInstruction_Number_ToBeIssued = currentInstruction_Number_ToBeIssued +  1 + Beq_ReservationStations[i].instruction->Immediate_Offset;
				
				cout << currentInstruction_Number_ToBeIssued<<"\n";
			}

			/// 
			this->Beq_ReservationStations[i].isBusy = false;
			this->Beq_ReservationStations[i].Instruction_Type = "";
			this->Beq_ReservationStations[i].Qj = "";
			this->Beq_ReservationStations[i].Qk = "";
			this->Beq_ReservationStations[i].Vj = "";
			this->Beq_ReservationStations[i].Vk = "";
			this->Beq_ReservationStations[i].instruction = nullptr;

			char numChar[10];
			_itoa_s(num, numChar, 10);
			string val = "B";
			val.append(numChar);

			output_result(val, this->Beq_ReservationStations[i].name);
			num++;
		}


		for (int i = 0; i < totalJal_Reservation_Stations; i++)
		{
			int static num = 1;

			if (this->Jal_ReservationStations[i].isBusy == false)
				continue;

			if (this->Jal_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue;

			if (this->Jal_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)
				continue;

			this->Jal_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;

			int rs1;

			if (Jal_ReservationStations[i].instruction->Instruction_Type=="JAL") {
				registerStatus[1].Register_Value = currentInstruction_Number_ToBeIssued;
				currentInstruction_Number_ToBeIssued = currentInstruction_Number_ToBeIssued + Jal_ReservationStations[i].instruction->Immediate_Offset;
				cout << currentInstruction_Number_ToBeIssued << "\n";
			}
			if (Jal_ReservationStations[i].instruction->Instruction_Type == "RETURN") {
				currentInstruction_Number_ToBeIssued = registerStatus[1].Register_Value;

				cout << currentInstruction_Number_ToBeIssued << "\n";
			}

			/// 
			this->Jal_ReservationStations[i].isBusy = false;
			this->Jal_ReservationStations[i].Instruction_Type = "";
			this->Jal_ReservationStations[i].Qj = "";
			this->Jal_ReservationStations[i].Qk = "";
			this->Jal_ReservationStations[i].Vj = "";
			this->Jal_ReservationStations[i].Vk = "";
			this->Jal_ReservationStations[i].instruction = nullptr;

			char numChar[10];
			_itoa_s(num, numChar, 10);
			string val = "J";
			val.append(numChar);

			output_result(val, this->Jal_ReservationStations[i].name);
			num++;
		}


		for (int i = 0; i < totalNeg_ReservationStations; i++)
		{
			int static num = 1;

			if (this->Neg_ReservationStations[i].isBusy == false)
				continue;

			if (this->Neg_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue; 

			if (this->Neg_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)
				continue; 

			this->Neg_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;

			int regNum = atoi(&this->Neg_ReservationStations[i].instruction->Rd.c_str()[1]);
			if (this->registerStatus[regNum].writing_reg == this->Neg_ReservationStations[i].name)
				this->registerStatus[regNum].writing_reg = "";

			///writing into  register
			int rs1;
			if (Neg_ReservationStations[i].instruction->Rs.c_str()[0] == 'R') {
				rs1 = registerStatus[atoi(&Neg_ReservationStations[i].instruction->Rs.c_str()[1])].Register_Value;
			}
			else {
				rs1 = stoi(Neg_ReservationStations->instruction[i].Rs);
			}


			int regnum_rd = atoi(&this->Neg_ReservationStations[i].instruction->Rd.c_str()[1]);
			//result written into Rd
			string rs1_bin = decimal_to_binary(rs1);
			
			if (registerStatus[regnum_rd].Register_Name != "R0")
				registerStatus[regnum_rd].Register_Value = twos_complement(rs1_bin);
			else
				registerStatus[regnum_rd].Register_Value = 0;
			
			/// 

			this->Neg_ReservationStations[i].isBusy = false;
			this->Neg_ReservationStations[i].Instruction_Type = "";
			this->Neg_ReservationStations[i].Qj = "";
			this->Neg_ReservationStations[i].Vj = "";
			this->Neg_ReservationStations[i].instruction = nullptr;

			char numChar[10];
			_itoa_s(num, numChar, 10);
			string val = "E";
			val.append(numChar);

			output_result(val, this->Neg_ReservationStations[i].name);
			num++;
		}
		

		for (int i = 0; i < totalNor_ReservationStations; i++)
		{
			int static num = 1;

			if (this->Nor_ReservationStations[i].isBusy == false)
				continue;

			if (this->Nor_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue; 

			if (this->Nor_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)
				continue; 

			this->Nor_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;

			int regNum = atoi(&this->Nor_ReservationStations[i].instruction->Rd.c_str()[1]);
			if (this->registerStatus[regNum].writing_reg == this->Nor_ReservationStations[i].name)
				this->registerStatus[regNum].writing_reg = "";
			///writing into  register
			int rs1, rs2;
			if (Nor_ReservationStations[i].instruction->Rs.c_str()[0] == 'R') {
				rs1 = registerStatus[atoi(&Nor_ReservationStations[i].instruction->Rs.c_str()[1])].Register_Value;
			}
			else {
				rs1 = stoi(Nor_ReservationStations->instruction[i].Rs);
			}

			if (Nor_ReservationStations[i].instruction->Rt.c_str()[0] == 'R') {
				rs2 = registerStatus[atoi(&Nor_ReservationStations[i].instruction->Rt.c_str()[1])].Register_Value;
			}
			else {
				rs2 = stoi(Nor_ReservationStations->instruction[i].Rt);
			}

			int regnum_rd = atoi(&this->Nor_ReservationStations[i].instruction->Rd.c_str()[1]);
			//result written into Rd
			string rs1_bin = decimal_to_binary(rs1);
			string rs2_bin = decimal_to_binary(rs2);
			if (registerStatus[regnum_rd].Register_Name != "R0")
				registerStatus[regnum_rd].Register_Value = nor_operation(rs1_bin, rs2_bin);
			else
				registerStatus[regnum_rd].Register_Value = 0;
			/// 
			this->Nor_ReservationStations[i].isBusy = false;
			this->Nor_ReservationStations[i].Instruction_Type = "";
			this->Nor_ReservationStations[i].Qj = "";
			this->Nor_ReservationStations[i].Qk = "";
			this->Nor_ReservationStations[i].Vj = "";
			this->Nor_ReservationStations[i].Vk = "";
			this->Nor_ReservationStations[i].instruction = nullptr;

			char numChar[10];
			_itoa_s(num, numChar, 10);
			string val = "N";
			val.append(numChar);

			output_result(val, this->Nor_ReservationStations[i].name);
			num++;
		}


		for (int i = 0; i < totalMultDiv_ReservationStations; i++)
		{
			int static num = 1;

			if (this->MultDiv_ReservationStations[i].isBusy == false)
				continue;

			if (this->MultDiv_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				continue; 

			if (this->MultDiv_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time == current_Cycle_Number)

			this->MultDiv_ReservationStations[i].instruction->Instruction_Status.Write_Back = current_Cycle_Number;

			int regNum = atoi(&this->MultDiv_ReservationStations[i].instruction->Rd.c_str()[1]);
			if (this->registerStatus[regNum].writing_reg == this->MultDiv_ReservationStations[i].name)
				this->registerStatus[regNum].writing_reg = "";

			///writing into  register
			int rs1, rs2;
			if (MultDiv_ReservationStations[i].instruction->Rs.c_str()[0] == 'R') {
				rs1 = registerStatus[atoi(&MultDiv_ReservationStations[i].instruction->Rs.c_str()[1])].Register_Value;
			}
			else {
				rs1 = stoi(MultDiv_ReservationStations->instruction[i].Rs);
			}

			if (MultDiv_ReservationStations[i].instruction->Rt.c_str()[0] == 'R') {
				rs2 = registerStatus[atoi(&MultDiv_ReservationStations[i].instruction->Rt.c_str()[1])].Register_Value;
			}
			else {
				rs2 = stoi(MultDiv_ReservationStations->instruction[i].Rt);
			}

			int regnum_rd = atoi(&this->MultDiv_ReservationStations[i].instruction->Rd.c_str()[1]);
			//result written into Rd
			if(registerStatus[regnum_rd].Register_Name!="R0")
			registerStatus[regnum_rd].Register_Value = rs1 * rs2;
			else
				registerStatus[regnum_rd].Register_Value = 0;
			/// 

			this->MultDiv_ReservationStations[i].isBusy = false;
			this->MultDiv_ReservationStations[i].Instruction_Type = "";
			this->MultDiv_ReservationStations[i].Qj = "";
			this->MultDiv_ReservationStations[i].Qk = "";
			this->MultDiv_ReservationStations[i].Vj = "";
			this->MultDiv_ReservationStations[i].Vk = "";
			this->MultDiv_ReservationStations[i].instruction = nullptr;

			char numChar[10];
			_itoa_s(num, numChar, 10);
			string val = "D";
			val.append(numChar);

			output_result(val, this->MultDiv_ReservationStations[i].name);
			num++;
		}


	}


	void execute()
	{
		for (int i = 0; i < totalLoad_ReservationStations; i++)
		{
			if (this->Load_ReservationStations[i].isBusy == false)
				continue;

			if (this->Load_ReservationStations[i].fu != "")
				continue;

			if (this->Load_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->Load_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue; 
				this->Load_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->Load_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;


				if (this->Load_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{  
					this->Load_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}

			if (this->Load_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->Load_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->Load_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{  
				this->Load_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}


		}


		for (int i = 0; i < totalStore_ReservationStations; i++)
		{
			if (this->Store_ReservationStations[i].isBusy == false)
				continue;

			if (this->Store_ReservationStations[i].fu != "")
				continue;
			if (this->Store_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->Store_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue; 
				this->Store_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->Store_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;

				if (this->Store_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{   
					this->Store_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}

			if (this->Store_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->Store_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->Store_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{   
				this->Store_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}

		}


		for (int i = 0; i < totalAddSub_ReservationStations; i++)
		{
			if (this->AddSub_ReservationStations[i].isBusy == false)
				continue;

			if (this->AddSub_ReservationStations[i].Qj != "" || this->AddSub_ReservationStations[i].Qk != "")
				continue;

			if (this->AddSub_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->AddSub_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue; 
				this->AddSub_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->AddSub_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;

				if (this->AddSub_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{   
					this->AddSub_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}



			if (this->AddSub_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->AddSub_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->AddSub_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{   //execution completed
				this->AddSub_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}

		}

		for (int i = 0; i < totalBeq_Reservation_Stations; i++)
		{
			if (this->Beq_ReservationStations[i].isBusy == false)
				continue;

			if (this->Beq_ReservationStations[i].Qj != "" || this->Beq_ReservationStations[i].Qk != "")
				continue;

			if (this->Beq_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->Beq_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue;
				this->Beq_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->Beq_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;

				if (this->Beq_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{
					this->Beq_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}



			if (this->Beq_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->Beq_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->Beq_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{   //execution completed
				this->Beq_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}

		}

		for (int i = 0; i < totalJal_Reservation_Stations; i++)
		{
			if (this->Jal_ReservationStations[i].isBusy == false)
				continue;

			if (this->Jal_ReservationStations[i].Qj != "" || this->Jal_ReservationStations[i].Qk != "")
				continue;

			if (this->Jal_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->Jal_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue;
				this->Jal_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->Jal_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;

				if (this->Jal_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{
					this->Jal_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}



			if (this->Jal_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->Jal_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->Jal_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{   //execution completed
				this->Jal_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}

		}

		for (int i = 0; i < totalNeg_ReservationStations; i++)
		{
			if (this->Neg_ReservationStations[i].isBusy == false)
				continue;

			if (this->Neg_ReservationStations[i].Qj != "")
				continue;

			if (this->Neg_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->Neg_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue;
				this->Neg_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->Neg_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;

				if (this->Neg_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{ 
					this->Neg_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}

			if (this->Neg_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->Neg_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->Neg_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{  
				this->Neg_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}

		}

		for (int i = 0; i < totalNor_ReservationStations; i++)
		{
			if (this->Nor_ReservationStations[i].isBusy == false)
				continue;

			if (this->Nor_ReservationStations[i].Qj != "" || this->Nor_ReservationStations[i].Qk != "")
				continue;

			if (this->Nor_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->Nor_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue;
				this->Nor_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->Nor_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;

				if (this->Nor_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{
					this->Nor_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}



			if (this->Nor_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->Nor_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->Nor_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{   //execution completed
				this->Nor_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}

		}

		for (int i = 0; i < totalMultDiv_ReservationStations; i++)
		{
			if (this->MultDiv_ReservationStations[i].isBusy == false)
				continue;

			if (this->MultDiv_ReservationStations[i].Qj != "" || this->MultDiv_ReservationStations[i].Qk != "")
				continue;

			if (this->MultDiv_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time == -1)
			{
				if (this->MultDiv_ReservationStations[i].instruction->Instruction_Status.Issue_Instruction == current_Cycle_Number)
					continue; 

				this->MultDiv_ReservationStations[i].instruction->Instruction_Status.Execution_Start_Time = current_Cycle_Number;
				this->MultDiv_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;

				if (this->MultDiv_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
				{  
					this->MultDiv_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
					continue;
				}
				else
				{
					continue;
				}
			}

			if (this->MultDiv_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining != 0)
				this->MultDiv_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining--;
			else continue;

			if (this->MultDiv_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining == 0)
			{  this->MultDiv_ReservationStations[i].instruction->Instruction_Status.Execution_Complete_Time = current_Cycle_Number;
				continue;
			}
			else
			{
				continue;
			}

		}


	}

	void simulate()
	{

		int currentInstruction_Number_ToBeIssued = 0;
		current_Cycle_Number = 0;



		while (true)
		{
			cout << "Current Cycle Number= " << current_Cycle_Number;
			print();
			cout << endl;
			for (int i = 0; i < totalRegisters; i++) {
				cout << "Register " << i << ": " << registerStatus[i].Register_Value<<endl;
			}
			for (int i = 0; i < totalMemoryLocations; i++) {
				cout << "Memory Location " << data_memory[i].Data_Memory_Location << ": " << data_memory[i].Memory_Value<< endl;
			}
			char refresh_entry;
			cout << endl << "Enter any character and press enter for new frame: ";
			cin >> refresh_entry;
			current_Cycle_Number++;
			system("cls");
			int flag = Issue_InstructionInstruction(currentInstruction_Number_ToBeIssued);
			if (flag != -1)
				currentInstruction_Number_ToBeIssued++;

			execute();
			Write_Back(currentInstruction_Number_ToBeIssued);



		}

	}

	void print()
	{
		cout << endl << "Instructions:" << endl;

		for (int i = 0; i < totalInstructions; i++)
		{
			char arr[10];
			_itoa_s(i, arr, 10);
			strcat_s(arr, ".");

			if (instructions[i].Instruction_Type == Instruction_Type::LOAD || instructions[i].Instruction_Type == Instruction_Type::STORE)
			{

				cout << std::left << setw(3) << arr << std::left << setw(5) << instructions[i].Instruction_Type << setfill(' ') << std::right << setw(4) << instructions[i].Rt << setw(5) << instructions[i].Immediate_Offset << "+" << setw(5) << instructions[i].Rs;
				cout << endl;
			}
			else if (instructions[i].Instruction_Type == Instruction_Type::BEQ) {
				cout << std::left << setw(3) << arr << std::left << setw(5) << instructions[i].Instruction_Type << std::right << setw(4) << instructions[i].Rd << setw(5) << instructions[i].Rs << setw(6) << instructions[i].Immediate_Offset;
				cout << endl;
			}
			else if (instructions[i].Instruction_Type == Instruction_Type::JAL) {
				cout << std::left << setw(3) << arr << std::left << setw(5) << instructions[i].Instruction_Type << std::right << setw(4) << instructions[i].Rd << setw(5) << instructions[i].Rs << setw(6) << instructions[i].Immediate_Offset;
				cout << endl;
			}
			else
			{

				cout << std::left << setw(3) << arr << std::left << setw(5) << instructions[i].Instruction_Type << std::right << setw(4) << instructions[i].Rd << setw(5) << instructions[i].Rs << setw(6) << instructions[i].Rt;
				cout << endl;
			}
		}
		cout << "\t\t\t\t\t" <<"  Issue" << "   Start" << "  Finish     Write" << endl;

		cout << "\t\t\t\t\t" << "___________________________________";
		cout << endl;
		int j = 0;
		for (int i = 0; i < totalInstructions; i++)
		{

			char instructionIssue[10];
			char execution_Start[10];
			char Execution_Complete_Time[10];
			char instruction_Write[10];

			_itoa_s(this->instructions[i].Instruction_Status.Issue_Instruction, instructionIssue, 10);
			_itoa_s(this->instructions[i].Instruction_Status.Execution_Start_Time, execution_Start, 10);
			_itoa_s(this->instructions[i].Instruction_Status.Execution_Complete_Time, Execution_Complete_Time, 10);
			_itoa_s(this->instructions[i].Instruction_Status.Write_Back, instruction_Write, 10);
			cout <<"Instruction "<<i << "\t\t\t\t" << "|" << std::right << setw(7) << (instructions[i].Instruction_Status.Issue_Instruction == -1 ? "" : instructionIssue) << "|" << setw(7) << (instructions[i].Instruction_Status.Execution_Start_Time == -1 ? "" : execution_Start) << "|" << setw(7) << (instructions[i].Instruction_Status.Execution_Complete_Time == -1 ? "" : Execution_Complete_Time) << "|" << setw(10) << (instructions[i].Instruction_Status.Write_Back == -1 ? "" : instruction_Write) << "|";
			cout << endl;

			cout << "\t\t\t\t\t" << "|_______|_______|_______|__________|";
			cout << endl;
			j++;
		}
		cout << "Reservation Stations:";
		cout << endl;
		cout << "  Name " << "\t\t\t\t" <<"  Busy    Op      Vj       Vk       Qj       Qk ";
		cout << endl;
		cout << "\t\t\t\t" << "___________________________________________________";
		
		for (int i = 0; i < totalAddSub_ReservationStations; i++)
		{
			cout << endl;
			cout << std::right << setw(7) << AddSub_ReservationStations[i].name << "\t\t\t\t" << "|" << setw(5) << (AddSub_ReservationStations[i].isBusy == true ? "yes" : "no") << "|" << setw(7) << AddSub_ReservationStations[i].Instruction_Type << "|" << setw(8) << AddSub_ReservationStations[i].Vj << "|" << setw(8) << AddSub_ReservationStations[i].Vk << "|" << setw(8) << AddSub_ReservationStations[i].Qj << "|" << setw(8) << AddSub_ReservationStations[i].Qk << "|";
			if (AddSub_ReservationStations[i].instruction != nullptr)
			{
				cout << setw(3) << AddSub_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining;
			}
			cout << endl;
			cout << "\t\t\t\t" << "|_____|_______|________|________|________|________|";
		}


		for (int i = 0; i < totalMultDiv_ReservationStations; i++)
		{
			cout << endl;
			cout << std::right << setw(7) << MultDiv_ReservationStations[i].name << "\t\t\t\t" << "|" << setw(5) << (MultDiv_ReservationStations[i].isBusy == true ? "yes" : "no") << "|" << setw(7) << MultDiv_ReservationStations[i].Instruction_Type << "|" << setw(8) << MultDiv_ReservationStations[i].Vj << "|" << setw(8) << MultDiv_ReservationStations[i].Vk << "|" << setw(8) << MultDiv_ReservationStations[i].Qj << "|" << setw(8) << MultDiv_ReservationStations[i].Qk << "|";
			if (MultDiv_ReservationStations[i].instruction != nullptr)
			{
				cout << setw(3) << MultDiv_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining;
			}
			cout << endl;
			cout << "\t\t\t\t" << "|_____|_______|________|________|________|________|";
		}

		
		for (int i = 0; i < totalNeg_ReservationStations; i++)
		{
			cout << endl;
			cout << std::right << setw(7) << Neg_ReservationStations[i].name << "\t\t\t\t" << "|" << setw(5) << (Neg_ReservationStations[i].isBusy == true ? "yes" : "no") << "|" << setw(7) << Neg_ReservationStations[i].Instruction_Type << "|" << setw(8) << Neg_ReservationStations[i].Vj << "|" << setw(8) << Neg_ReservationStations[i].Vk << "|" << setw(8) << Neg_ReservationStations[i].Qj << "|" << setw(8) << Neg_ReservationStations[i].Qk << "|";
			if (Neg_ReservationStations[i].instruction != nullptr)
			{
				cout << setw(3) << Neg_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining;
			}
			cout << endl;
			cout << "\t\t\t\t" << "|_____|_______|________|________|________|________|";
		}

		for (int i = 0; i < totalNor_ReservationStations; i++)
		{
			cout << endl;
			cout << std::right << setw(7) << Nor_ReservationStations[i].name << "\t\t\t\t" << "|" << setw(5) << (Nor_ReservationStations[i].isBusy == true ? "yes" : "no") << "|" << setw(7) << Nor_ReservationStations[i].Instruction_Type << "|" << setw(8) << Nor_ReservationStations[i].Vj << "|" << setw(8) << Nor_ReservationStations[i].Vk << "|" << setw(8) << Nor_ReservationStations[i].Qj << "|" << setw(8) << Nor_ReservationStations[i].Qk << "|";
			if (Nor_ReservationStations[i].instruction != nullptr)
			{
				cout << setw(3) << Nor_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining;
			}
			cout << endl;
			cout << "\t\t\t\t" << "|_____|_______|________|________|________|________|";
		}
		for (int i = 0; i < totalBeq_Reservation_Stations; i++)
		{
			cout << endl;
			cout << std::right << setw(7) << Beq_ReservationStations[i].name << "\t\t\t\t" << "|" << setw(5) << (Beq_ReservationStations[i].isBusy == true ? "yes" : "no") << "|" << setw(7) << Beq_ReservationStations[i].Instruction_Type << "|" << setw(8) << Beq_ReservationStations[i].Vj << "|" << setw(8) << Beq_ReservationStations[i].Vk << "|" << setw(8) << Beq_ReservationStations[i].Qj << "|" << setw(8) << Beq_ReservationStations[i].Qk << "|";
			if (Beq_ReservationStations[i].instruction != nullptr)
			{
				cout << setw(3) << Beq_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining;
			}
			cout << endl;
			cout << "\t\t\t\t" << "|_____|_______|________|________|________|________|";
		}
		for (int i = 0; i < totalJal_Reservation_Stations; i++)
		{
			cout << endl;
			cout << std::right << setw(7) << Jal_ReservationStations[i].name << "\t\t\t\t" << "|" << setw(5) << (Jal_ReservationStations[i].isBusy == true ? "yes" : "no") << "|" << setw(7) << Jal_ReservationStations[i].Instruction_Type << "|" << setw(8) << Jal_ReservationStations[i].Vj << "|" << setw(8) << Jal_ReservationStations[i].Vk << "|" << setw(8) << Jal_ReservationStations[i].Qj << "|" << setw(8) << Jal_ReservationStations[i].Qk << "|";
			if (Jal_ReservationStations[i].instruction != nullptr)
			{
				cout << setw(3) << Jal_ReservationStations[i].instruction->Instruction_Status.executionCyclesRemaining;
			}
			cout << endl;
			cout << "\t\t\t\t" << "|_____|_______|________|________|________|________|";
		}

	}
	Tomasulo()
	{

	}
};

string decimal_to_binary(int number) {
	string bin;
	if (number == 0) {
		bin = '0';
	}
	else {
		int n = (int)(log2(number));
		bin = bitset<64>(number).to_string().substr(64 - n - 1);
	}
	return bin;
}

int twos_complement(string bin) {
	int len, i;
	bool firstone = false;
	string twos;
	len = bin.length();
	twos.resize(len);

	for (i = (len - 1); i >= 0; i--)
	{
		if (firstone == false)
		{
			if (bin[i] == '0')
			{
				twos[i] = '0';
			}
			else
			{
				twos[i] = '1';
				firstone = true;
			}
		}
		else
		{
			if (bin[i] == '0')
			{
				twos[i] = '1';
			}
			else
			{
				twos[i] = '0';
			}
		}
	}

	int two_complement_int = stoi(twos, 0, 2);

	return two_complement_int;
}

int nor_operation(string bin1, string bin2) {
	string res_bin;
	int len1, len2, i;
	len1 = bin1.length();
	len2 = bin2.length();
	int biglen = (len1 > len2) ? len1 : len2;
	for (int i = 0; i < biglen; i++)
		res_bin.insert(0, "0");
	if (len2 > len1) {
		for (int i = 0; i < abs(len2 - len1); i++)
			bin1.insert(0, "0");
	}
	else if (len1 > len2) {
		for (int i = 0; i < abs(len2 - len1); i++)
			bin1.insert(0, "0");
	}

	for (int i = 0; i < biglen; i++) {
		if (bin1[i] == '0' && bin2[i] == '0') {
			res_bin[i] = '1';
		}
		else {
			res_bin[i] = '0';
		}
	}
	int res_int = stoi(res_bin, 0, 2);

	return res_int;
}