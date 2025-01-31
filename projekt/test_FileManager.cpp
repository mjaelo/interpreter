/*
* Tutaj znajdują się zrobione przeze mnie testy dla poszczególnych funkcjonalności.
* Trzeba pamiętać, że jeśli plik jest usuwany to w pamięci dysku zostają dane. Znikają
  tylko zajęte bloki z wektora bitowego
* test statycznego obiektu należy uruchomić 2 razy
 */

#include "FileManager.h"
#include "MemoryManager.h"
#include "pipe.h"
#include <iomanip>
#include <iostream>
#include "Planista.h"
#include "Procesy.h"

using namespace std;

bool messages = true;
bool detailedMessages = true;
bool operationStatus = true;

const std::string procName = "process";

void displayFunctionOutcome(const int &outcome) {
	if (operationStatus) {
		if (outcome == FILE_ERROR_NONE) { std::cout << "Operacja powiodla sie!\n"; }
		else if (outcome == FILE_ERROR_EMPTY_NAME)		{ std::cout << "Pusta nazwa!\n"; }
		else if (outcome == FILE_ERROR_NAME_TOO_LONG)	{ std::cout << "Nazwa za dluga!\n"; }
		else if (outcome == FILE_ERROR_NAME_USED)		{ std::cout << "Nazwa zajeta!\n"; }
		else if (outcome == FILE_ERROR_NO_INODES_LEFT)	{ std::cout << "Osiagnieto limit plikow!\n"; }
		else if (outcome == FILE_ERROR_DATA_TOO_BIG)	{ std::cout << "Dane za duze!\n"; }
		else if (outcome == FILE_ERROR_NOT_FOUND)		{ std::cout << "Nie znaleziono pliku!\n"; }
		else if (outcome == FILE_ERROR_NOT_OPENED)		{ std::cout << "Plik nie jest otwarty!\n"; }
		else if (outcome == FILE_ERROR_OPENED)			{ std::cout << "Plik jest otwarty!\n"; }
		else if (outcome == FILE_ERROR_SYNC)			{ std::cout << "Semafor opuszczony!\n"; }
		else if (outcome == FILE_ERROR_NOT_R_MODE)		{ std::cout << "Plik nie jest do odczytu!\n"; }
		else if (outcome == FILE_ERROR_NOT_W_MODE)		{ std::cout << "Plik nie jest do zapisu!\n"; }
		else if (outcome == FILE_SYNC_WAITING)			{ std::cout << "Zasob zajety!\n"; }
		else { std::cout << "Nie obsluzony blad: " << outcome << "\n"; }
		std::cout << '\n';
	}
}

