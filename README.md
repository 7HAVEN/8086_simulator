# 8086_simulator

a simple 8086 simulator made in c++ 
it supports basic instructions like moving data in and out of memory and basic arithmetic operations like add , sub , mul and div.

## currently supported instructions 

currently it supports writing 8 bit and 16 bit data to memory and in between registers

### MOV
```asm
MOV <REG,REG> moving data between registers
  MOV ax,bx
  MOV ds,ax
  MOV ah,al
 ```
 ```asm
MOV <MEMORY,REG> moving data between mem and registers
  MOV [offset],reg(8bit)
  MOV ah,[0043]
  MOV [0323],ch
  
```
 ```asm
MOV <REG,immediate data> moving immediate data into registers
MOV AX,43
MOV ch,12
  
```
### Arihmetic instructions
#### ADD

Note: please avoid data overflow  as flag register are not currently supported.
Due to which wrong results might be produced and you will have no way of knowing.
```asm
ADD AL,AH
ADD AX,06
ADD AH,BH
```
#### SUB
```asm
SUB AH,BH
SUB AX,06
SUB AH,BH
```
#### MUL
```asm
MUL AH,BH
MUL AX,06
```

#### DIV
DIV AH,BL
note div operations currently dont support reading data from memory
## Usage
### Linux
```bash
git clone  https://github.com/7HAVEN/8086_simulator.git --recursive
cd 8086_simulator
mkdir build
cd build
cmake  -- build .
./simulator
```
### Windows

```bash
git clone  https://github.com/7HAVEN/8086_simulator.git --recursive 
cd 8086_simulator
```
Then open the project in visual studio 
and then select cmake file as starting point and click run 

Note: you must have cmake and Linux building tools in visual studio

## UI
the ui is made in imgui 
![image](https://github.com/7HAVEN/oops_cpp/blob/main/image2.png)

## DISCLAIMBER
pls dont read the code base its bad for your mental health i dont know how i managed to write such bad code its abysmal and doesn't follow any 
particular style and severe lack of comments is also a big problem but they dont teach us 
good coding practices in the university. and this thing doesn't support hex data so  this is not an exact way how 8086 will behave therefor your results may vary
i made this as  university project and i passed the examination so i dont wanna fix any of these major issues for now and if you wanna use it feel free to clone the repo and add on this project. 

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/7HAVEN/8086_simulator/blob/main/LICENSE)


## Authors

- [@7HAVEN](https://www.github.com/7HAVEN)

