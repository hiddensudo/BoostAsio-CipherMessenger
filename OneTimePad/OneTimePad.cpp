#include "OneTimePad.h"

wchar_t OneTimePad::getLetterByNumber(const std::wstring& number) {
    for(const auto& pair : letters) {
            if(pair.second == number) {
                return pair.first;
            }
        }
    return L'\0';
}

std::wstring OneTimePad::getNumberByLetter(const wchar_t& letter) {
    for(const auto& pair : letters) {
            if(pair.first == letter) {
                return pair.second;
            }
        }
    return L"";
}

void OneTimePad::toLowerCase(std::wstring& text) {
    transform(text.begin(), text.end(), text.begin(), towlower);
}

std::wstring OneTimePad::toTable(std::wstring text) {
    std::wstring result;
    for(int i = 0; i < text.size(); ++i) {
        for(int j = 0; j < letters.size(); ++j) {
            if(text[i] == letters[j].first) {
                result += letters[j].second;
            }
        }
    }
    return result;
}

std::wstring OneTimePad::keySizeToTextSize(std::wstring text, std::wstring& key) {
    std::wstring result;
    for(int i = 0; i < text.size(); ++i) {
        result += key[i%key.size()];
    }
    return result;
}

std::wstring OneTimePad::cipher() {
    this->cipherText = toTable(this->text);
    this->cipherKey = toTable(this->key);
    this->cipherKey = keySizeToTextSize(this->cipherText, this->cipherKey);

    for(int i = 0; i < this->cipherText.size(); ++i) {
        int num = (std::stoi(std::wstring(1, this->cipherText[i])) + std::stoi(std::wstring(1, this->cipherKey[i]))) % 10;
        this->cipherText[i] = static_cast<wchar_t>(L'0' + num);
    }

    return cipherText;
}

std::wstring OneTimePad::decipher() {
    this->cipherText = this->text;
    this->cipherKey = toTable(this->key);
    this->cipherKey = keySizeToTextSize(this->cipherText, this->cipherKey);

    for(int i = 0; i < this->cipherText.size(); ++i) {
        int ki = (std::stoi(std::wstring(1, this->cipherText[i])));
        int ci = std::stoi(std::wstring(1, this->cipherKey[i]));
        int num = ((ki-ci) % 10 + 10) % 10;
        this->cipherText[i] = static_cast<wchar_t>(L'0' + num);
    }

    std::wstring result;
    std::string buffer;
    for (wchar_t c : cipherText) {
        buffer += c;
        if (buffer.size() == 2 || (buffer.size() == 1 &&  std::stoi(buffer) >= 1 && std::stoi(buffer) <= 7)) {
            result += getLetterByNumber(std::wstring(buffer.begin(), buffer.end()));
            buffer.clear();
        }
    }

    // Додаткова перевірка для обробки пробілів
    if (!buffer.empty()) {
        result += getLetterByNumber(std::wstring(buffer.begin(), buffer.end()));
    }

    return result;

}


OneTimePad::OneTimePad(std::wstring text, std::wstring key) {
    this->text = text;
    this->key = key;
}