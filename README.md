# 1.Input description
輸入n個instruction，以-1當作結束  

註: 每一個instruction前面不能有空格，輸入範例如下  

註2: 若此instruction前面需要label的話，輸入格式需為”L”+”數字”(此數字是阿拉伯數字不是中文數字)+”:”+” ”(空格)+”instruction”  

註3: 每個instruction要換行。  

![image](https://github.com/fup3su6/ALCO_project1/blob/master/input.jpg)
 
# 2.Output description
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

註4: (對照表)  

![image](https://github.com/fup3su6/ALCO_project1/blob/master/RISC-V.jpg)



# 3.Basic method
* 利用while(getline){ }將每一行instrucion讀入存起來  
* 先判斷有沒有label  
* 用逗號切割字串得到數字的值  
* 把register跟immediate值存起來

# 4.Code analysis
```c++
#include<iostream>
#include<bitset>
#include<string>
using namespace std;
```



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
