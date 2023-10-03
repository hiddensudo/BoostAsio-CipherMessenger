#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cwctype>

class OneTimePad {
private:
    std::vector<std::pair<wchar_t, std::wstring>> letters = {
        {L'а', L"1"},  {L'и', L"2"},  {L'т', L"3"},  {L'е', L"4"},
        {L'с', L"5"},  {L'н', L"6"},  {L'о', L"7"},  {L'б', L"81"},
        {L'в', L"82"}, {L'г', L"83"}, {L'д', L"84"}, {L'ж', L"85"},
        {L'з', L"86"}, {L'к', L"87"}, {L'л', L"88"}, {L'м', L"89"},
        {L'п', L"80"}, {L'р', L"91"}, {L'у', L"92"}, {L'ф', L"93"},
        {L'х', L"94"}, {L'ц', L"95"}, {L'ч', L"96"}, {L'ш', L"97"},
        {L'щ', L"98"}, {L'ъ', L"99"}, {L'ы', L"90"}, {L'ь', L"01"},
        {L'э', L"02"}, {L'ю', L"03"}, {L'я', L"04"}, {L' ', L"00"}};

    std::wstring cipherText;
    std::wstring cipherKey;
    
    std::wstring text;    
    std::wstring key;

    wchar_t getLetterByNumber(const std::wstring& number);
    std::wstring getNumberByLetter(const wchar_t& letter);
    void toLowerCase(std::wstring& text);
    std::wstring toTable(std::wstring text);
    std::wstring keySizeToTextSize(std::wstring text, std::wstring& key);
    
public:
    std::wstring cipher();
    std::wstring decipher();
    OneTimePad(std::wstring text, std::wstring key);
};