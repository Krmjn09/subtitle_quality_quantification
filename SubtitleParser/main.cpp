#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

struct Subtitle
{
    int index;
    std::string timestamp;
    std::string text;
};

std::vector<Subtitle> parseSRT(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<Subtitle> subtitles;
    std::string line;
    Subtitle sub;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        if (std::regex_match(line, std::regex("^\\d+$")))
        {
            sub.index = std::stoi(line);
        }
        else if (std::regex_match(line, std::regex("^\\d{2}:\\d{2}:\\d{2},\\d{3} --> \\d{2}:\\d{2}:\\d{2},\\d{3}$")))
        {
            sub.timestamp = line;
        }
        else
        {
            sub.text = line;
            subtitles.push_back(sub);
        }
    }
    return subtitles;
}

bool validateLineLength(const Subtitle &sub, int maxChars)
{
    return sub.text.length() <= maxChars;
}

int main()
{
    auto subs = parseSRT("../SubtitleParser/test1.srt");
    for (const auto &sub : subs)
    {
        if (!validateLineLength(sub, 42))
        {
            std::cout << "Line too long in subtitle #" << sub.index << std::endl;
        }
    }
    return 0;
}