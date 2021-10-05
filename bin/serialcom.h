#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <string>
#include <vector>

std::string get_data(int fd);

std::vector<float> parse_data(std::string& pose);

int connect();

#endif
