#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef GEOHASH_H_H
#define GEOHASH_H_H

static const char base32_alphabet[32] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'b', 'c', 'd', 'e', 'f', 'g',
        'h', 'j', 'k', 'm', 'n', 'p', 'q', 'r',
        's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
};

char *base32_encode(char *str);
char *lon_lat_to_binary(double lon, double lat, int precision);
double * char_to_binary(char *str, size_t put_str_length);
double * binary_to_lon_Lat(int *bin, size_t bin_length);

#endif
