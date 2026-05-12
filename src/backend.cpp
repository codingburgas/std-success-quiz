#include "include/backend.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

static vector<Test> g_tests = {
    {
        "Safety Basics",
        {
            { "What is the first step in safety?", { "Stop", "Think", "Run", "Hide" } },
            { "Who to call in emergency?", { "Friend", "Supervisor", "Nobody", "Mail" } }
        }
    },
    {
        "Protocol Quiz",
        {
            { "What is protocol A?", { "Option1", "Option2", "Option3", "Option4" } },
            { "How often to check logs?", { "Daily", "Weekly", "Monthly", "Never" } }
        }
    }
};

string getTestName(int id)
{
    if (id < 0 || id >= static_cast<int>(g_tests.size())) return string();
    return g_tests[id].name;
}

TestQuestion getTestQuestion(int id, int index)
{
    TestQuestion empty;
    if (id < 0 || id >= static_cast<int>(g_tests.size())) return empty;
    const auto& qs = g_tests[id].questions;
    if (index < 0 || index >= static_cast<int>(qs.size())) return empty;
    return qs[index];
}

int getTotalQuestions()
{
    return static_cast<int>(g_tests.size());
}

static const string progressFile = "quiz_progress.txt";

static unordered_map<int, string> readProgress()
{
    unordered_map<int, string> m;
    ifstream in(progressFile);
    if (!in.is_open()) return m;
    string line;
    while (getline(in, line))
    {
        if (line.empty()) continue;
        auto pos = line.find(':');
        if (pos == string::npos) continue;
        int id = stoi(line.substr(0, pos));
        m[id] = line.substr(pos + 1);
    }
    return m;
}

static void writeProgress(const unordered_map<int, string>& m)
{
    ofstream out(progressFile, ios::trunc);
    for (auto& p : m) out << p.first << ":" << p.second << "\n";
}

void saveQuizAnswers(int id, const vector<uint8_t>& answers)
{
    auto m = readProgress();
    stringstream ss;
    for (size_t i = 0; i < answers.size(); ++i)
    {
        if (i) ss << ",";
        ss << static_cast<int>(answers[i]);
    }
    m[id] = ss.str();
    writeProgress(m);
}

bool loadQuizAnswers(int id, vector<uint8_t>& answers)
{
    answers.clear();
    auto m = readProgress();
    auto it = m.find(id);
    if (it == m.end()) return false;
    string s = it->second;
    string token;
    stringstream ss(s);
    while (getline(ss, token, ',')) {
        try { answers.push_back(static_cast<uint8_t>(stoi(token))); }
        catch (...) { answers.push_back(0); }
    }
    return true;
}