# 8086_simulator

a simple 8086 simulator made in c++ 
it supports basic instructions 
## currently supported instructions 
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
## Usage

```bash
mkdir build
cd build

cmake  -- build .

./simulator
```
## UI
the ui is made in imgui 
![image](https://github.com/7HAVEN/oops_cpp/blob/main/image2.png)

## DISCLAIMBER
pls dont read the code base its bad for your mental health i dont know how i managed to write such bad code its abysmal and doesn't follow any 
particular style and severe lack of comments is also a big problem but they dont teach us 
good coding practices in the university. and this thing doesn't support hex data so ya this is not an exact way how 8086 will behave so your results may vary
i made this as  university project and i passed the examination so i dont wanna fix any of these major issues for now and if you wanna use it feel free to clone the repo and add on this project. 

[![MIT License](https://img.shields.io/apm/l/atomic-design-ui.svg?)](https://github.com/tterb/atomic-design-ui/blob/master/LICENSEs)


## Authors

- [@7HAVEN](https://www.github.com/7HAVEN)

