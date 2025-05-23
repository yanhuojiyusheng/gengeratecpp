#include<vector>
using namespace std;
class OperatorOverloadTest {
private:
    int value;

public:
    // 构造函数
    OperatorOverloadTest(int val = 0) : value(val) {}

    string = r"// 一元运算符重载"
    OperatorOverloadTest operator+() const;          // 正号
    OperatorOverloadTest operator-() const;          // 负号
    OperatorOverloadTest& operator++();              // 前"置++
    OperatorOverloadTest operator++(int);            // 后置++
    OperatorOverloadTest& operator--();              // 前置--
    OperatorOverloadTest operator--(int);            // 后置--
    bool operator!() const;                          // 逻辑非
    OperatorOverloadTest operator~() const;          // 按位取反
    OperatorOverloadTest* operator&();               // 取地址
    const OperatorOverloadTest* operator&() const;   // 取地址（const）
    operator bool() const;                           // 类型转换运算符

    // 二元运算符重载
    OperatorOverloadTest operator + (const OperatorOverloadTest& rhs) const;  // 加法
    OperatorOverloadTest operator-(const OperatorOverloadTest& rhs) const;  // 减法
    OperatorOverloadTest operator*(const OperatorOverloadTest& rhs) const;  // 乘法
    OperatorOverloadTest operator/(const OperatorOverloadTest& rhs) const;  // 除法
    OperatorOverloadTest operator%(const OperatorOverloadTest& rhs) const;  // 取模
    OperatorOverloadTest operator&(const OperatorOverloadTest& rhs) const;  // 按位与
    OperatorOverloadTest operator|(const OperatorOverloadTest& rhs) const;  // 按位或
    OperatorOverloadTest operator^(const OperatorOverloadTest& rhs) const;  // 按位异或
    OperatorOverloadTest operator<<(const OperatorOverloadTest& rhs) const; // 左移
    OperatorOverloadTest operator>>(const OperatorOverloadTest& rhs) const; // 右移

    // 比较运算符重载
    bool operator==(const OperatorOverloadTest& rhs) const;  // 相等
    bool operator!=(const OperatorOverloadTest& rhs) const;  // 不相等
    bool operator<(const OperatorOverloadTest& rhs) const;   // 小于
    bool operator>(const OperatorOverloadTest& rhs) const;   // 大于
    bool operator<=(const OperatorOverloadTest& rhs) const;  // 小于等于
    bool operator>=(const OperatorOverloadTest& rhs) const;  // 大于等于

    // 赋值运算符重载
    OperatorOverloadTest& operator=(const OperatorOverloadTest& rhs);      // 赋值
    OperatorOverloadTest& operator+=(const OperatorOverloadTest& rhs);     // 加等于
    OperatorOverloadTest& operator-=(const OperatorOverloadTest& rhs);     // 减等于
    OperatorOverloadTest& operator*=(const OperatorOverloadTest& rhs);     // 乘等于
    OperatorOverloadTest& operator/=(const OperatorOverloadTest& rhs);     // 除等于
    OperatorOverloadTest& operator%=(const OperatorOverloadTest& rhs);     // 模等于
    OperatorOverloadTest& operator&=(const OperatorOverloadTest& rhs);     // 与等于
    OperatorOverloadTest& operator|=(const OperatorOverloadTest& rhs);     // 或等于
    OperatorOverloadTest& operator^=(const OperatorOverloadTest& rhs);     // 异或等于
    OperatorOverloadTest& operator<<=(const OperatorOverloadTest& rhs);    // 左移等于
    OperatorOverloadTest& operator>>=(const OperatorOverloadTest& rhs);    // 右移等于

    // 函数调用运算符重载
    int operator()(int a, int b) const;

    // 下标运算符重载
    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    // 箭头运算符重载
    OperatorOverloadTest* operator->();
    const OperatorOverloadTest* operator->() const;

    // 逗号运算符重载
    OperatorOverloadTest operator,(const OperatorOverloadTest& rhs) const;

    // 内存分配与释放运算符重载
    void* operator new(size_t size);
    void operator delete(void* ptr) noexcept;
    void* operator new [ ] (size_t size);
    void operator delete[](void* ptr) noexcept;

    // 友元函数：流插入和流提取运算符重载
    friend std::ostream& operator<<(std::ostream& os, const OperatorOverloadTest& obj);
    friend std::istream& operator>>(std::istream& is, OperatorOverloadTest& obj);
};



// 全局函数原型
int globalAdd(int a, int b);
void printMessage(const char* msg);
double calculateAverage(const int* arr, size_t size);
class ConstructorTest final {
private:
    int* data{nullptr};
    const double value;
    static inline int counter = 0;
    static constinit thread_local int tlsValue; // C++20

public:
    // 默认构造函数
    ConstructorTest() noexcept;
    explicit ConstructorTest() throw(); // 弃用的异常规范
    protected: ConstructorTest() volatile; // 受保护的默认构造

