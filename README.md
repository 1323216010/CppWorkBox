## SimpleDataFrame

```C++
#include <iostream>
#include <string>
#include "utils/headers/SimpleDataFrame.h"


int main() {
    SimpleDataFrame df("data.csv");
    std::cout << "Value at [1, 2]: " << df.getValueByName(2, "Global_time_stamp") << std::endl;  // 访问特定值
    auto temp = df.getColumnDataAs<double>("aps_single_SWIDE_viscoElastic_F0_INFU");
    df.insertColumn("test", {"-", "-", "1", "2", "3"});
    df.deleteRows({0, 1});
    df.to_csv("output.csv");
    return 0;
}

```

## math_functions

```c++
#include <iostream>
#include "utils/headers/math_functions.h"

int main() {
    checkSmooth(quad, "quad", -10, 10, 1000);
    checkSmooth(absFunc, "absFunc", -10, 10, 1000, 0.05);  // 对于absFunc，可以尝试使用更小的阈值
    checkSmooth(piecewise, "piecewise", -10, 10, 1000);

    std::cin.get();

    return 0;
}
```

