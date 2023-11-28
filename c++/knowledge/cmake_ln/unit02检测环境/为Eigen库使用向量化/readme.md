- 大多数处理器提供向量指令集，代码可以利用这些特性，获得更高的性能。
- 由于线性代数运算可以从Eigen库中获得很好的加速，所以在使用Eigen库时，就要考虑向量化。
- 我们所要做的就是，指示编译器为我们检查处理器，并为当前体系结构生成本机指令。
- 不同的编译器供应商会使用不同的标志来实现这一点：
    - GNU编译器使用-march=native标志来实现这一点
    - Intel编译器使用-xHost标志。
    
- 使用CheckCXXCompilerFlag.cmake模块提供的check_cxx_compiler_flag函数进行编译器标志的检查:
`check_cxx_compiler_flag("-march=native" _march_native_works)`
这个函数接受两个参数:
第一个是要检查的编译器标志。
第二个是用来存储检查结果(true或false)的变量。如果检查为真，我们将工作标志添加到_CXX_FLAGS变量中，该变量将用于为可执行目标设置编译器标志。