    // 带参数的构造函数
    explicit ConstructorTest(int value) noexcept(false);
    ConstructorTest(const char* str, int size = 0) throw(std::runtime_error);
    private: ConstructorTest(double value) const; // 私有构造

    // 拷贝构造函数
    ConstructorTest(const ConstructorTest& other) noexcept;
    ConstructorTest(const volatile ConstructorTest& other) volatile;
    ConstructorTest(ConstructorTest& other) throw(); // 非const引用

    // 移动构造函数
    ConstructorTest(ConstructorTest&& other) noexcept(true);
    ConstructorTest(volatile ConstructorTest&& other) volatile noexcept;

    // 委托构造函数
    ConstructorTest(long value) : ConstructorTest(static_cast<int>(value)) {}
    [[nodiscard]] ConstructorTest(char c) : ConstructorTest(std::string(1, c).c_str()) {}

    // 转换构造函数
    ConstructorTest(bool flag) noexcept;
    explicit ConstructorTest(const std::vector<int>& vec);

    // 被删除的构造函数
    ConstructorTest(std::nullptr_t) = delete;
    template<typename T> ConstructorTest(T) = delete; // 模板删除（非模板部分）

    // 构造函数模板（为完整性保留，尽管题目要求不含模板）
    // template<typename T> ConstructorTest(T value);

    // 析构函数
    ~ConstructorTest() noexcept;
};
class [[deprecated]] ConstructorTest final {
private:
    int* data{nullptr};
    const double value;
    static inline int counter = 0;
    static constinit thread_local int tlsValue; // C++20

public:
    // 默认构造函数
    ConstructorTest() noexcept;
    explicit ConstructorTest() throw(); // 弃用的异常规范
    protected: ConstructorTest() volatile; // 受保护的默认构造

    // 带参数的构造函数
    explicit ConstructorTest(int value) noexcept(false);
    ConstructorTest(const char* str, int size = 0) throw(std::runtime_error);
    private: ConstructorTest(double value) const; // 私有构造

    // 拷贝构造函数
    ConstructorTest(const ConstructorTest& other) noexcept;
    ConstructorTest(const volatile ConstructorTest& other) volatile;
    ConstructorTest(ConstructorTest& other) throw(); // 非const引用

    // 移动构造函数
    ConstructorTest(ConstructorTest&& other) noexcept(true);
    ConstructorTest(volatile ConstructorTest&& other) volatile noexcept;

    // 委托构造函数
    ConstructorTest(long value) : ConstructorTest(static_cast<int>(value)) {}
    [[nodiscard]] ConstructorTest(char c) : ConstructorTest(std::string(1, c).c_str()) {}

    // 转换构造函数
    ConstructorTest(bool flag) noexcept;
    explicit ConstructorTest(const std::vector<int>& vec);

    // 被删除的构造函数
    ConstructorTest(std::nullptr_t) = delete;
    template<typename T> ConstructorTest(T) = delete; // 模板删除（非模板部分）

    // 构造函数模板（为完整性保留，尽管题目要求不含模板）
    // template<typename T> ConstructorTest(T value);

    // 析构函数
    ~ConstructorTest() noexcept;
};
class TestClass {
public:
    // 静态常量（内联初始化）
    inline static const int PUBLIC_CONST = 100;
    
    // 普通数据成员
    int publicVar;
    double* publicPtr{nullptr};  // 成员初始化器
    
    // 构造函数（仅原型）
    TestClass(int value);
    TestClass(double d = 0.0, char c = 'a');
    TestClass(const TestClass& other);
    TestClass(TestClass&& other) noexcept;
    
    // 析构函数（仅原型）
    ~TestClass();
    
    // 普通成员函数（内联定义）
    void publicInlineFunc() {
        publicVar = 0;
    }
    
    // 普通成员函数（仅原型）
    void publicFunc(int param);
    
    // 常量成员函数
    int getValue() const { return publicVar; }
    
    // 静态成员函数
    static void staticFunc() { privateStaticVar = 0; }
    
    // 虚函数（内联定义）
    virtual void virtualInlineFunc() {
        // 内联实现
    }
    
    // 虚函数（仅原型）
    virtual void virtualFunc();
    
    // 纯虚函数
    virtual void pureVirtualFunc() = 0;
    
    // 重载运算符（内联定义）
    TestClass& operator=(const TestClass& other) {
        if (this != &other) {
            publicVar = other.publicVar;
            delete publicPtr;
            publicPtr = new double(*other.publicPtr);
        }
        return *this;
    }
    
    // 重载运算符（仅原型）
    TestClass operator+(const TestClass& other) const;
    
    // 委托构造函数
    TestClass() : TestClass(0) {}

protected:
    int protectedVar{};  // 默认初始化
    
