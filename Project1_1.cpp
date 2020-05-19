#include<iostream>
#include<bitset>
#include<string>
using namespace std;
int label[1000];
bool check = false;

void IR(string str, string func7, string func3, string opcode) {
	string rs[3];
	int p = 0;
	for (int i = 0;i < str.size();i++) {
		if (str[i] == ',') {
			p++;
			continue;
		}

		if (str[i] == 45 || (str[i] > 47 && str[i] < 58))
			rs[p] += str[i];
	}
	int rd = stoi(rs[0]);
	int rs1 = stoi(rs[1]);
	int rs2 = stoi(rs[2]);
	if (check == true) {
		cout << func7 << " " << bitset<5>(rs2) << " " << bitset<5>(rs1) << " " << func3 << " " << bitset<5>(rd) << " " << "0010011" << endl;
		check = false;
	}
	else {
		if (opcode == "0110011")
			cout << func7 << " " << bitset<5>(rs2) << " " << bitset<5>(rs1) << " " << func3 << " " << bitset<5>(rd) << " " << "0110011" << endl;
		else
			cout << bitset<12>(rs2) << " " << bitset<5>(rs1) << " " << func3 << " " << bitset<5>(rd) << " " << "0010011" << endl;
	}
}
void load(string str, string func3) {
	string rs[3];
	int p = 0;
	for (int i = 0;i < str.size();i++) {
		if (str[i] == ',' || str[i] == '(') {
			p++;
			continue;
		}

		if (str[i] > 47 && str[i] < 58)
			rs[p] += str[i];
	}
	int rd = stoi(rs[0]);
	int offet = stoi(rs[1]);
	int rs1 = stoi(rs[2]);
	cout << bitset<12>(offet) << " " << bitset<5>(rs1) << " " << func3 << " " << bitset<5>(rd) << " " << "0000011" << endl;
}
void S(string str, string func3) {
	string rs[3];
	int p = 0;
	for (int i = 0;i < str.size();i++) {
		if (str[i] == ',' || str[i] == '(') {
			p++;
			continue;
		}

		if (str[i] > 47 && str[i] < 58)
			rs[p] += str[i];
	}
	int rs2 = stoi(rs[0]);
	int offset = stoi(rs[1]);
	int rs1 = stoi(rs[2]);
	bitset<12> b0(offset);
	string s, s1, s2;
	s = b0.to_string();
	s1 = s.substr(0, 7);
	s2 = s.substr(7, 5);
	cout << s1 << " " << bitset<5>(rs2) << " " << bitset<5>(rs1) << " " << func3 << " " << s2 << " " << "0100011" << endl;
}

void SB(string str, string func3) {
	string rs[3];
	int p = 0;
	for (int i = 0;i < str.size();i++) {
		if (str[i] == ',') {
			p++;
			continue;
		}

		if (str[i] > 47 && str[i] < 58)
			rs[p] += str[i];
	}
	int rs1 = stoi(rs[0]);
	int rs2 = stoi(rs[1]);
	int buf = stoi(rs[2]);
	int offset = label[buf];
	bitset<13> b0(offset);
	string s, s1, s2, s3, s4;
	s = b0.to_string();
	s1 = s.substr(0, 1);
	s2 = s.substr(1, 1);
	s3 = s.substr(2, 6);
	s4 = s.substr(8, 4);
	cout << s1 << s3 << " " << bitset<5>(rs2) << " " << bitset<5>(rs1) << " " << func3 << " " << s4 << s2 << " " << "1100011" << endl;
}
void jj(string str) {
	string rs[2];
	int p = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ',') {
			p++;
			continue;
		}

		if (str[i] > 47 && str[i] < 58)
			rs[p] += str[i];
	}
	int rd = stoi(rs[0]);
	int buf = stoi(rs[1]);
	int offset = label[buf];
	bitset<21> b0(offset);
	string s, s1, s2, s3, s4;
	s = b0.to_string();
	s1 = s.substr(0, 1);
	s2 = s.substr(1, 8);
	s3 = s.substr(9, 1);
	s4 = s.substr(10, 10);
	cout << s1 << " " << s4 << " " << s3 << " " << s2 << " " << bitset<5>(rd) << " " << "1101111" << endl;
}

