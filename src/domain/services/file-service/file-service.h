#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

namespace Game
{
  struct FileDataValue
  {
    std::string key;
    std::string value;
  };

  struct FileData
  {
    std::vector<FileDataValue> values;
  };

  class FileService
  {
  public:
    void saveToBinaryFile(const std::string &fileName, const std::vector<FileData> &fileDataList)
    {
      std::ofstream file(fileName, std::ios::binary | std::ios::trunc);

      if (!file.is_open())
      {
        throw std::runtime_error("Unable to open file: " + fileName);
      }

      size_t fileDataCount = fileDataList.size();
      file.write(reinterpret_cast<const char *>(&fileDataCount), sizeof(size_t));

      for (const auto &fileData : fileDataList)
      {
        this->saveFileData(file, fileData);
      }

      file.close();
    }

    std::vector<FileData> loadFromBinaryFile(const std::string &fileName)
    {
      std::ifstream file(fileName, std::ios::binary);
      std::vector<FileData> fileDataList;

      if (!file.is_open())
      {
        return fileDataList;
      }

      size_t fileDataCount;

      file.read(reinterpret_cast<char *>(&fileDataCount), sizeof(size_t));

      for (size_t i = 0; i < fileDataCount; ++i)
      {
        fileDataList.push_back(this->loadFileData(file));
      }

      file.close();

      return fileDataList;
    }

  private:
    void saveFileData(std::ofstream &file, const FileData &fileData)
    {

      size_t valuesCount = fileData.values.size();
      file.write(reinterpret_cast<const char *>(&valuesCount), sizeof(size_t));

      for (const auto &value : fileData.values)
      {
        this->saveFileDataValue(file, value);
      }
    }

    FileData loadFileData(std::ifstream &file)
    {
      FileData fileData;
      size_t valuesCount;

      file.read(reinterpret_cast<char *>(&valuesCount), sizeof(size_t));

      for (size_t i = 0; i < valuesCount; ++i)
      {
        fileData.values.push_back(this->loadFileDataValue(file));
      }

      return fileData;
    }

    void saveFileDataValue(std::ofstream &file, const FileDataValue &value)
    {

      size_t keySize = value.key.size();
      file.write(reinterpret_cast<const char *>(&keySize), sizeof(size_t));
      file.write(value.key.c_str(), keySize);

      size_t valueSize = value.value.size();
      file.write(reinterpret_cast<const char *>(&valueSize), sizeof(size_t));
      file.write(value.value.c_str(), valueSize);
    }

    FileDataValue loadFileDataValue(std::ifstream &file)
    {
      FileDataValue value;
      size_t keySize, valueSize;

      file.read(reinterpret_cast<char *>(&keySize), sizeof(size_t));
      value.key.resize(keySize);
      file.read(&value.key[0], keySize);

      file.read(reinterpret_cast<char *>(&valueSize), sizeof(size_t));
      value.value.resize(valueSize);
      file.read(&value.value[0], valueSize);

      return value;
    }
  };
}