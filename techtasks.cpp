#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <algorithm>
_locale_t locale = _create_locale(LC_CTYPE, "Russian"); // локаль нужна для _tolower_l, поскольку tolower работает только с латиницей
char* Reverse(char* input) // функция для инвертирования строки
{
    char tmp;
    for (size_t i = 0; i < strlen((const char*)input) / 2; i++)
    {
        tmp = input[i];
        input[i] = input[strlen((const char*)input) - 1 - i];
        input[strlen((const char*)input) - 1 - i] = tmp;
    }
    return input;
}
char* RemoveExcess(char* input, char* blacklist)
{
    std::vector<char> vec;
    char* tmp;
    size_t j = 0;
    for (size_t i = 0; i < strlen((const char*)input); i++)
    {
        tmp = strchr(blacklist, input[i]); // проверяем символ из введенной строки в строке с удаляемыми символами
        if (tmp == NULL) // если символ не найден возвращается нулевой указатель, записываем данный символ
        {
            vec.push_back(input[i]);
        }
    }
    size_t size = vec.size();
    char* result = new char[size + 1];
    for (std::vector<char>::iterator ch = vec.begin(); ch != vec.end(); ch++) // записываем элементы вектора в массив
        result[ch - vec.begin()] = *ch;
    result[size] = '\0';
    return result;
}
bool isPalindrom(char* input) // функция проверки на палиндром
{
    static char banned[11] = { ' ','.',',',':','-',')','(','"',';','?','!'};
    input = RemoveExcess(input, banned);
    for (size_t i = 0; i < strlen((const char*)input) / 2; i++)
    {
        if (_tolower_l(input[i], locale) != _tolower_l(input[strlen((const char*)input) - 1 - i], locale))
            return false;
    }
    return true;
}
char* alltolower(char* input) // вспомогательная функция
{
    for (size_t i = 0; i < strlen((const char*)input); i++)
    {
        input[i] = _tolower_l(input[i], locale);
    }
    return input;
}
void ch_counter(char* input) // функция каждого вхождения символа в строке input
{
    std::vector<char> uniq_ch;
    std::vector<int> ch_counter;
    char* tmp = NULL;
    alltolower(input);
    uniq_ch.push_back(input[0]);
    ch_counter.push_back(1);
    for (size_t i = 1; i < strlen((const char*)input); i++)
    {
        tmp = strchr((&uniq_ch[0]), input[i]); // ищем повторяшки
        if (tmp == NULL) // если нету записываем в векторы информацию о символе
        {
            uniq_ch.push_back(input[i]);
            ch_counter.push_back(1);
        }
        else
        {
            ptrdiff_t index = std::find(uniq_ch.begin(), uniq_ch.end(), input[i]) - uniq_ch.begin(); // поиск индекса повторяющегося символа
            if (index < uniq_ch.size())
            {
                ch_counter[index]++;
            }
        }
    }
    for (size_t i = 0; i < uniq_ch.size(); i++)
    {
        std::cout << uniq_ch[i] << " : " << ch_counter[i] << "\n";
    }
}
int main()
{
    setlocale(LC_CTYPE, "Russian");
    system("chcp 1251");
    std::cout << "Задача 1.\nВведите строку, которую нужно реверсировать: ";
    char task1[256];
    std::cin.getline(task1, 256, '\n');
    char* reverse_input = Reverse(task1);
    std::cout << reverse_input << std::endl;
    std::cout << "Задача 2.\nВведите строку, которую мы проверим на признаки палиндрома: ";
    char task2[256];
    std::cin.getline(task2, 256, '\n');
    const char* result = (isPalindrom(task2)) ? "Эта строка - палиндром" : "Эта строка - не палиндром";
    std::cout << result;
    char task3[256];
    std::cout << "\nЗадача 3.\nВведите строку, в которой будут подсчитаны уникальные символы: ";
    std::cin.getline(task3, 256, '\n');
    ch_counter(task3);
}
