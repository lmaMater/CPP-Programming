#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <curl/curl.h>
#include "single_include/nlohmann/json.hpp"
#include "currency.h"

using json = nlohmann::json;

void printInsult(const std::string& response){
    json response_json = json::parse(response);
    std::string insult = response_json["insult"];
    std::cout << insult << '\n';
}

static int responseToString(void *contents, int size, int nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

int main() {

    system("chcp 65001");

    CURL *curl;
    curl = curl_easy_init();

    std::string response;
    CURLcode result;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.cbr-xml-daily.ru/daily_json.js");
        //curl_easy_setopt(curl, CURLOPT_URL, "http://evilinsult.com/generate_insult.php?lang=en&type=json");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseToString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        int counter = 0;
        while (1) {
            result = curl_easy_perform(curl);
            printCurrency(response);
            //printInsult(response);
            response.clear();

            counter++;
            Sleep(5000);
        }
        curl_easy_cleanup(curl);
    }

    //std::cout << response;
    /*
    json response_json = json::parse(response);
    json currency = response_json["quotes"];
    float usd_rub = currency["USDRUB"];

    std::cout << rubConvert(usd_rub, currency["USDRUB"]) << '\n';
    std::cout << rubConvert(usd_rub, currency["USDEUR"]) << '\n';
    std::cout << rubConvert(usd_rub, currency["USDJPY"]) << '\n';
    std::cout << rubConvert(usd_rub, currency["USDGBP"]) << '\n';
    */

    return 0;
}