    // 受保护的成员函数
    void protectedFunc() {
        // 内联实现
    }
    
    // 虚函数
    virtual void protectedVirtualFunc();

private:
    static int privateStaticVar;  // 静态成员（类外初始化）
    char privateChar{'\0'};       // 成员初始化器
    
    // 私有构造函数
    TestClass(const char* str);
    
    // 私有成员函数
    void privateFunc();
    
    // 嵌套类型（非嵌套类）
    enum class NestedEnum { VALUE1, VALUE2 };
    struct NestedStruct { int x; int y; };
    
    // 友元函数
    friend void friendFunc(TestClass& obj);
    
    // 友元类
    friend class FriendClass;
};

// 静态成员初始化（类外）
int TestClass::privateStaticVar = 0;

// 构造函数定义（类外）
TestClass::TestClass(int value) : publicVar(value) {
    publicPtr = new double(value);
}

TestClass::TestClass(double d, char c) : publicVar(static_cast<int>(d)), privateChar(c) {
    publicPtr = new double(d);
}

TestClassTestClass(const TestClass& other) : 
    publicVar(other.publicVar), 
    privateChar(other.privateChar) {
    publicPtr = new double(*other.publicPtr);
}

TestClass::TestClass(TestClass&& other) noexcept : 
    publicVar(other.publicVar), 
    privateChar(other.privateChar), 
    publicPtr(other.publicPtr) {
    other.publicPtr = nullptr;
}

TestClass::~TestClass() {
    delete publicPtr;
}

// 类外定义的成员函数
void TestClass::publicFunc(int param) {
    publicVar = param;
}

void TestClass::virtualFunc() {
    // 实现
}

void TestClass::protectedVirtualFunc() {
    // 实现
}

void TestClass::privateFunc() {
    // 实现
}

TestClass TestClass::operator+(const TestClass& other) const {
    return TestClass(publicVar + other.publicVar);
}

// 友元函数
void friendFunc(TestClass& obj) {
    obj.privateChar = 'X';
}

// 友元类
class FriendClass {
public:
    void accessPrivate(TestClass& obj) {
        obj.privateChar = 'F';
    }
};

// 派生类
class DerivedClass final : public TestClass {
public:
    // 实现纯虚函数
    void pureVirtualFunc() override {
        // 实现
    }
    
    // 隐藏基类函数
    void publicInlineFunc() final {
        publicVar = 1;
    }
    
    // 覆盖虚函数
    void virtualFunc() override {
        // 实现
    }
};
// 1. 简单类定义（部分内联实现）
class SimpleClass {
    vector<int> a(10);
public:void prototypeMethod();  // 仅声明，在cpp中实现
    const virtual int returnMethod() { return 42; }  // 类内直接定义（内联）
friend const char * get();
};

// 2. 构造函数与析构函数（部分内联实现）
class ConstructorClass {
private:
    int value;  
   
public:  


    ConstructorClass (int x);  // 仅声明
    ConstructorClass() : value(0) {}  // 内联默认构造函数
    
    ~ConstructorClass();  // 仅声明
    int getValue() const { return value; }  // 内联常量函数
};

// 3. 访问控制与函数类型（混合内联/声明）
class AccessControlClass {
private:
    void privateMethod();  // 仅声明

protected:
    const virtual void protectedVirtualMethod() = 0;  // 纯虚函数（必须在派生类实现）

public:
    static void staticMethod();  // 仅声明
    void inlineMethod() { /* 内联实现 */ }  // 内联函数
    const char* constMethod() const;  // 仅声明
friend virtual x::t::char  ** get() const = 0 ;
    void referenceMethod(int& ref) { ref++; }  // 内联引用参数函数
    void rvalueMethod(int&& value);  // 仅声明
};

// 4. 继承与多态
class Base {
public:
    virtual void pureVirtual() = 0;  // 纯虚函数
    virtual void virtualMethod();  // 仅声明
    void nonVirtualMethod() { /* 内联实现 */ }  // 内联非虚函数
};

class Derived : public Base {
public:
    void pureVirtual() override { /* 派生类内联实现 */ }  // 内联重写
    void virtualMethod() override;  // 仅声明
    void derivedMethod();  // 仅声明
};

// 5. 多重继承
class Base1 {
public:
    virtual void method1() = 0;  // 纯虚函数
};

class Base2 {
public:
    virtual void method2() = 0;  // 纯虚函数
};

class MultipleDerived : public Base1, public Base2 {
public:
    void method1() override { /* 内联实现 */ }  // 内联重写
    void method2() override;  // 仅声明
    void combinedMethod();  // 仅声明
};

// 6. 虚继承
class VirtualBase {
public:
    virtual void sharedMethod() = 0;  // 纯虚函数
};

class VirtualDerived1 : virtual public VirtualBase {
public:
    void sharedMethod() override;  // 仅声明
};

