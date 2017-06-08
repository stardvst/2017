#include <iostream>
#include <regex>

using namespace std;

string timeConversion(string s) {
    regex regex { R"((\d{2}):(\d{2}):(\d{2})(\w{2}))" };
    smatch info;
    regex_match(s, info, regex);

    string result;

    int hour = std::stoi(info[1]);
    int min = std::stoi(info[2]);
    int sec = std::stoi(info[3]);
    string ampm = info[4];

    if(hour >= 1 && hour <= 12 &&
       min >= 0 && min <= 59 &&
       sec >= 0 && sec <= 59) {
        if(ampm == "AM") {
            if(hour == 12) {
                result += "00:";
            } else {
                result += info[1];
                result += ":";
            }
        } else {
            switch(hour) {
                case 1:
                    result += "13:";
                    break;
                case 2:
                    result += "14:";
                    break;
                case 3:
                    result += "15:";
                    break;
                case 4:
                    result += "16:";
                    break;
                case 5:
                    result += "17:";
                    break;
                case 6:
                    result += "18:";
                    break;
                case 7:
                    result += "19:";
                    break;
                case 8:
                    result += "20:";
                    break;
                case 9:
                    result += "21:";
                    break;
                case 10:
                    result += "22:";
                    break;
                case 11:
                    result += "23:";
                    break;
                case 12:
                    result += "12:";
                    break;
            }
        }
        result += info[2];
        result.append(":");
        result += info[3];
    }

    return result;
}

int main() {
    string s;
    cin >> s;
    string result = timeConversion(s);
    cout << result << endl;

    std::cin.get();
    return 0;
}
