#include "../include/backend.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <unordered_map>

using namespace std;

void saveQuizAnswers(int id, vector<uint8_t> answers) {
	ofstream file("progress.txt", ios::app);
	if (!file.is_open()) return;

	file << id;
	for (int i = 0; i < (int)answers.size(); i++) {
		file << " " << (int)answers[i];
	}
	file << endl;
	file.close();
}

vector<uint8_t> loadQuizAnswers(int id){
	ifstream file("progress.txt");
	if (!file.is_open()) return vector<uint8_t>();

	int testId;
	while (file >> testId) {
		if (testId == id) {
			vector<uint8_t> answers;
			int ans;
			while (file.peek() != '\n' && file.peek() != EOF && file >> ans) {
				answers.push_back((uint8_t)ans);
			}
			file.close();
			return answers;
		}
		file.ignore(10000, '\n');
	}
	file.close();
	return vector<uint8_t>();
}

vector<int> getUncompletedTestList() {
    int totalTests = getTotalQuizes();
    vector<bool> isCompleted(totalTests, false);
    ifstream file("progress.txt");
    if (file.is_open()) {
        int testId;
        while (file >> testId) {
            if (testId >= 0 && testId < totalTests) {
                isCompleted[testId] = true;
            }
            file.ignore(10000, '\n');
        }
    }
	
    vector<int> uncompleted;
    for (int i = 0; i < totalTests; i++) {
        if (isCompleted[i] == false) {
            uncompleted.push_back(i);
        }
    }
    return uncompleted;
}

void removeQuizFromSave(int id) {
    ifstream inFile("progress.txt");
    if (!inFile.is_open()) return;

    vector<string> lines;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int testId;
        if (ss >> testId) {
            if (testId != id) {
                lines.push_back(line);
            }
        }
    }
    inFile.close();

    ofstream outFile("progress.txt");
    if (!outFile.is_open()) return;

    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();
}

