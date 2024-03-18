//
// Created by Pengcheng.yan on 2024/2/26.
//

#ifndef WORKBOX_SIMPLEDATAFRAME_H
#define WORKBOX_SIMPLEDATAFRAME_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>

class SimpleDataFrame {
private:
    std::vector<std::vector<std::string>> data;  // 存储数据行
    std::vector<std::string> columnNames;  // 存储列名
    std::unordered_map<std::string, size_t> columnIndex;  // 列名到列索引的映射

public:
    SimpleDataFrame(const std::string& filePath = "");

    void setColumnNames(const std::vector<std::string>& names);
    void addRow(const std::vector<std::string>& row);

    template <typename T>
    void addRow(const std::vector<T>& row);

    std::string getValue(int row, int col) const;
    std::string getValueByName(int row, const std::string& colName) const;
    void print() const;

    template <typename T>
    std::vector<T> getColumnDataAs(const std::string& colName) const;
    void to_csv(const std::string& filePath) const;

    void insertColumn(const std::string& colName, const std::vector<std::string>& colData, size_t position = std::string::npos);
    void deleteRows(const std::vector<size_t>& rowIndexes);
    void renameColumn(const std::string& oldName, const std::string& newName);

    template<typename NumericType>
    std::vector<std::string> convertToStrings(const std::vector<NumericType>& numericList);
    std::vector<std::string> splitStringByComma(const std::string& str);
};

template <typename T>
void SimpleDataFrame::addRow(const std::vector<T>& row) {
    std::vector<std::string> stringRow;  // 用于存储转换后的字符串行
    std::stringstream ss;

    for (const auto& elem : row) {
        ss.str("");  // 清空 stringstream
        ss.clear();  // 清除所有错误标志
        ss << elem;  // 将元素输出到 stringstream，利用流的自动类型转换
        stringRow.push_back(ss.str());  // 将转换后的字符串添加到 stringRow
    }

    // 如果是第一次添加行，且列名未设置，则将其设置为列名
    if (data.empty() && columnNames.empty()) {
        setColumnNames(stringRow);
    } else {
        // 确保后续添加的行与列名数量相匹配
        if (stringRow.size() == columnNames.size()) {
            data.push_back(stringRow);
        } else {
            std::cerr << "Row size does not match the number of columns." << std::endl;
        }
    }
}

template <typename T>
std::vector<T> SimpleDataFrame::getColumnDataAs(const std::string& colName) const {
    std::vector<T> columnData;
    columnData.reserve(data.size());  // 预分配足够的空间

    auto it = columnIndex.find(colName);
    if (it != columnIndex.end()) {
        size_t colIndex = it->second;
        std::istringstream iss;  // 重用一个字符串流对象

        for (const auto& row : data) {
            if (colIndex < row.size()) {
                iss.clear();
                iss.str(row[colIndex]);
                T value;
                if (iss >> value) {
                    columnData.push_back(value);
                } else {
                    columnData.push_back(T());  // 添加默认构造的值
                }
            }
        }
    }

    return columnData;
}

template <typename T>
std::vector<std::string> SimpleDataFrame::convertToStrings(const std::vector<T>& numericList) {
    std::vector<std::string> stringList;
    for (const T& value : numericList) {
        stringList.push_back(std::to_string(value));
    }
    return stringList;
}
#endif // WORKBOX_SIMPLEDATAFRAME_H
