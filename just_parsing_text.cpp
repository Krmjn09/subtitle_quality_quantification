#include<iostream>
#include<fstream>
#include<regex>
#include<vector>
using namespace std;
// Structure to store subtitle data
struct Subtitle {
    int index;
    string timestamp;
    string text;
};
// Function to parse an SRT file and extract subtitles
vector<Subtitle> parseSRT(const string &filename)
{
    ifstream file(filename);
    vector<Subtitle> subtitles;
    string line;
    Subtitle sub;
    // Reading file line by line
    while(getline(file,line))
    {
        if (line.empty()) 
            continue;

        // Check if the line is a subtitle index (a number)
        if (regex_match(line, regex("^\\d+$")))
        {
            sub.index = stoi(line); // Convert string to integer
        }
        else if (regex_match(line, regex("^\\d{2}:\\d{2}:\\d{2},\\d{3} --> \\d{2}:\\d{2}:\\d{2},\\d{3}$")))
        {
            sub.timestamp = line; // Store the timestamp
        }
        else
        {
            sub.text = line;          
            subtitles.push_back(sub); 
        }
    }
    return subtitles;
}
int main()
{
    // Parse the SRT file
    auto subs = parseSRT("test.srt");

   
    for (const auto &sub : subs)
    {
        cout << "Subtitle #" << sub.index << " (" << sub.timestamp << "): " << sub.text << endl;
    }

    return 0; 
}