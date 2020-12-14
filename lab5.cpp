#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

struct Student {
	char f[15];
	char i[15];
	char o[15];
	char gender[6];
	int age, course;
	int performance[3];
};

int menu(Student* students, int& stringCounter);
int eneterInformationAboutSutednrsFromFileAndStringCounter(Student* students);
void viewInformationAboutStudentsAsATable(Student* students, int& stringCounter);
void addInformationToFile(Student* students, int& stringCounter);
void deleteInformationFromFile(Student* students, int& stringCounter);
void editInformationAboutStudent(Student* students, int& stringCounter);
bool isHighScorer(Student* students, int i);
void sortFunc(Student* students, int& stringCounter);


int eneterInformationAboutSutednrsFromFileAndStringCounter(Student* students) {
	int stringCounter = 0;
	int filesize;
	fstream FILE;
	Student stud;
	bool pyst = false;
	char ch;
	FILE.open("for_lab5.txt", ios::in | ios::binary);
	if (!FILE.is_open()) {						// если файл не открыт
		cout << "File can not be open!\n";									// сообщить об этом
	}
	else {
		FILE.get(ch);				// считать символ
		if (FILE.eof()) {		// если конец 
			pyst = true;			// выйти из цикла
		}
		else {
			FILE.seekg(0, ios_base::beg);		// перейти на начало
		}

		if (pyst != true) {
			while (!FILE.eof()) {

				FILE.read((char*)&stud, sizeof(stud));
				students[stringCounter] = stud;
				stringCounter++;
			}
		}
		FILE.close();
		cout << "Information was parsed successfully! " << endl;
	}

	return stringCounter;
};

void viewInformationAboutStudentsAsATable(Student* students, int& stringCounter) {
	cout.setf(ios::left);
	cout << endl;
	cout << setw(15) << "F";
	cout << setw(15) << "I";
	cout << setw(15) << "O";
	cout << setw(10) << "AGE";
	cout << setw(13) << "GENDER";
	cout << setw(13) << "COURSE";
	cout << setw(15) << "RUSSIAN MARK";
	cout << setw(15) << "PHYSICS MARK";
	cout << setw(15) << "MATH MARK" << endl;
	for (int i = 0; i < stringCounter; i++) {
		cout.setf(ios::left);
		cout << endl;
		cout << setw(15) << students[i].f;
		cout << setw(15) << students[i].i;
		cout << setw(15) << students[i].o;
		cout << setw(10) << students[i].age;
		cout << setw(13) << students[i].gender;
		cout << setw(13) << students[i].course;
		cout << setw(15) << students[i].performance[0];
		cout << setw(15) << students[i].performance[1];
		cout << setw(15) << students[i].performance[2];
	}
};

void addInformationToFile(Student* students, int& stringCounter) {
	cout << "Please enter student's fio: ";
	cin >> students[stringCounter].f >> students[stringCounter].i >> students[stringCounter].o;
	cout << "Please enter student's age: ";
	cin >> students[stringCounter].age;
	cout << "Please enter student's gender: ";
	cin >> students[stringCounter].gender;
	cout << "Please enter student's course: ";
	cin >> students[stringCounter].course;
	cout << "Please enter student's performance(Russian mark, Physics mark, Math mark) from space: ";
	cin >> students[stringCounter].performance[0] >> students[stringCounter].performance[1] >> students[stringCounter].performance[2];
	stringCounter++;
	cout << "\nInformation was added successfully!\n";
};

void deleteInformationFromFile(Student* students, int& stringCounter) {
	char fHelper[15];
	char iHelper[15];
	char oHelper[15];
	int howManyUnitsIsCoincided = 0;
	int indexForDelete = -1;
	int lastStudentIndex;
	lastStudentIndex = stringCounter - 1;
	cout << "Please enter student's fio to find who will be deleted: ";
	cin >> fHelper >> iHelper >> oHelper;
	for (int i = 0; i < stringCounter; i++) {
		if (!strcmp(fHelper, students[i].f)) {
			howManyUnitsIsCoincided++;
		}
		if (!strcmp(iHelper, students[i].i)) {
			howManyUnitsIsCoincided++;
		}
		if (!strcmp(oHelper, students[i].o)) {
			howManyUnitsIsCoincided++;
		}
		if (howManyUnitsIsCoincided == 3) {
			indexForDelete = i;
		}
	}
	if (indexForDelete != -1) {
		Student temp = students[indexForDelete];
		students[indexForDelete] = students[lastStudentIndex];
		students[lastStudentIndex] = temp;
		stringCounter--;
	}
};

