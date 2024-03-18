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
    // ����ǵ�һ������У���������Ϊ����
    if (data.empty() && columnNames.empty()) {
        setColumnNames(row);
    } else {
        // ȷ��������ӵ���������������ƥ��
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
    return "";  // ���ؿ��ַ�����Ϊ����ָʾ
}

std::string SimpleDataFrame::getValueByName(int row, const std::string& colName) const {
    auto it = columnIndex.find(colName);
    if (it != columnIndex.end()) {
        return getValue(row, it->second);
    }
    return "";  // ����δ�ҵ�
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

    // ����ļ��Ƿ�ɹ���
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    // ����д������
    for (size_t i = 0; i < columnNames.size(); ++i) {
        outFile << columnNames[i];
        if (i < columnNames.size() - 1) outFile << ",";  // �������һ����������Ӷ���
    }
    outFile << "\n";

    // Ȼ��д������
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i < row.size() - 1) outFile << ",";  // �����е����һ��ֵ����Ӷ���
        }
        outFile << "\n";
    }

    outFile.close();  // �ر��ļ�
}

void SimpleDataFrame::insertColumn(const std::string& colName, const std::vector<std::string>& colData, size_t position) {
    if (position == std::string::npos || position > columnNames.size()) {
        position = columnNames.size();
    }

    // ���dataΪ�յ�colData�ǿգ���ʼ��data��ƥ��colData�Ĵ�С
    if (data.empty() && !colData.empty()) {
        for (size_t i = 0; i < colData.size(); ++i) {
            data.push_back(std::vector<std::string>(columnNames.size())); // Ϊÿ�������д������ַ���
        }
    }

    // ������ݳ����Ƿ������е�����ƥ��
    if (colData.size() > data.size()) {
        std::cerr << "Column data size does not match the number of rows." << std::endl;
        return;
    }

    columnNames.insert(columnNames.begin() + position, colName);

    // ����������ӳ��
    columnIndex.clear();
    for (size_t i = 0; i < columnNames.size(); ++i) {
        columnIndex[columnNames[i]] = i;
    }

    for (size_t i = 0; i < data.size(); ++i) {
        data[i].insert(data[i].begin() + position, i < colData.size() ? colData[i] : "0");
    }
}

void SimpleDataFrame::deleteRows(const std::vector<size_t>& rowIndexes) {
    // ����һ��ȥ��������������б�
    std::set<size_t> uniqueIndexes(rowIndexes.begin(), rowIndexes.end());

    // �Ӵ�С����������ɾ���У�ʹ��rbegin��rend���з������
    for (auto it = uniqueIndexes.rbegin(); it != uniqueIndexes.rend(); ++it) {
        size_t rowIndex = *it;
        // ����������Ƿ���Ч
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

    // ��ȡ������������
    size_t colIndex = it->second;

    // ���������б�
    columnNames[colIndex] = newName;

    // ���������Ѹ��ģ���Ҫ����������ӳ��
    columnIndex.erase(oldName);  // ɾ����������ӳ��
    columnIndex[newName] = colIndex;  // �����������ӳ��
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