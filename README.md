# DataLink_Send
dataLink_send.exe

## 出现的问题
### 1.出现烫烫

![Uploading image.png…]()


#### 出现原因：
由于定义了未初始的变量，编译器会自动初始化为0xCCCCCCCC，对应的中文字符为烫
#### 解决办法：
见链接  https://blog.csdn.net/kang___xi/article/details/80465939
