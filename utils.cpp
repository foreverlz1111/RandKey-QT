#include "utils.h"

#include <QRandomGenerator>
#include <QDebug>

QString utils::generate_random_string(int length, bool is_include_num, QString include_symbol)
{
    QString result;
    include_symbol.append(generateDefaultCharset(is_include_num));

    int chars_count=include_symbol.length();

    if (chars_count==0){
        return result;
    }
    for (int i=0;i<length;++i){
        int index = QRandomGenerator::global()->bounded(chars_count);// range [0~chars_count]
        result.append(include_symbol[index]);
    }
    return result;
}
QString utils::generate_random_num(int length,QString include_symbol){
    QString result;
    int chars_count=include_symbol.length();
    for (int i=0;i<length;++i){
        int index = QRandomGenerator::global()->bounded(chars_count);// range [0~chars_count]
        result.append(include_symbol[index]);
    }
    return result;
}
QString utils::generateDefaultCharset(bool is_include_num)
{
    QString chars;
    for (char c = 'A'; c <= 'Z'; ++c) chars.append(c);
    for (char c = 'a'; c <= 'z'; ++c) chars.append(c);
    if (is_include_num)for (char c = '0'; c <= '9'; ++c) chars.append(c);
    return chars;
}
utils::utils() {}