//File create, delete
void test1() {
	Planista p;
	MemoryManager mm;
	proc_tree tree(&mm, &p);
	FileManager FM(&p, &tree);
	tree.fork(new PCB(procName, 1));
	FM.set_messages(messages);
	FM.set_detailed_messages(detailedMessages);

	displayFunctionOutcome(FM.file_create("plik1", procName, "TekstTekst Tekst./*+$łążśyłóżźówa"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_create("plik2", procName, "TekstTekst Tekst./*+$łążśyłóżźówa"));
	displayFunctionOutcome(FM.file_write("plik2", procName, string("END")));

	cout << "--- Zawartosc Dysku (char) ---\n";
	FM.display_disk_content_char();
	cout << '\n';

	displayFunctionOutcome(FM.display_file_info("plik1"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_close("plik1", procName));
	displayFunctionOutcome(FM.file_delete("plik1", procName));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	cout << "--- Katalog Glowny ---\n";
	FM.display_root_directory();
	cout << '\n';
}

//Space fill and file delete
void test2() {
	Planista p;
	MemoryManager mm;
	proc_tree tree(&mm, &p);
	FileManager FM(&p, &tree);
	tree.fork(new PCB(procName, 1));
	FM.set_messages(messages);
	FM.set_detailed_messages(detailedMessages);

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';
	displayFunctionOutcome(FM.file_create("plik1", procName, "TekstTekst Tekst./*+$łążśyłóżźówa"));
	displayFunctionOutcome(FM.file_create("plik2", procName, "Blablablablablablablablabla"));
	displayFunctionOutcome(FM.file_create("plik3", procName, "Sratatatatatata"));

	displayFunctionOutcome(FM.file_close("plik2", procName));
	displayFunctionOutcome(FM.file_delete("plik2", procName));

	displayFunctionOutcome(FM.file_create("plik2", procName, "TekstTekst Tekst./*+$łążśyłóżźówaaaaaaaaaaaaa"));
	displayFunctionOutcome(FM.file_create("plik4", procName, "STARTWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWaWWWWWWWWWWWWWWWWWwwwwwwwwwwwwwwwwWWWWWWWWWWWWaWWWWWWWWWWWWWWWWWWWwWWWWWWWWWWWWWWWWWWWWasdjaskdjsdhasjdhasjkhasdasdasdjhas12234567890sdfghjkldasdsdfghjkl;trfdeysgygysdgas675as6d5ty1ehgshda.adhghgdEND"));
	displayFunctionOutcome(FM.file_create("plik5", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWm"));
	displayFunctionOutcome(FM.file_create("plik6", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWl"));
	displayFunctionOutcome(FM.file_create("plik7", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWk"));
	displayFunctionOutcome(FM.file_create("plik8", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWj"));
	displayFunctionOutcome(FM.file_create("plik9", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWi"));
	displayFunctionOutcome(FM.file_create("plik10", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWh"));
	displayFunctionOutcome(FM.file_create("plik11", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWg"));
	displayFunctionOutcome(FM.file_create("plik12", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWf"));
	displayFunctionOutcome(FM.file_create("plik13", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWe"));
	displayFunctionOutcome(FM.file_create("plik14", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWd"));
	displayFunctionOutcome(FM.file_create("plik15", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWc"));
	displayFunctionOutcome(FM.file_create("plik16", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWb"));
	displayFunctionOutcome(FM.file_create("plik17", procName, "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWa"));

	cout << '\n';
	displayFunctionOutcome(FM.display_file_info("plik4"));
	cout << '\n';

	cout << "--- Zawartosc Dysku (char) ---\n";
	FM.display_disk_content_char();
	cout << '\n';
	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	cout << "--- Parametry ---\n";
	FileManager::display_file_system_params();
	cout << '\n';

	cout << "--- Katalog Glowny ---\n";
	FM.display_root_directory();
}

//Allocation test
void test3() {
	//Test przygotowany dla bloków o rozmiarze 32 bajt
	Planista p;
	MemoryManager mm;
	proc_tree tree(&mm, &p);
	FileManager FM(&p, &tree);
	tree.fork(new PCB(procName, 1));

	FM.set_messages(messages);
	FM.set_detailed_messages(detailedMessages);

	displayFunctionOutcome(FM.file_create("plik1", procName, "Plik1Plik1Plik1Plik1Plik1Plik1"));

	displayFunctionOutcome(FM.file_create("plik2", procName, "Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2"));

	displayFunctionOutcome(FM.file_create("plik3", procName, "Plik3Plik3"));

	displayFunctionOutcome(FM.file_create("plik4", procName, "Plik4Plik4Plik4Plik4Plik4Plik4Plik4Plik4"));

	displayFunctionOutcome(FM.file_create("plik5", procName, "Plik5Plik5Plik5Plik5"));

	cout << "--- Zawartosc Dysku (char) ---\n";
	FM.display_disk_content_char();
	cout << '\n';

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_close("plik2", procName));
	displayFunctionOutcome(FM.file_delete("plik2", procName));

	displayFunctionOutcome(FM.file_close("plik4", procName));
	displayFunctionOutcome(FM.file_delete("plik4", procName));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_create("plik6", procName, "Plik6Plik6Plik6Plik6Plik6Plik6Plik6"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	cout << "--- Zawartosc Dysku (char) ---\n";
	FM.display_disk_content_char();
	cout << '\n';

	displayFunctionOutcome(FM.file_write("plik5", procName, "Plik5Plik5Plik5Plik5Plik5Plik5Plik5Plik5Plik5Plik5"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_write("plik3", procName, "Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3Plik3"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.display_file_info("plik3"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_create("plik7", procName, "Plik1Plik1Plik1Plik1"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_write("plik1", procName, "Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1Plik1"));

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.display_file_info("plik1"));
}

//File Open/Close
void test4() {
	Planista p;
	MemoryManager mm;
	proc_tree tree(&mm, &p);
	FileManager FM(&p, &tree);
	tree.fork(new PCB(procName, 1));

	FM.set_messages(messages);
	FM.set_detailed_messages(detailedMessages);

	displayFunctionOutcome(FM.file_create("plik1", string("Tekst")));

	displayFunctionOutcome(FM.file_open("plik1", procName, FILE_OPEN_R_MODE));

	displayFunctionOutcome(FM.file_write("plik1", procName, "Wpis"));

	displayFunctionOutcome(FM.file_close("plik1", procName));

	displayFunctionOutcome(FM.file_create("plik10", procName));
	displayFunctionOutcome(FM.file_create("plik11", procName));
	displayFunctionOutcome(FM.file_create("plik12", procName));
	displayFunctionOutcome(FM.file_create("plik13", procName));
	displayFunctionOutcome(FM.file_create("plik14", procName));
	displayFunctionOutcome(FM.file_create("plik15", procName));
	displayFunctionOutcome(FM.file_create("plik16", procName));
	displayFunctionOutcome(FM.file_create("plik17", procName));
	displayFunctionOutcome(FM.file_create("plik18", procName));
	displayFunctionOutcome(FM.file_create("plik19", procName));
	displayFunctionOutcome(FM.file_create("plik20", procName));

	displayFunctionOutcome(FM.file_close_all());

	std::string result;
	FM.file_read_all("plik1", procName, result);
	std::cout << result << '\n';
}

//Sequential Access test
void test5() {
	Planista p;
	MemoryManager mm;
	proc_tree tree(&mm, &p);
	FileManager FM(&p, &tree);
	tree.fork(new PCB(procName, 1));

	FM.set_messages(messages);
	FM.set_detailed_messages(detailedMessages);
	std::string result;

	displayFunctionOutcome(FM.file_create("plik1", procName, "SrataHakunaMatataBatata"));
	std::cout << "Zapisano: " << "SrataHakunaMatataBatata" << '\n';
	displayFunctionOutcome(FM.file_open("plik1", procName, FILE_OPEN_R_MODE));
	displayFunctionOutcome(FM.file_read("plik1", procName, 5, result));
	std::cout << "Odczyt 5 bajt: " << result << "\n";
	FM.file_read("plik1", procName, 6, result);
	std::cout << "Odczyt 5 bajt: " << result << "\n";
	FM.file_read("plik1", procName, 6, result);
	std::cout << "Odczyt 6 bajt: " << result << "\n";
	FM.file_read("plik1", procName, 6, result);
	std::cout << "Odczyt 6 bajt: " << result << "\n";
	FM.file_read("plik1", procName, 666, result);
	std::cout << "Odczyt 666 bajt: " << "Thank you satan!\n";

	displayFunctionOutcome(FM.file_append("plik1", procName, " The END"));
	displayFunctionOutcome(FM.display_file_info("plik1"));

}

//Write and append test
void test6() {
	Planista p;
	MemoryManager mm;
	proc_tree tree(&mm, &p);
	FileManager FM(&p, &tree);

	tree.fork(new PCB(procName, 1));

	FM.set_messages(messages);
	FM.set_detailed_messages(detailedMessages);

	displayFunctionOutcome(FM.file_create("plik1", procName, "Plik1Plik1Plik1Plik1Plik1Plik1"));

	displayFunctionOutcome(FM.file_create("plik2", procName, "Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2Plik2"));

	displayFunctionOutcome(FM.file_create("plik3", procName, "Plik3Plik3"));

	cout << "--- Zawartosc Dysku (char) ---\n";
	FM.display_disk_content_char();
	cout << '\n';

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.file_append("plik2", procName, "AppendAppendAppendAppendAppendAppendAppendAppendAppendAppend"));

	cout << "--- Zawartosc Dysku (char) ---\n";
	FM.display_disk_content_char();
	cout << '\n';

	cout << "--- Wektor Bitowy ---\n";
	FM.display_bit_vector();
	cout << '\n';

	displayFunctionOutcome(FM.display_file_info("plik2"));
}

//System test
void test7() {
	MemoryManager mm;
	Planista p;
	proc_tree tree(&mm, &p);
	FileManager fm(&p, &tree);
	Pipeline pipy(&tree);

	fm.set_messages(messages);
	fm.set_detailed_messages(detailedMessages);


	//Test pipek
	{
		tree.fork(new PCB("proc1", 1));
		tree.fork(new PCB("proc2", 1));
		tree.fork(new PCB("proc3", 1));
		tree.fork(new PCB("proc4", 1));
		tree.fork(new PCB("proc5", 1));
		tree.fork(new PCB("proc6", 1));

		p.AddProces(tree.find_proc("proc1"));
		p.AddProces(tree.find_proc("proc2"));
		p.AddProces(tree.find_proc("proc3"));
		p.AddProces(tree.find_proc("proc4"));
		p.AddProces(tree.find_proc("proc5"));
		p.AddProces(tree.find_proc("proc6"));

		pipy.createPipe("proc1", "proc2");
		pipy.createPipe("proc2", "proc1");
		if (pipy.existPipe("proc1", "proc2")) { std::cout << "Jest pipa proc1 proc2!\n"; }
		if (pipy.existPipe("proc2", "proc1")) { std::cout << "Jest pipa proc2 proc1!\n"; }

		pipy.write("proc1","proc2","Wysylam Ci tekst");

		std::cout << "Odebralem tekst: " << pipy.read("proc2", "proc1", 20) << '\n';
		pipy.deletePipe("proc1", "proc2");
		pipy.deletePipe("proc2", "proc1");
	}

	//Test zapisu (semafory)
	{
		std::cout << "Create Plik1 for proc1\n";
		displayFunctionOutcome(fm.file_create("Plik1", "proc1"));
		displayFunctionOutcome(fm.file_create("Plik2", "proc1","Tekst2"));
		displayFunctionOutcome(fm.file_close("Plik2", "proc1"));
		p.displayPCBLists();

		std::cout << "Open Plik1 for proc2\n";
		displayFunctionOutcome(fm.file_open("Plik1", "proc2", FILE_OPEN_W_MODE));
		p.displayPCBLists();

		std::cout << "Write Plik1 from proc1\n";
		displayFunctionOutcome(fm.file_write("Plik1", "proc1", "tekst1"));

		std::cout << "Write Plik1 from proc2\n";
		displayFunctionOutcome(fm.file_write("Plik1", "proc2", "tekst2"));

		tree.display_tree();
		fm.file_close_all();
		p.displayPCBLists();
	}

	//Test odczytu (semafory)
	{
		std::cout << "Open Plik1 for proc1\n";
		displayFunctionOutcome(fm.file_open("Plik1", "proc1", FILE_OPEN_R_MODE));
		displayFunctionOutcome(fm.file_open("Plik2", "proc1", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		std::cout << "Open Plik1 for proc2\n";
		displayFunctionOutcome(fm.file_open("Plik1", "proc2", FILE_OPEN_R_MODE));
		displayFunctionOutcome(fm.file_open("Plik2", "proc2", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		std::cout << "Open Plik1 for proc3\n";
		displayFunctionOutcome(fm.file_open("Plik1", "proc3", FILE_OPEN_R_MODE));
		displayFunctionOutcome(fm.file_open("Plik2", "proc3", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		displayFunctionOutcome(fm.file_open("Plik1", "proc4", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		displayFunctionOutcome(fm.file_open("Plik1", "proc5", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		displayFunctionOutcome(fm.file_open("Plik1", "proc6", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		std::string temp1;
		std::string temp2;
		std::string temp3;
		std::string temp4;
		std::string temp5;
		std::string temp6;

		std::cout << "Read sync test\n";

		displayFunctionOutcome(fm.file_read_all("Plik1", "proc1", temp1));
		displayFunctionOutcome(fm.file_read_all("Plik1", "proc2", temp2));
		displayFunctionOutcome(fm.file_read_all("Plik1", "proc3", temp3));

		std::cout << "Proc1: " << temp1 << '\n';
		std::cout << "Proc2: " << temp2 << '\n';
		std::cout << "Proc3: " << temp3 << '\n';

		temp1.clear();
		temp2.clear();
		temp3.clear();

		fm.file_close("Plik1", "proc1");
		std::cout << "Open Plik1 for proc2\n";
		displayFunctionOutcome(fm.file_open("Plik1", "proc2", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		std::cout << "Open Plik1 for proc3\n";
		displayFunctionOutcome(fm.file_close("Plik1", "proc3"));

		std::cout << "Open Plik1 for proc6\n";
		displayFunctionOutcome(fm.file_open("Plik1", "proc6", FILE_OPEN_R_MODE));
		p.displayPCBLists();

		displayFunctionOutcome(fm.file_read_all("Plik1", "proc1", temp1));
		displayFunctionOutcome(fm.file_read_all("Plik1", "proc2", temp2));
		displayFunctionOutcome(fm.file_read_all("Plik1", "proc3", temp3));
		displayFunctionOutcome(fm.file_read_all("Plik1", "proc4", temp4));
		displayFunctionOutcome(fm.file_read_all("Plik1", "proc5", temp5));
		displayFunctionOutcome(fm.file_read_all("Plik1", "proc6", temp6));

		std::cout << "Proc1: " << temp1 << '\n';
		std::cout << "Proc2: " << temp2 << '\n';
		std::cout << "Proc3: " << temp3 << '\n';
		std::cout << "Proc4: " << temp4 << '\n';
		std::cout << "Proc5: " << temp5 << '\n';
		std::cout << "Proc6: " << temp6 << '\n';
	}

	p.displayPCBLists();
	displayFunctionOutcome(fm.file_open("Plik1", "proc5", FILE_OPEN_W_MODE));
	p.displayPCBLists();

	//Test dzieci
	{
		tree.fork(new PCB("prockidParent", 1));
		tree.fork(new PCB("prockid1", tree.find_proc("prockidParent")->PID));
		tree.fork(new PCB("prockid2", tree.find_proc("prockid1")->PID));
		tree.fork(new PCB("prockid3", tree.find_proc("prockid2")->PID));
		tree.fork(new PCB("prockid4", tree.find_proc("prockid3")->PID));

		p.AddProces(tree.find_proc("prockidParent"));
		p.AddProces(tree.find_proc("prockid1"));
		p.AddProces(tree.find_proc("prockid2"));
		p.AddProces(tree.find_proc("prockid3"));
		p.AddProces(tree.find_proc("prockid4"));

		tree.display_tree();

		p.displayPCBLists();
	}

	//Sprzątanie
	{
		fm.file_close_all();

		p.displayPCBLists();
		tree.exit(tree.find_proc("proc1")->PID);
		tree.exit(tree.find_proc("proc2")->PID);
		tree.exit(tree.find_proc("proc3")->PID);
		tree.exit(tree.find_proc("proc4")->PID);
		tree.exit(tree.find_proc("proc5")->PID);
		tree.exit(tree.find_proc("proc6")->PID);
		p.displayPCBLists();
	}

	tree.display_tree();
}

int main() {
	const vector<string>desc{
		"File Create, Delete", "Space Fill and File Delete", "Allocation", "File Open/Close",
		"Sequential Access", "Write and append test", "System test"
	};

	const auto run = [](void fun()) {
		system("cls");
		fun();
		cout << '\n';
		system("pause");
		system("cls");
	};

	system("cls");
	const vector<void(*)()>functions{ &test1, &test2, &test3, &test4, &test5, &test6, &test7 };

	while (true) {
		//Elementy stałe
		cout << "Messages: " << (messages ? "Enabled" : "Disabled") << '\n';
		cout << "Detailed Messages: " << (detailedMessages ? "Enabled" : "Disabled") << "\n";
		cout << "Operation Status: " << (operationStatus ? "Enabled" : "Disabled") << "\n\n";

		FileManager::display_file_system_params();
		cout << "\n\n";

		cout << setfill('0') << setw(2) << -3 << ". " << "Enable/Disable Operation Status" << '\n';
		cout << setfill('0') << setw(2) << -2 << ". " << "Enable/Disable Detailed Messages" << '\n';
		cout << setfill('0') << setw(2) << -1 << ". " << "Enable/Disable Messages" << '\n';
		cout << setfill('0') << setw(2) << 0 << ". " << "Exit" << "\n\n";

		//Wyświetla numery i opisy poszczególnych testów
		for (unsigned int i = 0; i < desc.size(); i++) {
			cout << setfill('0') << setw(2) << i + 1 << ". " << desc[i] << '\n';
		}
		cout << "\nPodaj numer(-3 do " << functions.size() << "): ";

		int testNum;
		cin >> testNum;

		//Włączanie/wyłączanie statusu operacji
		if (testNum == -3) {
			if (operationStatus) {
				std::cout << "\nOperation status disabled\n\n";
				system("pause");
				operationStatus = false;
			}
			else {
				std::cout << "\nOperation status enabled\n\n";
				system("pause");
				operationStatus = true;
			}
		}

		//Włączanie/wyłączanie szczegółowych wiadomości
		if (testNum == -2) {
			if (detailedMessages) {
				std::cout << "\nDetailed messages disabled\n\n";
				system("pause");
				detailedMessages = false;
			}
			else {
				std::cout << "\nDetailed messages enabled\n\n";
				system("pause");
				detailedMessages = true;
			}
		}

		//Włączanie/wyłączanie wiadomości
		if (testNum == -1) {
			if (messages) {
				std::cout << "\nMessages disabled\n\n";
				system("pause");
				messages = false;
			}
			else {
				std::cout << "\nMessages enabled\n\n";
				system("pause");
				messages = true;
			}
		}

		//Działa jeśli wybrano poprawny numer testu
		else if (static_cast<size_t>(testNum) >= 1 && static_cast<size_t>(testNum) <= functions.size()) {
			run(functions[testNum - 1]);
		}

		//Wyjście
		else if (testNum == 0) { break; }

		system("cls");
	}
}
