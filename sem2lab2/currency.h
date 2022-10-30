#include <curl/curl.h>
#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;

// struct to store valute
class Valute {
private:
    std::string char_code;
    std::string id;
    int nominal;
    std::string name;
    float previous;
    float value;
public:
    explicit Valute(const json &valute)
            : char_code(valute["CharCode"]),
              id(valute["ID"]),
              nominal(valute["Nominal"]),
              name(valute["Name"]),
              previous(valute["Previous"]),
              value(valute["Value"]) {}

    std::string toString() {
        std::string out;
        out += "_______________________________________\n";
        out += char_code + '/' + "RUB " + '\n';
        out += std::to_string(nominal) + " " + name
               + " к Российскому рублю:" + '\n';
        out += "Current:\t" + std::to_string(value) + '\n';
        out += "Previous:\t" + std::to_string(previous);
        return out;
    }
};

void printCurrency(const std::string& response) {
    json response_json = json::parse(response);
    std::string date = response_json["Date"];
    std::string previous_date = response_json["PreviousDate"];
    json valutes = response_json["Valute"];

    std::cout << "Date:\t\t" << date << '\n';
    std::cout << "Previous date:\t" << previous_date << '\n';

    for (const json &valute: valutes) {
        Valute cur(valute);
        std::cout << cur.toString() << '\n';
    }
}