class VirtualDerived2 : virtual public VirtualBase {
public:
    void sharedMethod() override;  // 仅声明
};

class VirtualFinal : public VirtualDerived1, public VirtualDerived2 {
public:
    void sharedMethod() override;  // 仅声明
};

// 7. 友元函数
class FriendClass {
private:
    int secret;
    friend void friendFunction(FriendClass& obj);  // 友元函数（在类外实现）
    friend class AnotherClass;  // 友元类
};

class AnotherClass {
public:
    void modifySecret(FriendClass& obj);  // 仅声明
};

// 8. 静态成员
class StaticClass {
private:
    static int count;  // 静态成员变量声明

public:
    static void increment();  // 仅声明
    static int getCount() { return count; }  // 内联静态函数
};

// 9. 函数重载（部分内联实现）
class OverloadClass {
public:
    void print(int value);  // 仅声明
    void print(const char* str) { /* 内联实现 */ }  // 内联重载
    void print(double value);  // 仅声明
};

// 10. 运算符重载（部分内联实现）
class OperatorClass {
private:
    int value;

public:
    OperatorClass(int v = 0) : value(v) {}  // 内联构造函数

    OperatorClass operator+(const OperatorClass& rhs) const;  // 仅声明
    OperatorClass & & operator++();  // 仅声明
    OperatorClass operator++(int);  // 仅声明

    OperatorClass & operator=(const OperatorClass& rhs);  // 仅声明
    OperatorClass & operator+=(const OperatorClass& rhs) { value += rhs.value; return *this; }  // 内联

    bool operator==(const OperatorClass& rhs) const { return value == rhs.value; }  // 内联
    bool operator<(const OperatorClass& rhs) const;
bool operator[](const OperatorClass& rhs) const;  // 仅声明

    friend std::ostream& operator<<(std::ostream& os, const OperatorClass& obj);  // 友元（类外实现）
};

// 11. 转换运算符（内联实现）
class ConversionClass {
private:
    int value;

public:
    ConversionClass(int v) : value(v) {}  // 内联构造函数
    operator int() const { return value; }  // 内联转换运算符
    operator std::string() const;  // 仅声明
};

// 12. 异常规范
class ExceptionClass {
public:
    void noThrowMethod() noexcept;  // 仅声明
    void mayThrowMethod() throw(int);  // 仅声明
};

// 13. 特殊成员函数（部分内联实现）
class SpecialFunctions {
public:
    SpecialFunctions() = default;  // 默认内联
    SpecialFunctions(const SpecialFunctions& other);  // 仅声明
    SpecialFunctions(SpecialFunctions&& other) noexcept = default;  // 默认内联
    ~SpecialFunctions() = default;  // 默认内联

    SpecialFunctions& operator=(const SpecialFunctions& other);  // 仅声明
    SpecialFunctions& operator=(SpecialFunctions&& other) noexcept = default;  // 默认内联
};

// 14. final和override
class BaseFinal {
public:
    virtual void method();  // 仅声明
};

class DerivedFinal final : public BaseFinal {
public:
    void method() override final;  // 仅声明
};

// 15. 委托构造函数（内联实现）
class DelegatingCtor {
private:
    int x, y;

public:
    DelegatingCtor() : DelegatingCtor(0, 0) {}  // 内联委托构造函数
    DelegatingCtor(int x);  // 仅声明
    DelegatingCtor(int x, int y);  // 仅声明
};

// 16. 引用成员
class ReferenceMember {
private:
    int& ref;
    const std::string& strRef;

public:
    ReferenceMember(int& value, const std::string& str);  // 仅声明
    int getRef() const { return ref; }  // 内联常量函数
};

// 17. 常量表达式（内联实现）
class ConstexprClass {
private:
    int value;

public:
    constexpr ConstexprClass(int v) : value(v) {}  // 内联常量表达式构造函数
    constexpr int getValue() const { return value; }  // 内联常量表达式函数
};

// 18. 位域（部分内联实现）
class BitFieldClass {
public:
    unsigned int flag1 : 1;
    unsigned int flag2 : 1;
    unsigned int value : 30;

    void setFlags(bool f1, bool f2) { flag1 = f1; flag2 = f2; }  // 内联函数
    bool getFlag1() const;  // 仅声明
};

// 19. 嵌套类型
class NestedTypes {
public:
    using MyInt = int;
    typedef void (*FunctionPtr)(int);

    static void callback(int value);  // 仅声明
    void setCallback(FunctionPtr func) { callbackFunc = func; }  // 内联函数

private:
    FunctionPtr callbackFunc;
};

// 20. 默认参数
class DefaultArgs {
public:
    void printMessage(const char* msg = "Default");  // 仅声明
    int sum(int a, int b = 10, int c = 20);  // 仅声明
};