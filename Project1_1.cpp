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
		
	}