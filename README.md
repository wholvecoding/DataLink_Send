# DataLink_Send
dataLink_send.exe

## 出现的问题
### 1.项目配置
1.1项目->属性->高级->字符集->多字符
![image](https://github.com/wholvecoding/DataLink_Send/assets/126675746/019be591-62dc-4eab-adf3-c012b5e540cf)
1.2 项目->属性->c/c++->SDL检查
![image](https://github.com/wholvecoding/DataLink_Send/assets/126675746/3bd04a54-326b-4f22-9e16-036dbe608e1a)
1.3 项目->属性->链接器->输入->附加依赖项
添加 ws2_32.lib
1.4 项目->属性->链接器->系统->子系统->windows(窗口)
![image](https://github.com/wholvecoding/DataLink_Send/assets/126675746/9e16ca2b-3393-489c-a615-88ed7bb3c02a)

### 2.出现烫烫

![image](https://github.com/wholvecoding/DataLink_Send/assets/126675746/8d047e26-5cb6-4233-9737-65aef30a43e0)



#### 出现原因：
由于定义了未初始的变量，编译器会自动初始化为0xCCCCCCCC，对应的中文字符为烫
#### 解决办法：
见链接  https://blog.csdn.net/kang___xi/article/details/80465939
