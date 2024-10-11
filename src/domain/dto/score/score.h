#pragma once
#include <string>
#include <string_view>
#include "../../global/global-services/global-services.h"

namespace Game
{
  class Score
  {
  private:
    const std::string createdAt;
    const std::string playerName;
    const std::string elapsedTime;

  public:
    Score(
        std::string_view _createdAt,
        std::string_view _playerName,
        std::string_view _elapsedTime) : createdAt(_createdAt),
                                         playerName(_playerName),
                                         elapsedTime(_elapsedTime) {}

    std::string getCreatedAt() const
    {
      return this->createdAt;
    }

    std::string getPlayerName() const
    {
      return this->playerName;
    }

    std::string getElapsedTime() const
    {
      return this->elapsedTime;
    }

    FileData toFileData() const
    {
      FileData fileData;
      fileData.values.push_back({"createdAt", this->createdAt});
      fileData.values.push_back({"playerName", this->playerName});
      fileData.values.push_back({"elapsedTime", this->elapsedTime});
      return fileData;
    }

    static Score fromFileData(const FileData &fileData)
    {
      std::string createdAt;
      std::string playerName;
      std::string elapsedTime;

      for (const auto &item : fileData.values)
      {
        if (item.key == "createdAt")
        {
          createdAt = item.value;
        }
        else if (item.key == "playerName")
        {
          playerName = item.value;
        }
        else if (item.key == "elapsedTime")
        {
          elapsedTime = item.value;
        }
      }

      if (createdAt.empty() || playerName.empty() || elapsedTime.empty())
      {
        throw std::runtime_error("Missing required fields in FileData");
      }

      return Score(createdAt, playerName, elapsedTime);
    }
  };
}