void jr(string str, string func3) {
	string rs[3];
	int p = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ',') {
			p++;
			continue;
		}

		if (str[i] > 47 && str[i] < 58)
			rs[p] += str[i];
	}
	int rd = stoi(rs[0]);
	int rs1 = stoi(rs[1]);
	int offet = stoi(rs[2]);
	cout << bitset<12>(offet) << " " << bitset<5>(rs1) << " " << func3 << " " << bitset<5>(rd) << " " << "1100111" << endl;
}
void remain(string str, string opcode) {
	string rs[2];
	int p = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ',') {
			p++;
			continue;
		}

		if (str[i] > 47 && str[i] < 58)
			rs[p] += str[i];
	}
	int rd = stoi(rs[0]);
	int offset = stoi(rs[1]);
	bitset<20> b0(offset);
	cout << b0 << " " << bitset<5>(rd) << " " << opcode << endl;
}
int main() {
	string buffer;
	string inst[1000];

	int n = 1;
	while (getline(cin, buffer)) {
		if (buffer == "-1")
			break;
		inst[n] = buffer;
		for (int k = 0;k < buffer.size();k++) {
			if (buffer[k] == ':') {
				int m = buffer[k - 1] - '0';
				label[m] = n;
			}
		}
		n++;
	}
	int pos;
	for (int j = 0;j < n;j++) {
		if (inst[j][0] == 'L') {
			pos = inst[j].find(" ");
			inst[j].erase(0, pos + 1);
		}
		pos = inst[j].find(" ");
		string x = inst[j].substr(0, pos);
		if (x == "add") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "000", "0110011");
		}
		else if (x == "sub") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0100000", "000", "0110011");
		}
		else if (x == "sll") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "001", "0110011");
		}
		else if (x == "slt") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "010", "0110011");
		}
		else if (x == "sltu") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "011", "0110011");
		}
		else if (x == "xor") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "100", "0110011");
		}
		else if (x == "srl") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "101", "0110011");
		}
		else if (x == "sra") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0100000", "101", "0110011");
		}
		else if (x == "or") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "110", "0110011");
		}
		else if (x == "and") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "111", "0110011");
		}
		else if (x == "slli") {
			check = true;
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "001", "0010011");
		}
		else if (x == "srli") {
			check = true;
			IR(inst[j].substr(pos, inst[j].size() - 1), "0000000", "101", "0010011");
		}
		else if (x == "srai") {
			check = true;
			IR(inst[j].substr(pos, inst[j].size() - 1), "0100000", "101", "0010011");
		}
		else if (x == "addi") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0", "000", "0010011");
		}
		else if (x == "slti") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0", "010", "0010011");
		}
		else if (x == "sltiu") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0", "011", "0010011");
		}
		else if (x == "xori") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0", "100", "0010011");
		}
		else if (x == "ori") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0", "110", "0010011");
		}
		else if (x == "andi") {
			IR(inst[j].substr(pos, inst[j].size() - 1), "0", "111", "0010011");
		}
		else if (x == "lb") {
			load(inst[j].substr(pos, inst[j].size() - 1), "000");
		}
		else if (x == "lh") {
			load(inst[j].substr(pos, inst[j].size() - 1), "001");
		}
		else if (x == "lw") {
			load(inst[j].substr(pos, inst[j].size() - 1), "010");
		}
		else if (x == "lbu") {
			load(inst[j].substr(pos, inst[j].size() - 1), "100");
		}
		else if (x == "lhu") {
			load(inst[j].substr(pos, inst[j].size() - 1), "101");
		}
		else if (x == "sb" || x == "sd") {
			S(inst[j].substr(pos, inst[j].size() - 1), "000");
		}
		else if (x == "sh") {
			S(inst[j].substr(pos, inst[j].size() - 1), "001");
		}
		else if (x == "sw") {
			S(inst[j].substr(pos, inst[j].size() - 1), "010");
		}
		else if (x == "beq") {
			SB(inst[j].substr(pos, inst[j].size() - 1), "000");
		}
		else if (x == "bne") {
			SB(inst[j].substr(pos, inst[j].size() - 1), "001");
		}
		else if (x == "blt") {
			SB(inst[j].substr(pos, inst[j].size() - 1), "100");
		}
		else if (x == "bge") {
			SB(inst[j].substr(pos, inst[j].size() - 1), "101");
		}
		else if (x == "bltu") {
			SB(inst[j].substr(pos, inst[j].size() - 1), "110");
		}
		else if (x == "bgeu") {
			SB(inst[j].substr(pos, inst[j].size() - 1), "111");
		}
		else if (x == "jalr") {
		jr(inst[j].substr(pos, inst[j].size() - 1), "000");
		}
		else if (x == "jal") {
		jj(inst[j].substr(pos, inst[j].size() - 1));
		}
		else if (x == "lui") {
		remain(inst[j].substr(pos, inst[j].size() - 1), "0110111");
		}
		else if (x == "auipc") {
		remain(inst[j].substr(pos, inst[j].size() - 1), "0010111");
		}
	}