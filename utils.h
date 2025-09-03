#ifndef UTILS_H
#define UTILS_H

#include <QString>


class utils
{
public:
    QString generate_random_string(int length, bool is_include_num=true, QString include_symbol="" );
    QString generateDefaultCharset(bool is_include_num);
    QString generate_random_num(int length, QString include_symbol="");
    utils();
};

#endif // UTILS_H
