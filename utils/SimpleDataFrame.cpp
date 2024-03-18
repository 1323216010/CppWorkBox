//
// Created by Pengcheng.yan on 2024/2/26.
//

#include "headers/SimpleDataFrame.h"
#include <fstream>
#include <set>

SimpleDataFrame::SimpleDataFrame(const std::string& filePath) {
    if (!filePath.empty()) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return;
        }

        std::string line;
        bool isFirstLine = true;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;
            std::vector<std::string> row;

            while (std::getline(ss, value, ',')) {
                row.push_back(value);
            }

            if (isFirstLine) {
                setColumnNames(row);
                isFirstLine = false;
            } else {
                addRow(row);
            }
        }

        file.close();
    }
}

void SimpleDataFrame::setColumnNames(const std::vector<std::string>& names) {
    columnNames = names;
    columnIndex.clear();
    for (size_t i = 0; i < names.size(); ++i) {
        columnIndex[names[i]] = i;
    }
}

void SimpleDataFrame::addRow(const std::vector<std::string>& row) {
    // 如果是第一次添加行，将其设置为列名
    if (data.empty() && columnNames.empty()) {
        setColumnNames(row);
    } else {
        // 确保后续添加的行与列名数量相匹配
        if (row.size() == columnNames.size()) {
            data.push_back(row);
        } else {
            std::cerr << "Row size does not match the number of columns." << std::endl;
        }
    }
}

std::string SimpleDataFrame::getValue(int row, int col) const {
    if (row >= 0 && row < data.size() && col >= 0 && col < data[row].size()) {
        return data[row][col];
    }
    return "";  // 返回空字符串作为错误指示
}

std::string SimpleDataFrame::getValueByName(int row, const std::string& colName) const {
    auto it = columnIndex.find(colName);
    if (it != columnIndex.end()) {
        return getValue(row, it->second);
    }
    return "";  // 列名未找到
}

void SimpleDataFrame::print() const {
    for (const auto& name : columnNames) {
        std::cout << name << " ";
    }
    std::cout << std::endl;

    for (const auto& row : data) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

void SimpleDataFrame::to_csv(const std::string& filePath) const {
    std::ofstream outFile(filePath);

    // 检查文件是否成功打开
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    // 首先写入列名
    for (size_t i = 0; i < columnNames.size(); ++i) {
        outFile << columnNames[i];
        if (i < columnNames.size() - 1) outFile << ",";  // 不在最后一个列名后添加逗号
    }
    outFile << "\n";

    // 然后写入数据
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i < row.size() - 1) outFile << ",";  // 不在行的最后一个值后添加逗号
        }
        outFile << "\n";
    }

    outFile.close();  // 关闭文件
}

void SimpleDataFrame::insertColumn(const std::string& colName, const std::vector<std::string>& colData, size_t position) {
    if (position == std::string::npos || position > columnNames.size()) {
        position = columnNames.size();
    }

    // 如果data为空但colData非空，初始化data以匹配colData的大小
    if (data.empty() && !colData.empty()) {
        for (size_t i = 0; i < colData.size(); ++i) {
            data.push_back(std::vector<std::string>(columnNames.size())); // 为每个现有列创建空字符串
        }
    }

    // 检查数据长度是否与现有的行数匹配
    if (colData.size() > data.size()) {
        std::cerr << "Column data size does not match the number of rows." << std::endl;
        return;
    }

    columnNames.insert(columnNames.begin() + position, colName);

    // 更新列索引映射
    columnIndex.clear();
    for (size_t i = 0; i < columnNames.size(); ++i) {
        columnIndex[columnNames[i]] = i;
    }

    for (size_t i = 0; i < data.size(); ++i) {
        data[i].insert(data[i].begin() + position, i < colData.size() ? colData[i] : "0");
    }
}

void SimpleDataFrame::deleteRows(const std::vector<size_t>& rowIndexes) {
    // 创建一个去重且排序的索引列表
    std::set<size_t> uniqueIndexes(rowIndexes.begin(), rowIndexes.end());

    // 从大到小遍历索引并删除行，使用rbegin和rend进行反向迭代
    for (auto it = uniqueIndexes.rbegin(); it != uniqueIndexes.rend(); ++it) {
        size_t rowIndex = *it;
        // 检查行索引是否有效
        if (rowIndex < data.size()) {
            data.erase(data.begin() + rowIndex);
        } else {
            std::cerr << "Row index out of range: " << rowIndex << std::endl;
        }
    }
}

void SimpleDataFrame::renameColumn(const std::string& oldName, const std::string& newName) {
    auto it = columnIndex.find(oldName);
    if (it == columnIndex.end()) {
        std::cerr << "Column '" << oldName << "' not found." << std::endl;
        return;
    }

    // 获取旧列名的索引
    size_t colIndex = it->second;

    // 更新列名列表
    columnNames[colIndex] = newName;

    // 由于列名已更改，需要更新列索引映射
    columnIndex.erase(oldName);  // 删除旧列名的映射
    columnIndex[newName] = colIndex;  // 添加新列名的映射
}

std::vector<std::string> SimpleDataFrame::splitStringByComma(const std::string& str) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, ',')) {
        result.push_back(item);
    }

    return result;
}