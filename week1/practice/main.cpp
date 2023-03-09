#include <iostream>

/*  Решение на задачата от упражнението от седмица 1
**
**  задача 5 от списъка със задачи за упражнение
**
*/

/// @brief Функция, която замества ? в @query с думи от списъка words
/// @param query [in] string with ? placeholders
/// @param words [in] array of words
/// @return new dynamically allocated string
char* replacePlaceholders(const char *query, const char** words)
{
    int numPlaceholders = 0;
    int queryLen = 0;
    // Тук намираме дължината на входящото "изречение"(заявка), заедно с броя на въпросителните в него
    while (query[queryLen] != '\0') {
        if (query[queryLen] == '?') {
            ++numPlaceholders;
        }
        ++queryLen;
    }

    int totalWordLength = 0; /// Тук акумулураме сумата от дължината на думите
    for (int i = 0; i < numPlaceholders; ++i) {
        totalWordLength += strlen(words[i]);
    }

    int finalSize = queryLen - numPlaceholders + totalWordLength;
    char* replacedQuery = new char[finalSize + 1];
    /// Инициализираме заделената памет с 0
    memset(replacedQuery, 0, finalSize + 1);

    int wordIt = 0;
    int queryIt = 0;
    for (int i = 0; i < queryLen; ++i) {
        if (query[i] == '?') {
            int wordLen = strlen(words[wordIt]);
            /// strcat намира терминиращата нула и "залепя" 
            /// новия стринг от нея, така спестяваме едно обхождане
            /// можем да оптмизираме използвайки memcpy
            /// memcpy(replacedQuery + queryIt, words[wordIt], wordLen);
            strcat(replacedQuery, words[wordIt]);
            queryIt += wordLen;
            ++wordIt;
        } else {
            replacedQuery[queryIt] = query[i];
            ++queryIt;
        }
    }

    return replacedQuery;
}

int main(int argc, char** argv)
{
    const char *words[] =  {"Name", "Person", "ID", "10"};
    const char* finalQuery = replacePlaceholders("SELECT ? FROM ? WHERE ?=?;", words);

    std::cout << finalQuery << std::endl;
    delete[] finalQuery;
    return 0;
}