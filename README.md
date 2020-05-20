# README
## 1.Topic
將輸入的instruction轉成machine code :pushpin:
## 2.Input description
輸入n個instruction，以-1當作結束  

:warning: 每一個instruction前面不能有空格，輸入範例如下  

:warning:  若此instruction前面需要label的話，輸入格式需為”L”+”數字”(此數字是阿拉伯數字不是中文數字)+”:”+” ”(空格)+”instruction”  

:warning: 每個instruction要換行。  

![image](https://github.com/fup3su6/ALCO_project1/blob/master/input.jpg)
 
## 3.Output description
按照RV32I Base Integer Instruction Set對照表(註4)的格式，將對應的type或inst的machine code印出，如上面input會有以下結果。  

以`add x2,x2,x23`為例  

其格式為 `func7(7 bit) rs2(5 bit) rs1(5 bit) func3(3 bit) rd(5 bit) opcode(7 bit)`  

後面x2的2放到`rs1`，x23的23放到`rs2`，前面x2的2放到`rd`  

`func7`、`func3`、`opcode`參照對照表  

轉換成`machine code`為`0000000 10111 00010 000 00010 0110011`

再以`bne x24,x23,L2`為例  

其格式為 `Imm[12|10:5](7 bit) rs2(5 bit) rs1(5 bit) func3(3 bit) imm[4:1|11](5 bit) opcode(7 bit)`  

其中，branch taken後跳到的`L2: `的位置為6 (從上而下 從1開始算pc)
則imm為000000000101
x24的24放到`rs1`，x23的23放到`rs2`，L2的6放到 `offset`(也就是imm)  

`func3`、`opcode`參照對照表  

轉換成`machine code`為`0000000 10111 11000 001 00110 1100011`  

![image](https://github.com/fup3su6/ALCO_project1/blob/master/output2.jpg)

:mag: (對照表)  

![image](https://github.com/fup3su6/ALCO_project1/blob/master/RISC-V.jpg)

## 4.Basic method
* 利用while(getline){ }將每一行instrucion讀入存起來  
* 先判斷有沒有label  
* 用逗號切割字串得到數字的值  
* 把register跟immediate值存起來

## 5.Code analysis
```c++
#include<iostream>
#include<bitset>
#include<string>
using namespace std;
int label[1000];
bool check = false;
```
使用`cin/cout`，`include<iostream>`  

會使用到2進位數字，`include<bitset>`來將10進位轉換成2進位  

使用string取instruction，`include<string>`  

宣告一個`global` `int array` `label` 寫入label位置  

宣告一個`global` `bool` `check` 判斷type，true為slli、srli、srai type，false為其他IR type

```c++

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
```
宣告一個`string` `buffer` 存getline的string，如果是”-1”就結束程式  

宣告一個`string` `array` `inst` 將每一條指令以string型態存入  

for迴圈跑每一行string的size，若有`:`存在代表那行有label，紀錄label，也就是Lm的位置 ex: L2的位子在instruction的第6行，則`label[2] = 6`。  

方式: 先將那格char– ‘0’的ascii變成數字index再存入

```c++
int pos;
	for (int j = 0;j < n;j++) {
		if (inst[j][0] == 'L') {
			pos = inst[j].find(" ");
			inst[j].erase(0, pos + 1);
		}
		pos = inst[j].find(" ");
		string x = inst[j].substr(0, pos);
```
宣告一個`int pos` 暫存find字元位置(本指令第一個空格)  

for迴圈跑n次(n=inst數量)，如果當前inst的第一格為’L’就把它擦掉(0到pos+1)  

宣告一個`string x` 存每行inst第一個空格前的字串ex:add、beq…(0到pos)

```c++
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
```
判斷x為哪個字串  

如果是`I/R type`，呼叫`IR(string str, string func7, string func3, string opcode)`  

第一個參數為去掉add/beq/…(指令中第一個字串)instruction的`substr`(從pos到instruction最後一位)  

第二個為`func7`  第三個為`func3`  第四個為`opcode`

```c++
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
```
如果x是`load type`，呼叫`load(string str, string func3)`  

第一個參數為去掉add/beq/…(指令中第一個字串)instruction的`substr`(從pos到instruction最後一位)  

第二個為`func3`

```c++
else if (x == "sb" || x == "sd") {
			S(inst[j].substr(pos, inst[j].size() - 1), "000");
		}
		else if (x == "sh") {
			S(inst[j].substr(pos, inst[j].size() - 1), "001");
		}
		else if (x == "sw") {
			S(inst[j].substr(pos, inst[j].size() - 1), "010");
		}
```
如果x是`store type`，呼叫`S(string str, string func3)`  

第一個參數為去掉add/beq/…(指令中第一個字串)instruction的`substr`(從pos到instruction最後一位)  

第二個為`func3`

```c++
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
```

如果x是`SB type`，呼叫`SB(string str, string func3)`  

第一個參數為去掉add/beq/…(指令中第一個字串)instruction的`substr`(從pos到instruction最後一位)  

第二個為`func3`

```c++
else if (x == "jalr") {
		jr(inst[j].substr(pos, inst[j].size() - 1), "000");
		}
```
如果x是`jalr`，呼叫`jr(string str, string func3)`  

第一個參數為去掉add/beq/…(指令中第一個字串)instruction的`substr`(從pos到instruction最後一位)  

第二個為`func3`

```c++
else if (x == "jal") {
		jj(inst[j].substr(pos, inst[j].size() - 1));
		}
```

如果x是`jal`，呼叫`jj(string str)`  

參數為去掉add/beq/…(指令中第一個字串)instruction的`substr`(從pos到instruction最後一位)

```c++
else if (x == "lui") {
		remain(inst[j].substr(pos, inst[j].size() - 1), "0110111");
		}
		else if (x == "auipc") {
		remain(inst[j].substr(pos, inst[j].size() - 1), "0010111");
		}
	}//end for
}//end main
```
如果x是`lui/auipc`，呼叫`remain(string str, string opcode)`  

第一個參數為去掉add/beq/…(指令中第一個字串)instruction的`substr`(從pos到instruction最後一位)  

第二個放`opcode`

```c++
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
```
`void IR(string str ,string func7,string func3,string opcode)`  
  
用來實作`R Type`與`I Type` instructions，傳入四個值分別為 `處理過後的字串`(詳情請看main function) `func7` `func3` `opcode` ，方便底下實作判斷   

宣告`string rs[3]` 用來存`rs1` `rs2` `rd` 分別的string  

宣告`int p` 存`rs[]`的位子，p = 0代表`rd`，p = 1代表`rs1`，p = 2代表`rs2`  

for迴圈從字串的第一個位子開始到最後  

如果遇到`,`就代表進入下一個位子p++，如果是數字就加入字串內  

宣告 `int rd` `int rs1` `int rs2` 並將剛剛存好的`string`利用`stoi`轉換為`int`  

如果`check`為`true`為`slli` `srli` `srai` `Type`，按照對照表的格式印出，else為其他的`IR Type`  

IR Type再判斷opcode，如果`opcode`為`"0110011"`代表`R Type`，其他 `opcode`為 `"0010011"`代表 `I Type`，再依照格式利用bitset調整bit印出

```c++
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
```
`void load(string str, string func3)`  
 
用來實作`load Type` instructions，傳入2個值分別為 `處理過後的字串`(詳情請看main function) `func3`，方便底下實作判斷    
 
宣告`string rs[3]` 用來存`rd` `offset` `rs1` 分別的string    

宣告`int p` 存`rs[]`的位子，p = 0代表`rd`，p = 1代表`offet`，p = 2代表`rs1`    

for迴圈從字串的第一個位子開始到最後    

如果遇到`,`或`(`就代表進入下一個位子p++，如果是數字就加入字串內    

宣告 `int rd` `int offset` `int rs1` 並將剛剛存好的`string`利用`stoi`轉換為`int`    

再依照格式利用bitset調整bit印出

```c++
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
```
`void S(string str, string func3)`  

用來實作 `store Type` instructions，傳入2個值分別為 `處理過後的字串`(詳情請看main function) `func3`，方便底下實作判斷     

宣告`string rs[3]` 用來存`rs2` `offset` `rs1` 分別的string    

宣告`int p` 存`rs[]`的位子，p = 0代表`rs2`，p = 1代表`offet`，p = 2代表`rs1`    

for迴圈從字串的第一個位子開始到最後    

如果遇到`,`或`(`就代表進入下一個位子p++，如果是數字就加入字串內    

宣告 `int rs2` `int offset` `int rs1` 並將剛剛存好的`string`利用`stoi`轉換為`int`    

又因為`store type`的`offset`要依他的表格分段切割再重新排列，先將`offset`轉成`12bit`的bitset `b0`，將b0轉成string後用`substr`分割，再依照格式利用bitset調整bit印出

```c++
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
```
`void SB(string str, string func3)`  

用來實作 `SB Type` instructions，傳入2個值分別為 `處理過後的字串`(詳情請看main function) `func3`，方便底下實作判斷   
  
宣告`string rs[3]` 用來存`rs1` `rs2` `buf` 分別的string  
  
宣告`int p` 存`rs[]`的位子，p = 0代表`rs1`，p = 1代表`rs2`，p = 2代表`buf`    

for迴圈從字串的第一個位子開始到最後    

如果遇到`,`就代表進入下一個位子p++，如果是數字就加入字串內    

宣告 `int rs1` `int rs2` `int buf`並將剛剛存好的`string`利用`stoi`轉換為`int`  
 
宣告 `int offset`存label為buf的位置  
 
又因為`SB type`的`offset`要依他的表格分段切割再重新排列，先將`offset`轉成`13bit`的bitset `b0`，將b0轉成string後用`substr`分割，再依照格式利用bitset調整bit印出  

```c++
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
```
`void jj(string str)`  

用來實作 `jal` instructions，傳入值為 `處理過後的字串`(詳情請看main function) 方便底下實作判斷  
   
宣告`string rs[2]` 用來存`rd` `buf` 分別的string  
  
宣告`int p` 存`rs[]`的位子，p = 0代表`rd`， p = 1代表`buf`  
  
for迴圈從字串的第一個位子開始到最後    

如果遇到`,`就代表進入下一個位子p++，如果是數字就加入字串內   
 
宣告 `int rd` `int buf`並將剛剛存好的`string`利用`stoi`轉換為`int`  
 
宣告 `int offset`存標籤為buf的位置  
 
又因為`jal`的`offset`要依他的表格分段切割再重新排列，先將`offset`轉成`21bit`的bitset `b0`，將b0轉成string後用`substr`分割，再依照格式利用bitset調整bit印出  

```c++
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
```
`void jr(string str, string func3)`  

用來實作 `jalr` instructions，傳入值為 `處理過後的字串`(詳情請看main function) `func3`，方便底下實作判斷   
  
宣告`string rs[3]` 用來存`rd` `rs1` `offet` 分別的string  
  
宣告`int p` 存`rs[]`的位子，p = 0代表`rd`， p = 1代表`rs1`，p = 2代表`offet`  
  
for迴圈從字串的第一個位子開始到最後    

如果遇到`,`就代表進入下一個位子p++，如果是數字就加入字串內    

宣告 `int rd` `int buf` `int offet`並將剛剛存好的`string`利用`stoi`轉換為`int`，再依照格式利用bitset調整bit印出  

```c++
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
```
`void remain(string str, string opcode)`  

用來實作 `lui/auipc` instructions，傳入值為 `處理過後的字串`(詳情請看main function) `opcode`，方便底下實作判斷    
 
宣告`string rs[2]` 用來存`rd` `offset` 分別的string  
  
宣告`int p` 存`rs[]`的位子，p = 0代表`rd`， p = 1代表`offset`  
 
for迴圈從字串的第一個位子開始到最後    

如果遇到`,`就代表進入下一個位子p++，如果是數字就加入字串內    

宣告 `int rd` `int offset`並將剛剛存好的`string`利用`stoi`轉換為`int`，再依照格式利用bitset調整bit印出