void editInformationAboutStudent(Student* students, int& stringCounter) {
	char newF[15];
	char newI[15];
	char newO[15];
	char newGender[6];
	int newAge, newCourse;
	int newPerformance_1, newPerformance_2, newPerformance_3;
	int howManyUnitsIsCoincided = 0;
	int indexToEdit = -1;
	cout << "Please enter student's fio to find who will be edited: ";
	cin >> newF >> newI >> newO;
	for (int i = 0; i < stringCounter; i++) {
		if (!strcmp(newF, students[i].f)) {
			howManyUnitsIsCoincided++;
		}
		if (!strcmp(newI, students[i].i)) {
			howManyUnitsIsCoincided++;
		}
		if (!strcmp(newO, students[i].o)) {
			howManyUnitsIsCoincided++;
		}
		if (howManyUnitsIsCoincided == 3) {
			indexToEdit = i;
		}
		howManyUnitsIsCoincided = 0;
	}
	if (indexToEdit != -1) {
		cout << "Please enter new information or enter 0 to leave unchanged." << endl;
		cout << "Please enter new student's fio: ";
		cin >> newF >> newI >> newO;
		cout << "Please enter new student's age: ";
		cin >> newAge;
		cout << "Please enter new student's gender: ";
		cin >> newGender;
		cout << "Please enter new student's course: ";
		cin >> newCourse;
		cout << "Please enter new student's russian mark: ";
		cin >> newPerformance_1;
		cout << "Please enter new student's physics mark: ";
		cin >> newPerformance_2;
		cout << "Please enter new student's math mark: ";
		cin >> newPerformance_3;


		if (newF[0] != '0') {
			strcpy_s(students[indexToEdit].f, newF);
		}
		if (newI[0] != '0') {
			strcpy_s(students[indexToEdit].i, newI);
		}
		if (newO[0] != '0') {
			strcpy_s(students[indexToEdit].o, newO);
		}
		if (newAge != 0) {
			students[indexToEdit].age = newAge;
		}
		if (newGender[0] != '0') {
			strcpy_s(students[indexToEdit].gender, newGender);
		}
		if (newCourse != 0) {
			students[indexToEdit].course = newCourse;
		}
		if (newPerformance_1 != 0) {
			students[indexToEdit].performance[0] = newPerformance_1;
		}
		if (newPerformance_2 != 0) {
			students[indexToEdit].performance[1] = newPerformance_2;
		}
		if (newPerformance_3 != 0) {
			students[indexToEdit].performance[2] = newPerformance_3;
		}

		cout << "Done!" << endl;
	}
	else {
		cout << "Student was not found!" << endl;
	}
};

bool isHighScorer(Student* students, int i) {
	if (students[i].performance[0] >= 9 && students[i].performance[1] >= 9 && students[i].performance[2] >= 9) {
		return true;
	}
	return false;
};

void sortFunc(Student* students, int& stringCounter) {    //функция для нахождения  отличников на n курсе и создания файла с ними
	int courseNumber;
	cout << "Please enter a course number to sort: "; cin >> courseNumber;
	int counter = 0;
	for (int i = 0; i < stringCounter; i++) {
		if (students[i].course == courseNumber && isHighScorer(students, i)) {
			ofstream file_1("highscorers.txt");
			file_1.open("highscorers.txt", ios::out | ios::binary);
			for (int i = 0; i < 100; i++) {
				file_1.write((char*)&students[i], sizeof(students[i]));
			}
			cout << "Done!" << endl;
		}
		else cout << "There are no highscorers!" << endl;
	}
};

void saveInformationToFile(Student* students, int stringCounter) {
	fstream file;
	file.open("C:\\Users\\Artem\\source\\repos\\lab5\\for_lab5.txt", ios::out | ios::binary);
	if (file.is_open()) {
		for (int i = 0; i < stringCounter; i++) {
			file.write((char*)&students[i], sizeof(students[i]));
		}
	}
	file.close();
}


int menu(Student* students, int& stringCounter) {
	int switchHelper;
	string countinueHelper;
	cout << "Available actions: " << endl << "Enter information from file - 1 " << endl << "View information about students as a table - 2" << endl << "Add item to the list - 3" << endl << "Delete item from the list - 4" << endl << "Edit information - 5" << endl << "Find highscores - 6" << endl << "Save information" << endl;
	cout << "Plese choose the action you need: "; cin >> switchHelper;
	switch (switchHelper)
	{
	case 1:
	{	
		eneterInformationAboutSutednrsFromFileAndStringCounter(students);
		stringCounter = eneterInformationAboutSutednrsFromFileAndStringCounter(students);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 2:
	{
		viewInformationAboutStudentsAsATable(students, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 3:
	{
		addInformationToFile(students, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 4:
	{
		deleteInformationFromFile(students, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 5:
	{
		editInformationAboutStudent(students, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 6:
	{
		sortFunc(students, stringCounter);
		cout << endl;
		cout << "Do you want to countinue? "; cin >> countinueHelper;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	};
	case 7:
	{
		saveInformationToFile(students, stringCounter); cout << "Do you want to countinue? "; cin >> countinueHelper;
		if (countinueHelper == "yes") {
			break;
		}
		else {
			return 0;
		}
	}
	case 0: return 0;
	}
	return menu(students, stringCounter);
};


int main() {
	Student* students = new Student[100];
	int stringCounter = 0;
	menu(students, stringCounter);
	return 0;
}