static vector<Test> g_tests = {
    {
        "Safety Basics",
        {
            { "What should you do before starting work?", { "Check equipment", "Ignore instructions", "Run immediately", "Leave the area" } },
            { "Who should you report hazards to?", { "Supervisor", "Random visitor", "Nobody", "Friends" } },
            { "What does PPE stand for?", { "Personal Protective Equipment", "Public Protection Event", "Private Policy Equipment", "Power Protection Entry" } },
            { "What should you do during a fire alarm?", { "Evacuate calmly", "Hide", "Ignore it", "Keep working" } },
            { "Why are safety signs important?", { "They warn about dangers", "They decorate walls", "They slow work", "They replace training" } },
            { "What is the safest way to lift heavy objects?", { "Use proper posture", "Twist your back", "Lift quickly", "Use one hand" } },
            { "What should you wear in hazardous areas?", { "Protective gear", "Sandals", "Loose clothes", "No equipment" } }
        }
    },
    {
        "Protocol Quiz",
        {
            { "What is the purpose of protocol A?", { "Standardize procedures", "Increase confusion", "Replace employees", "Avoid communication" } },
            { "How often should logs be checked?", { "Daily", "Yearly", "Never", "Only weekends" } },
            { "Why are protocols important?", { "They ensure consistency", "They waste time", "They reduce teamwork", "They replace managers" } },
            { "Who approves protocol updates?", { "Management", "Customers", "Visitors", "Nobody" } },
            { "What should be documented?", { "Important actions", "Personal opinions", "Random thoughts", "Nothing" } },
            { "What happens if protocols are ignored?", { "Risks increase", "Everything improves", "Nothing changes", "Work becomes faster" } },
            { "Where are protocols usually stored?", { "Company system", "Trash bin", "Personal notebook only", "Nowhere" } }
        }
    },
    {
        "Cyber Security",
        {
            { "What is a strong password?", { "Long and unique", "123456", "password", "Same for all accounts" } },
            { "What should you do with suspicious emails?", { "Report them", "Open attachments", "Reply immediately", "Forward everywhere" } },
            { "What is phishing?", { "A scam to steal data", "A backup method", "A coding language", "A firewall" } },
            { "Why use two-factor authentication?", { "Extra security", "Faster login", "Less privacy", "To disable passwords" } },
            { "What should antivirus software do?", { "Protect systems", "Delete hardware", "Slow internet", "Replace users" } },
            { "What is malware?", { "Malicious software", "A monitor type", "Office equipment", "A protocol" } },
            { "How often should software be updated?", { "Regularly", "Never", "Every 10 years", "Only after attacks" } }
        }
    },
    {
        "Office Rules",
        {
            { "What time should employees arrive?", { "On time", "Whenever they want", "At midnight", "Only afternoons" } },
            { "Why is teamwork important?", { "Improves productivity", "Creates confusion", "Avoids communication", "Reduces quality" } },
            { "What should employees respect?", { "Company policies", "No rules", "Only personal opinions", "Random decisions" } },
            { "What is appropriate office behavior?", { "Professional conduct", "Shouting", "Ignoring colleagues", "Breaking equipment" } },
            { "How should conflicts be handled?", { "Calm discussion", "Fighting", "Ignoring forever", "Public arguments" } },
            { "Why keep the workspace clean?", { "Safety and organization", "Decoration only", "No reason", "To waste time" } },
            { "Who should access confidential data?", { "Authorized staff", "Everyone", "Visitors", "Competitors" } }
        }
    },
    {
        "Computer Basics",
        {
            { "What does CPU stand for?", { "Central Processing Unit", "Computer Power Utility", "Central Program Usage", "Control Processing User" } },
            { "What device stores files permanently?", { "SSD", "RAM", "CPU", "GPU" } },
            { "What is an operating system?", { "System software", "A browser", "An antivirus", "A monitor" } },
            { "Which is an input device?", { "Keyboard", "Monitor", "Speaker", "Projector" } },
            { "What does RAM do?", { "Temporary memory", "Permanent storage", "Internet access", "Cooling" } },
            { "What is a browser used for?", { "Access websites", "Edit videos", "Build hardware", "Print documents" } },
            { "Which is a common file extension?", { ".txt", ".chair", ".wall", ".desk" } }
        }
    },
    {
        "Networking Fundamentals",
        {
            { "What does LAN mean?", { "Local Area Network", "Long Access Node", "Light Array Network", "Logical Access Network" } },
            { "What device connects networks?", { "Router", "Printer", "Scanner", "Speaker" } },
            { "What is an IP address?", { "Network identifier", "Password", "Protocol cable", "Antivirus" } },
            { "What does Wi-Fi provide?", { "Wireless connection", "Power supply", "Data storage", "Cooling" } },
            { "What is a firewall?", { "Security system", "Office wall", "Cooling device", "Printer software" } },
            { "What does download mean?", { "Receive data", "Delete files", "Print documents", "Restart computer" } },
            { "What is bandwidth?", { "Data transfer capacity", "Monitor size", "Battery power", "CPU speed" } }
        }
    },
    {
        "First Aid",
        {
            { "What is the emergency number in Europe?", { "112", "9999", "411", "123" } },
            { "What should you do first in an emergency?", { "Stay calm", "Panic", "Run away", "Ignore it" } },
            { "What helps stop bleeding?", { "Apply pressure", "Drink water", "Run", "Sleep" } },
            { "Why is CPR important?", { "Can save lives", "Improves internet", "Repairs bones instantly", "Cools the body" } },
            { "What should you do for burns?", { "Cool with water", "Apply ice directly", "Ignore them", "Cover with dirt" } },
            { "Who should perform medical procedures?", { "Trained people", "Anyone randomly", "Children", "Visitors" } },
            { "Why use a first aid kit?", { "Provide basic treatment", "Decoration", "Store snacks", "Charge devices" } }
        }
    },
    {
        "Environmental Awareness",
        {
            { "Why recycle materials?", { "Reduce waste", "Increase pollution", "Waste energy", "Destroy resources" } },
            { "What saves electricity?", { "Turning off unused devices", "Leaving lights on", "Overheating systems", "Using broken equipment" } },
            { "What is renewable energy?", { "Energy from natural sources", "Energy from trash only", "Expired batteries", "Nuclear waste" } },
            { "Why reduce plastic use?", { "Protect environment", "Increase costs", "Waste materials", "Create pollution" } },
            { "What pollutes air?", { "Vehicle emissions", "Trees", "Clean water", "Solar panels" } },
            { "What should be done with batteries?", { "Dispose properly", "Throw anywhere", "Burn them", "Store in food areas" } },
            { "Why conserve water?", { "Protect resources", "Increase waste", "Flood buildings", "Damage systems" } }
        }
    },
    {
        "Customer Service",
        {
            { "How should customers be treated?", { "Respectfully", "Rudely", "Ignored", "Aggressively" } },
            { "What is good communication?", { "Clear and polite", "Confusing and loud", "Silent treatment", "Random answers" } },
            { "Why listen to customers?", { "Understand needs", "Waste time", "Avoid solutions", "Increase problems" } },
            { "How should complaints be handled?", { "Professionally", "Ignored", "Mocked", "Deleted immediately" } },
            { "What builds customer trust?", { "Honesty", "False promises", "Rudeness", "Delays" } },
            { "Why is patience important?", { "Improves interactions", "Creates conflict", "Reduces quality", "Slows systems" } },
            { "What should employees provide?", { "Helpful support", "Arguments", "Misinformation", "No response" } }
        }
    },
    {
        "General Knowledge",
        {
            { "What planet is known as the Red Planet?", { "Mars", "Venus", "Earth", "Jupiter" } },
            { "How many continents are there?", { "7", "5", "9", "12" } },
            { "What is H2O commonly called?", { "Water", "Oxygen", "Hydrogen", "Salt" } },
            { "Who invented the telephone?", { "Alexander Graham Bell", "Newton", "Einstein", "Tesla" } },
            { "What is the capital of France?", { "Paris", "Berlin", "Madrid", "Rome" } },
            { "What gas do plants absorb?", { "Carbon dioxide", "Oxygen", "Helium", "Nitrogen" } },
            { "Which ocean is the largest?", { "Pacific Ocean", "Atlantic Ocean", "Indian Ocean", "Arctic Ocean" } }
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

int getTotalQuizes()
{
    return static_cast<int>(g_tests.size());
}

int getTotalQuestions(int quizId)
{
	return (int)g_tests[quizId].questions.size();
}
